# Data / SQLite

[← 宠物本体](../README.md) · [← 根目录](../../README.md)

LongPet 本体使用 SQLite 保存结构化、可恢复的数据。

- [DatabaseManager](DatabaseManager.md)
- [Repositories](Repositories.md)
- [SQLiteSchema](SQLiteSchema.md)
- [PersistenceRules](PersistenceRules.md)

## 规则

```text
Page × SQL
Service → Repository → SQLite
Family App × direct DB
```

模型文件、原始音频、摄像头帧不应塞进 SQLite。