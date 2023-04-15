#ifndef QCHESS_H
#define QCHESS_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include "PublicDef.h"

class QChess : public QPushButton
{
    Q_OBJECT
public:
    QChess(CAMP_TYPE camp, CHESS_TYPE type,int posx,int posy, QWidget *parent = nullptr);
    void SetChessType(CAMP_TYPE camp, CHESS_TYPE type);
    void updatePic();
    void Show();        // 翻开棋子
    bool moveButton(int movex, int movey);
    void otherShow();
    void unselect();
    int posx;
    int posy;

signals:
    void confirmType();//用于阵营确立

public slots:
    void OnClick();

protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);



private:
     CAMP_TYPE m_camp; // 阵营
     CHESS_TYPE m_type;// 棋子类型
     bool m_bShown;// 是否被翻开
     bool m_bSelect;
};

#endif // QCHESS_H
