# MotionService

[← Services](README.md)

## 1. 核心定位

`MotionService` 专门负责 LongPet 小车/移动底盘的高层运动控制。

硬件控制权分层应明确为：

```text
龙芯板：决定“想怎么移动”
   ↓
MotionService：安全检查、控制权仲裁、限速、超时
   ↓
UartRobotDriver / MCU protocol adapter
   ↓
单片机：直接控制电机/驱动器，执行底层实时控制
   ↓
小车底盘
```

龙芯板是**间接控制者**，单片机是运动执行的**直接控制者**。

## 2. 为什么从 RobotService 中单独拆出

普通宠物表现动作与底盘移动的风险等级不同。

例如：

```text
点头 / 摆动 → 表现动作
前进 / 转向 → 会改变整机空间位置
```

底盘移动需要额外处理：

- 控制权仲裁；
- 最大速度；
- 指令超时；
- MCU heartbeat/watchdog；
- 目标丢失立即停车；
- Emergency 强制停车；
- 自动跟随的 enable/disable；
- MCU fault 回传。

因此建议长期保留：

```text
RobotService  → 非底盘的宠物表现/执行器动作
MotionService → 小车移动
```

若最终实体机构非常简单，也可以由同一个 MCU 执行，但软件职责仍建议分开。

## 3. 推荐 API

第一版可以非常小：

```cpp
void stop(MotionStopReason reason);
void submitIntent(const MotionIntent& intent);
void setEnabled(bool enabled);
```

后续可增加：

```cpp
void setSpeedLimit(...);
MotionTelemetry telemetry() const;
```

## 4. 控制权仲裁

任何时刻只允许一个运动来源成为当前 owner。

推荐优先级原则：

```text
EmergencyStop
    > Local safety stop
    > User local command
    > AutoFollow
    > PetBehavior / Idle movement
```

这里是产品控制权原则，不等于 Linux realtime priority。

家属 Electron 应用默认**不应获得远程驾驶权限**。如果未来增加远程驾驶，应作为独立安全功能重新设计，而不是复用普通 settings command。

## 5. MotionIntent 安全过滤

`MotionService` 在把意图交给 Driver 前至少检查：

- 当前是否允许移动；
- source 是否仍拥有控制权；
- 速度/角速度是否超限；
- 命令是否过期；
- Emergency 是否激活；
- MCU 是否在线；
- 必要安全传感器状态（若硬件具备）。

## 6. 与视觉自动跟随的关系

正确链路：

```text
PerceptionService
    ↓ PersonObservation
AutoFollowController
    ↓ MotionIntent
MotionService
    ↓ safety/arbitration
MCU Driver
```

禁止：

```text
Vision model
→ UART
→ 电机
```

视觉模型只提供观测；自动跟随控制器产生运动意图；MotionService 做最终上层安全门。

## 7. MCU 失联

龙芯板检测通信超时后必须：

```text
标记 motion unavailable
停止继续发送普通运动意图
通知上层
```

同时 MCU 固件自身必须具有独立 watchdog：如果一定时间没有收到有效 heartbeat/运动续租，应自行停车。具体超时时间由电机性能与实测决定，不能只依赖 Linux 进程来保证停车。

## 8. PetStateMachine 的关系

底盘运动 mode 不应全部塞进 `PetStateMachine`。

例如：

```text
Companion + AutoFollow
Speaking + stationary
Control + user movement
```

运动是一个正交子系统。

但高层状态可以限制运动：

```text
Emergency → force stop
Sleep     → movement disabled
Booting   → movement disabled
```

## 9. 线程

MotionService 本身应轻量，不做视觉推理。

高频电机闭环留给 MCU；龙芯只需要相对低频地发送目标/续租并接收 telemetry。

## 10. 引入版本

底盘通信接入时即可引入；视觉自动跟随后再增加 `AutoFollowController`。