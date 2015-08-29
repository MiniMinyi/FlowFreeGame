#ifndef CHOOSEWIDGET_H
#define CHOOSEWIDGET_H

#include "stdafx.h"
#include <QSignalMapper>
#include <QPainter>
#include <QWidget>

namespace Ui {
class ChooseWidget;
}

class ChooseWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChooseWidget(QWidget *parent = 0);
    ~ChooseWidget();
protected:
    void paintEvent(QPaintEvent *);
private:
    Ui::ChooseWidget *ui;
    QSignalMapper *m;
    void mapPushbutton();

public slots:
    void on_return_clicked();
    void on_pushbutton_clicked();

signals:
    void sendWidgetSignal(Widget);
    void sendFilename(QString);
};

#endif // CHOOSEWIDGET_H
