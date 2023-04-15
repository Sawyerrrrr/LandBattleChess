#ifndef CLIENTWD_H
#define CLIENTWD_H

#include <QWidget>
#include "PublicDef.h"

namespace Ui {
class clientwd;
}

class clientwd : public QWidget
{
    Q_OBJECT

public:
    explicit clientwd(QWidget *parent = nullptr);
    ~clientwd();

private slots:
    void on_pushButton_clicked();
    void readMessage();
    void displayError(QAbstractSocket::SocketError);
signals:
    void recv();
private:
    Ui::clientwd *ui;
};

#endif // CLIENTWD_H
