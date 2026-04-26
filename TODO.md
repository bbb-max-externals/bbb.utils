# TODO

## Phase 0: Project Setup
- [x] Add min-api as git submodule at `deps/min-api/`
- [x] Create root `CMakeLists.txt`
- [x] Create `package-info.json`
- [x] Create directory structure (`source/projects/`, `source/bbb/`, `externals/`, `help/`)

## Phase 1: Common Module
- [x] Implement `source/bbb/process.h` — `bbb::execute()` with fork/exec/pipe/poll

## Phase 2: bbb.utils.shell
- [x] Create `source/projects/bbb.utils.shell/bbb.utils.shell.cpp`
- [x] Create `source/projects/bbb.utils.shell/CMakeLists.txt`
- [x] Add to root CMakeLists.txt

## Phase 3: bbb.utils.osascript
- [x] Create `source/projects/bbb.utils.osascript/bbb.utils.osascript.cpp`
- [x] Create `source/projects/bbb.utils.osascript/CMakeLists.txt`
- [x] Add to root CMakeLists.txt

## Phase 4: Verification
- [x] CMake build succeeds
- [x] Both `.mxo` files generated in `externals/`
- [ ] Load test in Max (manual)
