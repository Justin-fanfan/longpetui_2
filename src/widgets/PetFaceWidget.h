#pragma once

#include <QTimer>
#include <QWidget>

class QPainter;

enum class PetExpression {
    Default,
    DefaultOpen,
    Playful,
    Happy,
    Worried,
    Angry,
    Sleep,
    Listening,
    Thinking,
    Speaking,
    Alert,
    CuteCat
};

class PetFaceWidget final : public QWidget {
    Q_OBJECT

public:
    explicit PetFaceWidget(PetExpression expression = PetExpression::Default,
                           QWidget* parent = nullptr);

    PetExpression expression() const;
    void setExpression(PetExpression expression);
    void setAnimationEnabled(bool enabled);
    bool animationEnabled() const;
    void setCompact(bool compact);

    static QString expressionName(PetExpression expression);
    static QString expressionNameEn(PetExpression expression);

protected:
    void paintEvent(QPaintEvent* event) override;
    void showEvent(QShowEvent* event) override;
    void hideEvent(QHideEvent* event) override;

private:
    void syncTimer();
    void drawOpenEye(QPainter& painter, const QPointF& center, const QSizeF& size,
                     qreal pupilOffsetX = 0.0, bool blink = false) const;
    void drawClosedEye(QPainter& painter, qreal centerX, qreal centerY,
                       qreal halfWidth, bool happyArc) const;
    void drawExpression(QPainter& painter, bool blink) const;

    PetExpression m_expression;
    QTimer m_timer;
    int m_tick = 0;
    bool m_animationEnabled = true;
    bool m_compact = false;
};
