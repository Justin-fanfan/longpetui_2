# VisualTokens

[← Widgets](README.md)

## 定位

视觉设计常量的唯一集中来源。

当前包含：

```text
LongPetUi::Colors
LongPetUi::Metrics
```

例如：

```text
CanvasWidth = 1024
CanvasHeight = 600
PageMargin
StatusBarHeight
PrimaryButtonHeight
Accent
Danger
Surface
TextPrimary
```

## 使用原则

当多个页面反复出现同一个颜色/尺寸，应进入 Token，而不是继续复制数字。

## 不要放入

- Reminder timeout；
- server IP；
- model path；
- ASR sample rate；
- 数据库配置。

这些属于 RuntimeConfig/业务配置，不是视觉 Token。