#include "HomePage.h"

#include "widgets/PetFaceWidget.h"
#include "widgets/VisualComponents.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

HomePage::HomePage(QWidget* parent)
    : QWidget(parent)
{
    setProperty("page", true);
    setObjectName(QStringLiteral("appRoot"));
    auto* root = new QVBoxLayout(this);
    root->setContentsMargins(0, 0, 0, 32);
    root->setSpacing(0);

    auto* status = new StatusBarWidget(true, this);
    m_settingsButton = status->settingsButton();
    root->addWidget(status);
    root->addSpacing(8);

    auto* face = new PetFaceWidget(PetExpression::DefaultOpen, this);
    face->setFixedHeight(292);
    root->addWidget(face);

    auto* message = makeLabel(QStringLiteral("下午好，我一直在呢"), "petState", this);
    message->setAlignment(Qt::AlignCenter);
    message->setFixedHeight(56);
    root->addWidget(message);
    root->addStretch(1);

    auto* buttons = new QHBoxLayout;
    buttons->setContentsMargins(32, 0, 32, 0);
    buttons->setSpacing(16);
    m_talkButton = new LargeActionButton(QStringLiteral("陪我说话"),
        QStringLiteral(":/icons/microphone-dark.svg"), "primary", this);
    m_careButton = new LargeActionButton(QStringLiteral("今日关怀"),
        QStringLiteral(":/icons/care.svg"), "secondary", this);
    m_reminderButton = new LargeActionButton(QStringLiteral("提醒"),
        QStringLiteral(":/icons/reminder.svg"), "secondary", this);
    m_talkButton->setFixedHeight(96);
    m_careButton->setFixedHeight(96);
    m_reminderButton->setFixedHeight(96);
    buttons->addWidget(m_talkButton, 1);
    buttons->addWidget(m_careButton, 1);
    buttons->addWidget(m_reminderButton, 1);
    root->addLayout(buttons);
}

QPushButton* HomePage::talkButton() const { return m_talkButton; }
QPushButton* HomePage::careButton() const { return m_careButton; }
QPushButton* HomePage::reminderButton() const { return m_reminderButton; }
QPushButton* HomePage::settingsButton() const { return m_settingsButton; }
