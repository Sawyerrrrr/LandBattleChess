#include "clientwd.h"
#include "ui_clientwd.h"
#include "PublicDef.h"


clientwd::clientwd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::clientwd)
{
    ui->setupUi(this);
    setWindowTitle("连接服务器端");
    cSocket=new QTcpSocket(this);
    connect(cSocket,SIGNAL(readyRead()),this,SLOT(readMessage()));
    connect(cSocket,SIGNAL(error(QAbstractSocket::SocketError)),
             this,SLOT(displayError(QAbstractSocket::SocketError)));
}

clientwd::~clientwd()
{
    delete ui;
}

void clientwd::on_pushButton_clicked()
{
    baSize=0;

    if(cSocket){
    cSocket->abort();
    }                  //断掉之前的连接

    QString ip=ui->lineEdit->text();
    cSocket->connectToHost(ip,4399);

}

void clientwd::readMessage()
{
    QDataStream in(cSocket);
    in.setVersion(QDataStream::Qt_5_4);

    if(baSize==0){    //将需要接收的数据大小写入baSize
        if(cSocket->bytesAvailable()<(int)sizeof(quint16)){  //数据缓冲区可用字节数
            return;
        }
        in>>baSize;
    }

    if(cSocket->bytesAvailable()<baSize){   //如果没有得到全部的数据，则返回，继续接收数据
        return;
    }
    in>>message;
    qDebug()<<message;
    emit recv();
    baSize=0;
    this->hide();
}

void clientwd::displayError(QAbstractSocket::SocketError)
{
    qDebug() << cSocket->errorString();
}
