# Implementation Plan

## Architecture

```
bbb.utils/
├── CMakeLists.txt                    # Root CMake: add_subdirectory for each external
├── package-info.json                 # Max package metadata
├── deps/
│   └── min-api/                      # git submodule (includes max-sdk-base)
├── source/
│   ├── bbb/
│   │   └── process.h                 # Shared: fork/exec/pipe/poll subprocess utility
│   └── projects/
│       ├── bbb.utils.shell/
│       │   ├── CMakeLists.txt
│       │   └── bbb.utils.shell.cpp   # Shell command execution external
│       └── bbb.utils.osascript/
│           ├── CMakeLists.txt
│           └── bbb.utils.osascript.cpp  # AppleScript/JXA execution external
├── externals/                        # Build output (.mxo)
└── help/                             # Max help files
```

## Execution Model

### Async mode (default, @async=true)

1. Message handler receives command → spawns `std::thread`
2. Thread calls `bbb::execute()` → fork/exec/poll → captures result
3. Thread stores result in member, sets `std::atomic<bool>` completion flag
4. `c74::min::timer` polls every ~50ms → detects completion → outputs to outlets on main thread
5. Timer stops after delivering results

### Sync mode (@async=false)

1. Message handler calls `bbb::execute()` directly (blocks Max main thread)
2. Immediately outputs results to outlets

### Subprocess capture (process.h)

```
parent process (Max thread)
  ├── pipe(stdout_pipe[2])
  ├── pipe(stderr_pipe[2])
  ├── fork()
  │     └── child:
  │           dup2(stdout_pipe[1], STDOUT_FILENO)
  │           dup2(stderr_pipe[1], STDERR_FILENO)
  │           close read ends
  │           execvp(executable, args)
  ├── close write ends
  ├── poll([stdout_pipe[0], stderr_pipe[0]], ...)
  │     read available data into buffers
  └── waitpid() → exit_code
```

## Execution Order

1. Project scaffolding (submodule, CMake, dirs, package-info.json)
2. `source/bbb/process.h`
3. `bbb.utils.shell`
4. `bbb.utils.osascript`
5. Build verification
