# VoiceInteractionService

[← Services](README.md)

## 1. 定位

封装“一次从开始听到播放回复结束”的语音业务会话。

如果把所有音频 chunk、Remote AI session、取消、timeout 都写进 AppController，Controller 会迅速膨胀，因此远端语音稳定后建议提取该 Service。

## 2. 会话状态

```text
Idle
Starting
Capturing
WaitingResult
ReceivingReply
Playing
Cancelling
Failed
```

这些是**语音会话内部状态**，不要放进 PetStateMachine。

## 3. 依赖

```text
AudioService
RemoteAiService
AiCapabilityPolicy（可选）
```

## 4. 典型流程

```text
start()
→ RemoteAiService.startSpeechSession
→ AudioService fork PCM to session
→ send chunks
→ endpoint / finish capture
→ wait ASR/reply
→ receive TTS chunks
→ AudioService playback
→ finished
```

## 5. 输出给 AppController

```cpp
signals:
    void listeningStarted();
    void transcriptUpdated(QString text, bool final);
    void thinkingStarted();
    void replyTextReady(QString text);
    void speakingStarted();
    void finished();
    void failed(VoiceError error);
```

AppController 再将这些映射到 PetStateMachine。

## 6. Endpointing

“用户何时说完”可以由：

- 服务器端 VAD；
- 本地 VAD；
- 固定最大时长；
- 用户手动结束；

组合决定。架构不应把某一种 VAD 写死在 UI。

## 7. Cancel

必须支持：

```text
Emergency
用户取消
页面退出
服务器失联
```

立即取消当前 session 和 audio playback。

## 8. 引入版本

V0.3 早期可先由 AppController 编排；会话复杂后提取。