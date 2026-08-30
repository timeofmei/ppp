# Programming: Principles and Practice Using C++ 3e

Code for [PPP3e](https://www.stroustrup.com/programming.html). This project provides an easy-to-set-up C++23 learning environment in a Dev Container. It works on Linux, macOS, and WSL with Docker.

## Set up the environment on recent Linux distributions

If on Ubuntu 26.04+, Debian 14+ or Arch Linux (check if **clang 21+** and **gcc 15+** is available), then no Docker is required. Just install clang 21 and gcc 15, and run `./init.sh`. The `std` and `PPP` modules are compiled.

## Set up the environment

1. For Linux, install and start [Docker Engine](https://docs.docker.com/engine/install/) on the host.
2. For [Windows with WSL](https://docs.docker.com/desktop/setup/install/windows-install/) or [macOS](https://docs.docker.com/desktop/setup/install/mac-install/), install and start Docker Desktop on the host. 
3. Install the **Dev Containers** extension in VS Code.
4. Open the repository in VS Code and run **Dev Containers: Reopen in Container**. The container installs the required C++ toolchain and runs `init.sh` automatically to compile the `std` and `PPP` modules.

## Compile and run a program

```bash
clang++ -std=c++23 -IPPP -fprebuilt-module-path=.modules \
    c1/hello.cpp .modules/std.o .modules/PPP.o \
    -o c1/hello.out
c1/hello.out
```
