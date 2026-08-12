# Perception Models

[← Model](README.md)

## PersonObservation

建议只携带上层真正需要的信息：

```text
present
optional boundingBox
optional center / normalizedCenter
confidence
timestamp
optional trackId
optional distanceEstimate
```

若不是 Engineering UI，不必长期保存完整 detection tensor。

### 自动跟随使用时

`PersonObservation` 必须能判断数据是否已经过期，因此 `timestamp` 是重要字段。

如果后续使用目标锁定，可增加轻量 `trackId`；没有可靠 ReID 时不要伪装成“已识别具体老人身份”。

`distanceEstimate` 只有在真实模型/传感器能提供时才存在，不要因为 AutoFollow 需要距离就凭空把它当可靠数据。

## Gesture

使用 enum 表达产品可理解手势：

```text
Wave
ThumbsUp
Stop
Unknown
```

以真实模型能力为准。

### Stop 手势说明

`Gesture::Stop` 是一个视觉语义事件，不应在 PerceptionService 内直接变成电机 Emergency Stop。

正确链路：

```text
GestureEvent(Stop)
→ AppController / CreativeFeature
→ 按产品规则确认
→ MotionService.stop(...)
```

如果未来需要真正安全级手势停车，应单独定义置信度、连续确认、作用范围和失败策略。

## GestureEvent

在 Gesture 基础上带：

```text
timestamp
confidence
optional personId/context
```

PerceptionService 应完成 debounce 后再发出 GestureEvent。

## 边界

Perception Model 描述“视觉看到了什么”，Motion Model 描述“上层希望怎样移动”。

二者不要合并成：

```text
DetectionResult { leftMotorPwm, rightMotorPwm }
```

视觉与运动之间必须经过控制器和 MotionService。