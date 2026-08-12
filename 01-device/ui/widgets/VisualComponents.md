# VisualComponents

[← Widgets](README.md)

当前可直接复用的视觉组件包括：

## makeLabel

统一 role 驱动的 QLabel 创建，避免页面重复设置字体颜色。

## SvgIconWidget

渲染 QRC 中的轻量 SVG 图标。

## LargeActionButton

统一适老大按钮的图标、文字、尺寸和 role。

## StatusBarWidget

状态栏视觉。以后真实数据应通过 setter/model 输入，不能在 Widget 内联网。

## PageHeaderWidget

统一“返回 + 标题”。

## SectionCard

通用卡片容器，只是视觉组件，不代表业务对象。

## SettingRow

```text
Icon | Title/Subtitle | Control
```

## ReminderItem

Reminder 单项视觉，包括时间、标题、图标、状态。

## ToastWidget

短时非模态反馈。老人主界面尽量避免频繁 QMessageBox。

## 边界原则

这些组件可以知道自己的视觉属性，但不能知道 ReminderService、RemoteAiService 等业务对象。