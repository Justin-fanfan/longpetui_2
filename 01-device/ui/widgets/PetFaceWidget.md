# PetFaceWidget

[← Widgets](README.md)

## 1. 定位

LongPet 的核心视觉 Widget：

```text
PetExpression → 宠物脸图形与轻量动画
```

## 2. 当前表情集合

```text
Default
DefaultOpen
Playful
Happy
Worried
Angry
Sleep
Listening
Thinking
Speaking
Alert
CuteCat
```

## 3. 正式 API 边界

允许：

```cpp
setExpression(...)
setAnimationEnabled(...)
setCompact(...)
setBackgroundColor(...)
```

禁止让它知道：

```text
ASR
TTS
Remote AI
SQLite
Family App
Robot
Reminder
```

## 4. 必须继承当前性能优化

- 静态 QImage cache；
- one-shot blink；
- Listening / Thinking / Speaking 使用低刷新率；
- `hideEvent()` 停止 Timer；
- dirty-region update；
- 不使用持续 breathing；
- 不恢复 83 ms 全局整脸 repaint；
- 不引入 QML/OpenGL 仅为了表情。

## 5. 当前实机基线

现阶段优化后，动画页实测 CPU 已控制在约 15% 以内。正式迁移时应把这版作为性能基线，避免视觉合并时退化。

## 6. Companion 使用

长期待机推荐：

```text
DefaultOpen / Default
```

平时 0 FPS，仅偶发 blink。

`Speaking` 只在真正播放 TTS 时使用，不作为永久待机表情。

## 7. 与 PetBehaviorController

`PetBehaviorController` 决定使用哪个 `PetExpression`；`PetFaceWidget` 只负责把这个 expression 画出来。