FROM debian:sid-slim

RUN apt-get update \
    && apt-get install -y --no-install-recommends ca-certificates curl git gnupg lsb-release \
       python3 python3-pip python3-venv nodejs \
    && curl -fsSLo /tmp/llvm.sh https://apt.llvm.org/llvm.sh \
    && chmod +x /tmp/llvm.sh \
    && /tmp/llvm.sh 23 \
    && apt-get install -y --no-install-recommends libc++-23-dev libc++abi-23-dev libclang-rt-23-dev \
    && ln -s /usr/bin/clang-23 /usr/local/bin/clang \
    && ln -s /usr/bin/clang++-23 /usr/local/bin/clang++ \
    && ln -s /usr/bin/clangd-23 /usr/local/bin/clangd \
    && rm -f /tmp/llvm.sh \
    && rm -rf /var/lib/apt/lists/* \
    && useradd --create-home --uid 1000 --shell /bin/bash vscode
