# Knobs Integration

This branch repoints the `bitcoin` submodule to [`TABConf/bitcoinknobs`](https://github.com/TABConf/bitcoinknobs), a fork of Bitcoin Core maintained by the TABConf Knobs project. The GUI continues to consume the upstream-friendly `bitcoin` layout; no application logic changes are required.

## Submodule workflow

1. `git submodule sync`
2. `git submodule update --init --recursive`

These commands ensure the submodule is checked out with the forked remote metadata.

## Building against Knobs

The build remains identical to the upstream GUI instructions; the Knobs fork keeps the same public targets and build products as Bitcoin Core.

### Debian/Ubuntu

```bash
sudo apt update && sudo apt install -y \
  qt6-base-dev qt6-tools-dev qt6-l10n-tools qt6-tools-dev-tools \
  qt6-declarative-dev qml6-module-qtquick qml6-module-qtqml \
  libgl-dev libqrencode-dev qt6-wayland

git submodule update --init --recursive
cmake -B build
cmake --build build -j"$(nproc)"
./build/bin/bitcoin-core-app
```

### macOS

```bash
brew install qt@6 qrencode

git submodule update --init --recursive
cmake -B build -DQt6_DIR="$(brew --prefix)/opt/qt@6/lib/cmake/Qt6"
cmake --build build -j"$(sysctl -n hw.ncpu)"
./build/bin/bitcoin-core-app
```

## Notes

- The GUI intentionally imports Bitcoin Core code through the `bitcoin` submodule. Only the submodule remote changes in this branch.
- If Knobs ever diverges in API surface, add small `#ifdef`-guarded shims in the GUI layer instead of modifying Knobs directly.

