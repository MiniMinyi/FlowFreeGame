#ifndef PLAYWIDGET_H
#define PLAYWIDGET_H

#include "stdafx.h"
#include <QWidget>
#include <QString>
#include <QColor>
#include <QPoint>
#include <vector>
#include <utility>
#include <QSound>
#include <QSignalMapper>


namespace Ui {
class PlayWidget;
}

class PlayWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PlayWidget(QWidget *parent = 0);
    ~PlayWidget();


protected:
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    Ui::PlayWidget *ui;
    QSignalMapper *mapper;
    QSound connected,leak;

    //members about layout
    QString initfile,filename;
    std::vector<QString> level;
    int size,sx,sy,r,ex,ey,er,levelNum,levelTotal;
    int square[20][20];
    QColor color[20];
    void initLayout();
    void readLevelName();
    void initButton();
    //memebers about mouseevent
    bool isPress;
    bool isSetColor[20], isConnected[20];
    int px,py,cpx,cpy,moveColor,colorNum;
    int pineMap[20][20];
    std::vector<QPoint> pineRecord[10];
    QPoint returnSquarePos(QPoint c);
    void initGameArgu();
    void setMapping();
    void init();
    void testIfSucceed();

public slots:
    void on_return_click();
    void setInitFilename(QString);

signals:
    void sendWidgetSignal(Widget);
    void sendInitFilename(QString);
};

#endif // PLAYWIDGET_H
