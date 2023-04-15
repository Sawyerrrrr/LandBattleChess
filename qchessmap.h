#ifndef QCHESSMAP_H
#define QCHESSMAP_H

#include <QWidget>
#include <QLabel>
#include <QPoint>
#include "qchess.h"


class QChessMap : public QWidget
{
    Q_OBJECT
public:
    explicit QChessMap(const QPoint &size, QWidget *parent = nullptr);

    void initMap();

    QPoint GetChessPos(int nX, int nY);
    // 通过逻辑坐标获取实际坐标点,用于放置棋子位置

    QPoint GetChessSize();
    void enableAllButton();
    void drawButton();
    void checkButton(int posx,int posy);
    void eatButton(int posx,int posy,int posx2,int posy2);
    void bothVanished(int posx,int posy,int posx2,int posy2);


private:
    QPoint m_pSize;
    QPoint m_pChessSize;
    QLabel *m_lbBackground;
    QLabel *m_lbChessBoard;
    QVector<QChess*> m_chess;
};

#endif // QCHESSMAP_H
