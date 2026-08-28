# Programming: Principles and Practice Using C++ 3e

## Init environment

```bash
git clone https://github.com/timeofmei/ppp.git
cd ppp
./init.sh # Works on linux, compiles std and PPP modules
```

## Compile some program

```bash
clang++ -std=c++23 -IPPP -fprebuilt-module-path=.modules <path/to/xxx.cpp> .modules/std.o .modules/PPP.o -o <path/to/xxx.a>
<path/to/xxx.a>
```
