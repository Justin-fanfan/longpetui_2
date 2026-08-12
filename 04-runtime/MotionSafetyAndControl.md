# 运动安全与控制权

[← Runtime](README.md)

## 1. 为什么单独说明

小车运动与 UI 动画、Reminder、普通机器人表情动作不同：错误控制会让整机发生真实位移。因此运动链路必须有独立的安全和控制权规则。

## 2. 双层安全

### 龙芯侧

`MotionService` 负责：

- enable/disable；
- owner 仲裁；
- 速度限制；
- stale command 拒绝；
- target lost stop；
- Emergency/ Sleep 强制禁止移动；
- MCU fault/timeout 上报。

### MCU 侧

MCU 必须独立负责：

- 实时电机控制；
- command watchdog；
- heartbeat/lease timeout stop；
- reset 后默认停止；
- 最大输出限制；
- 直接可用的本地安全传感器处理。

Linux 卡顿或宠物进程崩溃时，MCU 仍应能停车。

## 3. 控制权优先级

建议：

```text
EmergencyStop
 > SafetyStop
 > UserLocal
 > AutoFollow
 > PetBehavior / IdleMotion
```

不要允许多个来源同时叠加左右轮命令。

## 4. 自动跟随限制

自动跟随默认应：

- 低速；
- 有明确启用条件；
- 目标丢失停车；
- observation 过期停车；
- 多人切换时先重新确认目标；
- 不把低置信度结果转换为运动；
- 不绕过 MCU watchdog。

## 5. 远程家属端

当前架构下，Electron 家属端可以查看/设置宠物状态，但**不默认具有实时驾驶小车的权限**。

如果未来增加远程驾驶，需要额外设计：

- 实时视频/状态反馈；
- 更强鉴权；
- command rate/lease；
- 延迟与断线停车；
- 用户现场安全提示；
- 权限与审计。

不要把它作为 `settings.update` 的自然扩展。

## 6. Emergency

`AttentionState::Emergency` 到达时，Application 层首先请求：

```text
MotionService.forceStop()
```

再处理 UI/TTS/其他动作。

运动停止不应该等待远端 AI、数据库或动画完成。

## 7. 测试矩阵

至少覆盖：

```text
正常前进/转向/停止
视觉目标丢失
摄像头停止更新
PerceptionService 崩溃/超时
龙芯应用退出
龙芯板与 MCU 通信断开
MCU reset
Emergency 抢占
Sleep 进入
Manual → AutoFollow 控制权切换
AutoFollow → Manual 控制权切换
```

## 8. 性能

不要依赖高频视觉推理来保证安全停车。安全停止必须依赖 timeout/watchdog 和本地安全规则，而不是“下一帧模型应该很快会看到障碍”。