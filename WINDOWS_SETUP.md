# Windows Setup (Native, No Docker)

This guide is for Windows users who do **not** want to use Docker. It sets up a native Windows environment for the PPP3e code in this repository.

The project needs:

- **GCC 15+** — provides `libstdc++.modules.json`, the source of the `std` / `std.compat` C++ standard library modules.
- **Clang 21+** — compiles those modules into `.pcm` / `.o` files (and `clangd` for IDE support).
- **bash + GNU tools + curl** — needed by `init.sh`.

Two routes are described below. **Route A (MSYS2)** mirrors the Docker/Linux workflow almost exactly and is recommended. **Route B (Visual Studio / MSVC)** uses Microsoft's toolchain — your source code needs no changes, but the build system is different.

---

## Route A: MSYS2 (recommended, mirrors the Linux workflow)

MSYS2 is a Linux-style environment for Windows. It ships a recent GCC **and** Clang together (GCC 16.x and Clang 22.x as of this writing), plus bash, curl, and GNU sed — so `init.sh` runs unchanged.

> [!NOTE]
> Why not WinLibs? WinLibs' newest releases (GCC 16.x) ship **without** Clang, and its Clang-bundled releases are older (GCC 14 + Clang 19) — below the required Clang 21. MSYS2 keeps both tools current in a single package repository.

### 1. Install MSYS2

Download and install from <https://www.msys2.org/>, then open the **"MSYS2 UCRT64"** terminal (not the default MSYS shell, and not mingw64).

### 2. Update MSYS2 and install the toolchain

```bash
pacman -Syu                      # update; on first run, close and reopen the terminal, then run it once more
pacman -S --needed \
    mingw-w64-ucrt-x86_64-gcc \
    mingw-w64-ucrt-x86_64-clang \
    mingw-w64-ucrt-x86_64-clang-tools-extra \
    mingw-w64-ucrt-x86_64-lld \
    git curl
```

- `gcc` provides libstdc++ and `libstdc++.modules.json` (GCC 15+).
- `clang` compiles the modules (Clang 21+); `clang-tools-extra` provides `clangd`.
- `lld` is the linker used for the module objects.

Verify:

```bash
g++ --version      # GCC 15+ (e.g. 16.2.0)
clang++ --version  # Clang 21+ (e.g. 22.1.8)
```

> [!IMPORTANT]
> Stay in the **UCRT64** environment for everything. Do not mix `ucrt64` and `mingw64` packages/tools — their runtime libraries are incompatible.

### 3. Get the code and build the modules

```bash
cd ~
git clone <your-ppp-repo-url> ppp   # or copy your existing checkout
cd ppp
./init.sh
```

`init.sh` downloads the PPP headers from stroustrup.com and compiles the `std`, `std.compat`, and `PPP` modules into `.modules/`.

> [!NOTE]
> **Line endings.** If you cloned with Git for Windows (default `core.autocrlf=true`), shell scripts may be checked out with CRLF line endings and `./init.sh` will fail with something like `$'\r': command not found`. Fix it by re-checking out with LF:
>
> ```bash
> git config core.autocrlf false
> git rm --cached -r . >/dev/null && git reset --hard
> ```
>
> Cloning inside the MSYS2 shell avoids this because it keeps LF endings.

### 4. Compile and run a program

```bash
clang++ -std=c++23 -Wall -Wextra -IPPP -fprebuilt-module-path=.modules \
    c1/hello.cpp .modules/std.o .modules/PPP.o \
    -o c1/hello.out
./c1/hello.out
```

### 5. Use it from VS Code

1. Install the **clangd** and **Code Runner** extensions.
2. Make the MSYS2 **UCRT64** shell the default integrated terminal (Terminal → New Terminal → profile: MSYS2 UCRT64), **or** add `C:\msys64\ucrt64\bin` to your Windows `PATH` so `clang++`/`g++` also work from cmd/PowerShell.
3. Code Runner needs this `executorMap` setting (the same as the Dev Container):

```json
"code-runner.executorMap": {
    "cpp": "clang++ -std=c++23 -Wall -Wextra -IPPP -fprebuilt-module-path=.modules $fullFileName .modules/std.o .modules/PPP.o -o $dir$fileNameWithoutExt.out && $dir$fileNameWithoutExt.out"
}
```

`compile_flags.txt` and `.clangd` already contain the module flags, so clangd understands the code out of the box.

---

## Route B: Visual Studio (MSVC) toolchain

MSVC fully supports C++23 modules and `import std;`. **Your source code needs no changes** — `c1/*.cpp` (`import std;`), `cx/*.cpp` (`#include "PPP.h"` → `import PPP;`), `PPP/PPP.ixx`, and `PPP/PPP_support.h` are all standard C++23 that MSVC accepts.

What changes is the **build setup**, not the code:

| | Clang (Linux / MSYS2) | MSVC |
| --- | --- | --- |
| Standard library module | compiled from GCC's `libstdc++.modules.json` via `init.sh` | built into the MSVC STL — `import std;` just works |
| Module artifacts | `.pcm` + `.o` | `.ifc` + `.obj` |
| Standard switch | `-std=c++23` | `/std:c++23` |
| Module flags | `-fmodule-output`, `-fprebuilt-module-path` | `/interface`, `/reference`, `/ifcOutput` |
| `compile_flags.txt` / `.clangd` | used | not used |

> [!IMPORTANT]
> Use a **recent Visual Studio 2022 (17.6 or newer, ideally the latest)**. Older versions, and VS 2019, do not support C++23 modules or `import std;` (and early 17.x builds had bugs with `export import std;`).

### Build with the Visual Studio IDE (easiest)

1. Create a Console App project.
2. Add `PPP/PPP.ixx` (MSVC recognizes `.ixx` as a module interface automatically) and your `.cpp` files.
3. Project properties → C/C++ → Language → set **C++ Language Standard** to `ISO C++23`, and make sure **Exception Handling** is `/EHsc`.
4. Build. MSBuild resolves the module dependency graph for you.

### Build on the command line with `cl.exe`

```bat
:: 1. Compile the PPP module interface
cl /std:c++23 /EHsc /utf-8 ^
    /interface PPP\PPP.ixx /ifcOutput .modules\PPP.ifc /Fo.modules\ ^
    /c PPP\PPP.ixx

:: 2. Compile + link a program (use /reference for every file that imports PPP)
cl /std:c++23 /EHsc /utf-8 ^
    /reference PPP=.modules\PPP.ifc ^
    c1\hello.cpp .modules\PPP.obj
```

> [!WARNING]
> - `/EHsc` is required — the PPP code throws exceptions (`error()`, `narrow()`, …).
> - Expect **warnings, not errors**, from `PPP_support.h` under `/W4` (e.g. C4018 signed/unsigned comparisons, C4296 `i < 0` on an unsigned type). These come from the upstream book code and are harmless.
> - clangd reads Clang `.pcm` files and **cannot** read MSVC `.ifc` files. With the MSVC toolchain, use the **C/C++ extension** (`ms-vscode.cpptools`) IntelliSense in VS Code, or the built-in IntelliSense in the Visual Studio IDE.

---

## Alternative: WSL2 (not native Windows, but nearly zero setup)

If you only want to avoid Docker and are fine with a Linux environment, WSL2 is the lowest-friction option: install a recent distro (e.g. Ubuntu 26.04+ or Arch), then follow the **"Set up the environment on recent Linux distributions"** section in the [README](./README.md) — just install clang 21+ and gcc 15+, and run `./init.sh`.
