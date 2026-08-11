#pragma once

#include <QWidget>

class QPushButton;

class CompanionPage final : public QWidget {
public:
    explicit CompanionPage(QWidget* parent = nullptr);
    QPushButton* revealButton() const;

private:
    QPushButton* m_revealButton = nullptr;
};
