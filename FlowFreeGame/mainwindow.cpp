#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "startwidget.h"
#include "aboutwidget.h"
#include "choosewidget.h"
#include "playwidget.h"

#include <QStackedWidget>
#include <QWidget>
#include <QSignalMapper>
#include <QToolBar>
#include <QAction>
#include <QIcon>
#include <QSound>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    stackedWidget(new QStackedWidget(this)),
    stWidget(new StartWidget),
    abWidget(new AboutWidget),
    chWidget(new ChooseWidget),
    plWidget(new PlayWidget),
    music(":/sound/music",this)
{

    music.setLoops(200);
    music.play();
    initToolbar();
    ui->setupUi(this);
    setCentralWidget(stackedWidget);
    stackedWidget->addWidget(stWidget);
    stackedWidget->addWidget(abWidget);
    stackedWidget->addWidget(chWidget);
    stackedWidget->addWidget(plWidget);

    stackedWidget->setCurrentWidget(stWidget);

    connect(stWidget,SIGNAL(sendWidgetSignal(Widget)),this,SLOT(setCurrentWidget(Widget)));
    connect(chWidget,SIGNAL(sendWidgetSignal(Widget)),this,SLOT(setCurrentWidget(Widget)));
    connect(abWidget,SIGNAL(sendWidgetSignal(Widget)),this,SLOT(setCurrentWidget(Widget)));
    connect(plWidget,SIGNAL(sendWidgetSignal(Widget)),this,SLOT(setCurrentWidget(Widget)));

    connect(chWidget,SIGNAL(sendFilename(QString)),plWidget,SLOT(setInitFilename(QString)));
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setCurrentWidget(Widget wid)
{
    switch (wid){
        case start:
            stackedWidget->setCurrentWidget(stWidget);
            setWindowTitle("Welcome to Flow Free Game ~");
            break;
        case choose:
            stackedWidget->setCurrentWidget(chWidget);
            setWindowTitle("Choose a level ...");
            break;
        case about:
            stackedWidget->setCurrentWidget(abWidget);
            setWindowTitle("About the game");
            break;
        case play:
            stackedWidget->setCurrentWidget(plWidget);
            setWindowTitle("Flow Free Game");
        default:
            break;

    }
}

void MainWindow::initToolbar()
{
    QToolBar *toolBar = addToolBar("MusicOn");
    QToolBar *toolBar2 = addToolBar("MusicOff");

    QAction *musicAction(new QAction(QIcon(":/images/music"),tr("Music"),toolBar) );
    toolBar->addAction(musicAction);
    connect(musicAction,SIGNAL(triggered(bool)),&music,SLOT(play()));

    QAction *musicOffAction(new QAction(QIcon(":/images/musicoff"),tr("MusicOff"),toolBar) );
    toolBar2->addAction(musicOffAction);
    connect(musicOffAction,SIGNAL(triggered(bool)),&music,SLOT(stop()));
}

/*void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,400,550,QPixmap("images/bgpicture"));
}*/

