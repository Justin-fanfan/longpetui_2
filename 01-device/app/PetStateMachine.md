# PetStateMachine

[← Application 模块](README.md)

## 1. 核心定位

宠物状态机是 LongPet **高层产品交互状态的唯一权威**。

它不描述模型内部状态，也不描述每一个网络连接状态、运动控制状态或底盘实时状态。

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

## 3. 哪些状态不放进 PetStateMachine

这些属于正交上下文或子系统状态：

```text
AI server connected
Family app connected
Human present
Bluetooth available
Network available
Motion MCU available
AutoFollow Disabled/Acquiring/Following/TargetLost
Motion owner
```

它们影响决策，但不是用户正在感知的主要宠物交互状态。

因此不要制造：

```text
CompanionFollowing
SpeakingFollowing
ControlMotionFault
```

等组合状态。

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

运动子系统自己的高频事件不需要全部进入状态机。

例如 `TargetOffsetUpdated`、`WheelSpeedChanged` 不属于 PetStateMachine event。

## 5. 迁移示例

```text
Booting → Companion
Companion --TouchReveal--> Control
Companion --WakeKeywordDetected--> Listening
Listening --SpeechCaptureFinished--> Thinking
Thinking --PlaybackStarted--> Speaking
Speaking --PlaybackFinished--> Companion
Control --ControlTimedOut--> Companion
Sleep --WakeRequested--> Companion/Control
```

## 6. Attention 优先级

```text
Emergency > Reminder > Normal interaction
```

Emergency 到达时，状态机只表达：

```text
Attention = Emergency
```

真正的副作用由 AppController 协调：

```text
MotionService stop
VoiceInteraction cancel
RobotService cancel
UI Alert/EmergencyPage
```

状态机本身不直接调用这些 Service。

Reminder 到达时，如果正在 Listening/Thinking/Speaking，可选择短暂延后而不是硬打断。具体策略由产品需求决定。

## 7. 与运动系统的关系

运动是独立子系统。

例如可以出现：

```text
InteractionState = Companion
AutoFollowState = Following
```

也可以是：

```text
InteractionState = Speaking
Motion = Stopped
```

高层状态只对运动施加门控规则：

```text
Booting   → movement disabled
Sleep     → movement disabled
Emergency → force stop
```

不要让 PetStateMachine 承担转向、速度、目标丢失等运动控制逻辑。

## 8. 推荐实现

2K0300 上不需要为此增加 Qt StateMachine 模块。第一版使用普通 C++ enum + 显式 transition table 即可：

```cpp
bool dispatch(PetEvent event);
PetStateSnapshot state() const;

signals:
    void stateChanged(PetStateSnapshot oldState,
                      PetStateSnapshot newState);
```

## 9. 不负责

- 运行 ASR；
- 运行 TTS；
- 页面 `setCurrentWidget()`；
- SQLite；
- Robot Driver；
- MotionService 的 owner/限速；
- AutoFollow steering；
- 网络重连。

## 10. 测试

它应该是项目里最容易做单元测试的核心类之一：

- 每个合法迁移；
- 非法迁移；
- Emergency 抢占；
- Reminder 延后/解除；
- Remote AI 中断后的恢复；
- Sleep/Booting 对运动 enable 的上层门控事件是否被 AppController 正确响应。

## 11. 引入版本

V0.2/V0.3。