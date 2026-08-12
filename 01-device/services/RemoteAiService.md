# RemoteAiService

[← Services](README.md)

## 1. 定位

宠物侧对“龙芯高性能 AI 推理服务器”的统一业务接口。

上层只看到能力：

```text
Remote ASR
Remote TTS
Remote text inference
optional advanced inference
```

不看到：

```text
当前 Wi-Fi 还是 Bluetooth
服务器内部模型是什么
Socket 如何 framing
```

## 2. 依赖

```text
RemoteAiService
    ↓
AiServerClient
    ↓
ITransport
   ├── NetworkTransport
   └── BluetoothTransport
```

## 3. 连接状态

Service 可以拥有自己的连接/会话状态：

```text
Disconnected
Connecting
Ready
Degraded
```

这些不是 PetStateMachine 的用户交互状态。

## 4. Capability

握手后缓存：

```text
ASR supported
TTS supported
Text inference supported
Protocol version
Audio formats
Maximum chunk/message size
```

并发出 `capabilitiesChanged`。

## 5. API 方向

```cpp
startSpeechSession(...);
sendAudioChunk(...);
finishAudio(...);
cancelSession(...);
requestTextInference(...);
```

事件：

```text
asrPartial
asrFinal
replyText
remoteAudioChunk
sessionFinished
serverUnavailable
```

## 6. 核心原则

Remote AI 是增强能力，不是宠物能否启动的硬依赖。

服务器断线：本地 UI、KWS、Reminder、视觉、本地创意功能仍继续运行。

## 7. Transport fallback

网络和 Bluetooth 的切换由 Connectivity/Client 完成，不能在 UI 写分支。

切换发生在新 session 前最安全；进行中的语音 session 中途切 transport 是否支持，应由协议明确，不要默认无缝。

## 8. 引入版本

V0.3。