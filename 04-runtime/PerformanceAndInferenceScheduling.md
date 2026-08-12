# 单核性能预算与推理调度

[← Runtime](README.md)

## 1. 当前 UI 基线

现有优化后的 `PetFaceWidget` 在 2K0300 Release 实机上，Speaking 等动画状态 CPU 已控制在约 15% 以内。这个结果已经可以作为正式迁移基线。

后续不要为了再省几个百分点大幅复杂化 UI；真正重要的是 AI 模块接入后的**整机组合负载**。

## 2. 本体本地任务

```text
Qt UI
Audio capture/playback
KWS
Vision person/gesture
AutoFollow control logic
MotionService / MCU communication
SQLite
Network/Bluetooth
Robot
Optional Local LLM
```

它们最终共享一个 CPU core，但并非每项都应是重任务。

其中：

```text
AutoFollowController
MotionService
MCU heartbeat/telemetry
```

应保持轻量、稳定、低抖动；真正重的是 Vision/KWS/Local LLM 等推理。

## 3. 优先级建议

```text
P0  UI / touch responsiveness
P0  Audio capture/playback continuity
P0  Motion stop / MCU heartbeat / safety handling
P1  active KWS / active speech session
P1  safety-critical perception（若存在）
P2  normal person/gesture perception / AutoFollow observation
P3  optional local language model
P4  engineering statistics / decorative work
```

这不是 OS realtime priority 表，而是产品资源分配原则。

注意：`Motion stop` 是高优先级，但不意味着龙芯要高频做电机闭环；实时闭环由 MCU 承担。

## 4. Companion

建议：

```text
UI：Default/Open，平时 0 FPS
KWS：常驻
Vision：低频
Motion：通常 stopped，MCU heartbeat/telemetry 轻量
Remote connection：异步 heartbeat
```

## 5. Listening / Remote ASR

远端承担完整 ASR 后，本体主要做：

```text
audio capture + network upload + low FPS UI
```

此时普通 Vision 可以适当降低频率，确保音频链路稳定。

如果 AutoFollow 正在启用，不建议简单把视觉完全暂停；更合理的是降低到仍能满足目标丢失检测的频率，或者根据产品策略在语音会话期间暂停跟随并停车。

## 6. AutoFollow

推荐：

```text
Vision：2～5 inference FPS 起步
AutoFollowController：仅消费 latest observation
MotionIntent：只保留最新值，不积压
MCU：独立实时闭环 + watchdog
```

不要为了控制底盘而把摄像头推理提到 20/30 FPS。

自动跟随安全不依赖“下一帧模型一定及时到达”，而依赖：

```text
observation timestamp
stale timeout
MotionService stop
MCU watchdog
```

## 7. Local LLM

如果启用：

- 只按需运行；
- 限制 context/output；
- 放 heavy worker；
- 推理期间普通视觉可暂停；
- 如果 AutoFollow 正在运行，优先考虑先停车/暂停跟随再运行重本地 LLM；
- 不允许在 UI 线程；
- 必须记录 RSS 和延迟。

## 8. InferenceScheduler

**不要 V0.1 创建。**

当实测发现 Vision、KWS、本地 LLM/其他 ORT inference 互相争抢后，再引入统一 Scheduler。

职责可以很小：

```text
同一时间限制重推理数量
给 active speech/safety task 更高优先级
Local LLM 运行时暂停 normal vision
只保留 latest vision request
```

MotionService 不应依赖 InferenceScheduler 才能执行 Stop；运动停止链必须始终可立即执行。

## 9. 推荐实测矩阵

```text
A Companion + KWS
B Companion + KWS + Vision
C Listening + audio upload + Vision
D Speaking + audio playback + Vision
E Vision + AutoFollow + MCU heartbeat
F Local LLM + UI
G Local LLM + Motion stopped
H Family sync + above workloads
```

记录：

- CPU%；
- RSS；
- UI touch latency；
- audio XRUN；
- KWS latency；
- vision inference latency/FPS；
- remote speech end-to-end latency；
- motion intent → MCU ACK latency；
- heartbeat/telemetry timeout；
- target lost → stop latency；
- local LLM completion latency。

## 10. 不建议

- ASR 4 线程 + Vision 4 线程；
- Camera 原始 FPS 全推理；
- 多个 Python worker 各加载一份 ORT；
- AutoFollow 命令按每帧无限排队；
- 用 Linux 用户态承担电机 PWM/实时闭环；
- 工程页面高频 `/proc` 采样；
- UI 恢复高帧率装饰动画。
