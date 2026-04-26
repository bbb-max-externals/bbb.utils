# TODO

## Phase 0: Project Setup
- [ ] Add min-api as git submodule at `deps/min-api/`
- [ ] Create root `CMakeLists.txt`
- [ ] Create `package-info.json`
- [ ] Create directory structure (`source/projects/`, `source/bbb/`, `externals/`, `help/`)

## Phase 1: Common Module
- [ ] Implement `source/bbb/process.h` — `bbb::execute()` with fork/exec/pipe/poll

## Phase 2: bbb.utils.shell
- [ ] Create `source/projects/bbb.utils.shell/bbb.utils.shell.cpp`
- [ ] Create `source/projects/bbb.utils.shell/CMakeLists.txt`
- [ ] Add to root CMakeLists.txt

## Phase 3: bbb.utils.osascript
- [ ] Create `source/projects/bbb.utils.osascript/bbb.utils.osascript.cpp`
- [ ] Create `source/projects/bbb.utils.osascript/CMakeLists.txt`
- [ ] Add to root CMakeLists.txt

## Phase 4: Verification
- [ ] CMake build succeeds
- [ ] Both `.mxo` files generated in `externals/`
- [ ] Load test in Max (manual)
