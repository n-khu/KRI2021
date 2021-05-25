#ifndef UDP_H
#define UDP_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include <math.h>
#include <netdb.h>

//#define SERVER "192.168.0.100"
#define SERVER "127.0.0.1"
#define MAXLINE 512

class UDP : public QThread
{
    Q_OBJECT
public:
    explicit UDP(QObject *parent = 0);
    void run();

private:
    void parsingData(char input[], int &out1, int &out2, int &out3, int &out4, int &out5, int &out6, int &out7, int &out8, int &out9,
                         int &out10, int &out11, int &out12, int &out13, int &out14, int &out15, int &out16, int &out17, int &out18, int &out19, int &out20);

signals:
    void rcvUDPData(int, int, int, int, int, int, int, int);
    void UDPStatusUpdated();

public slots:
    void updateUDPSendStatus(int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int);

};
#endif // UDP_H
