FROM debian:sid-slim

# Written by .devcontainer/pull-image.sh before the build:
# empty file = use official apt sources; non-empty = switch to a domestic Debian mirror
COPY apt-mirror.txt /tmp/apt-mirror.txt

RUN MIRROR=$(cat /tmp/apt-mirror.txt) \
    && if [ -n "$MIRROR" ]; then \
         sed -i "s|deb.debian.org|$MIRROR|g; s|security.debian.org|$MIRROR|g" /etc/apt/sources.list.d/debian.sources 2>/dev/null || true; \
         sed -i "s|deb.debian.org|$MIRROR|g; s|security.debian.org|$MIRROR|g" /etc/apt/sources.list 2>/dev/null || true; \
       fi \
    && apt-get update \
    && apt-get install -y --no-install-recommends ca-certificates clang-23 clangd-23 \
       libc++-23-dev libc++abi-23-dev libclang-rt-23-dev curl git \
       python3 python3-pip python3-venv nodejs \
    && ln -s /usr/bin/clang-23 /usr/local/bin/clang \
    && ln -s /usr/bin/clang++-23 /usr/local/bin/clang++ \
    && ln -s /usr/bin/clangd-23 /usr/local/bin/clangd \
    && rm -rf /var/lib/apt/lists/* \
    && useradd --create-home --uid 1000 --shell /bin/bash vscode \
    && printf "PS1='\\$ '\n" >> /home/vscode/.bashrc
