# Programming: Principles and Practice Using C++ 3e

## Init environment

Install and start Docker on the host, then install the **Dev Containers** and **clangd** extension in VS Code.

Open the repository in VS Code and run **Dev Containers: Reopen in Container**.
The container installs the required C++ toolchain and runs `init.sh` automatically
to compile the `std` and `PPP` modules.

## Compile some program

```bash
clang++ -std=c++23 -IPPP -fprebuilt-module-path=.modules <path/to/xxx.cpp> .modules/std.o .modules/PPP.o -o <path/to/xxx.a>
<path/to/xxx.a>
```
