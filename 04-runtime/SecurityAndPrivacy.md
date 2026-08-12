# 安全与隐私

[← Runtime](README.md)

LongPet 涉及老人、麦克风、摄像头和家属远程配置，通信边界需要从第一版协议就设计清楚。

## 1. 配对与身份

AI Server 和 Family App 都需要明确的设备身份/配对过程。

不要仅因为“在同一个局域网”就允许任意客户端修改 Reminder。

## 2. Family 命令白名单

允许：

```text
reminder.*
allowed settings.*
care/device query
```

默认拒绝未知命令。

## 3. 不开放

```text
shell
SQL
file browser
arbitrary command execution
raw UART/GPIO
```

## 4. 麦克风

远端 AI 音频上传只在明确语音 session 内发生。

不建议常态把麦克风流发送到服务器。

## 5. 摄像头

人体/手势优先本地推理。

除非未来明确加入远程视觉功能，否则原始 camera frame 不发 AI Server/Family App。

## 6. 消息限制

所有网络 decoder 限制：

- 最大 frame；
- 最大 JSON/control payload；
- 最大音频 queue；
- session 数量；
- 认证失败次数/重试；
- 未知 message type。

这是 512MB 本体防止异常对端耗尽内存的重要措施。

## 7. 凭证

不要在 Git、QSS、普通源代码常量中硬编码长期 token。

配对 secret/证书应保存在受限权限的数据目录中。

## 8. 日志

默认不要记录：

- 原始语音；
- 完整敏感对话；
- 家属凭证；
- camera frame。

开发模式也应做脱敏。