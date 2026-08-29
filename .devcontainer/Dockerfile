FROM mcr.microsoft.com/devcontainers/cpp:ubuntu26.04

RUN apt-get update \
    && apt-get install -y --no-install-recommends clangd \
    && rm -rf /var/lib/apt/lists/*
