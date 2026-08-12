# 本地 KWS → 远端 ASR / 推理 / TTS

[← Flows](README.md)

## 1. 唤醒

```text
ALSA Capture
 ↓
AudioService
 ↓
KeywordSpottingService
 ↓ keywordDetected
AppController
 ↓
PetStateMachine → Listening
```

## 2. 开始远端 speech session

```text
AppController / VoiceInteractionService
 ↓
RemoteAiService.startSpeechSession
 ↓
AiServerClient
 ↓
selected ITransport
```

同时 AudioService 将 active session 的 PCM fork 给 VoiceInteractionService。

## 3. 流式上传

```text
AudioFrame
→ bounded queue
→ speech.audio(sessionId, seq)
→ AI Server
```

不要录几十秒后一次性大包上传，也不要无限排队。

## 4. 识别

Server 可返回：

```text
ASR partial *
ASR final
```

UI 可以显示 partial，但业务意图通常只使用 final。

## 5. Thinking

当用户语音结束并等待回复时：

```text
PetStateMachine → Thinking
```

这是产品视觉状态，不等于 Transport state。

## 6. 回复

Server 返回：

```text
reply text
TTS audio chunks
```

文字可以先更新 ConversationPage。

真正第一段可播放 TTS 开始时：

```text
PetStateMachine → Speaking
```

## 7. 播放

```text
remote TTS chunks
→ bounded jitter buffer
→ AudioService
→ ALSA Output
```

播放期间可暂时 gate KWS，防止自触发。

## 8. 结束

```text
playback finished
→ VoiceInteractionService.finished
→ AppController
→ Speaking → Companion
```

## 9. Cancel

Emergency、用户取消、transport failure 都应清空当前 session 并回到明确状态。