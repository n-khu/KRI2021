#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QPixmap>
#include <QKeyEvent>
#include <QDebug>
#include <QFont>
#include <tcp.h>
#include <udp.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/stat.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    TCP* mtcp;
    UDP* mudp;

private:
    Ui::MainWindow *ui;
    void keyPressEvent(QKeyEvent *event);
signals:
    void UDPReady();
    void UDPSendReady(int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int);
    void TCPReady();
    void TeamFieldReady();
    void FormationReady();
    void MarkingModeReady();
    void MousePositioningReady();
    void TCPManualChanged(std::string);
public slots:
    void connectRefbox();
    void updateUDPStatus(int, int, int, int, int, int, int, int);
    void updateTCPStatus(std::string);
    void tcpHeader(int, int, int);
    void updateUDPLabel();
    void updateTCPLabel();
    void updateScore();
    void updateTeamAndField();
    void updateOdometryRobot();
    void coordinate(int,int,int,int,int,int);
    void coordinate2(int,int,int,int,int,int);
    void coordinate3(int,int,int,int,int,int);
    void refboxButtonClicked();
    void formationButtonClicked();
    void markingModeButtonClicked();
    void strategyButtonClicked();
    void mouseCurrentPos();
    void mouseClicked();
    void rotateRobot(int);
};

#endif // MAINWINDOW_H
