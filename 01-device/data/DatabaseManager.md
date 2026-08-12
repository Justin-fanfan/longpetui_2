# DatabaseManager

[← Data](README.md)

## 职责

- 创建/打开数据库；
- schema version；
- migration；
- PRAGMA 初始化；
- transaction helper；
- 统一 DB error；
- 关闭与恢复。

## 推荐选择

如果 Buildroot target 已包含 QtSql + QSQLITE plugin，可优先：

```text
Qt6::Sql
QSqlDatabase
QSqlQuery
```

若 rootfs 没有 QtSql，则直接封装 sqlite3 C API。

**二选一**，不要长期并存两套数据库访问方式。

## 线程

QSqlDatabase connection 与线程关联。若后续引入 DB worker，应为该线程单独创建 connection，不要把同一 connection 任意跨线程使用。

## Migration

```text
schema_version 1 → 2 → 3
```

每次升级用 transaction，并在板端做断电/失败恢复测试。

## 不负责

Reminder 查询业务、Care 聚合等由 Repository/Service 完成。