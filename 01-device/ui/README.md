# UI 模块

[← 宠物本体](../README.md) · [← 根目录](../../README.md)

LongPet UI 使用 Qt 6 Widgets，目标画布 1024×600，板端使用 linuxfb + tslib。

## 组成

- [MainWindow](MainWindow.md)
- [Pages](pages/README.md)
- [Widgets / Visual System](widgets/README.md)
- [现有 longpetui_2 → 正式工程迁移](UIPrototypeMigration.md)

## 核心规则

```text
Page：显示数据 + 发用户意图
Widget：复用视觉
MainWindow：页面容器
Application：决定产品流程
Service：提供能力
```

UI 主线程禁止执行 ORT inference、本地 LLM、阻塞音频/网络和大 SQL 操作。