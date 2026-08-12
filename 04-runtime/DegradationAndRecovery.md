# 降级与故障恢复

[← Runtime](README.md)

## 1. Remote AI Server 不可用

继续：

```text
UI
KWS
Reminder/Care
basic Vision
Robot
basic Motion control through MCU
local creative features
optional local LLM
```

完整 ASR/TTS 若无本地实现，则明确提示能力暂不可用。

## 2. AI session 中途掉线

必须：

```text
session timeout/cancel
→ stop audio upload
→ stop TTS buffer/playback
→ discard old session packets
→ user-facing feedback
→ return Companion
```

## 3. Network ↔ Bluetooth

新 session 前可重新选择可用 Transport。

进行中的 session 不要默认支持无缝迁移；除非协议专门实现 session resume。

## 4. Family App 不在线

完全不影响老人本地功能。需要联系家属时若发送失败，UI 必须明确展示失败/重试状态。

家属端离线也不影响 MotionService 或 MCU 本地安全策略。

## 5. Camera / Perception 故障

关闭依赖视觉的 Feature。

如果正在 AutoFollow：

```text
camera/perception stale
→ AutoFollowController loses target
→ MotionService stop
→ AutoFollow disabled / reacquiring
```

KWS、Reminder、UI 继续。

## 6. Robot Driver 故障

屏幕宠物继续工作；停止对应实体表现动作并记录错误。

## 7. Motion MCU / 底盘通信故障

龙芯侧：

```text
Driver timeout / MCU fault
→ MotionService marks unavailable
→ cancel AutoFollow
→ stop issuing normal movement commands
→ report fault
```

MCU 侧必须独立具备：

```text
heartbeat/lease timeout
→ motor stop
```

不能只依赖 Linux 侧发送一次 STOP。

## 8. LongPet 进程退出/崩溃

屏幕和业务自然停止，但底盘必须依靠 MCU watchdog 在通信租约超时后自动停车。

这是运动系统必须单独验证的故障场景。

## 9. MCU reset

MCU reset 后默认：

```text
motion disabled / stopped
```

不能恢复 reset 前的旧运动命令。

龙芯重新完成握手/状态确认后，才允许新的运动。

## 10. SQLite 故障

- migration 用 transaction；
- 打开失败要有明确 fallback/修复策略；
- 不要因为 Care 查询错误让 UI 主进程直接崩溃。

SQLite 故障也不应阻塞 Emergency stop。

## 11. Model 加载失败

单个可选模型失败只禁用对应 capability。

例如 Local LLM 加载失败不影响 KWS/Reminder。

视觉模型失败时，AutoFollow 必须禁用，但手动基础底盘控制是否保留由产品策略决定。

## 12. Watchdog

最终长期运行版本可考虑 Buildroot init/watchdog 级自动拉起，但应在主流程稳定后加入，而不是用 watchdog 掩盖崩溃。

注意系统 watchdog 与运动 MCU watchdog 是两件不同的事：

- 系统 watchdog：让 LongPet 软件/系统恢复；
- MCU watchdog：确保底盘在上层失联时尽快停车。
