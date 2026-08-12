# LocalLanguageService（可选）

[← Services](README.md)

## 1. 定位

封装宠物本体可选的几十 MB 级小语言模型。

它是离线增强能力，不应成为 LongPet 基础运行依赖。

## 2. 合适用途

- 简单意图归类；
- 短文本本地回复；
- 本地创意功能中的小型语言处理；
- Remote AI 不可用时的有限降级。

## 3. 不合适用途

- 常驻高频生成；
- 与视觉重模型并行抢单核 CPU；
- 安全关键 Emergency 唯一判定；
- 试图替代高性能 AI Server 的全部能力。

## 4. 生命周期

推荐支持 lazy load：

```text
首次真正需要 → load
内存压力/长期闲置 → 可选 unload
```

是否常驻由真实 RSS 和加载时间实测决定。

## 5. 推理限制

- context 限长；
- output token 限长；
- 放 Heavy Inference Worker；
- 运行时普通 Vision 可降频/暂停。

## 6. API

```cpp
void infer(LocalLanguageRequest request);

signals:
    void resultReady(LocalLanguageResult);
    void failed(...);
```

## 7. Provider 顺序

```text
Remote AI
→ LocalLanguageService（若启用）
→ Rule/Template
```

## 8. 引入条件

只有板端实际证明内存、延迟和 CPU 都可接受才启用生产配置。