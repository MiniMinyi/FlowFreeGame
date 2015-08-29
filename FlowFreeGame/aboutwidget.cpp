#include "aboutwidget.h"
#include "ui_aboutwidget.h"
#include "stdafx.h"
#include <QPixmap>
#include <QPainter>

AboutWidget::AboutWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AboutWidget)
{
    ui->setupUi(this);
    QPixmap about(":/images/about");
    ui->AboutTitle->setPixmap(about);
    ui->textBrowser->setText(tr("<p>Flow Free is a simple yet addictive puzzle game. </p> "
                              "<p>Connect matching colors with pipe to create a flow. "
                              "Pair all colors, and cover the entire board to solve each puzzle. "
                              "But watch out, pipes will break if they cross or overlap! </p>"
                              "<p>Give Flow Free a try, and experience 'mind like water'!</p>"));
    connect(ui->return_2,SIGNAL(clicked(bool)),this,SLOT(on_return_clicked()));
}

void AboutWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap backgroundPic(":/images/bgpicture");
    painter.drawPixmap(0,0,400,600,backgroundPic);
}

AboutWidget::~AboutWidget()
{
    delete ui;
}

void AboutWidget::on_return_clicked()
{
    emit sendWidgetSignal(start);
}
