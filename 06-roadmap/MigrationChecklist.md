# 架构迁移检查清单

[← Roadmap](README.md)

## 从 UI Prototype 开始

- [ ] 新建正式 `MainWindow : QWidget`；
- [ ] 迁入 PetFaceWidget 优化版；
- [ ] 迁入 VisualComponents/VisualTokens/QSS；
- [ ] Companion 改回 DefaultOpen/Default；
- [ ] 页面按钮 getter 逐步改 semantic signal；
- [ ] DemoWindow/UI Gallery 不进入生产主路径。

## 引入 SQLite

- [ ] DatabaseManager；
- [ ] schema version；
- [ ] Repository；
- [ ] Page 无 SQL；
- [ ] migration 测试。

## 引入 Remote AI

- [ ] AudioService 单一麦克风 ownership；
- [ ] KWS 本地常驻；
- [ ] AiServerClient sessionId/seq；
- [ ] Transport timeout；
- [ ] Remote capability handshake；
- [ ] TTS bounded buffer；
- [ ] disconnect 回 Companion；
- [ ] Speaking 期间 KWS 自触发策略。

## 引入 Vision

- [ ] latest-frame；
- [ ] 低 inference FPS；
- [ ] gesture debounce；
- [ ] PersonObservation 带 timestamp/confidence；
- [ ] 不把每帧写 DB；
- [ ] active voice 时测试 CPU；
- [ ] PerceptionService 不直接操作 UART/电机。

## 引入运动底盘 / MCU

- [ ] 明确龙芯高层控制、MCU 直接控制的边界；
- [ ] MotionService；
- [ ] MotionModels；
- [ ] Driver/MCU protocol version；
- [ ] Stop/Emergency Stop；
- [ ] command/heartbeat lease；
- [ ] MCU watchdog；
- [ ] MCU reset-safe；
- [ ] speed limit；
- [ ] Motion owner arbitration；
- [ ] telemetry/fault 回传；
- [ ] 龙芯进程退出后 MCU 自动停车；
- [ ] 通信断开后 MCU 自动停车；
- [ ] Sleep/Emergency 时禁止运动。

## 引入 AutoFollow

- [ ] AutoFollowController，不让视觉模型直接发运动命令；
- [ ] target acquire/lock；
- [ ] confidence threshold；
- [ ] dead zone / hysteresis；
- [ ] low-speed cap；
- [ ] stale observation stop；
- [ ] target lost stop；
- [ ] Manual/Emergency 抢占；
- [ ] 多人场景目标稳定性；
- [ ] 无可靠避障时只在受控低速场景开发/演示。

## 引入 Family App

- [ ] pairing/auth；
- [ ] command whitelist；
- [ ] DTO 而不是 raw DB；
- [ ] Reminder revision；
- [ ] 禁止 raw camera/mic 默认远程访问；
- [ ] 默认不授予实时底盘驾驶/PWM 权限。

## 发布前

- [ ] Release 板端；
- [ ] UI CPU 基线未退化；
- [ ] RSS 长稳；
- [ ] AI Server 故障降级；
- [ ] Camera/Robot/Motion 故障降级；
- [ ] AutoFollow target-loss 验证；
- [ ] Emergency 运动抢占验证；
- [ ] MCU heartbeat/watchdog 长稳；
- [ ] SQLite 恢复；
- [ ] 日志轮转；
- [ ] 密钥不在仓库；
- [ ] 长时间运行验收；
- [ ] 程序退出/崩溃后底盘必停。
