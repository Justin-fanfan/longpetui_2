#include "DemoWindow.h"

#include "pages/CarePage.h"
#include "pages/CompanionPage.h"
#include "pages/ConversationPage.h"
#include "pages/EmergencyPage.h"
#include "pages/EngineeringPage.h"
#include "pages/HomePage.h"
#include "pages/ReminderEditPage.h"
#include "pages/ReminderPage.h"
#include "pages/SettingsPage.h"
#include "pages/SleepPage.h"
#include "pages/UiGalleryPage.h"
#include "widgets/VisualComponents.h"
#include "widgets/VisualTokens.h"

#include <QShortcut>
#include <QStackedWidget>
#include <QTimer>
#include <QApplication>
#include <QDir>
#include <QEvent>
#include <QFile>
#include <QTextStream>

DemoWindow::DemoWindow(QWidget* parent)
    : QMainWindow(parent)
{
    setWindowTitle(QStringLiteral("LongPet UI Demo — UI-ONLY PROTOTYPE"));
    setFixedSize(LongPetUi::Metrics::CanvasWidth, LongPetUi::Metrics::CanvasHeight);

    m_stack = new QStackedWidget(this);
    m_stack->setObjectName(QStringLiteral("appRoot"));
    m_stack->setFixedSize(LongPetUi::Metrics::CanvasWidth, LongPetUi::Metrics::CanvasHeight);
    setCentralWidget(m_stack);

    m_companion = new CompanionPage(m_stack);
    m_home = new HomePage(m_stack);
    m_listening = new ConversationPage(ConversationMode::Listening, m_stack);
    m_thinking = new ConversationPage(ConversationMode::Thinking, m_stack);
    m_speaking = new ConversationPage(ConversationMode::Speaking, m_stack);
    m_care = new CarePage(m_stack);
    m_reminder = new ReminderPage(m_stack);
    m_reminderEdit = new ReminderEditPage(m_stack);
    m_settings = new SettingsPage(m_stack);
    m_emergency = new EmergencyPage(m_stack);
    m_sleep = new SleepPage(m_stack);
    m_engineering = new EngineeringPage(m_stack);
    m_gallery = new UiGalleryPage(m_stack);

    const QList<QWidget*> pages = {m_companion, m_home, m_listening, m_thinking, m_speaking,
                                    m_care, m_reminder, m_reminderEdit, m_settings,
                                    m_emergency, m_sleep, m_engineering, m_gallery};
    for (QWidget* page : pages) {
        m_stack->addWidget(page);
    }

    m_controlTimeout = new QTimer(this);
    m_controlTimeout->setSingleShot(true);
    m_controlTimeout->setInterval(12000);
    connect(m_controlTimeout, &QTimer::timeout, this, [this] {
        if (m_stack->currentWidget() == m_home)
            showPage(m_companion);
    });
    m_home->installEventFilter(this);
    for (QObject* child : m_home->findChildren<QObject*>())
        child->installEventFilter(this);

    connectDemoNavigation();
    addDemoShortcuts();
    showPage(m_companion);
}

void DemoWindow::showPage(QWidget* page)
{
    m_stack->setCurrentWidget(page);
    page->setFocus(Qt::OtherFocusReason);
    if (page == m_home)
        m_controlTimeout->start();
    else
        m_controlTimeout->stop();
}

bool DemoWindow::eventFilter(QObject* watched, QEvent* event)
{
    if (m_stack->currentWidget() == m_home
        && (event->type() == QEvent::MouseButtonPress
            || event->type() == QEvent::TouchBegin
            || event->type() == QEvent::KeyPress)) {
        m_controlTimeout->start();
    }
    return QMainWindow::eventFilter(watched, event);
}

