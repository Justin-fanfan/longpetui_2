# 本地创意功能示例

[← Features](README.md)

这些是架构示例，不代表必须全部实现。

## 1. 挥手回应

```text
PerceptionService: Wave
→ FeatureCoordinator
→ State允许
→ PetFace Playful
→ Robot nod/lookAtUser
```

## 2. 离线关键词动作

```text
KWS: “你好”
Remote AI unavailable
→ 本地固定回复/表情
→ optional Robot action
```

## 3. 温和喝水提醒

```text
CareSummary: 今日喝水不足
+ HumanPresent
+ 当前不是 Listening/Emergency
→ Reminder/Feature intent
→ 温和 UI/TTS/动作
```

## 4. 自动跟随用户（后续功能）

正确链路：

```text
PerceptionService
→ stable PersonObservation
→ AutoFollowController
→ MotionIntent
→ MotionService
→ Motion MCU
→ Chassis
```

第一版可以从“只转向对人”开始，再逐步加入低速前后跟随。

关键规则：

- 目标未稳定确认时不移动；
- 目标丢失立即/短延时停车；
- Emergency/Manual 可以抢占；
- 自动跟随默认低速；
- 没有可靠避障能力时只在受控场景开发/演示；
- 不允许 PerceptionService 直接发 UART/PWM。

## 5. 手势停止跟随

如果产品定义 `Stop` 手势可停止跟随：

```text
GestureEvent(Stop)
→ Feature/AppController
→ validate current AutoFollow state
→ disable AutoFollow
→ MotionService.stop(UserGesture)
```

它是一个产品交互规则，不是视觉模型直接成为硬件急停。

## 6. 久坐陪伴（如果未来有可靠数据）

感知到持续人在场只能作为一个输入，真正产品功能需明确判定规则，不能把低可信模型结果直接当健康结论。

## 7. 设计原则

- 本地可运行；
- 低 CPU；
- 可以中断；
- 不与 Emergency 抢优先级；
- 运动必须经过 MotionService；
- 不大量写数据库；
- 角色表达统一通过 PetBehaviorController；
- 视觉自动跟随控制由 AutoFollowController 单独承担，不塞进 PetBehaviorController。