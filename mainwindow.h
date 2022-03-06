#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebEngineView>
#include <QtWebView>
#include <QUrl>

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

private:
    Ui::MainWindow *ui;
    QWebEngineView *view;
    QWebEngineSettings *settings;
    QUrl AccueilUrl = QUrl("https://www.france.tv/");
    //QUrl AccueilUrl = QUrl("https://www.heficience.com/");
    QWebEngineProfile *profile;

private slots:
    void Accueil();
    void Quitter();
};
#endif // MAINWINDOW_H
