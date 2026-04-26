# bbb.utils

Max/MSP utility externals package.

## Objects

### Cross-platform (macOS + Windows)

| Object | Description |
|--------|-------------|
| `bbb.utils.base64` | Base64 encode / decode |
| `bbb.utils.env` | Get / set / unset environment variables |
| `bbb.utils.json` | JSON parse / stringify / query (nlohmann/json) |
| `bbb.utils.path` | Path join / split / resolve / basename / dirname |
| `bbb.utils.text` | String split / join / trim / replace / upper / lower / pad |
| `bbb.utils.uuid` | Generate UUID v4 strings |

### macOS only

| Object | Description |
|--------|-------------|
| `bbb.utils.clipboard` | Read / write macOS clipboard |
| `bbb.utils.filewatch` | Filesystem watcher (FSEvents) |
| `bbb.utils.hash` | SHA-256 / SHA-512 / MD5 hashing (CommonCrypto) |
| `bbb.utils.http` | HTTP client using curl (GET / POST / PUT / DELETE) |
| `bbb.utils.notify` | macOS notification center |
| `bbb.utils.osascript` | Execute AppleScript / JXA |
| `bbb.utils.regex` | POSIX regex match / replace |
| `bbb.utils.shell` | Execute shell commands |

## Build

### Local

```bash
mkdir -p build && cd build
cmake ..
cmake --build .
```

Output: `externals/*.mxo` (macOS), `externals/*.mxe64` (Windows)

### CI (GitHub Actions)

Push to `main` triggers automatic builds on both macOS and Windows.
Download artifacts from the [Actions tab](../../actions).

## Requirements

- macOS or Windows
- CMake 3.19+
- macOS: Xcode CLI tools
- Windows: Visual Studio 2022
- Max 8+
- min-api (included as submodule)

## Install

Copy the entire `bbb.utils/` directory to Max's packages folder:

```
~/Documents/Max 8/Packages/bbb.utils/
```

## Development

This project uses the [max-external](https://github.com/2bbb/max-external) skill for scaffolding and build configuration.

See `.agents/skills/max-external/` for project conventions, CMake macros, and common pitfalls.