void DemoWindow::connectDemoNavigation()
{
    connect(m_companion->revealButton(), &QPushButton::clicked, this, [this] { showPage(m_home); });
    connect(m_home->talkButton(), &QPushButton::clicked, this, [this] { showPage(m_listening); });
    connect(m_home->careButton(), &QPushButton::clicked, this, [this] { showPage(m_care); });
    connect(m_home->reminderButton(), &QPushButton::clicked, this, [this] { showPage(m_reminder); });
    connect(m_home->settingsButton(), &QPushButton::clicked, this, [this] { showPage(m_settings); });

    connect(m_listening->backButton(), &QPushButton::clicked, this, [this] { showPage(m_companion); });
    connect(m_listening->nextButton(), &QPushButton::clicked, this, [this] { showPage(m_thinking); });
    connect(m_thinking->backButton(), &QPushButton::clicked, this, [this] { showPage(m_companion); });
    connect(m_thinking->nextButton(), &QPushButton::clicked, this, [this] { showPage(m_speaking); });
    connect(m_speaking->backButton(), &QPushButton::clicked, this, [this] { showPage(m_companion); });
    connect(m_speaking->nextButton(), &QPushButton::clicked, this, [this] { showPage(m_companion); });

    connect(m_care->backButton(), &QPushButton::clicked, this, [this] { showPage(m_home); });
    connect(m_care->reminderButton(), &QPushButton::clicked, this, [this] { showPage(m_reminder); });
    connect(m_reminder->backButton(), &QPushButton::clicked, this, [this] { showPage(m_home); });
    connect(m_reminder->editButton(), &QPushButton::clicked, this, [this] { showPage(m_reminderEdit); });
    connect(m_reminderEdit->backButton(), &QPushButton::clicked, this, [this] { showPage(m_reminder); });
    connect(m_reminderEdit->cancelButton(), &QPushButton::clicked, this, [this] { showPage(m_reminder); });
    connect(m_reminderEdit->saveButton(), &QPushButton::clicked, this, [this] {
        m_reminderEdit->toast()->showMessage(QStringLiteral("已保存这条提醒（仅 UI Demo）"), 900);
        QTimer::singleShot(780, this, [this] { showPage(m_reminder); });
    });
    connect(m_settings->backButton(), &QPushButton::clicked, this, [this] { showPage(m_home); });

    connect(m_emergency->okayButton(), &QPushButton::clicked, this, [this] { showPage(m_companion); });
    connect(m_emergency->contactButton(), &QPushButton::clicked, this, [this] {
        m_emergency->toast()->showMessage(QStringLiteral("仅演示选择：不会拨号或发送消息"));
    });
    connect(m_sleep->wakeButton(), &QPushButton::clicked, this, [this] { showPage(m_home); });
    connect(m_engineering->backButton(), &QPushButton::clicked, this, [this] { showPage(m_gallery); });

    connect(m_gallery->companionButton(), &QPushButton::clicked, this, [this] { showPage(m_companion); });
    connect(m_gallery->listeningButton(), &QPushButton::clicked, this, [this] { showPage(m_listening); });
    connect(m_gallery->thinkingButton(), &QPushButton::clicked, this, [this] { showPage(m_thinking); });
    connect(m_gallery->speakingButton(), &QPushButton::clicked, this, [this] { showPage(m_speaking); });
    connect(m_gallery->homeButton(), &QPushButton::clicked, this, [this] { showPage(m_home); });
    connect(m_gallery->emergencyButton(), &QPushButton::clicked, this, [this] { showPage(m_emergency); });
    connect(m_gallery->sleepButton(), &QPushButton::clicked, this, [this] { showPage(m_sleep); });
    connect(m_gallery->engineeringButton(), &QPushButton::clicked, this, [this] { showPage(m_engineering); });
}

