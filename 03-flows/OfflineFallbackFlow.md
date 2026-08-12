# AI Server 不可用时的本地降级

[← Flows](README.md)

## 原则

Remote AI 是增强能力，因此离线时应“能力降级”，而不是“产品崩溃”。

## 本地始终可用

```text
Qt UI
PetStateMachine
Keyword Spotting
Reminder / Care
SQLite
基础人体/手势
Robot basic actions
local creative features
```

## 关键词动作

```text
KWS detects local command
 ↓
AppController
 ↓
若该关键词有本地功能
→ 直接执行本地 Feature/Reminder/UI
```

例如固定“你好”“提醒”等功能不一定需要完整 LLM。

## 需要自然语言理解

能力选择：

```text
Remote AI unavailable
 ↓
LocalLanguageService enabled?
 ├── yes → 小模型有限处理
 └── no  → 规则/模板或明确提示
```

## 完整 ASR

如果本体没有完整离线 ASR，不要伪装成有。

应明确：

```text
高级语音暂不可用
```

同时保留可用的关键词入口。

## UI

断线反馈应该产品化，不显示 socket errno 或模型路径。Engineering 页面可额外显示技术错误。