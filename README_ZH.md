C++20 CMake-Emscripten 模板
===============================

*为**C++20**源代码设置**原生**和**Web**构建环境。*

🤔 为什么创建这个仓库？
-----------------------

**问题：** 目前在使用C++20与Emscripten的`emcmake`时存在一个问题（[emscripten#22305](https://github.com/emscripten-core/emscripten/issues/22305)）。有一个修复方案在[PR#21987](https://github.com/emscripten-core/emscripten/pull/21987)中提出，但尚未合并。

**解决方案：** 本仓库提供了一个最小化设置，**导入了**[PR#21987](https://github.com/emscripten-core/emscripten/pull/21987)中提出的修复方案，**无需修改emscripten**本身。

**增强功能：** 在原始项目基础上，我们添加了Docker支持，使开发者可以通过简单的Docker命令快速构建项目，无需繁琐的环境配置。此外，还增加了一些示例函数，帮助新手更快地理解和学习C++20与WebAssembly的结合使用。

🥸 作为模板使用
---------------------

您可以将此仓库用作模板，然后在代码库中替换以下字符串：

 - `my_project`是CMake项目（和IDE解决方案）的名称。
 - `my_target`是CMake目标的名称，即生成的可执行文件或HTML文件的名称。

🏗️ 构建
-----------

这是一个常规的CMake项目，构建方式与普通CMake项目相同。**唯一的例外**是Web构建需要额外的选项（见下文）。

以下指令展示了如何手动调用CMake，但也提供了`CMakePresets.json`文件作为替代方案。

### 使用Docker构建（推荐）

最简单的方式是使用Docker，无需安装任何依赖项：

```bash
# 一键构建项目并生成JavaScript/WebAssembly文件
docker compose up --remove-orphans
```

这条命令会自动设置所有必要的环境，并使用Emscripten编译项目，输出可直接在浏览器中运行的文件。

### 原生构建

```bash
# 配置
cmake -B build-native
# 或使用 'cmake --preset native'

# 构建
cmake --build build-native

# 运行 (Windows & MSVC)
build/src/Debug/my_target.exe

# 运行 (其他系统)
build/src/my_target
```

### WebAssembly构建

**注意** *针对问题[emscripten#22305](https://github.com/emscripten-core/emscripten/issues/22305)的解决方法是将`CMAKE_CXX_COMPILER_CLANG_SCAN_DEPS`指向我们在`cmake/EmscriptenScanDepsFix`中的本地修复。*

```bash
# 激活emscripten环境 (Windows)
C:/path/to/emsdk/emsdk_env.bat

# 激活emscripten环境 (其他系统)
. /path/to/emsdk/emsdk_env.sh

# 配置
emcmake cmake -B build -DCMAKE_CXX_COMPILER_CLANG_SCAN_DEPS=cmake/EmscriptenScanDepsFix/emscan-deps
# 或使用 'emcmake cmake --preset web'

# 构建
cmake --build build

# 托管
python -m http.server 8000
# 然后浏览器访问 http://localhost:8000/build-web/src/my_target.html
```

📚 示例函数
-----------

为了帮助新手快速上手，我们在项目中添加了几个示例函数，展示了C++20与WebAssembly的交互方式：

- JavaScript/C++数据传递示例
- C++20新特性在WebAssembly中的应用
- DOM操作示例
- 异步函数调用示例

这些示例函数配有详细注释，可以作为开发者学习和实践的参考。 