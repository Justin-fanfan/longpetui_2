#pragma once

#include <QList>
#include <QWidget>

class QPushButton;
class QStackedWidget;
class ToastWidget;

class UiGalleryPage final : public QWidget {
public:
    explicit UiGalleryPage(QWidget* parent = nullptr);
    QPushButton* companionButton() const;
    QPushButton* listeningButton() const;
    QPushButton* thinkingButton() const;
    QPushButton* speakingButton() const;
    QPushButton* homeButton() const;
    QPushButton* emergencyButton() const;
    QPushButton* sleepButton() const;
    QPushButton* engineeringButton() const;
    void setGalleryTab(int index);

private:
    QWidget* createFacesPage();
    QWidget* createComponentsPage();
    QWidget* createTokensPage();

    QStackedWidget* m_stack = nullptr;
    QPushButton* m_companionButton = nullptr;
    QPushButton* m_listeningButton = nullptr;
    QPushButton* m_thinkingButton = nullptr;
    QPushButton* m_speakingButton = nullptr;
    QPushButton* m_homeButton = nullptr;
    QPushButton* m_emergencyButton = nullptr;
    QPushButton* m_sleepButton = nullptr;
    QPushButton* m_engineeringButton = nullptr;
    QList<QPushButton*> m_tabButtons;
    ToastWidget* m_toast = nullptr;
};
