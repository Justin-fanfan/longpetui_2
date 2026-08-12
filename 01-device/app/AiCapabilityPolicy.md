# AiCapabilityPolicy

[← Application 模块](README.md)

## 1. 为什么需要

LongPet 同时存在：

- 本地关键词识别；
- 本地基础视觉；
- 可选本地小语言模型；
- 外部高性能 AI Server 的 ASR/TTS/语言推理。

如果每个页面和 Controller 都写：

```cpp
if (serverConnected) ... else if (localModel) ...
```

降级策略会迅速失控。

## 2. 定位

它是一份**能力选择策略**，不执行模型。

建议能力矩阵：

| 能力 | 首选 | 降级 |
|---|---|---|
| 唤醒/关键词 | 本地 KWS | 必须本地可用 |
| 完整 ASR | Remote AI | 若未来有本地 ASR再加入；否则明确不可用 |
| TTS | Remote AI | 可退化为 UI 文本/提示音 |
| 文本推理 | Remote AI | 本地小模型 → 规则/模板 |
| 人体/手势 | 本地 | 降低频率/关闭该创意功能 |

## 3. API 方向

可以很简单：

```cpp
enum class Provider { Remote, Local, RuleBased, Unavailable };
Provider choose(AiCapability capability) const;
```

## 4. 不要过早创建

如果 V0.3 时只有“远端可用/不可用”一个判断，可以先放在 AppController。

只有 fallback 条件开始散落时，再提取成该类。

## 5. 安全原则

本地小语言模型和远端通用语言模型都不应直接成为 Emergency 等安全状态的唯一判定依据。安全触发应使用明确、可验证的业务规则与传感结果。