# LocalInference Adapters

[← Platform](README.md)

## 目标

隔离本地模型运行库。

推荐根据实际使用创建：

```text
OrtVisionEngine
SherpaKeywordEngine
LocalLlmEngine（可选）
```

## OrtVisionEngine

负责：

- ORT Session；
- input/output name；
- tensor；
- preprocess 的模型相关部分；
- inference；
- output decode 的底层部分。

2K0300 上继续沿用已经验证过的无 LSX/LASX 兼容 ORT 标量路径，不能在后续依赖升级中无意恢复不适配 SIMD 的 MLAS 实现。

## SherpaKeywordEngine

只封装关键词模型和 decode。KeywordSpottingService 负责 debounce/cooldown 和产品语义。

## LocalLlmEngine

只封装可选小模型的 load/infer/unload。

## 不负责

- 业务优先级；
- Page；
- state transition；
- 数据持久化。

## 推理并发

是否允许多个 engine 同时运行由 Runtime 的 InferenceScheduler/业务策略决定，不由每个 Engine 自己无限开线程。