FROM debian:forky-slim

RUN apt-get update \
    && apt-get install -y --no-install-recommends build-essential ca-certificates clang clangd curl git \
    && rm -rf /var/lib/apt/lists/* \
    && useradd --create-home --uid 1000 --shell /bin/bash vscode
