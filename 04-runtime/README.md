# 运行时、性能与可靠性

[← 根目录](../README.md)

2K0300 为单核、资源受限的平台，因此运行时策略和类分层同样重要。

- [线程模型](ThreadModel.md)
- [音频流水线](AudioPipeline.md)
- [单核性能与推理调度](PerformanceAndInferenceScheduling.md)
- [降级与故障恢复](DegradationAndRecovery.md)
- [安全与隐私](SecurityAndPrivacy.md)
- [日志与可观测性](ObservabilityAndLogging.md)

总原则：

> 不让 UI 等待重任务，不让多个本地重推理互相无意义抢单核，不让外部节点故障把本地核心能力一起拖垮。