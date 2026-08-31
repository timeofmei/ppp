#!/usr/bin/env bash
# ============================================================================
# pull-image.sh
# Ensures that the local docker daemon has $TAG so that the
# Dockerfile's FROM $TAG can be built without hitting Docker Hub
# directly (avoiding blocked/slow access from China).
#
# Acquisition order (fallback cascade):
#   0) Already present locally  -> exit immediately (idempotent; no network on reopen)
#   1) Connectivity test: curl https://www.google.com
#      reachable -> DOMESTIC=0, use official source; unreachable -> DOMESTIC=1, use mirrors
#   2) docker pull official     -> only when DOMESTIC=0
#   3) docker pull mirror       -> try each mirror + docker tag to rename
#   4) Manual fallback (no docker pull):
#      use curl against the registry HTTP API to fetch index/manifest/config/rootfs layer,
#      assemble a docker load-able archive and import it (only requires curl, no skopeo/crane)
#   Also: every run writes .devcontainer/apt-mirror.txt (empty=official apt source,
#        non-empty=domestic Debian apt source) for the Dockerfile to decide whether to switch.
# ============================================================================

# The image to fetch (edit these to use a different one; the rest of the
# script and the Dockerfile's FROM reference $TAG)
IMAGE="debian"
IMAGE_TAG="sid-slim"
TAG="$IMAGE:$IMAGE_TAG"
MIRRORS="dockerproxy.net docker.1ms.run docker.m.daocloud.io"
# Domestic Debian apt mirror (change here to use a different one)
DEBIAN_APT_MIRROR="mirrors.tuna.tsinghua.edu.cn"
# Directory of this script (.devcontainer/), resolved regardless of cwd
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"

log() { echo "[pull-debian] $*"; }

# ---------- 0) Fast path: image already present locally -> nothing to do ----------
# Runs before any network probe so a normal reconnect is near-instant.
if docker image inspect "$TAG" >/dev/null 2>&1; then
  log "$TAG already present, skipping"
  exit 0
fi

# Ensure the marker file always exists (default: official apt source) so the
# Dockerfile's COPY never fails, even if we exit early below
: > "$SCRIPT_DIR/apt-mirror.txt"

# ---------- 1) Connectivity test: google reachable -> official, otherwise domestic ----------
DOMESTIC=0
if curl -fsS -m 8 -o /dev/null https://www.google.com; then
  log "External network reachable: use official source"
else
  DOMESTIC=1
  log "External network unreachable: use domestic sources (DOMESTIC=1)"
fi

# Overwrite the marker with the domestic Debian mirror if applicable
if [ "$DOMESTIC" = "1" ]; then
  printf '%s\n' "$DEBIAN_APT_MIRROR" > "$SCRIPT_DIR/apt-mirror.txt"
  log "Marked domestic apt source: $DEBIAN_APT_MIRROR"
else
  : > "$SCRIPT_DIR/apt-mirror.txt"
  log "Marked official apt source (no switch)"
fi

# Portable timeout wrapper (macOS has no GNU timeout)
run_pull() {
  if command -v timeout >/dev/null 2>&1; then
    timeout 180 "$@"
  else
    "$@"
  fi
}

# ---------- 2) Official source (only when external network is reachable) ----------
if [ "$DOMESTIC" = "0" ]; then
  log "Trying docker pull $TAG (official source)..."
  if run_pull docker pull "$TAG"; then
    log "OK: docker pull $TAG"
    exit 0
  fi
  log "Official pull failed, falling back to domestic mirrors"
else
  log "Skipping official source, starting from domestic mirrors"
fi

# ---------- 3) Domestic mirror docker pull + tag ----------
for m in $MIRRORS; do
  log "Trying docker pull $m/library/$IMAGE:$IMAGE_TAG ..."
  if run_pull docker pull "$m/library/$IMAGE:$IMAGE_TAG"; then
    if docker tag "$m/library/$IMAGE:$IMAGE_TAG" "$TAG"; then
      log "OK: pulled from $m and retagged as $TAG"
      exit 0
    fi
  fi
done

# ---------- 4) Manual fallback: curl download + docker load ----------
log "All docker pulls failed, falling back to manual download + docker load ..."
command -v curl >/dev/null 2>&1 || { log "ERROR: curl not found, cannot download manually"; exit 1; }

TMP=$(mktemp -d) || exit 1
trap 'rm -rf "$TMP"' EXIT

