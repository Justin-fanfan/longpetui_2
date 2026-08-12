# SQLite Schema 建议

[← Data](README.md)

字段最终以真实需求为准，以下给出边界清晰的起点。

## reminders

```text
id INTEGER PRIMARY KEY
type
title
time_of_day
repeat_rule
enabled
revision
created_at
updated_at
```

## reminder_events

```text
id
reminder_id
scheduled_at
status
completed_at
```

## care_events

```text
id
event_type
value/source
created_at
```

## settings

```text
key PRIMARY KEY
value
updated_at
```

## paired_devices

```text
id
type             # family / ai-server
identity
credential_ref   # 不建议把敏感 secret 明文直接放这里
last_seen
created_at
```

## schema_meta

保存 schema version。

## 索引

根据真实查询增加，典型包括：

```text
reminders(enabled, time_of_day)
reminder_events(scheduled_at)
care_events(created_at)
```

不要先为每列建索引。

## 不存储

默认不存：

- 原始麦克风音频；
- 摄像头视频/帧；
- ONNX Tensor；
- 大量调试 FPS 样本。

除非某个功能明确需要并有数据保留策略。