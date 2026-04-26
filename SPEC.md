# Specification

## bbb.utils.shell

### Inlets / Outlets

| # | Direction | Type | Description |
|---|-----------|------|-------------|
| 0 | inlet | anything | Receives messages |
| 0 | outlet | symbol | stdout output |
| 1 | outlet | symbol | stderr output |
| 2 | outlet | selector | Object-level status: `"done <exit_code>"` or `"error <message>"` |

### Messages

| Message | Argument | Description |
|---------|----------|-------------|
| `exec` | symbol | Execute a shell command string: `<shell> -c "<command>"` |
| `run` | symbol | Run a shell script file: `<shell> <script_path>` |

### Attributes

| Name | Type | Default | Description |
|------|------|---------|-------------|
| `shell` | symbol | `"/bin/bash"` | Path to the shell binary |
| `async` | bool | `true` | Execute asynchronously |

### Behavior

- `exec`: spawns `<shell> -c "<command>"`, captures stdout/stderr separately
- `run`: spawns `<shell> <script_path>`, captures stdout/stderr separately
- When `@async` is true: command runs in a background thread, results delivered via timer polling
- When `@async` is false: command blocks Max until completion (use with caution)
- On completion: stdout → outlet 0, stderr → outlet 1, `"done <exit_code>"` → outlet 2
- On internal error (fork failure etc.): `"error <message>"` → outlet 2

---

## bbb.utils.osascript

### Inlets / Outlets

| # | Direction | Type | Description |
|---|-----------|------|-------------|
| 0 | inlet | anything | Receives messages |
| 0 | outlet | symbol | Script result |
| 1 | outlet | symbol | stderr output |
| 2 | outlet | selector | Object-level status: `"done"` or `"error <message>"` |

### Messages

| Message | Argument | Description |
|---------|----------|-------------|
| `exec` | symbol | Execute inline script source: `osascript -l <language> -e '<source>'` |
| `run` | symbol | Run a script file: `osascript -l <language> <script_path>` |

### Attributes

| Name | Type | Default | Description |
|------|------|---------|-------------|
| `language` | enum | `"applescript"` | Script language: `"applescript"` or `"javascript"` |
| `async` | bool | `true` | Execute asynchronously |

### Behavior

- `exec`: spawns `osascript -l <language> -e '<source>'`
- `run`: spawns `osascript -l <language> <script_path>`
- When `@language` is `"applescript"`: uses `-l AppleScript`
- When `@language` is `"javascript"`: uses `-l JavaScript`
- Async behavior identical to `bbb.utils.shell`
- On completion: result → outlet 0, stderr → outlet 1, `"done"` → outlet 2
- On internal error: `"error <message>"` → outlet 2

---

## Common: process.h

Shared utility for subprocess execution with stdout/stderr capture.

### Interface

```cpp
namespace bbb {

struct process_result {
    std::string stdout_output;
    std::string stderr_output;
    int exit_code;
};

process_result execute(const std::string &executable,
                       const std::vector<std::string> &args);

}
```

### Implementation

- Uses `pipe()` + `fork()` + `dup2()` + `execvp()` for subprocess spawning
- Uses `poll()` for non-blocking read from both stdout and stderr pipes simultaneously (avoids deadlock from full pipe buffers)
- Returns captured output and exit code
- Throws on fork/pipe/exec failure
