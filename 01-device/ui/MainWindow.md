# MainWindow

[← UI 模块](README.md)

## 推荐类型

```cpp
class MainWindow final : public QWidget
```

LongPet 不需要菜单栏、工具栏、Dock 等桌面窗口能力，因此正式版无需沿用 Demo 的 QMainWindow。

## 职责

- 1024×600 根画布；
- QStackedWidget 页面容器；
- 页面实例生命周期；
- `PageId → QWidget*`；
- 页面显示；
- 全局 Toast / Overlay；
- Windows preview 与 Linux fullscreen。

## 推荐 PageId

```cpp
enum class PageId {
    Companion,
    Home,
    Conversation,
    Care,
    Reminder,
    ReminderEdit,
    Settings,
    Emergency,
    Sleep
};
```

## 推荐 API

```cpp
void showPage(PageId page);
void showToast(const QString& text);
```

## V0.1

MainWindow 可以暂时管理：

```text
Companion ↔ Home
12～15 秒 Control timeout
Toast
```

## 后期

引入 AppController 后，MainWindow 只执行页面显示，不决定业务应该去哪个页面。

## 不负责

```text
ASR/TTS
SQLite
Vision
Network
Robot
State transition policy
```