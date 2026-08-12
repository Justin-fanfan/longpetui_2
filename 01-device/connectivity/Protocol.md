# 通信协议与消息模型

[← Connectivity](README.md)

AI Server 与 Family App 是两个不同协议域，建议分别版本化，但可以共用少量 envelope 设计。

## 1. 控制消息 Envelope

概念上建议：

```json
{
  "version": 1,
  "type": "speech.start",
  "requestId": "...",
  "deviceId": "...",
  "timestamp": 0,
  "payload": {}
}
```

字段最终以协议实现为准。

## 2. 二进制音频

不要把大量 PCM Base64 塞进 JSON。

推荐：

```text
小型控制消息 → JSON/CBOR 等
大块音频       → binary framed message
```

## 3. AI Session 必要字段

```text
protocolVersion
sessionId
sequence
audioFormat
payloadLength
messageType
```

握手应协商：

```text
sample rate
channels
PCM/codec
max chunk
ASR/TTS/LLM capability
```

## 4. Family 消息类型方向

```text
device.summary
care.summary
reminder.list
reminder.upsert
reminder.delete
settings.get
settings.update
command.result
heartbeat
```

## 5. Revision

可修改资源建议带：

```text
revision / updatedAt
```

家属端修改旧版本 Reminder 时可以发现冲突。

## 6. 错误

统一错误结构至少包括：

```text
code
message
requestId/sessionId
retryable
```

## 7. 防御性限制

协议 decoder 必须限制：

- frame size；
- audio queue；
- JSON/message nesting；
- 未知 type；
- 过期 session；
- 未鉴权 command。

防止异常对端把 512MB 设备拖垮。