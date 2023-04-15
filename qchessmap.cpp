#include "qchessmap.h"
#include <QLabel>
#include <QImage>
#include <QTime>
#include "PublicDef.h"

QChessMap::QChessMap(const QPoint &size, QWidget *parent) :
    QWidget(parent),
    m_pSize(size)
{

    m_pChessSize.ry() = 37;
    m_pChessSize.rx() = 73;

    initMap();


}

void QChessMap::initMap()
{
    m_lbBackground = new QLabel(this);
    m_lbBackground->setGeometry(0, 0, m_pSize.x(), m_pSize.y());

    QImage *img = new QImage();
    img->load(":/images/chess_board.png");

    QImage imgSacle = img->scaled(m_pSize.x(),m_pSize.y(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    m_lbBackground->setPixmap(QPixmap::fromImage(imgSacle));

    this->drawButton();
    for(int x = 0; x < 5;++x){
        for(int y = 0; y<12;++y){
              buttonMap[x][y]=1;    //存放所有可放棋子的逻辑坐标
        }

    }
}

void QChessMap::drawButton(){
    QVector<QPoint> posLogical;
    for(int x = 0; x < 5;++x){
        for(int y = 0; y<12;++y){
            if(!IsBarracks(x, y))
                posLogical.push_back(QPoint(x,y));  //存放所有可放棋子的逻辑坐标
        }
    }

    m_chess.clear();

    for(int type = CHESS_FALG; type<= CHESS_Engineer; ++type){
        for(int camp = RED;camp<=BLUE;++camp){
            for(int n = 0; n < GetChessTypeNum((CHESS_TYPE)type);++n){
                srand(seed);
                int nIndex = rand() % posLogical.size();
                QPoint pos = GetChessPos(posLogical[nIndex].x(), posLogical[nIndex].y());
                QChess *chess = new QChess((CAMP_TYPE)camp, (CHESS_TYPE)type,posLogical[nIndex].x(),posLogical[nIndex].y(),this);
                chess->setGeometry(pos.x(), pos.y(), m_pChessSize.x(),m_pChessSize.y());
                posLogical.remove(nIndex);
                m_chess.push_back(chess);
            }
        }
    }


}

QPoint QChessMap::GetChessPos(int nX, int nY)
{
    QPoint pos = QPoint(0,0);

    pos.rx() = 17 + (nX*(73 + 38)) ;  //第一颗棋子的左偏移+nx*（棋子宽+棋子左右间距）

    if(nY<=5){
        pos.ry() = 16 + (nY*(37 + 18));  //第一颗棋子的上偏移+ny*（棋子高+棋子上下间距）
    }else{
        pos.ry() = 465 + (nY-6)*(37 + 18);  //第7颗棋子的上偏移+ny*（棋子高+棋子上下间距）
    }
    return pos;
}

QPoint QChessMap::GetChessSize()
{
    return m_pChessSize;
}


void QChessMap::enableAllButton()
{
    for(int i = 0;i < this->m_chess.size();++i)
    {
        m_chess.at(i)->setEnabled(true);
    }
}


void QChessMap::checkButton(int posx,int posy)
{
    for(int i = 0;i < m_chess.size();++i)
    {
        if(this->m_chess.at(i)->moveButton(posx,posy))
        {

            this->m_chess.at(i)->otherShow();  //本地更新翻转
        }
    }
}


void QChessMap::eatButton(int posx,int posy,int posx2,int posy2)
{
    QChess* temp;
    for(int i = 0;i < m_chess.size();++i)
    {
        if(this->m_chess.at(i)->moveButton(posx,posy))
        {
            temp=this->m_chess.at(i);

        }

    }
    for(int i = 0;i < m_chess.size();++i){
    if(this->m_chess.at(i)->moveButton(posx2,posy2))
    {
        this->m_chess.at(i)->hide();
        this->m_chess.at(i)->setEnabled(false);
        temp->setGeometry(this->m_chess.at(i)->pos().x(),this->m_chess.at(i)->pos().y(),73,37);
        temp->posx=posx2;
        temp->posy=posy2;
        m_chess.remove(i);
    }
  }


}

void QChessMap::bothVanished(int posx,int posy,int posx2,int posy2){
    for(int i = 0;i < m_chess.size();++i)
    {
        if(this->m_chess.at(i)->moveButton(posx,posy))
        {

            this->m_chess.at(i)->hide();
            this->m_chess.at(i)->setEnabled(false);
            m_chess.remove(i);
        }

    }
    for(int i = 0;i < m_chess.size();++i){
    if(this->m_chess.at(i)->moveButton(posx2,posy2))
    {

        this->m_chess.at(i)->hide();
        this->m_chess.at(i)->setEnabled(false);
        m_chess.remove(i);
    }
    }
}
