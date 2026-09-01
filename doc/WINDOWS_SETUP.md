# Windows Setup (Native, No Docker)

This guide installs a native Windows Clang 23 + libc++ environment for the PPP3e code in this repository. It does not require Docker, WSL, MSYS2, or Visual Studio Build Tools.

## 1. Install Scoop

Open a regular PowerShell window and run:

```powershell
Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser
Invoke-RestMethod -Uri https://get.scoop.sh | Invoke-Expression
```

If Scoop is already installed, skip this step.

## 2. Install the LLVM-MinGW toolchain

```powershell
scoop install mingw-mstorsjo-llvm-ucrt
```

This package provides Clang, clangd, LLD, libc++, compiler-rt, LLVM libunwind, and the `std` / `std.compat` module sources.

Verify the installation:

```powershell
clang++ --version
clangd --version
clang++ -dumpmachine
```

The Clang version must be 23 or newer, and the target should be `x86_64-w64-windows-gnu` on a 64-bit Intel/AMD Windows system.

## 3. Build the modules

Clone and open this repository, then run:

```powershell
powershell -ExecutionPolicy Bypass -File .\init.ps1
```

`init.ps1` downloads the PPP headers and compiles `std`, `std.compat`, and `PPP` into `.modules`.

> [!TIP]
> After Scoop upgrades the toolchain, rerun `init.ps1` so that the precompiled modules match the new compiler.

## 4. Compile and run a program

```powershell
$cxx = (Get-Content -Raw .modules\compiler.path).Trim()

& $cxx -std=c++23 -stdlib=libc++ -IPPP `
    -fprebuilt-module-path=.modules `
    c1\hello.cpp .modules\std.obj .modules\PPP.obj `
    -o c1\hello.exe

.\c1\hello.exe
```
