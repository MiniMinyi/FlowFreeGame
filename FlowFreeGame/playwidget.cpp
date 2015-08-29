#include "stdafx.h"
#include "playwidget.h"
#include "ui_playwidget.h"
#include <QSignalMapper>
#include <QSound>
#include <QFile>
#include <QTextStream>
#include <QPainter>
#include <QPen>
#include <QMouseEvent>
#include <QMessageBox>

PlayWidget::PlayWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayWidget),
    connected(":/sound/resource/connected.wav",this),
    leak(":/sound/resource/leak.wav",this)
{
    ui->setupUi(this);
    connect(ui->goback,SIGNAL(clicked(bool)),this,SLOT(on_return_click()));
    ui->label->setPixmap(QPixmap(":/images/flowfree"));
    readLevelName();
    connect(this,SIGNAL(sendInitFilename(QString)),this,SLOT(setInitFilename(QString)));

    mapper = new QSignalMapper(this);
    connect(ui->last,SIGNAL(clicked(bool)),mapper,SLOT(map()));
    connect(ui->next,SIGNAL(clicked(bool)),mapper,SLOT(map()));
    connect(ui->restart,SIGNAL(clicked(bool)),mapper,SLOT(map()));
    connect(mapper,SIGNAL(mapped(QString)),this,SLOT(setInitFilename(QString)));
}

PlayWidget::~PlayWidget()
{
    delete ui;
}

void PlayWidget::setMapping()
{
    mapper->removeMappings(ui->last);
    mapper->removeMappings(ui->next);
    mapper->removeMappings(ui->restart);
    if (levelNum == 0)
        mapper->setMapping(ui->last,level[levelNum]);
    else
        mapper->setMapping(ui->last,level[levelNum-1]);
    if (levelNum == levelTotal)
        mapper->setMapping(ui->next,level[levelNum]);
    else
        mapper->setMapping(ui->next,level[levelNum+1]);
    mapper->setMapping(ui->restart,level[levelNum]);
}

void PlayWidget::readLevelName()
{
    QFile list(":/file/resource/settings/filelist.txt");
    list.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&list);
    while(!in.atEnd())
    {
        level.push_back(in.readLine(75));
    }
    list.close();
}

void PlayWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap backgroundPic(":/images/bgpicture");
    painter.drawPixmap(0,0,400,600,backgroundPic);
    for (int i = 0; i < size; ++ i)
        for (int j = 0; j < size; ++ j)
        {
            if (pineMap[i][j] > 0 && isSetColor[pineMap[i][j]])
            {
                painter.save();
                QColor co = color[pineMap[i][j]];
                co.setAlpha(50);
                painter.setBrush(co);
                painter.drawRect(sx+i*r,sy+j*r,r,r);
                painter.restore();
            }
            else
            {
                painter.drawRect(sx+i*r,sy+j*r,r,r);
            }
            if (square[i][j] > 0)
            {
                painter.save();
                painter.setPen(color[square[i][j]]);
                painter.setBrush(color[square[i][j]]);
                painter.drawEllipse(sx+i*r+ex,sy+j*r+ey,r+er,r+er);
                painter.restore();
            }
        }
    if (isPress)
    {
        painter.save();
        QColor co = color[moveColor];
        co.setAlpha(50);
        painter.setPen(co);
        painter.setBrush(co);
        painter.drawEllipse(cpx-r/2,cpy-r/2,r,r);
        painter.restore();
    }
    for (int i = 1; i <= colorNum; ++ i)
    {
        if (pineRecord[i].size() > 1)
            for (int j = 1; j < pineRecord[i].size(); ++ j)
            {
                int x1,x2,y1,y2;
                x1 = pineRecord[i][j-1].x()*r + r/2+ sx;
                x2 = pineRecord[i][j].x()*r + r/2 + sx;
                y1 = pineRecord[i][j-1].y()*r + r/2 + sy;
                y2 = pineRecord[i][j].y()*r + r/2 + sy;

                QPen pen(color[i],r+3*er,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin);
                painter.save();
                painter.setPen(pen);
                painter.drawLine(x1,y1,x2,y2);
                painter.restore();
            }
    }

}

void PlayWidget::on_return_click()
{
    emit sendWidgetSignal(choose);
}

void PlayWidget::setInitFilename(QString name)
{
    filename = name;
    std::vector<QString>::iterator pos =
            std::find(level.begin(),level.end(),filename);
    levelNum = pos - level.begin();
    levelTotal = level.end() - level.begin() - 1;
    initfile = ":/file/resource/settings/" + name;
    init();
    update();
}

void PlayWidget::initButton()
{
    if (levelNum == 0)
        ui->last->setEnabled(false);
    else ui->last->setEnabled(true);

    if (levelNum == levelTotal)
        ui->next->setEnabled(false);
    else ui->next->setEnabled(true);
}

void PlayWidget::init()
{
    initButton();
    setMapping();
    initLayout();
    initGameArgu();
}

void PlayWidget::initLayout()
{
    //  5*5: sx = 45; sy = 130; r = 60;
    //  6*6: sx = 40; sy = 110; r = 55;
    //  7*7: sx = 25; sy = 90;  r = 50;

    QColor color2[8]={Qt::gray,Qt::red,Qt::yellow,Qt::green,Qt::blue,Qt::cyan,Qt::magenta,
                    Qt::black};
    for (int i = 0; i < 8; ++ i)
        color[i] = color2[i];

    QFile file(initfile);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);
    in >> size;
    in >> colorNum;
    for (int i = 1; i <= colorNum; ++ i)
        isConnected[i] = false;
    in >> sx >> sy >> r;
    ex = ey = 10; er = -15;
    for (int i = 0; i < size; ++ i)
         for (int j = 0; j < size; ++ j)
          {
                in >> square[i][j];
          }

    file.close();
}

