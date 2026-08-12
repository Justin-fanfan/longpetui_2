# Perception Models

[← Model](README.md)

## PersonObservation

建议只携带上层真正需要的信息：

```text
present
optional boundingBox
confidence
timestamp
```

若不是 Engineering UI，不必长期保存完整 detection tensor。

## Gesture

使用 enum 表达产品可理解手势：

```text
Wave
ThumbsUp
Stop
Unknown
```

以真实模型能力为准。

## GestureEvent

在 Gesture 基础上带：

```text
timestamp
confidence
optional personId/context
```

PerceptionService 应完成 debounce 后再发出 GestureEvent。