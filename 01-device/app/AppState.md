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
};
```

还可以包含少量当前设备模式，但应克制。

## 3. 不应存放

- Reminder 全表；
- SQLite connection；
- 原始 PCM；
- 摄像头帧；
- ONNX Tensor；
- QWidget 指针；
- Family App 原始消息；
- 大语言模型上下文缓存。

这些分别属于对应模块。

## 4. 与 PetStateMachine 的关系

`PetStateMachine` 是高层交互状态的权威；`AppState` 可以包含它的 snapshot，并额外保存连接、人存在等**正交上下文**。

不要把：

```text
WiFiConnected
BluetoothConnected
HumanPresent
FamilyOnline
```

都变成 PetStateMachine 状态，否则状态数量会爆炸。

## 5. 版本建议

V0.1 不需要独立类。等跨模块上下文达到 3～5 项后再引入。