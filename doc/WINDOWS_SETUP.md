# Windows Setup (Native, No Docker)

This guide installs a native Windows Clang 21+ and libc++ environment for the PPP3e code in this repository. It does not require Docker, WSL, MSYS2, or Visual Studio Build Tools.

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

The Clang version must be 21 or newer, and the target should be `x86_64-w64-windows-gnu` on a 64-bit Intel/AMD Windows system.

## 3. Configure VS Code

Install the recommended **clangd** extension (`llvm-vs-code-extensions.vscode-clangd`) when VS Code prompts you to do so.

If VS Code was open while Scoop installed the toolchain, completely close all VS Code windows and reopen it. VS Code processes that were already running do not see the updated `PATH`.

If the clangd extension still says that clangd is not installed, open **Preferences: Open Workspace Settings (JSON)** from the VS Code Command Palette and set `clangd.path` to the full path printed by this command in the integrated terminal:

```powershell
(Get-Command clangd.exe).Source
```

For example (replace the user name with yours):

```json
{
    "clangd.path": "C:\\Users\\YOUR_NAME\\scoop\\apps\\mingw-mstorsjo-llvm-ucrt\\current\\bin\\clangd.exe"
}
```

Then run **clangd: Restart language server** from the Command Palette. There is no need to let the extension download a separate copy of clangd; the Scoop toolchain already includes the matching executable.

## 4. Build the modules

Clone and open this repository, then run:

```powershell
powershell -ExecutionPolicy Bypass -File .\init.ps1
```

`init.ps1` downloads the PPP headers and compiles `std`, `std.compat`, and `PPP` into `.modules`.

> [!TIP]
> After Scoop upgrades the toolchain, rerun `init.ps1` so that the precompiled modules match the new compiler.

## 5. Compile and run a program

```powershell
$cxx = (Get-Content -Raw .modules\compiler.path).Trim()

& $cxx -std=c++23 -stdlib=libc++ -IPPP `
    -fprebuilt-module-path=.modules `
    c1\hello.cpp .modules\std.obj .modules\PPP.obj `
    -o c1\hello.exe

.\c1\hello.exe
```
