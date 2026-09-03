FROM debian:forky-slim

RUN apt-get update \
    && apt-get install -y --no-install-recommends ca-certificates curl git \
       clang clangd libc++-dev libc++abi-dev libclang-rt-dev \
       nodejs python3 python3-pip python3-venv \
    && rm -rf /var/lib/apt/lists/* \
    && useradd --create-home --uid 1000 --shell /bin/bash vscode
