#include "mainwindow.h"
#include "DarkStyle.h"
#include "framelesswindow/framelesswindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QtWebEngineCore>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#ifdef __linux__
    a.setWindowIcon(QIcon(":/images/france-tv-2.svg"));
#elif _WIN32
    a.setWindowIcon(QIcon("./images/france-tv-2.ico"));
#elif __APPLE__
    a.setWindowIcon(QIcon("./images/france-tv-2.icns"));
#endif
    // style our application with custom dark style
    QApplication::setStyle(new DarkStyle);

    // create frameless window (and set windowState or title)
    FramelessWindow framelessWindow;

    //framelessWindow.setWindowState(Qt::WindowFullScreen);
    //framelessWindow.setWindowTitle("test title");
    //framelessWindow.setWindowIcon(QIcon("../images/france-tv.ico"));
#ifdef __linux__
    framelessWindow.setWindowIcon(QIcon(":/images/france-tv-2.ico"));
#elif _WIN32
    framelessWindow.setWindowIcon(QIcon("./france-tv-2.ico"));
#elif __APPLE__
    framelessWindow.setWindowIcon(QIcon(":/images/france-tv-2.icns"));
#endif

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "FranceTV_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    QCoreApplication::setOrganizationName("Paul_WOISARD");
    QCoreApplication::setOrganizationDomain("https://github.com/Paullux/");
    QCoreApplication::setApplicationName("FranceTV");

    qputenv("QTWEBENGINE_CHROMIUM_FLAGS", "--blink-settings=forceDarkModeEnabled=true,darkModeInversionAlgorithm=4 --proprietary-codecs --disable-logging");

    QLoggingCategory::setFilterRules("*qt.webenginecontext=false\n"
                                     "*js=false");

    // create our mainwindow instance
    MainWindow *w = new MainWindow;

    QObject::connect(&framelessWindow, &FramelessWindow::accueil, w, &MainWindow::accueil);
    QObject::connect(&framelessWindow, &FramelessWindow::sliderZoomValue, w, &MainWindow::changeZoomScaled);

    // add the mainwindow to our custom frameless window
    framelessWindow.setContent(w);
    framelessWindow.showMaximized();

    return a.exec();
}
