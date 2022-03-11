#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QCoreApplication>
#include <QWebEngineProfile>
#include <QWebEngineSettings>
#include <QDir>
#include <QWebEngineCookieStore>
#include <QPushButton>
#include <QDockWidget>
#include <QWidget>
#include <QGraphicsBlurEffect>

/*
frameless window class: it adds the MainWindow class inside the centralWidget
*/
BorderlessMainWindow::BorderlessMainWindow(QWidget *parent) : QMainWindow(parent, Qt::CustomizeWindowHint ) {
    setObjectName("borderlessMainWindow");
    setWindowFlags(Qt::FramelessWindowHint| Qt::WindowSystemMenuHint);
    // to fix taskbar minimize feature
    setWindowFlags(windowFlags() | Qt::WindowMinimizeButtonHint);

    mMainWindow = new MainWindow(this);
    setWindowTitle(mMainWindow->windowTitle());

    QVBoxLayout *verticalLayout = new QVBoxLayout();
    verticalLayout->setSpacing(0);
    verticalLayout->setMargin(1);

    QHBoxLayout *horizontalLayout = new QHBoxLayout();
    horizontalLayout->setSpacing(0);
    horizontalLayout->setMargin(0);

    mTitlebarWidget = new QWidget(this);
    mTitlebarWidget->setObjectName("titlebarWidget");
    mTitlebarWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    mTitlebarWidget->setLayout(horizontalLayout);

    mMinimizeButton = new QPushButton(mTitlebarWidget);
    mMinimizeButton->setObjectName("minimizeButton");
    connect(mMinimizeButton, SIGNAL(clicked()), this, SLOT(slot_minimized()));

    mRestoreButton = new QPushButton(mTitlebarWidget);
    mRestoreButton->setObjectName("restoreButton");
    mRestoreButton->setVisible(false);
    connect(mRestoreButton, SIGNAL(clicked()), this, SLOT(slot_restored()));

    mMaximizeButton = new QPushButton(mTitlebarWidget);
    mMaximizeButton->setObjectName("maximizeButton");
    connect(mMaximizeButton, SIGNAL(clicked()), this, SLOT(slot_maximized()));

    mCloseButton = new QPushButton(mTitlebarWidget);
    mCloseButton->setObjectName("closeButton");
    connect(mCloseButton, SIGNAL(clicked()), this, SLOT(slot_closed()));

    mWindowTitle = new QLabel(mTitlebarWidget);
    mWindowTitle->setObjectName("windowTitle");
    mWindowTitle->setText(windowTitle());

    horizontalLayout->addWidget(mWindowTitle);
    horizontalLayout->addStretch(1);
    horizontalLayout->addWidget(mMinimizeButton);
    horizontalLayout->addWidget(mRestoreButton);
    horizontalLayout->addWidget(mMaximizeButton);
    horizontalLayout->addWidget(mCloseButton);

    verticalLayout->addWidget(mTitlebarWidget);
    verticalLayout->addWidget(mMainWindow);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setObjectName("centralWidget");
    centralWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    centralWidget->setLayout(verticalLayout);

    setCentralWidget(centralWidget);
}
void BorderlessMainWindow::mousePressEvent(QMouseEvent* event) {
    if (!mTitlebarWidget->underMouse() && !mWindowTitle->underMouse())
        return;

    if(event->button() == Qt::LeftButton) {
        mMoving = true;
        mLastMousePosition = event->pos();
    }
}
void BorderlessMainWindow::mouseMoveEvent(QMouseEvent* event) {
    if (!mTitlebarWidget->underMouse() && !mWindowTitle->underMouse())
        return;

    if( event->buttons().testFlag(Qt::LeftButton) && mMoving) {
        this->move(this->pos() + (event->pos() - mLastMousePosition));
    }
}
void BorderlessMainWindow::mouseReleaseEvent(QMouseEvent* event) {
    if (!mTitlebarWidget->underMouse() && !mWindowTitle->underMouse())
        return;

    if(event->button() == Qt::LeftButton) {
        mMoving = false;
    }
}
void BorderlessMainWindow::mouseDoubleClickEvent(QMouseEvent *event) {
    Q_UNUSED(event);
    if (!mTitlebarWidget->underMouse() && !mWindowTitle->underMouse())
        return;

    mMaximized = !mMaximized;
    if (mMaximized) {
        slot_maximized();
    } else {
        slot_restored();
    }
}
void BorderlessMainWindow::slot_minimized() {
    setWindowState(Qt::WindowMinimized);
}
void BorderlessMainWindow::slot_restored() {
    mRestoreButton->setVisible(false);
    mMaximizeButton->setVisible(true);
    setWindowState(Qt::WindowNoState);
    setStyleSheet("#borderlessMainWindow{border:1px solid palette(highlight);}");
}
void BorderlessMainWindow::slot_maximized() {
    mRestoreButton->setVisible(true);
    mMaximizeButton->setVisible(false);
    setWindowState(Qt::WindowMaximized);
    setStyleSheet("#borderlessMainWindow{border:1px solid palette(base);}");
}
void BorderlessMainWindow::slot_closed() {
    close();
}

/*
MainWindow class: put all your code here
*/
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    statusBar()->setSizeGripEnabled(true);

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
    settings->setAttribute(QWebEngineSettings::WebGLEnabled, true);

    view->page()->profile()->setHttpUserAgent("Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/76.0.3809.132 Safari/537.36");
    view->load(AccueilUrl);
    view->setZoomFactor(1.5);
    setCentralWidget(view);
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

void MainWindow::changeZoomScaled(int value)
{
    view->setZoomFactor(value/10);
}