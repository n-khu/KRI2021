#ifndef TCP_H
#define TCP_H

#include <QObject>
#include <QObject>
#include <QThread>
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

Q_DECLARE_METATYPE(std::string)

#define BUFLEN 1024
#define SRV_IP "127.0.0.1"

class TCP : public QThread
{
    Q_OBJECT
public:
    explicit TCP(QObject *parent = 0);
    void run();

signals:
    void TCPStatusChanged(std::string);

private:
    int PORTRefbox = 28097;
};

#endif // TCP_H
