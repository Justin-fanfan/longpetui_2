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
- 创建 Audio/Camera/Inference/Robot/Motion adapter；
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
- UART/MCU 协议；
- 自动跟随控制算法；
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
→ 确认 Motion 默认 disabled/stopped
→ 启动 KWS
→ 后台连接/发现 AI Server 与 Family Link
```

UI 应尽快可见；远端连接不能阻塞首屏。

运动模块上电/初始化完成也不代表允许自动运动。MCU reset 后应保持 stopped，直到上层完成明确 enable/owner 流程。

## 6. 推荐退出顺序

```text
停止新的业务请求
→ MotionService stop / disable
→ 等待或确认 MCU stop/lease 即将失效
→ cancel remote speech session
→ stop audio/camera workers
→ flush 必要 DB transaction
→ disconnect transport
→ destroy UI/services
```

即使应用异常退出、来不及执行上述 shutdown，MCU watchdog 也必须在通信失联后自动停车。

## 7. 版本建议

- V0.1：可以没有独立 Application 类；
- V0.2：SQLite/Reminder 加入后开始引入；
- V0.3：Remote AI、Audio、KWS 加入后应正式使用；
- 运动底盘接入后，Application 负责把 MotionService/Driver 正确组装，但不实现运动算法。

目标是让最终 `main.cpp` 保持在几十行以内。