#include "choosewidget.h"
#include "ui_choosewidget.h"
#include "stdafx.h"
#include <QPixmap>
#include <QSignalMapper>
#include <QDebug>
#include <QPainter>

ChooseWidget::ChooseWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChooseWidget)
{
    ui->setupUi(this);
    QPixmap title(":/images/flowfree");
    ui->FlowFreeTitle->setPixmap(title);

    connect(ui->goback,SIGNAL(clicked(bool)),this,SLOT(on_return_clicked()));
    connect(ui->five1,SIGNAL(clicked(bool)),this,SLOT(on_pushbutton_clicked()));
    connect(ui->five2,SIGNAL(clicked(bool)),this,SLOT(on_pushbutton_clicked()));
    connect(ui->six1,SIGNAL(clicked(bool)),this,SLOT(on_pushbutton_clicked()));
    connect(ui->six2,SIGNAL(clicked(bool)),this,SLOT(on_pushbutton_clicked()));
    connect(ui->seven1,SIGNAL(clicked(bool)),this,SLOT(on_pushbutton_clicked()));
    connect(ui->seven2,SIGNAL(clicked(bool)),this,SLOT(on_pushbutton_clicked()));

    mapPushbutton();
}

void ChooseWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap backgroundPic(":/images/bgpicture");
    painter.drawPixmap(0,0,400,600,backgroundPic);
}

ChooseWidget::~ChooseWidget()
{
    delete ui;
}

void ChooseWidget::on_return_clicked()
{
    emit sendWidgetSignal(start);
}

void ChooseWidget::on_pushbutton_clicked()
{
    emit sendWidgetSignal(play);
}

void ChooseWidget::mapPushbutton()
{
    m = new QSignalMapper(this);
    connect(ui->five1,SIGNAL(clicked(bool)),m,SLOT(map()));
    m->setMapping(ui->five1,"five1.txt");

    connect(ui->five2,SIGNAL(clicked(bool)),m,SLOT(map()));
    m->setMapping(ui->five2,"five2.txt");

    connect(ui->six1,SIGNAL(clicked(bool)),m,SLOT(map()));
    m->setMapping(ui->six1,"six1.txt");

    connect(ui->six2,SIGNAL(clicked(bool)),m,SLOT(map()));
    m->setMapping(ui->six2,"six2.txt");

    connect(ui->seven1,SIGNAL(clicked(bool)),m,SLOT(map()));
    m->setMapping(ui->seven1,"seven1.txt");

    connect(ui->seven2,SIGNAL(clicked(bool)),m,SLOT(map()));
    m->setMapping(ui->seven2,"seven2.txt");

    connect(m,SIGNAL(mapped(QString)),this,SIGNAL(sendFilename(QString)));
}


