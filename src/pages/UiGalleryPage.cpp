#include "UiGalleryPage.h"

#include "widgets/PetFaceWidget.h"
#include "widgets/VisualComponents.h"
#include "widgets/VisualTokens.h"

#include <QButtonGroup>
#include <QFrame>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QProgressBar>
#include <QPushButton>
#include <QSlider>
#include <QStackedWidget>
#include <QStyle>
#include <QVBoxLayout>

namespace {
class FaceTile final : public QPushButton {
public:
    FaceTile(PetExpression expression, QWidget* parent)
        : QPushButton(parent), m_face(new PetFaceWidget(expression, this))
    {
        setObjectName(QStringLiteral("faceTile"));
        setProperty("selected", false);
        setFixedHeight(194);
        auto* layout = new QVBoxLayout(this);
        layout->setContentsMargins(6, 8, 6, 10);
        layout->setSpacing(2);
        m_face->setCompact(true);
        m_face->setBackgroundColor(LongPetUi::Colors::Surface);
        m_face->setAnimationEnabled(false);
        m_face->setAttribute(Qt::WA_TransparentForMouseEvents, true);
        layout->addWidget(m_face, 1);
        auto* label = makeLabel(PetFaceWidget::expressionNameEn(expression)
            + QStringLiteral("\n") + PetFaceWidget::expressionName(expression), "engineering", this);
        label->setAlignment(Qt::AlignCenter);
        label->setAttribute(Qt::WA_TransparentForMouseEvents, true);
        layout->addWidget(label);
    }

    void setSelected(bool selected, bool animate = true)
    {
        setProperty("selected", selected);
        m_face->setBackgroundColor(selected
            ? LongPetUi::Colors::SurfaceSecondary : LongPetUi::Colors::Surface);
        m_face->setAnimationEnabled(selected && animate);
        style()->unpolish(this);
        style()->polish(this);
        update();
    }

private:
    PetFaceWidget* m_face;
};

QFrame* swatch(const QString& name, const QString& color, QWidget* parent)
{
    auto* card = new QFrame(parent);
    card->setProperty("card", true);
    card->setFixedHeight(78);
    auto* layout = new QVBoxLayout(card);
    layout->setContentsMargins(12, 8, 12, 8);
    layout->setSpacing(4);
    auto* colorBar = new QFrame(card);
    colorBar->setFixedHeight(24);
    colorBar->setStyleSheet(QStringLiteral("background:%1;border-radius:8px;").arg(color));
    layout->addWidget(colorBar);
    auto* label = makeLabel(name + QStringLiteral("  ") + color, "engineering", card);
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);
    return card;
}
}

UiGalleryPage::UiGalleryPage(QWidget* parent)
    : QWidget(parent)
{
    setProperty("page", true);
    auto* root = new QVBoxLayout(this);
    root->setContentsMargins(32, 16, 32, 20);
    root->setSpacing(12);

    auto* header = new QHBoxLayout;
    auto* badge = new QLabel(QStringLiteral("DESIGN REVIEW"), this);
    badge->setObjectName(QStringLiteral("reviewBadge"));
    header->addWidget(badge);
    header->addWidget(makeLabel(QStringLiteral("UI Gallery"), "pageTitle", this));
    header->addStretch();

    auto* tabs = new QButtonGroup(this);
    tabs->setExclusive(true);
    const QStringList tabNames = {QStringLiteral("宠物表情"), QStringLiteral("组件"), QStringLiteral("设计令牌")};
    for (int i = 0; i < tabNames.size(); ++i) {
        auto* button = new QPushButton(tabNames[i], this);
        button->setProperty("role", "devTab");
        button->setCheckable(true);
        button->setChecked(i == 0);
        button->setFixedHeight(64);
        tabs->addButton(button, i);
        m_tabButtons.append(button);
        header->addWidget(button);
    }
    root->addLayout(header);

    m_stack = new QStackedWidget(this);
    m_stack->addWidget(createFacesPage());
    m_stack->addWidget(createComponentsPage());
    m_stack->addWidget(createTokensPage());
    root->addWidget(m_stack, 1);
    connect(tabs, &QButtonGroup::idClicked, m_stack, &QStackedWidget::setCurrentIndex);
    m_toast = new ToastWidget(this);
}

