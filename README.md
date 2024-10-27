C++20 CMake-Emscripten Template
===============================

*Setup for **Native** and **Web** build of **C++20** source code.*

🤔 Why this repository?
-----------------------

**Problem:** There is currently an issue when using C++20 with Emscripten's `emcmake` ([emscripten#22305](https://github.com/emscripten-core/emscripten/issues/22305)). There is a fix proposed in [PR#21987](https://github.com/emscripten-core/emscripten/pull/21987), but it has not been merged yet.

**Solution:** This repository provides a minimal setup that **imports the fix** proposed by [PR#21987](https://github.com/emscripten-core/emscripten/pull/21987) **without the need to modify emscripten** itself.

🥸 Using as a template
---------------------

You may use this repository as a template, then replace the following strings in the code base:

 - `my_project` is the name of the CMake project (and IDE solution).
 - `my_target` is the name of the CMake target, i.e., the name of the generated executable or HTML file.

🏗️ Building
-----------

This is a regular CMake project, that builds like a CMake project. The **only exception** is the extra option needed for Web build (see below).

These instructions show how to manually call CMake, but a `CMakePresets.json` file is also provided as an alternative.

### Native

```bash
# Configure
cmake -B build-native
# or 'cmake --preset native'

# Build
cmake --build build-native

# Run (Windows & MSVC)
build/src/Debug/my_target.exe

# Run (other)
build/src/my_target
```

### WebAssembly

**NB** *The workaround for issue [emscripten#22305](https://github.com/emscripten-core/emscripten/issues/22305) consists in pointing `CMAKE_CXX_COMPILER_CLANG_SCAN_DEPS` to the local fix that we have in `cmake/EmscriptenScanDepsFix`.*

```bash
# Activate emscripten env (Windows)
C:/path/to/emsdk/emsdk_env.bat

# Activate emscripten env (other)
. /path/to/emsdk/emsdk_env.sh

# Configure
emcmake cmake -B build -DCMAKE_CXX_COMPILER_CLANG_SCAN_DEPS=cmake/EmscriptenScanDepsFix/emscan-deps
# or 'emcmake cmake --preset web'

# Build
cmake --build build

# Host
python -m http.server 8000
# The browse to http://localhost:8000/build-web/src/my_target.html
```
