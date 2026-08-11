#include "EngineeringPage.h"

#include "widgets/VisualComponents.h"

#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>

namespace {
SectionCard* metricCard(const QString& name, const QString& value, QWidget* parent)
{
    auto* card = new SectionCard(parent);
    card->setFixedHeight(86);
    card->contentLayout()->setContentsMargins(20, 12, 20, 12);
    card->contentLayout()->setSpacing(2);
    card->contentLayout()->addWidget(makeLabel(name, "engineering", card));
    auto* valueLabel = makeLabel(value, "body", card);
    card->contentLayout()->addWidget(valueLabel);
    return card;
}
}

EngineeringPage::EngineeringPage(QWidget* parent)
    : QWidget(parent)
{
    setProperty("page", true);
    auto* root = new QVBoxLayout(this);
    root->setContentsMargins(32, 20, 32, 20);
    root->setSpacing(12);

    auto* header = new QHBoxLayout;
    auto* badge = new QLabel(QStringLiteral("DEMO DATA"), this);
    badge->setObjectName(QStringLiteral("demoBadge"));
    header->addWidget(badge);
    auto* title = makeLabel(QStringLiteral("工程演示"), "pageTitle", this);
    header->addWidget(title);
    header->addStretch();
    m_backButton = new QPushButton(QStringLiteral("返回设计展廊"), this);
    m_backButton->setProperty("role", "demoLink");
    m_backButton->setFixedSize(196, 64);
    header->addWidget(m_backButton);
    root->addLayout(header);

    auto* platformRow = new QHBoxLayout;
    platformRow->setSpacing(16);
    auto* platform = new SectionCard(this);
    platform->setFixedHeight(138);
    platform->contentLayout()->addWidget(makeLabel(QStringLiteral("平台 / 固定展示值"), "assist", platform));
    platform->contentLayout()->addWidget(makeLabel(
        QStringLiteral("Architecture  LoongArch64\nProcessor     Loongson 2K0300\nUI                 Qt 6"),
        "body", platform));
    platformRow->addWidget(platform, 5);
    auto* runtime = new SectionCard(this);
    runtime->setFixedHeight(138);
    runtime->contentLayout()->addWidget(makeLabel(QStringLiteral("模块 / 全部为模拟"), "assist", runtime));
    runtime->contentLayout()->addWidget(makeLabel(
        QStringLiteral("Runtime   ONNX Runtime（展示）\nASR         模拟\nVision     模拟"),
        "body", runtime));
    platformRow->addWidget(runtime, 6);
    root->addLayout(platformRow);

    auto* metrics = new QGridLayout;
    metrics->setHorizontalSpacing(12);
    metrics->setVerticalSpacing(10);
    const QList<QPair<QString, QString>> values = {
        {QStringLiteral("CPU · 模拟"), QStringLiteral("38%")},
        {QStringLiteral("RAM · 模拟"), QStringLiteral("286 MB")},
        {QStringLiteral("ASR · 模拟"), QStringLiteral("430 ms")},
        {QStringLiteral("Vision · 模拟"), QStringLiteral("310 ms")},
        {QStringLiteral("FPS · 模拟"), QStringLiteral("3.2")},
        {QStringLiteral("Inference · 模拟"), QStringLiteral("390 ms")},
        {QStringLiteral("Display"), QStringLiteral("1024 × 600")},
        {QStringLiteral("Backend"), QStringLiteral("未实现")}
    };
    for (int i = 0; i < values.size(); ++i)
        metrics->addWidget(metricCard(values[i].first, values[i].second, this), i / 4, i % 4);
    root->addLayout(metrics);

    auto* footer = makeLabel(QStringLiteral("本页全部指标为比赛演示假数据，并非实时采集。"), "danger", this);
    footer->setAlignment(Qt::AlignCenter);
    root->addWidget(footer);
}

QPushButton* EngineeringPage::backButton() const { return m_backButton; }
