# AppState

[← Application 模块](README.md)

## 1. 定位

`AppState` 是一份很小的跨模块状态快照，保存“其他模块经常需要知道、但不属于某一个 Service 内部实现”的信息。

## 2. 推荐内容

```cpp
struct AppState
{
    InteractionState interaction;
    AttentionState attention;

    bool aiServerReady = false;
    bool familyLinkReady = false;
    bool humanPresent = false;
    bool speechSessionActive = false;
    bool motionAvailable = false;
};
```

还可以包含少量当前设备模式，但应克制。

## 3. 运动相关边界

`AppState` 只需要知道类似：

```text
motionAvailable
```

这种会影响全局产品决策的摘要。

以下内容不要放进 AppState：

```text
left/right wheel speed
current PWM
MCU packet sequence
AutoFollow steering error
Motion owner
每帧 MotionTelemetry
```

这些属于 `MotionService` / Driver / `AutoFollowController` 内部状态。

如果未来确实有多个模块都需要读取某个稳定的 motion summary，可以增加一个小型只读 `MotionStatusSnapshot`，而不是不断膨胀 AppState。

## 4. 不应存放

- Reminder 全表；
- SQLite connection；
- 原始 PCM；
- 摄像头帧；
- ONNX Tensor；
- QWidget 指针；
- Family App 原始消息；
- 大语言模型上下文缓存；
- 高频底盘 telemetry。

这些分别属于对应模块。

## 5. 与 PetStateMachine 的关系

`PetStateMachine` 是高层交互状态的权威；`AppState` 可以包含它的 snapshot，并额外保存连接、人存在、运动模块可用性等**正交上下文**。

不要把：

```text
WiFiConnected
BluetoothConnected
HumanPresent
FamilyOnline
MotionAvailable
AutoFollowFollowing
```

都变成 PetStateMachine 状态，否则状态数量会爆炸。

## 6. 版本建议

V0.1 不需要独立类。等跨模块上下文达到 3～5 项后再引入。