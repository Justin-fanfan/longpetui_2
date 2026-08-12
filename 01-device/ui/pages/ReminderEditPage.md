# ReminderEditPage

[← Pages](README.md)

## 定位

Reminder 新建/编辑表单。

## 输入

```cpp
void setDraft(const ReminderDraft& draft);
```

## 输出

```cpp
signals:
    void saveRequested(const ReminderDraft& draft);
    void cancelRequested();
    void backRequested();
```

## 保存结果

真正保存由 ReminderService/Repository 完成。成功后 Controller 再让页面返回并显示 Toast。

不要出现：

```cpp
QSqlQuery query;
```

直接写在 Page 中。

## 引入版本

V0.2。