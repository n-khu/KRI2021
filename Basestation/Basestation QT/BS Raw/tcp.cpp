#include "tcp.h"
#include <QDebug>

TCP::TCP(QObject *parent) :
    QThread(parent)
{
    qRegisterMetaType<std::string>();
}

void TCP::run()
{
    std::string rcvString;
    int sockfd;
    char acc_refbox[2] = "L";

    struct sockaddr_in serv_addr;
    struct hostent *server;

    qDebug() << "Contacting REFBOX IP : " << SRV_IP;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        qDebug() << "ERROR opening socket";

    if ((server = gethostbyname(SRV_IP) ) == NULL)
        qDebug() << "ERROR, no such host\n";

    bzero( (char *) &acc_refbox, sizeof(acc_refbox));
    bzero( (char *) &serv_addr, sizeof(serv_addr));

    // zero out the structure
    serv_addr.sin_family = AF_INET;
    bcopy( (char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(PORTRefbox);

    if (::connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
        qDebug() << "ERROR connecting";

    int counter = 0;

    while (1)
    {
        counter++ ;
        if (counter == 10) counter = 0;
        read(sockfd, acc_refbox, sizeof(acc_refbox));

        if(strcmp(acc_refbox, "W") == 0) rcvString = "WELCOME";
        else if(strcmp(acc_refbox, "s") == 0) rcvString = "START";
        else if(strcmp(acc_refbox, "S") == 0) rcvString = "STOP";
        else if(strcmp(acc_refbox, "Z") == 0) rcvString = "RESET";
        else if(strcmp(acc_refbox, "1") == 0) rcvString = "FIRST HALF";
        else if(strcmp(acc_refbox, "2") == 0) rcvString = "SECOND HALF";
        else if(strcmp(acc_refbox, "h") == 0) rcvString = "HALF TIME";
        else if(strcmp(acc_refbox, "e") == 0) rcvString = "END GAME";
        else if(strcmp(acc_refbox, "N") == 0) rcvString = "DROPPED BALL";

        else if(strcmp(acc_refbox, "A") == 0) rcvString = "GOAL CYAN";
        else if(strcmp(acc_refbox, "K") == 0) rcvString = "KICKOFF CYAN";
        else if(strcmp(acc_refbox, "F") == 0) rcvString = "FREEKICK CYAN";
        else if(strcmp(acc_refbox, "G") == 0) rcvString = "GOALKICK CYAN";
        else if(strcmp(acc_refbox, "P") == 0) rcvString = "PENALTY CYAN";
        else if(strcmp(acc_refbox, "C") == 0) rcvString = "CORNER CYAN";
        else if(strcmp(acc_refbox, "T") == 0) rcvString = "THROWIN CYAN";
        else if(strcmp(acc_refbox, "I") == 0) rcvString = "REPAIR IN CYAN";
        else if(strcmp(acc_refbox, "O") == 0) rcvString = "REPAIR OUT CYAN";

        else if(strcmp(acc_refbox, "a") == 0) rcvString = "GOAL MAGENTA";
        else if(strcmp(acc_refbox, "k") == 0) rcvString = "KICKOFF MAGENTA";
        else if(strcmp(acc_refbox, "f") == 0) rcvString = "FREEKICK MAGENTA";
        else if(strcmp(acc_refbox, "g") == 0) rcvString = "GOALKICK MAGENTA";
        else if(strcmp(acc_refbox, "p") == 0) rcvString = "PENALTY MAGENTA";
        else if(strcmp(acc_refbox, "c") == 0) rcvString = "CORNER MAGENTA";
        else if(strcmp(acc_refbox, "t") == 0) rcvString = "THROWIN MAGENTA";
        else if(strcmp(acc_refbox, "i") == 0) rcvString = "REPAIR IN MAGENTA";
        else if(strcmp(acc_refbox, "o") == 0) rcvString = "REPAIR OUT MAGENTA";

        emit TCPStatusChanged(rcvString);
        qDebug() << acc_refbox;
        this->msleep(10);
    }
}
