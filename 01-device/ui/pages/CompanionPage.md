# CompanionPage

[← Pages](README.md)

## 定位

机器宠物绝大多数时间的默认沉浸界面。屏幕首先是一张“宠物脸”，而不是传统功能首页。

## 显示

- 大尺寸 `PetFaceWidget`；
- 默认建议 `DefaultOpen`；
- 不显示长期状态栏、菜单、卡片；
- 可有极少量必要提示。

## 输入

整屏触摸。

正式接口建议：

```cpp
signals:
    void controlRequested();
```

## 不负责

- 检测关键词；
- 判断 Remote AI；
- 状态机；
- Control timeout；
- 机器人动作。

## 性能

Companion 是长期待机页，应优先使用平时 0 FPS、仅低频 one-shot blink 的表情。不要常驻 Speaking 动画。

## V0.1

首批迁入正式工程。