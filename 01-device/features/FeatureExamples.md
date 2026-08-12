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

## 4. 久坐陪伴（如果未来有可靠数据）

感知到持续人在场只能作为一个输入，真正产品功能需明确判定规则，不能把低可信模型结果直接当健康结论。

## 5. 设计原则

- 本地可运行；
- 低 CPU；
- 可以中断；
- 不与 Emergency 抢优先级；
- 不大量写数据库；
- 角色表达统一通过 PetBehaviorController。