# bbb.utils

Max/MSP utility externals package.

## Objects

### bbb.utils.shell

Execute shell commands from Max.

- Execute inline commands via `exec` message
- Run shell script files via `run` message
- Configurable shell (`/bin/bash` by default)
- Async execution (non-blocking) with sync fallback

### bbb.utils.osascript

Execute AppleScript / JavaScript for Automation (JXA) from Max.

- Execute inline script source via `exec` message
- Run script files via `run` message
- Switch between AppleScript and JavaScript via `@language` attribute
- Async execution (non-blocking) with sync fallback

## Build

```bash
mkdir -p build && cd build
cmake ..
cmake --build .
```

Output: `externals/*.mxo`

## Requirements

- macOS
- CMake 3.19+
- Xcode CLI tools
- Max 8+

## Install

Copy the entire `bbb.utils/` directory to Max's packages folder:

```
~/Documents/Max 8/Packages/bbb.utils/
```
