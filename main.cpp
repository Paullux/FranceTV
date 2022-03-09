#include "mainwindow.h"
#include "DarkStyle.h"
#include "framelesswindow/framelesswindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // style our application with custom dark style
    QApplication::setStyle(new DarkStyle);

    // create frameless window (and set windowState or title)
    FramelessWindow framelessWindow;
    //framelessWindow.setWindowState(Qt::WindowFullScreen);
    //framelessWindow.setWindowTitle("test title");
    framelessWindow.setWindowIcon(a.style()->standardIcon(QStyle::SP_DesktopIcon));

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

    qputenv("QTWEBENGINE_CHROMIUM_FLAGS", "--blink-settings=forceDarkModeEnabled=true,darkModeInversionAlgorithm=4 --enable-logging --log-level=3 --widevine-path=\"I:/FranceTV/cmake-build-release/widevinecdm.dll\"");
    //qputenv("QTWEBENGINE_CHROMIUM_FLAGS", "--widevine-path=\"C:/Program Files/Google/Chrome/Application/99.0.4844.51/WidevineCdm/_platform_specific/win_x64/widevinecdm.dll\"");

    // create our mainwindow instance
    MainWindow *w = new MainWindow;

    // add the mainwindow to our custom frameless window
    framelessWindow.setContent(w);
    framelessWindow.showMaximized();

    //w.setWindowFlags(Qt::FramelessWindowHint);
    //w.showMaximized();
    return a.exec();
}
