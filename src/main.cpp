#include "DemoWindow.h"

#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QTimer>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    QApplication::setApplicationName(QStringLiteral("LongPetUiDemo"));
    QApplication::setOrganizationName(QStringLiteral("LongPet UI Prototype"));

    QFile styleFile(QStringLiteral(":/styles/app.qss"));
    if (styleFile.open(QIODevice::ReadOnly | QIODevice::Text))
        app.setStyleSheet(QString::fromUtf8(styleFile.readAll()));

    DemoWindow window;
    window.show();

    QString captureDirectory;
    for (const QString& argument : app.arguments()) {
        constexpr auto prefix = "--capture-dir=";
        if (argument.startsWith(QLatin1String(prefix)))
            captureDirectory = argument.mid(static_cast<int>(qstrlen(prefix)));
    }
    if (!captureDirectory.isEmpty()) {
        QTimer::singleShot(200, &window, [&app, &window, captureDirectory] {
            const QStringList captures = window.captureAllPages(captureDirectory);
            app.exit(captures.size() == 15 ? 0 : 2);
        });
    }
    return app.exec();
}
