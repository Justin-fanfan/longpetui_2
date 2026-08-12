# AiServerClient

[← Connectivity](README.md)

## 定位

实现“宠物 ↔ 龙芯 AI 推理服务器”的**应用层协议**。

结构：

```text
RemoteAiService
      ↓
AiServerClient
      ↓
ITransport
```

## 职责

- handshake；
- protocol version；
- server capabilities；
- session id；
- request id；
- audio chunk sequence；
- ASR/TTS/message decode；
- heartbeat；
- timeout；
- cancel；
- 错误映射。

## 推荐语音会话消息

```text
hello / capabilities
speech.start
speech.audio *
speech.audio_end
asr.partial *
asr.final
inference.result / reply.text
tts.audio *
speech.end
speech.cancel
error
heartbeat
```

## 重要

所有 session 相关消息必须带 `sessionId`。所有 chunk 必须有 sequence 或等价顺序语义。

这样即使旧 session 的迟到包到达，也不会被误当作当前语音会话。

## 不负责

- 打开麦克风；
- 播放 TTS；
- PetState；
- 选择 UI 表情。