QPoint PlayWidget::returnSquarePos(QPoint c)
// if the position is out of the layout then return qpoint(-1,-1)
{
    if (c.x() < sx || c.y() < sy || c.x() > sx + r*size || c.y() > sy + r*size)
        return QPoint(-1,-1);
    QPoint p;
    p.setX((c.x()-sx)/r);
    p.setY((c.y()-sy)/r);
    return p;
}

void PlayWidget::mouseMoveEvent(QMouseEvent *event)
{
    QPoint p = returnSquarePos(event->pos());
    if (isPress)
    {
        if (p.x() == -1 && p.y() == -1)
        {
        /*    isSetColor[moveColor] = true;
            isPress = false;
            update();
            return;*/
            return;
        }
        if (square[px][py] > 0 && isConnected[square[px][py]])
        {
            if (pineMap[p.x()][p.y()] != square[px][py])
                return;
        }
        if (p.x() == px && p.y() == py)
      {
         cpx = event->x(); cpy = event->y();
      }
        else
        if ( ( (p.x() == px && (p.y() == py - 1 || p.y() == py + 1)) ||
        (p.y() == py && (p.x() == px - 1 || p.x() == px + 1)) )/* &&
            (square[p.x()][p.y()] == 0 || square[p.x()][p.y()] == moveColor)*/)
        {
            if (square[p.x()][p.y()] > 0 && square[p.x()][p.y()] != moveColor)
            {
                return;
            }

            if (pineMap[p.x()][p.y()] > 0)
            {
                int pineColor = pineMap[p.x()][p.y()];
                if (isConnected[pineColor] && pineColor!=moveColor)
                    leak.play();
                std::vector<QPoint>::iterator pos =
                        std::find(pineRecord[pineColor].begin(), pineRecord[pineColor].end(),p);
                while (pineRecord[pineColor].end() > pos)
                {
                    QPoint em = pineRecord[pineColor].back();
                    pineMap[em.x()][em.y()] = 0;
                    pineRecord[pineColor].pop_back();
                }
                isConnected[pineColor] = false;
            //如果原本连通加上破裂声。
            }

        cpx = event->x(); cpy = event->y();

        if (! (square[px][py] > 0) || !isConnected[square[px][py]])
        {
            px = p.x(); py = p.y();
            pineRecord[moveColor].push_back(p);
            pineMap[p.x()][p.y()] = moveColor;
        }


        if (square[p.x()][p.y()] == moveColor && pineRecord[moveColor].size() > 1)
        {
            isConnected[moveColor] = true;
        }
    }
    else
    {
       // isPress = false;
    }
    update();
    }
}

void PlayWidget::mousePressEvent(QMouseEvent *event)
{
    QPoint p = returnSquarePos(event->pos());
    if (p.x() < 0 || p.y() < 0)
        return;
    if (square[p.x()][p.y()] > 0 || pineMap[p.x()][p.y()] > 0)
    {
        isPress = true;
        cpx = event->x(); cpy = event->y();
        px = p.x(); py = p.y();
        if (square[px][py] > 0)
        {
            moveColor = square[px][py];
            isConnected[moveColor] = false;
            isSetColor[moveColor] = false;
            while (!pineRecord[moveColor].empty())
            {
                QPoint em = pineRecord[moveColor].back();
                pineMap[em.x()][em.y()] = 0;
                pineRecord[moveColor].pop_back();
            }
            //pineRecord[moveColor].clear();
            pineRecord[moveColor].push_back(p);
            pineMap[px][py] = moveColor;

        }
        else
        {
            moveColor = pineMap[px][py];
            isConnected[moveColor] = false;
            isSetColor[moveColor] = false;
            std::vector<QPoint>::iterator pos =
                    std::find(pineRecord[moveColor].begin(), pineRecord[moveColor].end(),p);
            while (pineRecord[moveColor].end() > pos)
            {
                QPoint em = pineRecord[moveColor].back();
                pineMap[em.x()][em.y()] = 0;
                pineRecord[moveColor].pop_back();
            }
            pineRecord[moveColor].push_back(p);
            pineMap[px][py] = moveColor;
        }
    }
    update();
}

void PlayWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (isPress)
    {
        if (isConnected[moveColor])
            connected.play();
        isSetColor[moveColor] = true;
        isPress = false;
        moveColor = 0;
        testIfSucceed();
    }

    update();
}

void PlayWidget::testIfSucceed()
{
    for (int i = 1; i <= colorNum; ++ i)
        if (!isConnected[i])
            return;
    for (int i = 0; i < size; ++ i)
        for (int j = 0; j < size; ++ j)
            if (pineMap[i][j] == 0)
                return;
    QMessageBox::information(this,"Congratulations","<p>Congratulations!</p> You did a good job!",QMessageBox::Ok);

}

void PlayWidget::initGameArgu()
{
    isPress = false;
    px = py = 0; cpx = cpy = 0;
    moveColor = 0;
    for (int i = 0; i < size; ++ i)
    {
        for (int j = 0; j < size; ++ j)
            pineMap[i][j] = 0;
    }
    for (int i = 1; i <= colorNum; ++i)
        pineRecord[i].clear();
}