QWidget* UiGalleryPage::createFacesPage()
{
    auto* page = new QWidget(this);
    auto* grid = new QGridLayout(page);
    grid->setContentsMargins(0, 0, 0, 0);
    grid->setHorizontalSpacing(12);
    grid->setVerticalSpacing(16);
    const QList<PetExpression> expressions = {
        PetExpression::Default, PetExpression::DefaultOpen, PetExpression::Playful,
        PetExpression::Happy, PetExpression::Worried, PetExpression::Angry,
        PetExpression::Sleep, PetExpression::Listening, PetExpression::Thinking,
        PetExpression::Speaking, PetExpression::Alert, PetExpression::CuteCat
    };
    QList<FaceTile*> tiles;
    for (int i = 0; i < expressions.size(); ++i) {
        auto* tile = new FaceTile(expressions[i], page);
        tiles.append(tile);
        grid->addWidget(tile, i / 6, i % 6);
        connect(tile, &QPushButton::clicked, page, [tiles, tile] {
            for (FaceTile* candidate : tiles)
                candidate->setSelected(candidate == tile);
        });
    }
    tiles.first()->setSelected(true, false);
    return page;
}

QWidget* UiGalleryPage::createComponentsPage()
{
    auto* page = new QWidget(this);
    auto* grid = new QGridLayout(page);
    grid->setContentsMargins(0, 0, 0, 0);
    grid->setHorizontalSpacing(16);
    grid->setVerticalSpacing(12);

    auto* normal = new QPushButton(QStringLiteral("Button Normal"), page);
    normal->setProperty("role", "primary");
    auto* pressed = new QPushButton(QStringLiteral("Button Pressed"), page);
    pressed->setProperty("role", "primary");
    pressed->setDown(true);
    auto* disabled = new QPushButton(QStringLiteral("Button Disabled"), page);
    disabled->setEnabled(false);
    auto* danger = new QPushButton(QStringLiteral("Danger Button"), page);
    danger->setProperty("role", "danger");
    grid->addWidget(normal, 0, 0);
    grid->addWidget(pressed, 1, 0);
    grid->addWidget(disabled, 2, 0);
    grid->addWidget(danger, 3, 0);

    auto* card = new SectionCard(page);
    card->contentLayout()->addWidget(makeLabel(QStringLiteral("Section Card"), "body", card));
    card->contentLayout()->addWidget(makeLabel(QStringLiteral("大留白、低密度、无阴影"), "assist", card));
    grid->addWidget(card, 0, 1, 2, 1);
    grid->addWidget(new ReminderItem(QStringLiteral("12:00"), QStringLiteral("喝水"),
        QStringLiteral(":/icons/water.svg"), ReminderVisualState::Pending, page), 2, 1, 1, 2);

    auto* slider = new QSlider(Qt::Horizontal, page);
    slider->setRange(0, 100);
    slider->setValue(60);
    slider->setFixedWidth(180);
    grid->addWidget(new SettingRow(QStringLiteral(":/icons/volume.svg"), QStringLiteral("Setting Row"),
        QStringLiteral("Demo slider"), slider, page), 0, 2, 2, 1);
    auto* toastButton = new QPushButton(QStringLiteral("显示 Toast"), page);
    toastButton->setProperty("role", "secondary");
    auto* componentNote = makeLabel(QStringLiteral("Toast · Cards · ReminderItem\n所有状态只用于视觉审核"), "assist", page);
    auto* bottomRow = new QHBoxLayout;
    bottomRow->setSpacing(16);
    bottomRow->addWidget(toastButton);
    bottomRow->addWidget(componentNote, 1);
    grid->addLayout(bottomRow, 3, 1, 1, 2);
    connect(toastButton, &QPushButton::clicked, page, [this] {
        if (m_toast)
            m_toast->showMessage(QStringLiteral("这是一个本地 UI Demo Toast"));
    });
    return page;
}

