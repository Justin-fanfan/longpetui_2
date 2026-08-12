# longpetui_2 → 正式 LongPet 迁移

[← UI 模块](README.md)

## 直接复用

```text
src/widgets/PetFaceWidget.*
src/widgets/VisualComponents.*
src/widgets/VisualTokens.h
resources/resources.qrc
resources/styles/app.qss
icons
cmake/toolchains/loongarch64-buildroot.cmake
```

## 页面复制后改造

当前 Prototype 很多页面通过 `QPushButton* xxxButton()` 暴露内部控件供 DemoWindow 连接。

正式页面逐步改为：

```cpp
signals:
    void xxxRequested();
```

页面内部把按钮 click 转成语义 signal。

## 不进入生产主路径

```text
DemoWindow
UiGalleryPage
captureAllPages()
F1～F12 shortcuts
纯 Demo navigation
硬编码假工程指标
```

`EngineeringPage` 可以保留为比赛/开发构建选项，但不要成为老人日常导航的一部分。

## V0.1 最小迁移

```text
main.cpp
MainWindow
CompanionPage
HomePage
PetFaceWidget
VisualComponents
VisualTokens
resources/qss
```

## V0.1 Companion

当前 Prototype 为性能测试曾把 Speaking 放到 Companion。正式项目应切回 `DefaultOpen` 或 `Default`，以保持长期待机几乎静态。