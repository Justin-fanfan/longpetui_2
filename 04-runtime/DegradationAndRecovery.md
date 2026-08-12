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

## 5. Camera 故障

关闭依赖视觉的 Feature；KWS、Reminder、UI 继续。

## 6. Robot Driver 故障

屏幕宠物继续工作；停止实体动作并记录错误。

## 7. SQLite 故障

- migration 用 transaction；
- 打开失败要有明确 fallback/修复策略；
- 不要因为 Care 查询错误让 UI 主进程直接崩溃。

## 8. Model 加载失败

单个可选模型失败只禁用对应 capability。

例如 Local LLM 加载失败不影响 KWS/Reminder。

## 9. Watchdog

最终长期运行版本可考虑 Buildroot init/watchdog 级自动拉起，但应在主流程稳定后加入，而不是用 watchdog 掩盖崩溃。