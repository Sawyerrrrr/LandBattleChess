#include "qchess.h"
#include <QMessageBox>


QChess::QChess(CAMP_TYPE camp, CHESS_TYPE type,int posx,int posy, QWidget *parent) :
    QPushButton(parent),
    m_camp(camp),
    m_type(type),
    m_bShown(false),
    m_bSelect(false),
    posx(posx),
    posy(posy)
{
    updatePic();
    connect(this, SIGNAL(clicked()), this, SLOT(OnClick()));
}


void QChess::SetChessType(CAMP_TYPE camp, CHESS_TYPE type){
    m_camp = camp;
    m_type = type;
    updatePic();
}

void QChess::updatePic()
{
    QString qsUrl = "border-image:url(";
    if(m_bShown == false){
        qsUrl += GetChessPic(CHESS_UNKONWN, m_camp);
    }else{
        qsUrl += GetChessPic(m_type, m_camp);
    }
    qsUrl += ");";
    if(m_bSelect)
       qsUrl += "border-width:5px;border-radius:10px;border-color: rgb(34, 255, 145);";
    setStyleSheet(qsUrl);

}

void QChess::OnClick()
{
    if(!myTurn)return;

    if(!m_bShown){
        myTurn=false;//轮次结束

        m_bShown = true;
        updatePic();

        if(red_num<1&&blue_num<1&&!campdif){
            //翻棋数量
            if(m_camp==RED)red_num++;
            if(m_camp==BLUE)blue_num++;

            if(red_num==1){
                campdif = 1;
                myColor="RED";
            }

            if(blue_num==1){
                campdif = 1;
                myColor="BLUE";
            }
        }

        QString px = QString::number(this->posx);
        QString py = QString::number(this->posy);
        QString type = "翻棋";
        QString optr=type+"&"+px+"&"+py+"&"+myColor;
        SendMessageToOther(optr);

        return;
    }


    m_bSelect = !m_bSelect;
    updatePic();

    if(m_bSelect){
        qDebug()<<"存入坐标："<<this->posx<<"  "<<this->posy;
        v.push_back(QPoint(this->posx,this->posy));
        camp.push_back(this->m_camp);
        type.push_back(this->m_type);
        pbv.push_back(this);

        if(v.size() == 1 && ((camp.at(0) == 0 && myColor == "BLUE") || (camp.at(0) == 1 && myColor == "RED")))
        {
            qDebug()<<"碰到了对方阵营的棋子";
            QChess *temp1 = dynamic_cast<QChess*>(pbv.at(0));
            temp1->unselect();

            pbv.clear();
            v.clear();
            camp.clear();
            type.clear();
            return;
        }


        if(v.size() == 2){
            if(camp.at(0) != camp.at(1))
            {
                if((type.at(0) - type.at(1) < 0 && type.at(0) != CHESS_BOMB && type.at(1) != CHESS_BOMB)|| (type.at(0) == CHESS_Engineer && (type.at(1) == CHESS_MINE || type.at(1) == CHESS_FALG))){

                    //可以吃子
                    myTurn=false;//轮次结束
                    //pbv.at(0)->setGeometry(this->pos().x(),this->pos().y(),37,73);


                    QChess *temp = dynamic_cast<QChess*>(pbv.at(0));
                    temp->setGeometry(this->pos().x(),this->pos().y(),73,37);
                    temp->unselect();
                    this->unselect();

                    //buttonMap[temp->posy][temp->posx] = 0;
                    //buttonMap[temp->posy][temp->posx] = 1;

                    temp->posx = v.at(1).x();
                    temp->posy = v.at(1).y();

                    pbv.at(1)->hide();
                    pbv.at(1)->setEnabled(false);

                    //发送网络消息 两个坐标位置 4个数字
                    QString s ="吃子";
                    s +="&"+QString::number(v.at(0).y()) + "&"+ QString::number(v.at(0).x()) +"&"
                                                + QString::number(v.at(1).y()) + "&"+ QString::number(v.at(1).x());
                    //增加两个如果y是两位数的话1，不是0

                    qDebug()<<s;
                    SendMessageToOther(s);
                    v.clear();
                    camp.clear();
                    type.clear();
                    pbv.clear();

                }
               else if(type.at(0) - type.at(1) == 0 || type.at(1) == CHESS_BOMB ||type.at(0) == CHESS_BOMB)
                {
                    myTurn=false;

                    pbv.at(0)->hide();
                    pbv.at(1)->hide();

                    pbv.at(0)->setEnabled(false);
                    pbv.at(1)->setEnabled(false);

                    buttonMap[v.at(0).y()][v.at(1).x()] = 0;
                    buttonMap[v.at(1).y()][v.at(1).x()] = 0;

                    //发送网络消息 两个坐标位置 4个数字
                    QString s ="抵消";
                    s +="&"+ QString::number(v.at(0).y()) +"&"+  QString::number(v.at(0).x())
                                                +"&"+  QString::number(v.at(1).y()) + "&"+ QString::number(v.at(1).x());
                    v.clear();
                    camp.clear();
                    type.clear();
                    pbv.clear();

                    SendMessageToOther(s);
                }
                else
                {
                    //吃不了
                    QChess *one = dynamic_cast<QChess *>(pbv.at(0));
                    QChess *two = dynamic_cast<QChess *>(pbv.at(1));
                    one->unselect();
                    two->unselect();
                    v.clear();
                    camp.clear();
                    type.clear();
                    pbv.clear();

                }
            }
            else
            {
                QChess *one = dynamic_cast<QChess *>(pbv.at(0));
                QChess *two = dynamic_cast<QChess *>(pbv.at(1));

                one->unselect();
                two->unselect();

                //撞色了点击了另一边之后，两个按钮都要重新变回未选中状态

                v.clear();
                camp.clear();
                type.clear();
                pbv.clear();
            }

        }

    }
    else if(!m_bSelect)
    {
        v.clear();
        camp.clear();
        type.clear();
        pbv.clear();
    }

    updatePic();
}
void QChess::otherShow()
{
    this->m_bShown = true;
    this->updatePic();
}
bool QChess::moveButton(int movex, int movey)
{
    if(this->posx == movex && this->posy == movey && this->isEnabled()){
        return true;
    }

    return false;
}




void QChess::unselect()
{
    this->m_bSelect = false;
    this->updatePic();
}


void QChess::mousePressEvent(QMouseEvent *e){
    QPushButton::mousePressEvent(e);
    this->move(this->pos().x()+3,this->pos().y()+3);

}

void QChess::mouseReleaseEvent(QMouseEvent *e) {
    QPushButton::mouseReleaseEvent(e);
    this->move(this->pos().x()-3,this->pos().y()-3);

}

