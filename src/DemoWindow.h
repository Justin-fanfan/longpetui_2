#pragma once

#include <QMainWindow>
#include <QStringList>

class QStackedWidget;
class QTimer;
class QEvent;
class CompanionPage;
class HomePage;
class ConversationPage;
class CarePage;
class ReminderPage;
class ReminderEditPage;
class SettingsPage;
class EmergencyPage;
class SleepPage;
class EngineeringPage;
class UiGalleryPage;

class DemoWindow final : public QMainWindow {
public:
    explicit DemoWindow(QWidget* parent = nullptr);
    QStringList captureAllPages(const QString& directory);

protected:
    bool eventFilter(QObject* watched, QEvent* event) override;

private:
    void connectDemoNavigation();
    void addDemoShortcuts();
    void showPage(QWidget* page);

    QStackedWidget* m_stack = nullptr;
    QTimer* m_controlTimeout = nullptr;
    CompanionPage* m_companion = nullptr;
    HomePage* m_home = nullptr;
    ConversationPage* m_listening = nullptr;
    ConversationPage* m_thinking = nullptr;
    ConversationPage* m_speaking = nullptr;
    CarePage* m_care = nullptr;
    ReminderPage* m_reminder = nullptr;
    ReminderEditPage* m_reminderEdit = nullptr;
    SettingsPage* m_settings = nullptr;
    EmergencyPage* m_emergency = nullptr;
    SleepPage* m_sleep = nullptr;
    EngineeringPage* m_engineering = nullptr;
    UiGalleryPage* m_gallery = nullptr;
};
