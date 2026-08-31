FROM debian:sid-slim

RUN apt-get update \
    && apt-get install -y --no-install-recommends ca-certificates clang-23 clangd-23 \
       libc++-23-dev libc++abi-23-dev libclang-rt-23-dev curl git \
       python3 python3-pip python3-venv nodejs \
    && ln -s /usr/bin/clang-23 /usr/local/bin/clang \
    && ln -s /usr/bin/clang++-23 /usr/local/bin/clang++ \
    && ln -s /usr/bin/clangd-23 /usr/local/bin/clangd \
    && rm -rf /var/lib/apt/lists/* \
    && useradd --create-home --uid 1000 --shell /bin/bash vscode \
    && printf "PS1='\\$ '\n" >> /home/vscode/.bashrc
