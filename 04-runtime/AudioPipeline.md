# 音频流水线

[← Runtime](README.md)

音频是 LongPet 中最需要避免“各模块各自为政”的资源。

## 1. 推荐唯一 Capture Pipeline

```text
ALSA Input
    ↓
AudioService
    ├── KWS branch（常态）
    └── Remote speech branch（会话期间）
```

不要：

```text
KWS 自己 snd_pcm_open
Remote ASR 又 snd_pcm_open
```

## 2. 常态 Companion

```text
microphone capture
→ local KWS
```

远端不持续收到音频。

## 3. 唤醒后

```text
KWS detected
→ speech session start
→ AudioService 开启 second consumer
→ PCM chunks 上传
```

## 4. 音频格式

统一在 AudioService/handshake 中处理：

```text
sample rate
channels
sample format
remote encoding
```

页面不出现这些参数。

## 5. Queue

所有 PCM/TTS queue 都必须有上限。

网络跟不上时可以：

- 丢弃不可恢复旧数据并失败当前 session；
- 降低/协商码率；
- 明确 timeout。

不能无限占 512MB RAM。

## 6. TTS Playback

```text
Remote audio chunk
→ jitter/bounded buffer
→ AudioService
→ ALSA Output
```

如果 server 支持 streaming，可在缓冲到安全最小量后开始播放，不必等完整文件。

## 7. 自触发

Speaking 期间第一版可以暂停 KWS decision 或 gate 麦克风送 KWS，避免 TTS 触发唤醒词。

## 8. Emergency

必须能立即：

```text
stop remote upload
clear TTS buffer
stop playback
```

然后进入安全状态。