# LongPet UI Prototype Merge Guide

> 本文只说明视觉资产的取用边界，不设计任何业务接口。

## A. 推荐直接复制

- `resources/styles/app.qss` 中经过第三阶段 1024×600 视觉 QA 的颜色、文字、按钮、卡片和状态样式。
- `resources/icons/` 中的本地轻量 SVG。
- `src/widgets/VisualTokens.h` 中的纯视觉颜色与尺寸常量。
- `docs/UI_DESIGN.md` 中的颜色、字号、间距、圆角、触控尺寸和动画约束。
- 经过人工审核的宠物表情几何比例。

复制前仍需确认生产项目的字体、资源前缀和目标 linuxfb 环境。

## B. 推荐人工合并

- `PetFaceWidget` 的 QPainter 绘制与低频局部动画；Sleep / Emergency 中的动画关闭策略需一并保留。
- `LargeActionButton`、三栏平衡的 `StatusBarWidget`、`SectionCard`、`SettingRow`、`ReminderItem`、`ToastWidget` 等视觉控件。
- Home、Care、Reminder、Settings、Emergency、Sleep 等 Page QWidget 的布局实现。
- 1024×600 下的固定尺寸和布局比例。

这些文件包含原型所需的具体布局和演示文案，生产项目应按实际页面结构人工选择，不应整目录覆盖。

## C. 不应该复制到生产项目

- `DemoWindow`。
- `UiGalleryPage` 与全部 Design Review 内容。
- F1～F12 开发快捷导航。
- Demo 页面之间的直接 `QStackedWidget::setCurrentWidget()` 连接。
- Listening / Thinking / Speaking 的假文本与演示状态切换。
- Care、Reminder、Engineering 的固定假数据。
- Settings 中只改变控件外观的 slider / switch。
- Emergency 中“不会拨号”的演示确认。
- Demo-only Toast、页面跳转按钮、表情选择辅助代码。
- `--capture-dir` 全页面截图模式与 `DemoWindow::captureAllPages()`。

不得从这些 Demo 行为推导或创建 Service、Controller、Model、Repository、EventBus、业务状态机、硬件抽象或未来 signal/slot 接口。

## 当前视觉 QA 状态

- 12 个页面和 Gallery 的 3 个页签视图已按 1024×600 检查，无滚动条、裁切或布局越界。
- Home 保持宠物为第一视觉中心；状态栏时间使用左右平衡布局固定在屏幕水平中轴。
- 老人侧主要操作为 80～112 px 高；设置滑块的实际触控高度为 64 px。
- 十种宠物表情使用同一粗圆端几何语言；Worried 与 Default 已保留明确静态差异。
- 生产合并前仍需在目标 linuxfb 字体与物理 7 英寸面板上复核字形、对比度和触控手感。
