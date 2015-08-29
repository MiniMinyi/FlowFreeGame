#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "stdafx.h"
#include <QMainWindow>
#include <QSound>

class StartWidget;
class AboutWidget;
class ChooseWidget;
class PlayWidget;
class QStackedWidget;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
 //   void paintEvent(QPaintEvent *event);

private:
 //   void matchButton();
    void initToolbar();
    Ui::MainWindow *ui;
    QStackedWidget *stackedWidget;
    StartWidget *stWidget;
    ChooseWidget *chWidget;
    AboutWidget *abWidget;
    PlayWidget *plWidget;
    QSound music;

public slots:
    void setCurrentWidget(Widget);
};

#endif // MAINWINDOW_H