void DemoWindow::addDemoShortcuts()
{
    const QList<QPair<QKeySequence, QWidget*>> shortcuts = {
        {QKeySequence(QStringLiteral("Shift+F1")), m_companion},
        {QKeySequence(Qt::Key_F1), m_home},
        {QKeySequence(Qt::Key_F2), m_listening},
        {QKeySequence(Qt::Key_F3), m_thinking},
        {QKeySequence(Qt::Key_F4), m_speaking},
        {QKeySequence(Qt::Key_F5), m_care},
        {QKeySequence(Qt::Key_F6), m_reminder},
        {QKeySequence(Qt::Key_F7), m_reminderEdit},
        {QKeySequence(Qt::Key_F8), m_settings},
        {QKeySequence(Qt::Key_F9), m_sleep},
        {QKeySequence(Qt::Key_F10), m_emergency},
        {QKeySequence(Qt::Key_F11), m_engineering},
        {QKeySequence(Qt::Key_F12), m_gallery}
    };
    for (const auto& entry : shortcuts) {
        auto* shortcut = new QShortcut(entry.first, this);
        connect(shortcut, &QShortcut::activated, this, [this, page = entry.second] { showPage(page); });
    }
}

QStringList DemoWindow::captureAllPages(const QString& directory)
{
    QDir outputDir(directory);
    if (!outputDir.exists() && !outputDir.mkpath(QStringLiteral(".")))
        return {};

    struct CaptureEntry { QString name; QWidget* page; int galleryTab = -1; };
    const QList<CaptureEntry> pages = {
        {QStringLiteral("01-companion.png"), m_companion},
        {QStringLiteral("02-control-touch-reveal.png"), m_home},
        {QStringLiteral("03-listening.png"), m_listening},
        {QStringLiteral("04-thinking.png"), m_thinking},
        {QStringLiteral("05-speaking.png"), m_speaking},
        {QStringLiteral("06-care.png"), m_care},
        {QStringLiteral("07-reminder.png"), m_reminder},
        {QStringLiteral("08-reminder-edit.png"), m_reminderEdit},
        {QStringLiteral("09-settings.png"), m_settings},
        {QStringLiteral("10-emergency.png"), m_emergency},
        {QStringLiteral("11-sleep.png"), m_sleep},
        {QStringLiteral("12-engineering.png"), m_engineering},
        {QStringLiteral("13-ui-gallery-faces.png"), m_gallery, 0},
        {QStringLiteral("14-ui-gallery-components.png"), m_gallery, 1},
        {QStringLiteral("15-ui-gallery-tokens.png"), m_gallery, 2}
    };

    QStringList captured;
    QStringList diagnostics;
    for (const auto& entry : pages) {
        if (entry.galleryTab >= 0)
            m_gallery->setGalleryTab(entry.galleryTab);
        showPage(entry.page);
        QApplication::processEvents(QEventLoop::AllEvents, 80);
        const QString path = outputDir.filePath(entry.name);
        const QPixmap image = m_stack->grab(QRect(0, 0,
            LongPetUi::Metrics::CanvasWidth, LongPetUi::Metrics::CanvasHeight));
        const QSize targetSize(LongPetUi::Metrics::CanvasWidth, LongPetUi::Metrics::CanvasHeight);
        const QSize logicalSize = image.deviceIndependentSize().toSize();
        const bool sizeOk = logicalSize == targetSize;
        const QPixmap outputImage = image.size() == targetSize
            ? image : image.scaled(targetSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        const bool saved = outputImage.save(path, "PNG");
        diagnostics.append(QStringLiteral("%1 logical=%2x%3 native=%4x%5 saved=%6")
            .arg(entry.name).arg(logicalSize.width()).arg(logicalSize.height())
            .arg(image.width()).arg(image.height()).arg(saved));
        if (sizeOk && saved) {
            captured.append(path);
        }
    }

    QFile manifest(outputDir.filePath(QStringLiteral("capture-manifest.txt")));
    if (manifest.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&manifest);
        stream << "LongPet UI Demo capture\n";
        stream << "Canvas: 1024x600\n";
        stream << "Pages: " << captured.size() << "/" << pages.size() << "\n";
        for (const QString& path : captured)
            stream << path << "\n";
        for (const QString& diagnostic : diagnostics)
            stream << diagnostic << "\n";
    }
    showPage(m_companion);
    return captured;
}
