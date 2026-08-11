# LongPet UI Demo

> **THIS PROJECT IS A UI-ONLY PROTOTYPE.**  
> **NO BUSINESS LOGIC IS IMPLEMENTED.**

LongPet UI Demo 是一个独立的 Qt 6 Widgets 视觉原型，用于展示面向老年人的 7 英寸横屏机器宠物界面。它只包含本地页面跳转、视觉状态、Demo slider 和固定假数据。

## 运行要求

- Windows 10/11 开发预览环境
- Qt 6.5 或更高版本，包含 Core、Gui、Widgets、Svg
- CMake 3.21 或更高版本
- Ninja + MinGW、MSVC 或其他与 Qt 安装匹配的工具链
- 窗口 client area 固定为 1024×600

## 构建

常规方式：

```powershell
cmake -S . -B build
cmake --build build
```

本机 Qt 不在默认搜索路径时，可指定 Qt：

```powershell
cmake -S . -B build -G Ninja `
  -DCMAKE_PREFIX_PATH=D:/Qt/6.11.0/mingw_64 `
  -DCMAKE_MAKE_PROGRAM=D:/Qt/Tools/Ninja/ninja.exe `
  -DCMAKE_CXX_COMPILER=D:/Qt/Tools/mingw1310_64/bin/g++.exe
cmake --build build
```

## 页面

- Home
- Listening
- Thinking
- Speaking
- Care / 今日关怀
- Reminder / 提醒列表
- Reminder Edit / 提醒编辑
- Settings
- Emergency
- Sleep
- Engineering Demo
- UI Gallery

从 Home 可浏览老人侧主要流程。开发展示快捷键：`F1` Home、`F2` Listening、`F3` Thinking、`F4` Speaking、`F5` Care、`F6` Reminder、`F7` Reminder Edit、`F8` Settings、`F9` Sleep、`F10` Emergency、`F11` Engineering、`F12` UI Gallery。

## UI Gallery

UI Gallery 是开发审核工具，不是面向老人的产品页面。它集中展示十种宠物表情、按钮状态、卡片、提醒项、设置项、Toast、颜色和文字层级。表情卡可以直接点击，只有当前选中的表情启用轻量动画。

## 本地资源

- `resources/styles/app.qss`：集中视觉样式。
- `resources/icons/`：统一 48×48 本地 SVG 图标。
- `resources/resources.qrc`：Qt Resource System 入口，运行时只使用 `:/...` 路径。
- `reference-assets/`：第一阶段的概念参考，不在运行时直接加载。

## Demo Data

Care、Reminder、Conversation、Settings 和 Engineering 中的文本、数值、网络状态和指标全部为写死的演示数据。工程页始终显示 `DEMO DATA`；本项目不会读取 CPU/RAM、调用网络、保存提醒、联系家人或控制系统设置。

## 明确不包含

AI、ASR、TTS、录音、播放、摄像头、OpenCV、ONNX、网络、天气 API、数据库、提醒调度、通知、联系人、系统音量/亮度/Wi-Fi、GPIO、UART、机器人控制、系统监控及任何生产接口。
