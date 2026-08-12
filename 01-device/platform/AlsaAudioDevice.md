# AlsaAudioDevice

[← Platform](README.md)

## 推荐拆分

```text
AlsaAudioInput
AlsaAudioOutput
```

## Input 负责

- `snd_pcm_open`；
- sample rate/channel/format；
- period/buffer；
- capture；
- XRUN recovery；
- timestamp；
- 关闭设备。

## Output 负责

- playback；
- buffer；
- XRUN recovery；
- stop/flush。

## 上层

只把标准化 `AudioFrame` 交给 AudioService。

## 不负责

- KWS；
- Remote protocol；
- TTS 生成；
- PetState。

## 设备占有

尽量由 AudioService 统一创建一次 Input/Output，避免多个 Service 重复打开同一 ALSA device。