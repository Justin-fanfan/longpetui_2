# 安全与隐私

[← Runtime](README.md)

LongPet 涉及老人、麦克风、摄像头、家属远程配置和实体运动，因此通信与控制边界需要从第一版协议就设计清楚。

## 1. 配对与身份

AI Server 和 Family App 都需要明确的设备身份/配对过程。

不要仅因为“在同一个局域网”就允许任意客户端修改 Reminder 或控制设备。

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
motor PWM / wheel register
```

## 4. 家属端与运动权限

当前架构下，家属 Electron 应用默认**没有实时驾驶底盘的权限**。

普通 `settings.update`、`command` 或 Reminder 消息不能被扩展成：

```text
forward
turn
left_pwm
right_pwm
```

如果未来确实需要远程驾驶，必须作为独立高风险功能重新设计，包括：

- 更强的鉴权/授权；
- 独立 command namespace；
- 运动 lease/timeout；
- 实时状态反馈；
- 断线自动停车；
- 审计；
- 老人现场提示；
- 必要视频/环境感知边界。

## 5. Remote AI 与运动权限

AI Server 可返回文本、TTS 或高级推理结果，但默认也不能直接控制底盘。

正确链路只能是：

```text
Remote result
→ AppController / validated local feature
→ MotionService
→ MCU
```

Remote AI 不能越过本地安全策略直接发 MCU/UART/PWM。

## 6. 麦克风

远端 AI 音频上传只在明确语音 session 内发生。

不建议常态把麦克风流发送到服务器。

## 7. 摄像头

人体/手势/AutoFollow 基础视觉优先本地推理。

除非未来明确加入远程视觉功能，否则原始 camera frame 不发 AI Server/Family App。

## 8. 消息限制

所有网络 decoder 限制：

- 最大 frame；
- 最大 JSON/control payload；
- 最大音频 queue；
- session 数量；
- 认证失败次数/重试；
- 未知 message type。

这是 512MB 本体防止异常对端耗尽内存的重要措施。

## 9. 凭证

不要在 Git、QSS、普通源代码常量中硬编码长期 token。

配对 secret/证书应保存在受限权限的数据目录中。

## 10. 日志

默认不要记录：

- 原始语音；
- 完整敏感对话；
- 家属凭证；
- camera frame。

运动日志可以记录：

```text
motion source
mode
stop reason
fault code
command/session sequence
```

但不要记录无意义的高频原始控制流直到把存储写满。

开发模式也应做脱敏。