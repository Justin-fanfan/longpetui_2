# 视觉自动跟随 → 小车运动数据流

[← Flows](README.md)

## 1. 前提

自动跟随建立在两个已经独立验证的基础能力上：

1. 人体/目标观测稳定；
2. 龙芯 → MCU → 底盘的 stop/watchdog/低速运动链路稳定。

不要把“视觉模型能看到人”和“设备可以安全自主跟随”当成同一个完成条件。

## 2. 正常链路

```text
CameraCapture
   ↓ latest frame
PerceptionService
   ↓ PersonObservation
AutoFollowController
   ↓ MotionIntent
MotionService
   ↓ safety + ownership + speed limit
UartRobotDriver / motion MCU protocol adapter
   ↓
Motion MCU
   ↓ realtime motor control
Motor Driver / Chassis
```

## 3. 目标获取

```text
No target
→ AcquiringTarget
→ 连续若干次可靠 observation
→ lock target
→ Following
```

刚检测到一个人体框时不应立即前进。

## 4. 转向

第一版可以只根据人在画面中的横向位置：

```text
left of dead zone  → TurnLeftSlow
inside dead zone   → no turn
right of dead zone → TurnRightSlow
```

使用 dead zone 和 hysteresis 防止左右抖动。

## 5. 前进/保持距离

只有存在足够可靠的距离依据时才决定前进。

可能来源：

- 目标框大小的粗略距离估计；
- 双目/ToF/超声；
- 其他后续传感器。

如果只能做人框检测，建议先实现“朝向目标”，再逐步实现低速跟随，不要假设单帧框大小就是可靠避障/距离系统。

## 6. 目标丢失

```text
Following
→ observation timeout / confidence lost
→ MotionService.stop(TargetLost)
→ TargetLost
→ reacquire
```

禁止沿最后方向继续盲目前进。

## 7. Emergency / Sleep / Manual 抢占

```text
Emergency
→ MotionService force stop
→ AutoFollow suspended

Sleep
→ motion disabled

User local motion command
→ AutoFollow loses ownership
```

## 8. MCU 失联

龙芯侧：

```text
Driver timeout
→ MotionService marks unavailable
→ AutoFollow SafetyStopped
```

MCU 侧：

```text
heartbeat/lease timeout
→ motor stop
```

两边都要有保护，不能只靠某一侧。

## 9. 性能

视觉推理可保持低频，例如从 2～5 inference FPS 起步；AutoFollowController 本身只做轻量控制计算。

运动命令频率不必等于 camera FPS，也不应无限积压。只保留最新有效 MotionIntent。

## 10. 开发顺序

```text
手动/固定命令低速运动
→ stop/watchdog
→ telemetry
→ 视觉目标观测
→ 只转向对人
→ 目标丢失停车
→ 低速前后跟随
→ 更完整安全传感器融合
```
