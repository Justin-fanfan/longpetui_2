# CMake 演进

[← Build](README.md)

## 1. V0.1

继续一个 target：

```text
LongPet
```

Qt 基础依赖：

```text
Qt6::Core
Qt6::Gui
Qt6::Widgets
Qt6::Svg
```

## 2. SQLite

若采用 QtSql：

```text
Qt6::Sql
```

并确认 Buildroot target 中存在 QSQLITE plugin。

若没有，直接 link sqlite3 adapter，不要为了统一外观同时保留两套。

## 3. 网络

真实使用时再增加：

```text
Qt6::Network
Qt6::WebSockets（如果最终协议选择且 rootfs 包含）
```

不要因为架构可能使用 WebSocket 就提前增加模块。

## 4. 第三方 AI

ORT、sherpa-onnx、OpenCV 依赖应尽量限制到相应 Platform/Service 源文件或 target，不让 UI 全局 include。

## 5. Feature Options

后期可以加入：

```cmake
option(LONGPET_ENABLE_VISION "Enable local vision" ON)
option(LONGPET_ENABLE_REMOTE_AI "Enable remote AI server" ON)
option(LONGPET_ENABLE_LOCAL_LLM "Enable local small language model" OFF)
option(LONGPET_ENABLE_FAMILY_LINK "Enable family app link" ON)
option(LONGPET_BUILD_UI_TOOLS "Build UI gallery/tools" OFF)
```

默认值以实际版本为准。

## 6. 何时拆 library

V0.1/V0.2 不拆。

当出现：

```text
大量可单测业务逻辑
多个 executable/tools
重复 link
```

再考虑：

```text
longpet_core
LongPet executable
```

不要一次拆十几个静态库。

## 7. 交叉编译

继续使用当前已验证的 `cmake/toolchains/loongarch64-buildroot.cmake`，target 依赖必须来自 sysroot，host Qt tools 来自 SDK host path。