#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QHBoxLayout>
#include <QCoreApplication>
#include <QWebEngineProfile>
#include <QWebEngineSettings>
#include <QNetworkAccessManager>
#include <QDir>
#include <QWebEngineCookieStore>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString home=QDir::homePath();

    QWebEngineProfile::defaultProfile()->setPersistentCookiesPolicy(QWebEngineProfile::ForcePersistentCookies);
    QWebEngineProfile* defaultProfile = QWebEngineProfile::defaultProfile();
    defaultProfile->setCachePath(home + "/AppData/Roaming/FranceTV/cache/");
    defaultProfile->setPersistentStoragePath(home + "/AppData/Roaming/FranceTV/persistentstorage/");

    view = new QWebEngineView(this);

    settings = view->page()->settings();
    settings->setAttribute(QWebEngineSettings::AutoLoadImages, true);
    settings->setAttribute(QWebEngineSettings::PluginsEnabled, true);
    settings->setAttribute(QWebEngineSettings::JavascriptEnabled, true);

    profile = view->page()->profile();

    profile->setHttpUserAgent("Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/99.0.4844.51 Safari/537.36");

    view->load(AccueilUrl);
    view->setZoomFactor(1.5);
    setCentralWidget(view);

    actionAccueil = ui->actionAccueil;
    actionQuitter = ui->actionQuitter;

    connect(actionAccueil, &QAction::triggered, this, &MainWindow::Accueil);
    connect(actionQuitter, &QAction::triggered, this, &MainWindow::Quitter);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Quitter()
{
    qApp->quit();
}

void MainWindow::Accueil()
{
    view->load(AccueilUrl);
}
