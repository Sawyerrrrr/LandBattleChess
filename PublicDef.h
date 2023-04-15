#ifndef PUBLICDEF_H
#define PUBLICDEF_H

#include <QString>
#include <QtNetwork>
#include <QDebug>
#include <QPushButton>

enum CHESS_TYPE{
    CHESS_UNKONWN = 0,
    CHESS_FALG,         // 军旗   1
    CHESS_MINE,         // 地雷   3
    CHESS_BOMB,         // 炸弹   2
    CHESS_Commande,     // 司令   1
    CHESS_General,      // 军长   1
    CHESS_Maj_general,  // 师长   2
    CHESS_Brigadier,    // 旅长   2
    CHESS_Colonel,      // 团长   2
    CHESS_Major,        // 营长   2
    CHESS_Captain,      // 连长   3
    CHESS_Lieutenant,   // 排长   3
    CHESS_Engineer      // 工兵   3
};

// 阵营
enum CAMP_TYPE{
    RED,
    BLUE
};




extern QTcpServer* tcpServer;
extern QTcpSocket* tcpSocket;
extern quint16 baSize;
extern QString message;//存放从服务器接收到的字符串
extern QTcpSocket* cSocket;
extern QString typeMessage;

//全局变量设置
extern QString SystemMessage;
extern QString typeMessage;
extern int lastTime;
extern bool hasConnectToServer;

//新增bool变量用于判断是否启动鼠标捕捉事件
extern bool Mousecheck;
//新增vector<QPoint>用于确定前后位置已经确定，可以开始变换
extern QVector<QPoint> v;
//新增两个vector记录棋子的类型和职位
extern QVector<CAMP_TYPE> camp;
extern QVector<CHESS_TYPE> type;

//新增一个二维数组维护铁路部分
extern int wholeMap[12][5];
//新增一个二维数组表示各个点上是否有按钮存在
extern int buttonMap[12][5];

//判断铁路位置
extern bool canWalk(QVector<QPoint> vv, int checkMine);
//新增dfs用于判断铁路是否能走
extern bool res;

extern QVector<QPoint> vv;
extern QVector<QPushButton*> pbv ;

//新增两个计数变量表示自己翻出的红蓝棋数量
extern int red_num;
extern int blue_num;

extern QString myColor;//我的阵营
extern bool myTurn;//我的轮次
extern int seed;//随机种子

extern int campdif;




void SendMessageToOther(QString operation);


int GetChessTypeNum(CHESS_TYPE type);
// 获取各个棋子的数量


bool IsBarracks(int nX, int nY);

QString GetChessPic(CHESS_TYPE type, CAMP_TYPE camp);
bool canEat();
bool canMove();

#endif // PUBLICDEF_H
