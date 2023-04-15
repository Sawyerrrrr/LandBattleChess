#ifndef SEVERWD_H
#define SEVERWD_H

#include <QWidget>
#include <QHostInfo>
#include "PublicDef.h"

namespace Ui {
class Severwd;
}

class Severwd : public QWidget
{
    Q_OBJECT

public:
    explicit Severwd(QWidget *parent = nullptr);
    ~Severwd();
    QString HostIP;

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void sendMessage();
    void readMessage();
signals:
    void recv();
private:
    Ui::Severwd *ui;
};

#endif // SEVERWD_H
