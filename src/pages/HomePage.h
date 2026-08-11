#pragma once

#include <QWidget>

class QPushButton;

class HomePage final : public QWidget {
public:
    explicit HomePage(QWidget* parent = nullptr);

    QPushButton* talkButton() const;
    QPushButton* careButton() const;
    QPushButton* reminderButton() const;
    QPushButton* settingsButton() const;

private:
    QPushButton* m_talkButton = nullptr;
    QPushButton* m_careButton = nullptr;
    QPushButton* m_reminderButton = nullptr;
    QPushButton* m_settingsButton = nullptr;
};
