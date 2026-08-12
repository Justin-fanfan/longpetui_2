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
- [ ] 不把每帧写 DB；
- [ ] active voice 时测试 CPU。

## 引入 Family App

- [ ] pairing/auth；
- [ ] command whitelist；
- [ ] DTO 而不是 raw DB；
- [ ] Reminder revision；
- [ ] 禁止 raw camera/mic 默认远程访问。

## 发布前

- [ ] Release 板端；
- [ ] UI CPU 基线未退化；
- [ ] RSS 长稳；
- [ ] AI Server 故障降级；
- [ ] Camera/Robot 故障降级；
- [ ] SQLite 恢复；
- [ ] 日志轮转；
- [ ] 密钥不在仓库；
- [ ] 长时间运行验收。