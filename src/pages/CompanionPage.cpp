#include "CompanionPage.h"

#include "widgets/PetFaceWidget.h"

#include <QPushButton>
#include <QVBoxLayout>

CompanionPage::CompanionPage(QWidget* parent)
    : QWidget(parent)
{
    setProperty("page", true);
    setObjectName(QStringLiteral("companionPage"));

    auto* root = new QVBoxLayout(this);
    root->setContentsMargins(0, 0, 0, 0);
    root->addWidget(new PetFaceWidget(PetExpression::Speaking, this));

    m_revealButton = new QPushButton(this);
    m_revealButton->setProperty("role", "companionReveal");
    m_revealButton->setGeometry(0, 0, 1024, 600);
    m_revealButton->setFocusPolicy(Qt::NoFocus);
    m_revealButton->setAccessibleName(QStringLiteral("显示控制界面"));
    m_revealButton->raise();
}

QPushButton* CompanionPage::revealButton() const { return m_revealButton; }
