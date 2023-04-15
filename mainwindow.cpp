#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QImage>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_map = new QChessMap(QPoint(550, 800));

    m_map->setGeometry(10,30, 550, 800);

    this->layout()->addWidget(m_map);
    connect(ui->actionCreate_Game,SIGNAL(triggered()),this,SLOT(createSever()));
    connect(ui->actionConnect_to_Sever,SIGNAL(triggered()),this,SLOT(createClient()));
    connect(ui->actioni_m_Ready,SIGNAL(triggered()),this,SLOT(startGame()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createSever()
{
    Severwd* swd=new Severwd();
    connect(swd,SIGNAL(recv()),this,SLOT(addressData()));
    swd->show();
}

void MainWindow::createClient()
{
    clientwd* cwd=new clientwd();
    connect(cwd,SIGNAL(recv()),this,SLOT(addressData()));
    cwd->show();
}


void MainWindow::addressData()
{
    qDebug()<<message;
    //对收到的指令进行解析
    QStringList qlist=message.split("&");

    //收到开始游戏的信号
    if(qlist[0] == "start")
    {
        if(qlist.size()==2){
            qDebug()<<seed<<" "<<qlist[1];
            seed=qlist[1].toInt();
            initMap();
        }
    }

    if(qlist[0]=="翻棋"){
        myTurn=true;//如果对方已经走好 轮到我的轮次

        int posx=qlist[1].toInt();
        int posy=qlist[2].toInt();

        this->m_map->checkButton(posx,posy);
        if(qlist[3]=="RED"){
            myColor="BLUE";
            qDebug()<<"您是蓝色阵营";
            campdif = 1;
        }else if(qlist[3]=="BLUE"){
            myColor="RED";
            qDebug()<<"您是红色阵营";
            campdif = 1;
        }
    }
    if(qlist[0]=="吃子"){
        myTurn=true;
        int y1=qlist[1].toInt();
        int x1=qlist[2].toInt();
        int y2=qlist[3].toInt();
        int x2=qlist[4].toInt();
        this->m_map->eatButton(x1,y1,x2,y2);
        buttonMap[y1][x1]=0;
        buttonMap[y2][x2]=1;
    }
    if(qlist[0]=="抵消"){
        myTurn=true;
        int y1=qlist[1].toInt();
        int x1=qlist[2].toInt();
        int y2=qlist[3].toInt();
        int x2=qlist[4].toInt();
        this->m_map->bothVanished(x1,y1,x2,y2);
        buttonMap[y1][x1]=0;
        buttonMap[y2][x2]=0;
    }

 }

void MainWindow::startGame()
{
    if(tcpServer==NULL && cSocket==NULL){
        return;
    }
    if(tcpServer!=NULL){
        qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
        seed=qrand()%100;
        initMap();
        //双方点击start,之后开始游戏
        SendMessageToOther(QString("start")+"&"+QString::number(seed));
    }else{
        SendMessageToOther("start");
    }

        this->m_map->enableAllButton();
    }


void MainWindow::initMap()
{
    this->layout()->removeWidget(m_map);

    m_map = new QChessMap(QPoint(550, 800));

    m_map->setGeometry(10,30, 550, 800);

    this->layout()->addWidget(m_map);
}
