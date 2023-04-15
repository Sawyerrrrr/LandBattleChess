#include "PublicDef.h"


QTcpServer* tcpServer;
QTcpSocket* tcpSocket;
quint16 baSize;
QTcpSocket* cSocket;


QString message;
bool hasConnectToServer=false;
int red_num = 0;
int blue_num = 0;
QString myColor;
bool myTurn=true;


bool Mousecheck = false;

bool res = false;
QVector<QPoint> v;
QVector<CAMP_TYPE> camp;
QVector<CHESS_TYPE> type;
int seed;


int wholeMap[12][5];

int buttonMap[12][5];

QVector<QPoint> vv;
QVector<QPushButton*> pbv ;


int campdif = 0;


int GetChessTypeNum(CHESS_TYPE type)
{
    switch (type) {
    case CHESS_FALG:
    case CHESS_Commande:
    case CHESS_General:
        return 1;
    case CHESS_BOMB:
    case CHESS_Maj_general:  // 师长   2
    case CHESS_Brigadier:    // 旅长   2
    case CHESS_Colonel:    // 团长   2
    case CHESS_Major:        // 营长   2
        return  2;
    case CHESS_MINE:
    case CHESS_Captain:      // 连长   3
    case CHESS_Lieutenant:   // 排长   3
    case CHESS_Engineer:      // 工兵   3
        return 3;
    default:
        return 0;
    }
}


bool IsBarracks(int nX, int nY)
{
    if((nX == 1 && nY == 2)
       || (nX == 1 && nY == 4)
       || (nX == 2 && nY == 3)
       || (nX == 3 && nY == 2)
       || (nX == 3 && nY == 4)
       || (nX == 1 && nY == 7)
        || (nX == 1 && nY == 9)
        || (nX == 2 && nY == 8)
        || (nX == 3 && nY == 7)
        || (nX == 3 && nY == 9)){
        return true;
    }
    return  false;
}

QString GetChessPic(CHESS_TYPE type, CAMP_TYPE camp)
{
    QString qsUrl = ":/images/";
    if(type == CHESS_UNKONWN)
        return qsUrl += "chess.png";

    if(camp == RED)
        qsUrl += "red_";
    else
        qsUrl += "blue_";

    switch (type) {
    case CHESS_FALG:
        qsUrl += "flag";
        break;
    case CHESS_Commande:
        qsUrl += "Commande";
        break;
    case CHESS_General:
        qsUrl += "General";
        break;
    case CHESS_BOMB:
        qsUrl += "bomb";
        break;
    case CHESS_Maj_general:
        qsUrl += "Maj_general";
        break;
    case CHESS_Brigadier:
        qsUrl += "Brigadier";
        break;
    case CHESS_Colonel:
        qsUrl += "Colonel";
        break;
    case CHESS_Major:
        qsUrl += "Major";
        break;
    case CHESS_MINE:
        qsUrl += "mine";
        break;
    case CHESS_Captain:
        qsUrl += "Captain";
        break;
    case CHESS_Lieutenant:
        qsUrl += "Lieutenant";
        break;
    case CHESS_Engineer:
        qsUrl += "engineer";
        break;
    default:
        return "";
    }
    qsUrl += ".png";
    return qsUrl;
}

void SendMessageToOther(QString operation)
{
    QByteArray ba; //用于暂存我们要发送的数据
    QDataStream out(&ba,QIODevice::WriteOnly);
    //使用数据流写入数据
    out.setVersion(QDataStream::Qt_5_4);
    //设置数据流的版本，客户端和服务器端使用的版本要相同
    out<<(quint16) 0;
    out<<QString(operation);
    out.device()->seek(0);
    out<<(quint16) (ba.size()-sizeof(quint16));

    //如果是服务端
    if(tcpServer!=NULL){
        tcpSocket->write(ba);
    }else{//如果是客户端
        qDebug()<<operation;
        cSocket->write(ba);
    }
}



bool canMove(QVector<QPoint> v){
    int x2=v[1].x();
    int y2=v[1].y();
    if(!buttonMap[x2][y2])
    {
        return true;
    }
    return false;
}

