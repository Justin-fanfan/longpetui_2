# CarePage

[← Pages](README.md)

## 定位

向老人展示当天的关怀摘要。

## 数据模型

建议页面只接收 `CareSummary`：

```text
喝水完成情况
用药状态
活动摘要
互动摘要
更新时间
```

## 推荐 API

```cpp
void setSummary(const CareSummary& summary);

signals:
    void backRequested();
    void reminderRequested();
```

## 不负责

- 自己统计今天喝了几次水；
- 查 SQLite；
- 同步 Electron；
- 判断异常。

统计统一在 `CareService`，这样宠物 UI 和家属端看到的是同一套业务口径。

## 引入版本

V0.2。