# LongPet 架构决策与约束

[← 根目录](README.md)

## A1. 宠物本体必须可自治

Remote AI Server 和 Family App 都是可选连接。断开时本体保留：

```text
UI / KWS / Reminder / SQLite / basic Vision / Robot / local features
```

## A2. UI 不直接访问能力实现

```text
Page → signal → AppController → Service
```

禁止 Page 直接使用 sherpa、ORT、SQLite、Socket、UART。

## A3. 本地 KWS 与完整 ASR 分离

KWS 常驻本地；完整 ASR 按 speech session 优先交给高性能服务器。

## A4. 一个麦克风 ownership

AudioService 统一持有 capture pipeline，并分别分发给 KWS 和 active remote speech session。

## A5. PetStateMachine 只管理产品高层状态

推荐 `InteractionState + AttentionState`。Network、Bluetooth、HumanPresent 等是上下文，不制造组合状态。

## A6. Remote AI 有 capability handshake

宠物不能把某一版服务器能力写死。ASR/TTS/LLM、audio format、protocol version 都需要协商/版本化。

## A7. Family App 走业务 API，不走数据库同步

所有 Reminder/Settings 修改最终进入对应 Service。Electron 不知道 SQLite schema。

## A8. SQLite 只保存有业务意义的结构化数据

不默认保存 raw PCM、camera frame、每帧 detection、模型 tensor。

## A9. 单核下不并发堆重模型

UI/Audio/KWS 优先。Vision 低频；可选 Local LLM 按需，必要时暂停普通视觉。只有实际出现竞争后再增加 InferenceScheduler。

## A10. 不建立宠物端微服务架构

默认一个 Qt 主进程 + 少量 worker。若复用 Python AI，最多优先考虑一个长期驻留 AI worker，而不是多个临时 Python 进程。

## A11. 只有真实多实现边界才抽接口

`ITransport` 值得，因为有 Network/Bluetooth。

Repository、Service 等如果只有一个实现，不需要机械制造 `Ixxx + Impl + Factory`。

## A12. 使用 Qt signal/slot，不建立全局字符串 EventBus

保持调用链可追踪和类型安全。

## A13. 所有外部会话都可取消和超时

Remote speech、Family command、Robot motion 都不能形成无法中断的长操作。

## A14. 安全优先级最高

Emergency 可以抢占普通 Conversation/Feature；通用 LLM 输出不能作为安全关键动作的唯一判据。

## A15. 日志可关联但不默认保存隐私原始数据

Remote speech 使用 sessionId 关联日志；默认不记录 raw audio/camera/secret。