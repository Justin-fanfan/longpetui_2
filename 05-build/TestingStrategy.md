# 测试策略

[← Build](README.md)

## 1. 纯 C++ 单元测试

优先测试：

```text
PetStateMachine
Reminder repeat calculation
AiCapabilityPolicy
Protocol codec
DTO validation
```

这些不需要 2K0300 硬件。

## 2. SQLite 测试

使用临时 DB 验证：

- migration；
- Reminder CRUD；
- transaction rollback；
- revision conflict；
- Care summary 查询。

## 3. Transport 测试

提供 Fake/Loopback Transport 验证：

- 分片；
- seq；
- timeout；
- stale session；
- oversize frame；
- reconnect。

## 4. Mock AI Server

建议在 PC 上提供一个简单测试工具：

```text
tools/mock-ai-server/
```

能够：

- 接收 audio；
- 返回固定 ASR；
- 延迟回复；
- 分块 TTS；
- 主动断线；
- 返回错误。

宠物联调不必每次依赖真实大模型服务器。

## 5. Family 测试

可提供 mock family client，验证配对、Reminder 修改和无权限命令拒绝。

## 6. UI 回归

现有 `longpetui_2` 的 capture 工具留在 UI Prototype，继续做 Windows 1024×600 截图回归；不进入生产主路径。

## 7. 板端组合负载

至少测试：

```text
Companion + KWS
KWS + Vision
Remote Listening + Vision
Speaking playback + Vision
Local LLM + UI
Family sync + voice
```

## 8. 故障注入

- AI Server 中途断开；
- Bluetooth 断开；
- Camera unavailable；
- Audio XRUN；
- SQLite write error；
- Robot driver timeout；
- Family 发旧 revision。

## 9. 长稳

最终版本需进行数小时到数十小时级运行测试，观察：

```text
RSS 是否增长
timer 是否泄漏
重连是否循环失控
DB 是否持续膨胀
audio/camera 是否可恢复
UI 是否仍响应
```