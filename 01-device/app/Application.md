# Application / main.cpp

[← Application 模块](README.md)

## 1. 定位

`Application` 是宠物主进程的 **Composition Root**。它只负责组装系统，不负责业务算法。

最终建议：

```text
main.cpp
  ↓
Application
  ├── MainWindow
  ├── AppController
  ├── PetStateMachine
  ├── Services
  ├── Database
  ├── Platform adapters
  └── Connectivity clients
```

## 2. 主要职责

- 加载部署配置和 Feature Flag；
- 打开 SQLite；
- 创建 MainWindow；
- 创建 AppController、PetStateMachine；
- 创建本版本启用的 Service；
- 创建 Audio/Camera/Inference/Robot adapter；
- 创建 Remote AI 与 Family 通信组件；
- 建立 Qt signal/slot；
- 管理初始化和退出顺序；
- 将不可恢复的初始化错误交给统一错误处理。

## 3. 不负责

- 页面布局；
- Reminder 到期算法；
- ASR/TTS；
- ORT Session 细节；
- SQLite 查询语句；
- UART 协议；
- 状态迁移规则。

## 4. 推荐 API 轮廓

```cpp
class Application final : public QObject
{
    Q_OBJECT
public:
    explicit Application(QObject* parent = nullptr);
    bool initialize();
    void show();
    void shutdown();

private:
    MainWindow* m_window = nullptr;
    AppController* m_controller = nullptr;
    PetStateMachine* m_stateMachine = nullptr;
};
```

## 5. 推荐启动顺序

```text
QApplication
→ 加载 RuntimeConfig
→ 初始化日志
→ 打开/迁移 SQLite
→ 初始化轻量 Platform
→ 创建 Services
→ 创建 UI
→ 建立 signal/slot
→ 恢复可恢复状态
→ PetStateMachine = Companion
→ 启动 KWS
→ 后台连接/发现 AI Server 与 Family Link
```

UI 应尽快可见；远端连接不能阻塞首屏。

## 6. 推荐退出顺序

```text
停止新的业务请求
→ cancel remote speech session
→ stop audio/camera workers
→ flush 必要 DB transaction
→ disconnect transport
→ destroy UI/services
```

## 7. 版本建议

- V0.1：可以没有独立 Application 类；
- V0.2：SQLite/Reminder 加入后开始引入；
- V0.3：Remote AI、Audio、KWS 加入后应正式使用。

目标是让最终 `main.cpp` 保持在几十行以内。