QWidget* UiGalleryPage::createTokensPage()
{
    auto* page = new QWidget(this);
    auto* root = new QVBoxLayout(page);
    root->setContentsMargins(0, 0, 0, 0);
    root->setSpacing(12);
    auto* colors = new QGridLayout;
    colors->setSpacing(10);
    const QList<QPair<QString, QString>> tokens = {
        {QStringLiteral("Background"), QStringLiteral("#121210")},
        {QStringLiteral("Surface"), QStringLiteral("#23211E")},
        {QStringLiteral("Text"), QStringLiteral("#F6F1E7")},
        {QStringLiteral("Accent"), QStringLiteral("#F2B84B")},
        {QStringLiteral("Success"), QStringLiteral("#82C9A5")},
        {QStringLiteral("Warning"), QStringLiteral("#E4BE72")},
        {QStringLiteral("Danger"), QStringLiteral("#EF7B70")},
        {QStringLiteral("Divider"), QStringLiteral("#3C3934")}
    };
    for (int i = 0; i < tokens.size(); ++i)
        colors->addWidget(swatch(tokens[i].first, tokens[i].second, page), i / 4, i % 4);
    root->addLayout(colors);

    auto* typeCard = new SectionCard(page);
    auto* typeRow = new QHBoxLayout;
    typeRow->addWidget(makeLabel(QStringLiteral("页面标题 32"), "pageTitle", typeCard));
    typeRow->addStretch();
    typeRow->addWidget(makeLabel(QStringLiteral("正文 24"), "body", typeCard));
    typeRow->addStretch();
    typeRow->addWidget(makeLabel(QStringLiteral("辅助文字 20"), "assist", typeCard));
    typeCard->contentLayout()->addLayout(typeRow);
    root->addWidget(typeCard);

    auto* navLabel = makeLabel(QStringLiteral("Companion 交互流程（仅 UI Demo）"), "assist", page);
    root->addWidget(navLabel);
    auto* interactionNav = new QHBoxLayout;
    interactionNav->setSpacing(10);
    m_companionButton = new QPushButton(QStringLiteral("Companion"), page);
    m_listeningButton = new QPushButton(QStringLiteral("Listening"), page);
    m_thinkingButton = new QPushButton(QStringLiteral("Thinking"), page);
    m_speakingButton = new QPushButton(QStringLiteral("Speaking"), page);
    m_homeButton = new QPushButton(QStringLiteral("Control"), page);
    for (QPushButton* button : {m_companionButton, m_listeningButton, m_thinkingButton,
                                m_speakingButton, m_homeButton}) {
        button->setProperty("role", "demoLink");
        interactionNav->addWidget(button, 1);
    }
    root->addLayout(interactionNav);

    auto* supportingNav = new QHBoxLayout;
    supportingNav->setSpacing(10);
    m_emergencyButton = new QPushButton(QStringLiteral("Emergency"), page);
    m_sleepButton = new QPushButton(QStringLiteral("Sleep"), page);
    m_engineeringButton = new QPushButton(QStringLiteral("Engineering"), page);
    for (QPushButton* button : {m_emergencyButton, m_sleepButton, m_engineeringButton}) {
        button->setProperty("role", "demoLink");
        supportingNav->addWidget(button, 1);
    }
    root->addLayout(supportingNav);
    root->addStretch();
    return page;
}

QPushButton* UiGalleryPage::companionButton() const { return m_companionButton; }
QPushButton* UiGalleryPage::listeningButton() const { return m_listeningButton; }
QPushButton* UiGalleryPage::thinkingButton() const { return m_thinkingButton; }
QPushButton* UiGalleryPage::speakingButton() const { return m_speakingButton; }
QPushButton* UiGalleryPage::homeButton() const { return m_homeButton; }
QPushButton* UiGalleryPage::emergencyButton() const { return m_emergencyButton; }
QPushButton* UiGalleryPage::sleepButton() const { return m_sleepButton; }
QPushButton* UiGalleryPage::engineeringButton() const { return m_engineeringButton; }

void UiGalleryPage::setGalleryTab(int index)
{
    if (m_stack && index >= 0 && index < m_stack->count()) {
        m_stack->setCurrentIndex(index);
        if (index < m_tabButtons.size())
            m_tabButtons[index]->setChecked(true);
    }
}
