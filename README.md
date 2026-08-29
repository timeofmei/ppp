# Programming: Principles and Practice Using C++ 3e

Code for [PPP3e](https://www.stroustrup.com/programming.html). Uses a Dev Container to provide an easy-to-set-up C++23 learning environment setup. Works on Linux or WSL with Docker.

## Set up the environment

1. Install and start [Docker Engine](https://docs.docker.com/engine/install/) on the host.
2. Install the **Dev Containers** extension in VS Code.
3. Open the repository in VS Code and run **Dev Containers: Reopen in Container**. The container installs the required C++ toolchain and runs `init.sh` automatically to compile the `std` and `PPP` modules.

## Compile and run a program

```bash
clang++ -std=c++23 -IPPP -fprebuilt-module-path=.modules c1/hello.cpp .modules/std.o .modules/PPP.o -o c1/hello.out
c1/hello.out
```
