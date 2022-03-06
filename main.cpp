#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "FranceTV_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    QCoreApplication::setOrganizationName("Paul WOISARD");
    QCoreApplication::setOrganizationDomain("https://github.com/Paullux/");
    QCoreApplication::setApplicationName("FranceTV");

    qputenv("QTWEBENGINE_CHROMIUM_FLAGS", "--blink-settings=forceDarkModeEnabled=true,darkModeInversionAlgorithm=4 --enable-logging --log-level=3 --widevine-path=\"./widevinecdm.dll\"");
    //qputenv("QTWEBENGINE_CHROMIUM_FLAGS", "--widevine-path=\"C:/Program Files/Google/Chrome/Application/99.0.4844.51/WidevineCdm/_platform_specific/win_x64/widevinecdm.dll\"");
    MainWindow w;
    w.showMaximized();
    return a.exec();
}
