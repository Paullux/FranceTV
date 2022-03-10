#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebEngineView>
#include <QtWebView>
#include <QUrl>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QtWidgets>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QAction *actionAccueil;
    QAction *actionQuitter;
    QUrl AccueilUrl = QUrl("https://www.france.tv/");
    QWebEngineView *view;

private:
    Ui::MainWindow *ui;
    QWebEngineSettings *settings;
    //QWebEngineProfile *profile;
    QPushButton *closeButton;
    QPushButton *homeButton;
    QLabel *titleLabel;
    QLabel *scaleLabel;
    QGridLayout *myWebView;

public slots:
    void Quitter();
    void Accueil();
};

/*
this class is to add frameless window support and do all the stuff with titlebar and buttons
*/
class BorderlessMainWindow: public QMainWindow
{
Q_OBJECT
public:
    explicit BorderlessMainWindow(QWidget *parent = 0);
    ~BorderlessMainWindow() {}
protected:
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseDoubleClickEvent(QMouseEvent *event);
private slots:
    void slot_minimized();
    void slot_restored();
    void slot_maximized();
    void slot_closed();
private:
    MainWindow *mMainWindow;
    QWidget *mTitlebarWidget;
    QLabel *mWindowTitle;
    QPushButton *mMinimizeButton;
    QPushButton *mRestoreButton;
    QPushButton *mMaximizeButton;
    QPushButton *mCloseButton;
    QPoint mLastMousePosition;
    bool mMoving;
    bool mMaximized;
};

#endif // MAINWINDOW_H
