# Programming: Principles and Practice Using C++ 3e

Code for [PPP3e](https://www.stroustrup.com/programming.html). This project provides an easy-to-set-up C++23 learning environment in a Dev Container. It works on Linux, macOS, and WSL with Docker. If you are on Windows or macOS and have no interest in installing Docker, see [WINDOWS_SETUP](doc/WINDOWS_SETUP.md) or [MACOS_SETUP](doc/MACOS_SETUP.md). Otherwise, follow the steps below.

The Dev Container uses Debian Forky's default **Clang and libc++** (currently 21). Native installations use the newest Clang 18+ available on `PATH` and its matching libc++; `init.sh` on Linux/macOS and `init.ps1` on Windows record that compiler so the modules and your code are always built by the same version.

## Set up the environment on recent Linux distributions

If your Linux distribution provides **Clang 18+**, `clangd`, and the matching libc++ development package, Docker is not required. Ubuntu 24.04 LTS (Clang 18) and Debian 13 (Clang 19) are the earliest releases whose default `clang` package meets this requirement. Install the packages and run `./init.sh`; the `std`, `std.compat`, and `PPP` modules are compiled locally.

## Set up the environment

1. For Linux, install and start [Docker Engine](https://docs.docker.com/engine/install/) on the host.
2. For [Windows with WSL](https://docs.docker.com/desktop/setup/install/windows-install/) or [macOS](https://docs.docker.com/desktop/setup/install/mac-install/), install and start Docker Desktop on the host.
3. Install the **Dev Containers** extension in VS Code.
4. Open the repository in VS Code and run **Dev Containers: Reopen in Container**. The container installs the required C++ toolchain and runs `init.sh` automatically to compile the `std` and `PPP` modules.

> [!NOTE]
> On Windows, clone the repository **inside WSL** (e.g. `~/projects/ppp`) using WSL's own Git — **not** onto the Windows drive (`C:\`). Cloning inside WSL keeps the files on the Linux filesystem with LF line endings (WSL's Git does not convert them by default), which avoids CRLF issues with `init.sh` and gives much better I/O performance than `/mnt/c/...`. Cloning to the Windows drive (`C:\`) is also viable, but note that the files are then accessed via `/mnt/c/...` (slower I/O) and, if cloned with Windows Git's default `core.autocrlf=true`, shell scripts are checked out with CRLF line endings and will fail inside the container.

## Proxy configuration (Optional)

If your host machine needs a proxy to reach the internet (e.g. a local Clash/V2Ray instance or a corporate proxy), the Dev Container is set up to inherit your `http_proxy` / `https_proxy` environment variables, so `init.sh`, `apt`, and VS Code extensions running inside the container (such as the Codex extension) can use them too.

> [!IMPORTANT]
> **Do not modify `.devcontainer/devcontainer.json`.** It is the same file for all platforms and already handles the proxy for you. The only thing you need to change is the proxy **environment variables on your own host** — set `http_proxy` / `https_proxy` there (see the examples in the table below), then reopen the container.

> [!IMPORTANT]
> The container only inherits proxy variables that are **already set on the host**. If your proxy software is configured inside the app but no `http_proxy` / `https_proxy` environment variable exists on the host, the container will not see them.

The correct setup method depends on your platform:

> [!TIP]
> On macOS and Windows / WSL2 (Docker Desktop), install or upgrade to the latest Docker Desktop and enable **host** networking (Docker Desktop 4.34+: **Settings → Resources → Network → Enable host networking**).

| Platform | Docker Networking mode | Proxy address to use | Notes |
| --- | --- | --- | --- |
| Linux (Docker Engine) | host | `http://127.0.0.1:PORT` | In `~/.bashrc`,<br>`export http_proxy=http://127.0.0.1:7890`<br>`export https_proxy=http://127.0.0.1:7890` |
| macOS (Docker Desktop) | host (4.34+, opt-in) | `http://127.0.0.1:PORT` | 1. In Docker Desktop, enable **Settings → Resources → Network → Enable host networking**.<br>2. In `~/.zshrc`,<br>`export http_proxy=http://127.0.0.1:7890`<br>`export https_proxy=http://127.0.0.1:7890` |
| Windows / WSL2 (Docker Desktop) | host (4.34+, opt-in) | `http://127.0.0.1:PORT` | 1. In Docker Desktop, enable **Settings → Resources → Network → Enable host networking**.<br>2. In WSL Settings, set **WSL networking mode** to **mirrored**.<br>3. Set the variables **inside WSL**, not in Windows environment variables. Works when the proxy runs inside Windows (e.g. Clash Verge Rev). In `~/.bashrc`,<br>`export http_proxy=http://127.0.0.1:7890`<br>`export https_proxy=http://127.0.0.1:7890` |
| Windows / WSL2 (native Docker Engine) | host | `http://127.0.0.1:PORT` | Set the variables **inside WSL**, not in Windows environment variables. Works when the proxy runs inside WSL (e.g. Clash in WSL). In `~/.bashrc`,<br>`export http_proxy=http://127.0.0.1:7890`<br>`export https_proxy=http://127.0.0.1:7890` |

## Compile and run a program

```bash
PPP_CXX=$(<.modules/compiler.path)
"$PPP_CXX" -std=c++23 -stdlib=libc++ -Wall -Wextra -IPPP -fprebuilt-module-path=.modules \
    c1/hello.cpp .modules/std.o .modules/PPP.o \
    -o c1/hello.out
c1/hello.out
```

## VS Code shortcuts

- **`Ctrl+Alt+N`** — compile & run the current `.cpp` file (`C++: build & run` task)
- **`Ctrl+Shift+B`** — compile only (`C++: build` task)

Both are installed automatically by `init.sh` inside the Dev Container.
