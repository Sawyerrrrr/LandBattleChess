#include "severwd.h"
#include "ui_severwd.h"
#include "PublicDef.h"

Severwd::Severwd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Severwd)
{
    ui->setupUi(this);
    setWindowTitle("Sever Creation");
    QString localHostName=QHostInfo::localHostName();
    QHostInfo info=QHostInfo::fromName(localHostName);

    /*
 QList<QHostAddress> listAddress = hostInfo.addresses();
    if(!listAddress.isEmpty())  //获取主机IP地址列表可能为空。在不为空的情况下使用第一个IP地址。
    {
        LineEditAddress->setText(listAddress.at(2).toString());
    }*/

    for(QHostAddress addr:info.addresses()){
        if(addr.protocol()==QAbstractSocket::IPv4Protocol){
        this->HostIP=addr.toString();
        }
    }
    ui->label_2->setText(HostIP);
}

Severwd::~Severwd()
{
    delete ui;
}

void Severwd::on_pushButton_clicked()
{
    tcpServer=new QTcpServer(this);
    if(!tcpServer->listen(QHostAddress::Any,4399)){
        qDebug()<<tcpServer->errorString();
        close();
    }

    connect(tcpServer,SIGNAL(newConnection()),this,SLOT(sendMessage()));
    qDebug()<<"服务器开始监听4399端口";
    ui->pushButton->setEnabled(false);
}

void Severwd::on_pushButton_2_clicked()
{

}

void Severwd::sendMessage()
{
    QByteArray ba;
    QDataStream ds(&ba,QIODevice::WriteOnly);
    ds.setVersion(QDataStream::Qt_5_4);
    ds<<(qint16)0;   //用两个字节表示数据长度
    ds<<QString("连接成功!");
    ds.device()->seek(0);
    ds<<(qint16)(ba.size()-sizeof(quint16));    //总数据大小减去数据块开头两个字节大小

    tcpSocket=tcpServer->nextPendingConnection();
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(readMessage()));
    tcpSocket->write(ba);
    this->hide();
}

void Severwd::readMessage()
{
    QDataStream in(tcpSocket);
    in.setVersion(QDataStream::Qt_5_4);

    if(baSize==0){    //将需要接收的数据大小写入baSize
        if(tcpSocket->bytesAvailable()<(int)sizeof(quint16)){  //数据缓冲区可用字节数
            return;
        }
        in>>baSize;
    }

    if(tcpSocket->bytesAvailable()<baSize){   //如果没有得到全部的数据，则返回，继续接收数据
        return;
    }
    in>>message;
    qDebug()<<message;
    emit recv();
    baSize=0;
    this->hide();
}
