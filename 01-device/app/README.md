# Application 层

[← 宠物本体](../README.md) · [← 根目录](../../README.md)

Application 层负责“产品现在应该做什么”，是 UI 与各业务 Service 之间的协调层。

## 组成

- [Application](Application.md)：Composition Root，创建对象、加载配置并完成依赖接线。
- [AppController](AppController.md)：接收 UI/Service 事件并编排业务流程。
- [AppState](AppState.md)：少量跨模块状态快照与能力状态。
- [PetStateMachine](PetStateMachine.md)：宠物高层交互状态及合法迁移。
- [PetBehaviorController](PetBehaviorController.md)：把产品状态映射成屏幕表情和实体行为。
- [AiCapabilityPolicy](AiCapabilityPolicy.md)：决定远端 AI、本地小模型、规则降级的能力选择。

## 依赖原则

```text
UI → Application → Services → Data / Platform / Connectivity
```

Application 层可以知道多个 Service，但不应出现 ONNX、sherpa、SQLite SQL、UART 字节或 QWidget 绘制细节。

## V0.1

V0.1 只需要 `MainWindow + Pages + Widgets`。本目录中的类按真实功能逐步引入，不要一次性建立空壳。