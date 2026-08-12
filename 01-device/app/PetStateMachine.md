# PetStateMachine

[← Application 模块](README.md)

## 1. 核心定位

宠物状态机是 LongPet **高层产品交互状态的唯一权威**。

它不描述模型内部状态，也不描述每一个网络连接状态。

## 2. 推荐采用“两维状态”而不是一个巨大 enum

### InteractionState

```cpp
enum class InteractionState
{
    Booting,
    Companion,
    Control,
    Listening,
    Thinking,
    Speaking,
    Sleep
};
```

### AttentionState

```cpp
enum class AttentionState
{
    None,
    Reminder,
    Emergency
};
```

这样可以避免创造：

```text
EmergencyWhileSpeaking
EmergencyWhileControl
ReminderWhileListening
ReminderWhileCompanion
...
```

这种组合状态。

## 3. 为什么连接状态不放进状态机

这些属于上下文：

```text
AI server connected
Family app connected
Human present
Bluetooth available
Network available
```

它们影响决策，但不是用户正在感知的主要宠物交互状态。

## 4. 推荐事件

```text
BootCompleted
TouchReveal
ControlTimedOut
WakeKeywordDetected
SpeechCaptureFinished
AsrFinalReceived
ReplyReady
PlaybackStarted
PlaybackFinished
CancelConversation
ReminderDue
ReminderDismissed
EmergencyRaised
EmergencyCleared
SleepRequested
WakeRequested
RemoteAiLost
```

## 5. 迁移示例

```text
Booting → Companion
Companion --TouchReveal--> Control
Companion --WakeKeyword--> Listening
Listening --CaptureFinished--> Thinking
Thinking --PlaybackStarted--> Speaking
Speaking --PlaybackFinished--> Companion
Control --Timeout--> Companion
Sleep --Wake--> Companion/Control
```

## 6. Attention 优先级

```text
Emergency > Reminder > Normal interaction
```

Emergency 到达时，AppController 可以根据策略取消当前语音会话、停止普通动作并进入 Alert 表现。

Reminder 到达时，如果正在 Listening/Thinking/Speaking，可选择短暂延后而不是硬打断。具体策略由产品需求决定。

## 7. 推荐实现

2K0300 上不需要为此增加 Qt StateMachine 模块。第一版使用普通 C++ enum + 显式 transition table 即可：

```cpp
bool dispatch(PetEvent event);
PetStateSnapshot state() const;

signals:
    void stateChanged(PetStateSnapshot oldState,
                      PetStateSnapshot newState);
```

## 8. 不负责

- 运行 ASR；
- 运行 TTS；
- 页面 `setCurrentWidget()`；
- SQLite；
- Robot Driver；
- 网络重连。

## 9. 测试

它应该是项目里最容易做单元测试的核心类之一：

- 每个合法迁移；
- 非法迁移；
- Emergency 抢占；
- Reminder 延后/解除；
- Remote AI 中断后的恢复。

## 10. 引入版本

V0.2/V0.3。