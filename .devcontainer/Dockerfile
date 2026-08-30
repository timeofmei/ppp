FROM debian:forky-slim

# Written by .devcontainer/pull-image.sh before the build:
# empty file = use official apt sources; non-empty = switch to a domestic Debian mirror
COPY apt-mirror.txt /tmp/apt-mirror.txt

RUN MIRROR=$(cat /tmp/apt-mirror.txt) \
    && if [ -n "$MIRROR" ]; then \
         sed -i "s|deb.debian.org|$MIRROR|g; s|security.debian.org|$MIRROR|g" /etc/apt/sources.list.d/debian.sources 2>/dev/null || true; \
         sed -i "s|deb.debian.org|$MIRROR|g; s|security.debian.org|$MIRROR|g" /etc/apt/sources.list 2>/dev/null || true; \
       fi \
    && apt-get update \
    && apt-get install -y --no-install-recommends build-essential ca-certificates clang clangd curl git \
    && rm -rf /var/lib/apt/lists/* \
    && useradd --create-home --uid 1000 --shell /bin/bash vscode \
    && printf "PS1='\\$ '\n" >> /home/vscode/.bashrc
