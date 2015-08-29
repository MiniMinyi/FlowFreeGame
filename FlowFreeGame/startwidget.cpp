#include "startwidget.h"
#include "ui_startwidget.h"
#include "stdafx.h"

#include <QSignalMapper>
#include <QStackedWidget>
#include <QCheckBox>
#include <QPainter>
#include <QPixmap>

StartWidget::StartWidget(QWidget *parent):
    QWidget(parent),
    ui(new Ui::StartWidget)
{
    ui->setupUi(this);
    QPixmap title(":/images/flowfree");
    ui->label->setPixmap(title);

    connect(ui->play,SIGNAL(clicked(bool)),this,SLOT(on_play_clicked()));
    connect(ui->about,SIGNAL(clicked(bool)),this,SLOT(on_about_clicked()));

}

StartWidget::~StartWidget()
{
    delete ui;
}

void StartWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap backgroundPic(":/images/bgpicture");
    painter.drawPixmap(0,0,400,600,backgroundPic);
}

void StartWidget::on_about_clicked()
{
    emit sendWidgetSignal(about);
}

void StartWidget::on_play_clicked()
{
    emit sendWidgetSignal(choose);
}

