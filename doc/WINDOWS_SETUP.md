# Windows Setup (Native, No Docker)

This guide is for Windows users who do **not** want to use Docker. It sets up a Windows environment for the PPP3e code in this repository.

The project needs:

- **Clang 23+ and its matching libc++** — provide and compile the `std` / `std.compat` modules (and include `clangd` for IDE support).
- **bash + GNU tools + curl** — needed by `init.sh`.

Two routes are described below: native MSYS2 with its CLANG64 environment, or WSL2.

---

## MSYS2 (recommended, mirrors the Linux workflow)

MSYS2 is a Linux-style environment for Windows. Its Clang and libc++ packages must be version 23 or newer for this project.

### 1. Install MSYS2

Download and install from <https://www.msys2.org/>, then open the **"MSYS2 CLANG64"** terminal (not the default MSYS, UCRT64, or MINGW64 shell).

### 2. Update MSYS2 and install the toolchain

```bash
pacman -Syu                      # update; on first run, close and reopen the terminal, then run it once more
pacman -S --needed \
    mingw-w64-clang-x86_64-clang \
    mingw-w64-clang-x86_64-clang-tools-extra \
    mingw-w64-clang-x86_64-libc++ \
    mingw-w64-clang-x86_64-lld \
    git curl
```

- `clang` and `libc++` provide and compile the standard library modules; `clang-tools-extra` provides `clangd`.
- `lld` is the linker used for the module objects.

Verify:

```bash
clang++ --version  # Clang 23+ (e.g. 23.1.0)
```

> [!IMPORTANT]
> Stay in the **CLANG64** environment for everything. Do not mix `clang64`, `ucrt64`, and `mingw64` packages or object files; each environment has its own toolchain and library prefix.

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
PPP_CXX=$(<.modules/compiler.path)
"$PPP_CXX" -std=c++23 -stdlib=libc++ -IPPP -fprebuilt-module-path=.modules \
    c1/hello.cpp .modules/std.o .modules/PPP.o \
    -o c1/hello.out
./c1/hello.out
```

### 5. Use it from VS Code

1. Install the **clangd** extension.
2. Make the MSYS2 **CLANG64** shell the default integrated terminal (Terminal → New Terminal → profile: MSYS2 CLANG64), **or** add `C:\msys64\clang64\bin` to your Windows `PATH` so `clang++` works from cmd/PowerShell.

`compile_flags.txt` and `.clangd` already contain the module flags, so clangd understands the code out of the box.

---

## Alternative: WSL2 (not native Windows, but nearly zero setup)

If you only want to avoid Docker and are fine with a Linux environment, [WSL2](https://learn.microsoft.com/windows/wsl/install) is the lowest-friction option: install a recent distro, then follow the **"Set up the environment on recent Linux distributions"** section in the [README](../README.md) — install Clang 23+, clangd, and the matching libc++ development package, then run `./init.sh`.
