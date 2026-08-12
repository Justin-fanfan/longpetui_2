# 龙芯高性能 AI 推理服务器边界

[← 外部系统](README.md)

## 1. 服务器角色

外部龙芯高性能计算机是 LongPet 的**增强 AI 节点**，主要提供比 2K0300 本体更强的：

- 完整 ASR；
- 高质量 TTS；
- 更强文本/语言推理；
- 后续可选高级 AI 能力。

它不是宠物底盘的实时控制器。

## 2. 宠物侧抽象

宠物侧统一使用：

```text
RemoteAiService
    ↓
AiServerClient
    ↓
NetworkTransport / BluetoothTransport
```

AppController 不知道服务器内部模型，也不知道底层链路。

## 3. 标准远端语音链路

```text
本地麦克风
→ 本地 KWS 唤醒
→ 创建 speech session
→ 流式发送音频
→ Server ASR
→ Server inference
→ 返回文本
→ Server TTS
→ 流式/分块返回音频
→ 宠物播放
```

## 4. 为什么 KWS 仍放在本地

如果连“开始一次远端语音会话”都依赖服务器持续听麦克风：

- 断网后入口消失；
- 常态上传音频增加隐私与流量；
- 链路故障直接破坏基础交互。

因此本地 KWS 是稳定入口，Remote ASR 是会话级增强。

## 5. Capability Negotiation

连接建立后，Server 应返回自身 capability，例如：

```text
protocol version
ASR supported
TTS supported
text inference supported
supported audio formats
maximum chunk size
optional streaming flags
```

宠物不要假设每一版 Server 都支持完全相同功能。

## 6. Network / Bluetooth

两者只是 Transport。

Network 通常适合高带宽音频；Bluetooth 作为近距离/备用链路时，需要根据真实实现测试吞吐和 MTU。

协议必须允许协商：

```text
PCM / optional codec
sample rate
chunk size
```

而不是把 LAN 参数写死到 Bluetooth。

## 7. 与实体运动的边界

Remote AI 可以产生：

```text
文本回复
语义意图建议
高层功能建议
```

但默认不能产生“直接执行的底盘命令”。

禁止：

```text
AI Server
→ UART / PWM / wheel command
```

如果未来远端模型识别出类似“去找老人”“跟随用户”的高层意图，也必须经过宠物本地验证：

```text
Remote result
→ AppController / local validated feature
→ AutoFollowController or other local controller
→ MotionService
→ Motion MCU
```

本地 `MotionService`、MCU watchdog 和安全限制始终拥有最终约束权。

高网络延迟/断线也意味着远端 Server 不适合做实时电机闭环。

## 8. 会话取消

以下场景必须可以取消 Remote Session：

- 用户取消；
- Emergency；
- 页面/状态改变；
- server timeout；
- transport 断开；
- 新的高优先级交互。

Server 迟到的旧 session 数据必须通过 `sessionId` 丢弃。

## 9. 断线降级

```text
AI Server unavailable
├── 本地 KWS继续
├── Reminder/Care继续
├── 本地视觉继续
├── Robot/UI继续
├── Motion/MCU 基础能力继续
├── AutoFollow（若完全本地实现）可继续，受本地安全策略约束
├── 本地小模型（若启用）可有限降级
└── 规则/模板创意功能继续
```

不能出现“AI Server 断开 → 宠物整机不可用”。

## 10. 数据与隐私

默认只在明确的 speech session 内上传所需音频。服务器是否落盘保存音频必须是明确配置，不能由协议实现默认为永久保存。

基础人体/手势/AutoFollow 视觉默认本地处理；未来若上传视觉数据，也需要单独的数据最小化与权限设计。