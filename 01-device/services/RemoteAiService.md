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

当项目真正出现多链路发现、链路评分和 fallback 后，可由 `ConnectivityManager` 为 `AiServerClient` 提供候选端点和推荐 Transport。

## 3. 状态所有权

需要把“链路状态”和“Remote AI 能力状态”分开，避免与 `ConnectivityManager` 重复维护同一事实。

### ConnectivityManager 负责

```text
Network available
Bluetooth available
AI server endpoint discovered
selected/preferred transport
last successful endpoint
```

### AiServerClient / RemoteAiService 负责

```text
Client disconnected/connecting
Protocol handshake
Remote AI ready/degraded
Current speech session
Server capabilities
```

也就是说：

> ConnectivityManager 回答“现在有什么链路/端点可以尝试”；RemoteAiService 回答“远端 AI 能力现在是否真的可用”。

这些状态都不是 `PetStateMachine` 的用户交互状态。

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

不要仅凭“TCP/Bluetooth 已连接”就认为 ASR/TTS 一定可用，必须以协议握手和 capability 为准。

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

网络和 Bluetooth 的候选选择由 Connectivity/Client 完成，不能在 UI 写分支。

切换发生在新 session 前最安全；进行中的语音 session 中途切 transport 是否支持，应由协议明确，不要默认无缝迁移。

如果当前版本只有一个固定网络地址，可暂时不创建独立 `ConnectivityManager`，由 `RemoteAiService/AiServerClient` 管理即可；等多链路需求真实出现后再提取。

## 8. 引入版本

V0.3。