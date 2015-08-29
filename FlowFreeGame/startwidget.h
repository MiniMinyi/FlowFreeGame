#ifndef STARTWIDGET_H
#define STARTWIDGET_H

#include "stdafx.h"
#include <QStackedWidget>


namespace Ui {
class StartWidget;
}

class StartWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StartWidget(QWidget *parent = 0);
    ~StartWidget();
protected:
    void paintEvent(QPaintEvent *);
private:
    Ui::StartWidget *ui;

public slots:
    void on_play_clicked();
    void on_about_clicked();

signals:
    void sendWidgetSignal(Widget);

};

#endif // STARTWIDGET_H
