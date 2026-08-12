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
SQLite
Network/Bluetooth
Robot
Optional Local LLM
```

它们最终共享一个 CPU core。

## 3. 优先级建议

```text
P0  UI / touch responsiveness
P0  Audio capture/playback continuity
P1  active KWS / active speech session
P1  safety-critical perception（若存在）
P2  normal person/gesture perception
P3  optional local language model
P4  engineering statistics / decorative work
```

这不是 OS realtime priority 表，而是产品资源分配原则。

## 4. Companion

建议：

```text
UI：Default/Open，平时 0 FPS
KWS：常驻
Vision：低频
Remote connection：异步 heartbeat
```

## 5. Listening / Remote ASR

远端承担完整 ASR 后，本体主要做：

```text
audio capture + network upload + low FPS UI
```

此时普通 Vision 可以适当降低频率，确保音频链路稳定。

## 6. Local LLM

如果启用：

- 只按需运行；
- 限制 context/output；
- 放 heavy worker；
- 推理期间普通视觉可暂停；
- 不允许在 UI 线程；
- 必须记录 RSS 和延迟。

## 7. InferenceScheduler

**不要 V0.1 创建。**

当实测发现 Vision、KWS、本地 LLM/其他 ORT inference 互相争抢后，再引入统一 Scheduler。

职责可以很小：

```text
同一时间限制重推理数量
给 active speech/safety task 更高优先级
Local LLM 运行时暂停 normal vision
只保留 latest vision request
```

## 8. 推荐实测矩阵

```text
A Companion + KWS
B Companion + KWS + Vision
C Listening + audio upload + Vision
D Speaking + audio playback + Vision
E Local LLM + UI
F Family sync + above workloads
```

记录：

- CPU%；
- RSS；
- UI touch latency；
- audio XRUN；
- KWS latency；
- vision inference latency/FPS；
- remote speech end-to-end latency；
- local LLM completion latency。

## 9. 不建议

- ASR 4 线程 + Vision 4 线程；
- Camera 原始 FPS 全推理；
- 多个 Python worker 各加载一份 ORT；
- 工程页面高频 `/proc` 采样；
- UI 恢复高帧率装饰动画。