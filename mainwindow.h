#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include "qchessmap.h"
#include "severwd.h"
#include "clientwd.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initMap();

private:
    Ui::MainWindow *ui;
    QChessMap *m_map;
    bool my=false;
    bool other=false;
public slots:
    void createSever();
    void createClient();
    void addressData();
    void startGame();

};
#endif // MAINWINDOW_H
