# Windows Setup (Native, No Docker)

This guide is for Windows users who do **not** want to use Docker. It sets up a Windows environment for the PPP3e code in this repository.

The project needs:

- **GCC 15+** — provides `libstdc++.modules.json`, the source of the `std` / `std.compat` C++ standard library modules.
- **Clang 21+** — compiles those modules into `.pcm` / `.o` files (and `clangd` for IDE support).
- **bash + GNU tools + curl** — needed by `init.sh`.

Two routes are described below. **MSYS2** mirrors the Docker/Linux workflow almost exactly and is recommended. **Alternative: WSL2** has almost the same environment to run the code.

---

## MSYS2 (recommended, mirrors the Linux workflow)

MSYS2 is a Linux-style environment for Windows. It ships a recent GCC **and** Clang together (GCC 16.x and Clang 22.x as of this writing), plus bash, curl, and GNU sed — so `init.sh` runs unchanged.

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
clang++ -std=c++23 -IPPP -fprebuilt-module-path=.modules \
    c1/hello.cpp .modules/std.o .modules/PPP.o \
    -o c1/hello.out
./c1/hello.out
```

### 5. Use it from VS Code

1. Install the **clangd** extension.
2. Make the MSYS2 **UCRT64** shell the default integrated terminal (Terminal → New Terminal → profile: MSYS2 UCRT64), **or** add `C:\msys64\ucrt64\bin` to your Windows `PATH` so `clang++`/`g++` also work from cmd/PowerShell.

`compile_flags.txt` and `.clangd` already contain the module flags, so clangd understands the code out of the box.

---

## Alternative: WSL2 (not native Windows, but nearly zero setup)

If you only want to avoid Docker and are fine with a Linux environment, [WSL2](https://learn.microsoft.com/windows/wsl/install) is the lowest-friction option: install a recent distro (e.g. Ubuntu 26.04+ or Arch), then follow the **"Set up the environment on recent Linux distributions"** section in the [README](./README.md) — just install clang 21+ and gcc 15+, and run `./init.sh`.
