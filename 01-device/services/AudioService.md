# AudioService

[← Services](README.md)

## 1. 为什么需要统一 AudioService

LongPet 至少有两个消费者需要麦克风：

```text
本地 Keyword Spotting
远端 ASR 音频上传
```

如果二者各自打开 ALSA 设备，会产生设备抢占、格式不一致和重复缓冲问题。

因此推荐由 AudioService **统一拥有一个 capture pipeline**。

## 2. 职责

- 启动/停止底层 AudioInput；
- 统一 sample format；
- 将 PCM 送给 KWS；
- 语音会话期间额外将 PCM 送给 VoiceInteraction/RemoteAi；
- 管理 AudioOutput；
- 播放远端 TTS PCM/音频块；
- bounded buffer；
- XRUN/error 上报；
- TTS 播放期间的 KWS 抑制策略。

## 3. 推荐数据流

```text
ALSA Capture
   ↓
AudioService
   ├── always → KeywordSpottingService
   └── active speech session → VoiceInteractionService
```

播放：

```text
Remote TTS chunk
→ VoiceInteractionService
→ AudioService
→ ALSA Playback
```

## 4. 自触发问题

宠物播放 TTS 时，麦克风可能重新听到自己的声音。

V0.x 最简单策略可以是：

```text
Speaking playback期间暂时 gate KWS
```

未来若加入回声消除，再调整。

## 5. Buffer 原则

- 队列必须有上限；
- 网络慢时不能无限堆 PCM；
- TTS jitter buffer 也必须有最大时长；
- Emergency/cancel 时能立即清空当前 session buffer。

## 6. 不负责

- 识别关键词；
- Remote protocol；
- TTS 生成；
- UI 状态。

## 7. 引入版本

V0.3 语音链路开发时。