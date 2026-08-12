# 测试策略

[← Build](README.md)

## 1. 纯 C++ 单元测试

优先测试：

```text
PetStateMachine
Reminder repeat calculation
AiCapabilityPolicy
Protocol codec
DTO validation
AutoFollowController dead-zone / target-loss logic
MotionService ownership / speed-limit / stale-command logic
```

这些不需要 2K0300 硬件。

## 2. SQLite 测试

使用临时 DB 验证：

- migration；
- Reminder CRUD；
- transaction rollback；
- revision conflict；
- Care summary 查询。

## 3. Transport 测试

提供 Fake/Loopback Transport 验证：

- 分片；
- seq；
- timeout；
- stale session；
- oversize frame；
- reconnect。

## 4. Mock AI Server

建议在 PC 上提供一个简单测试工具：

```text
tools/mock-ai-server/
```

能够：

- 接收 audio；
- 返回固定 ASR；
- 延迟回复；
- 分块 TTS；
- 主动断线；
- 返回错误。

宠物联调不必每次依赖真实大模型服务器。

## 5. Family 测试

可提供 mock family client，验证配对、Reminder 修改和无权限命令拒绝。

还应验证家属协议不能通过普通 command 获得底盘 PWM/实时驾驶能力。

## 6. UI 回归

现有 `longpetui_2` 的 capture 工具留在 UI Prototype，继续做 Windows 1024×600 截图回归；不进入生产主路径。

## 7. MotionService 逻辑测试

不接真实底盘时，用 FakeMotionDriver 验证：

```text
AutoFollow owner 获得/释放
Manual 抢占 AutoFollow
Emergency 抢占所有 owner
Sleep 禁止运动
速度/角速度超限被 clamp/reject
stale intent 被拒绝
MCU unavailable 后禁止继续运动
```

## 8. MCU / 底盘台架测试

在真正接视觉之前，单独验证：

```text
STOP
低速前进/后退/转向
heartbeat/lease
telemetry
command timeout
CRC/error handling
Emergency stop
```

必须做故障注入：

- LongPet 进程退出 → MCU 自动停车；
- 龙芯板与 MCU 通信断开 → MCU 自动停车；
- command 停止续租 → MCU 自动停车；
- MCU reset → 默认停车，不恢复旧命令；
- fault flag → MotionService 进入不可用/停止。

## 9. 自动跟随测试

按阶段测试，不要第一轮直接跑完整跟随：

```text
A 固定图片/录像 → PersonObservation 稳定性
B 人在左/中/右 → MotionIntent 是否符合预期
C target lost → 必须 Stop
D 多人切换 → 不应每帧乱换目标
E 只转向对人
F 低速前后跟随
G Emergency / Manual 抢占
```

如果没有可靠避障传感器，自动跟随测试应限定在低速、空旷、受控场景。

## 10. 板端组合负载

至少测试：

```text
Companion + KWS
KWS + Vision
Remote Listening + Vision
Speaking playback + Vision
Vision + AutoFollow control
Local LLM + UI
Family sync + voice
```

记录：

```text
CPU
RSS
UI latency
Vision inference latency
KWS latency
audio XRUN
motion command latency
MCU telemetry timeout
```

## 11. 故障注入

- AI Server 中途断开；
- Bluetooth 断开；
- Camera unavailable；
- Perception stale；
- Audio XRUN；
- SQLite write error；
- Robot driver timeout；
- Motion MCU timeout/reset；
- AutoFollow target loss；
- Family 发旧 revision；
- Emergency 在底盘运动中触发。

## 12. 长稳

最终版本需进行数小时到数十小时级运行测试，观察：

```text
RSS 是否增长
timer 是否泄漏
重连是否循环失控
DB 是否持续膨胀
audio/camera 是否可恢复
UI 是否仍响应
MCU heartbeat 是否稳定
Motion owner 是否会卡死
```

长稳结束时必须验证底盘仍能可靠 Stop，并且系统退出后 MCU 会自动停车。