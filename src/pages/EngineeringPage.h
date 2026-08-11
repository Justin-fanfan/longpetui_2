#pragma once

#include <QWidget>

class QPushButton;

class EngineeringPage final : public QWidget {
public:
    explicit EngineeringPage(QWidget* parent = nullptr);
    QPushButton* backButton() const;

private:
    QPushButton* m_backButton = nullptr;
};
