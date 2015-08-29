#ifndef ABOUTWIDGET_H
#define ABOUTWIDGET_H

#include "stdafx.h"
#include <QWidget>

namespace Ui {
class AboutWidget;
}

class AboutWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AboutWidget(QWidget *parent = 0);
    ~AboutWidget();
protected:
    void paintEvent(QPaintEvent *);
private:
    Ui::AboutWidget *ui;
signals:
    void sendWidgetSignal(Widget);
public slots:
    void on_return_clicked();

};

#endif // ABOUTWIDGET_H
