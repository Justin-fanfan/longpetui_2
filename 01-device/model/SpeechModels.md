# Speech / AI Models

[← Model](README.md)

## AudioFormat

```text
sampleRate
channels
sampleFormat/encoding
```

Audio format 必须由 AudioService/Remote handshake 统一，不能在页面里写死。

## SpeechSessionId

每次远端语音交互拥有唯一 session id，用于关联 audio/asr/reply/tts/cancel。

## Transcript

```text
text
isFinal
optional confidence
```

## AiReply

```text
text
optional metadata
```

TTS 二进制音频不要塞入长生命周期 Model；应以 bounded chunk 流传递。

## RemoteAiCapabilities

```text
protocolVersion
supportsAsr
supportsTts
supportsTextInference
supportedAudioFormats
limits
```

连接握手后更新。