ACCEPT_INDEX='Accept: application/vnd.docker.distribution.manifest.list.v2+json, application/vnd.oci.image.index.v1+json'
ACCEPT_MANIFEST='Accept: application/vnd.oci.image.manifest.v1+json, application/vnd.docker.distribution.manifest.v2+json'

for m in $MIRRORS; do
  log "Manual download attempt: $m"
  rm -f "$TMP"/*

  # 4.1) Fetch index (manifest list) and resolve the amd64 manifest digest
  if ! curl -fsSL --max-time 60 -H "$ACCEPT_INDEX" \
       "https://$m/v2/library/$IMAGE/manifests/$IMAGE_TAG" -o "$TMP/index.json"; then
    log "  $m: failed to fetch index, trying next source"
    continue
  fi
  AMD64=$(grep -oE '"digest":"sha256:[a-f0-9]{64}","mediaType":"[^"]*","platform":\{"architecture":"amd64","os":"linux"' "$TMP/index.json" | head -1 | grep -oE 'sha256:[a-f0-9]{64}')
  if [ -z "$AMD64" ]; then
    # Fallback: take the first non-attestation (os=linux) digest
    AMD64=$(grep -oE '"digest":"sha256:[a-f0-9]{64}","mediaType":"[^"]*","platform":\{"architecture":"[^"]*","os":"linux"' "$TMP/index.json" | head -1 | grep -oE 'sha256:[a-f0-9]{64}')
  fi
  if [ -z "$AMD64" ]; then
    log "  $m: could not parse a platform manifest digest, trying next source"
    continue
  fi
  log "  platform manifest digest: $AMD64"

  # 4.2) Fetch that platform's manifest and resolve config and layer digests
  if ! curl -fsSL --max-time 60 -H "$ACCEPT_MANIFEST" \
       "https://$m/v2/library/debian/manifests/$AMD64" -o "$TMP/manifest.json"; then
    log "  $m: failed to fetch platform manifest, trying next source"
    continue
  fi
  CONFIG=$(grep -oE '"config":\{"mediaType":"[^"]*","digest":"sha256:[a-f0-9]{64}"' "$TMP/manifest.json" | grep -oE 'sha256:[a-f0-9]{64}' | head -1)
  LAYER=$(grep -oE '"layers":\[\{"mediaType":"[^"]*","digest":"sha256:[a-f0-9]{64}"' "$TMP/manifest.json" | grep -oE 'sha256:[a-f0-9]{64}' | head -1)
  if [ -z "$CONFIG" ] || [ -z "$LAYER" ]; then
    log "  $m: failed to parse config/layer digest, trying next source"
    continue
  fi

  # 4.3) Download the config and layer blobs
  if ! curl -fsSL --max-time 60 "https://$m/v2/library/debian/blobs/$CONFIG" -o "$TMP/config.json" \
     || ! curl -fsSL --max-time 300 "https://$m/v2/library/debian/blobs/$LAYER" -o "$TMP/layer.bin"; then
    log "  $m: blob download failed, trying next source"
    continue
  fi

  # 4.4) Handle the layer compression (decompress gzip to .tar, most compatible with docker load)
  if [ "$(head -c 2 "$TMP/layer.bin" | od -An -tx1 | tr -d ' \n')" = "1f8b" ]; then
    mv "$TMP/layer.bin" "$TMP/layer.tar.gz" && gzip -df "$TMP/layer.tar.gz"
  else
    mv "$TMP/layer.bin" "$TMP/layer.tar"
  fi
  if [ ! -f "$TMP/layer.tar" ]; then
    log "  $m: layer decompression failed, trying next source"
    continue
  fi

  # 4.5) Assemble the docker load archive (manifest.json + config.json + layer.tar)
  printf '[{"Config":"config.json","RepoTags":["%s"],"Layers":["layer.tar"]}]\n' "$TAG" > "$TMP/manifest.json"
  tar -C "$TMP" -cf "$TMP/image.tar" manifest.json config.json layer.tar

  # 4.6) Import via docker load and verify
  if docker load -i "$TMP/image.tar"; then
    if docker image inspect "$TAG" >/dev/null 2>&1; then
      log "OK: manually downloaded and imported $TAG from $m"
      exit 0
    fi
  fi
  log "  $m: docker load did not succeed, trying next source"
done

log "ERROR: all sources and manual download failed, could not obtain $TAG"
exit 1
