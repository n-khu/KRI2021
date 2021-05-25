#include "udp.h"

int sockfd;
int ref1, ref2, ref3;
int a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t;
int u, v, w, x, y, z,aa,ab,ac,ad,ae,af,ag,ah,ai,aj,ak,al,am;
int pcounts = 1;

int CYANUDP = 1;
int MAGENTAUDP = 2;
int TEAMUDP = CYANUDP;

int KIRIUDP = 1;
int KANANUDP = 2;
int FIELDUDP = KIRIUDP;

int formationModeUDP = 0;
int markingModeUDP = 0;

char buffer[MAXLINE];
char buffer_send[MAXLINE];
char send_data[MAXLINE];
char* pry3;
struct sockaddr_in servaddr, cliaddr;
struct robots
{
    int coor_x[5];
    int coor_y[5];
    int dist_ball;
    int reset_x[5];
    int reset_y[5];
    int angle_ball;
    int mark;
    int x_ball[3];
    int y_ball[3];
    int yaw;
    int x_cm[0];
    int y_cm[0];
} striker_2_temporary, striker_3_temporary, keeper_temporary;

UDP::UDP(QObject *parent) :
    QThread(parent)
{
    connect(this,SIGNAL(UDPStatusUpdated()),this,SLOT(start()));
}

void UDP::run()
{
    qDebug() << "Starting..";

    // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    // Filling server information
    servaddr.sin_family      = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port        = htons(8080);

    // Bind the socket with the server address
    if ( bind(sockfd, (const struct sockaddr *)&servaddr,
            sizeof(servaddr)) < 0 )
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    unsigned int len = sizeof(servaddr);
    int n;
    int count = 0;
    int counter = 0;

    while(1)
    {
        count++;
        if (count == 50) count = 0;
        counter++ ;
        if (counter == 10) counter = 0;

        if(count == 4)
        {
//        for(int x = 0; x < 5; x++)
//        {
            recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, (struct sockaddr *) &cliaddr, &len);
            parsingData(buffer, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t);
            memset(buffer, 0, sizeof(buffer));

            if (a == 30)		//STRIKER_2
            {
                striker_2_temporary.coor_y[0] = b;
                striker_2_temporary.coor_x[0] = c;
                striker_2_temporary.dist_ball = d;
                striker_2_temporary.angle_ball = e;
                striker_2_temporary.x_ball[0] = f;
                striker_2_temporary.y_ball[0] = g;
                striker_2_temporary.yaw = h;
                striker_2_temporary.mark = 1;
                striker_2_temporary.x_cm[0] = i;
                striker_2_temporary.y_cm[0] = j;

                qDebug() << striker_2_temporary.coor_x[0];
                emit rcvUDPData(a, striker_2_temporary.coor_x[0], striker_2_temporary.coor_y[0], striker_2_temporary.dist_ball, striker_2_temporary.angle_ball, striker_2_temporary.x_ball[0], striker_2_temporary.y_ball[0], striker_2_temporary.yaw);
            }

            if (a == 60)		//STRIKER_3
            {
                striker_3_temporary.coor_y[0] = b;
                striker_3_temporary.coor_x[0] = c;
                striker_3_temporary.dist_ball = d;
                striker_3_temporary.angle_ball = e;
                striker_3_temporary.x_ball[0] = f;
                striker_3_temporary.y_ball[0] = g;
                striker_3_temporary.yaw = h;
                striker_3_temporary.mark = 1;
                striker_3_temporary.x_cm[0] = i;
                striker_3_temporary.y_cm[0] = j;
                emit rcvUDPData(a, striker_3_temporary.coor_x[0], striker_3_temporary.coor_y[0], striker_3_temporary.dist_ball, striker_3_temporary.angle_ball, striker_3_temporary.x_ball[0], striker_3_temporary.y_ball[0], striker_3_temporary.yaw);
            }

            if (a == 90)		//KEEPER
            {
                keeper_temporary.coor_y[0] = b;
                keeper_temporary.coor_x[0] = c;
                keeper_temporary.dist_ball = d;
                keeper_temporary.angle_ball = e;
                keeper_temporary.x_ball[0] = f;
                keeper_temporary.y_ball[0] = g;
                keeper_temporary.yaw = h;
                keeper_temporary.mark = 1;
                keeper_temporary.x_cm[0] = 0;
                keeper_temporary.y_cm[0] = 0;
                emit rcvUDPData(a, keeper_temporary.coor_x[0], keeper_temporary.coor_y[0], keeper_temporary.dist_ball, keeper_temporary.angle_ball, keeper_temporary.x_ball[0], keeper_temporary.y_ball[0], keeper_temporary.yaw);
            }
        }
//        }

        if(count == 2)
        {
            sprintf(buffer_send,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",ref1,ref2,
                    ref3,striker_3_temporary.coor_x[2],striker_3_temporary.coor_y[2],striker_2_temporary.coor_x[2],
                    striker_2_temporary.coor_y[2],keeper_temporary.coor_x[2],keeper_temporary.coor_y[2],striker_3_temporary.coor_x[4],
                    striker_3_temporary.coor_y[4],striker_2_temporary.coor_x[4],striker_2_temporary.coor_y[4],keeper_temporary.coor_x[4],
                    keeper_temporary.coor_y[4],striker_3_temporary.yaw,striker_2_temporary.yaw,keeper_temporary.yaw,striker_3_temporary.dist_ball,
                    striker_2_temporary.dist_ball,keeper_temporary.dist_ball,striker_3_temporary.angle_ball,striker_2_temporary.angle_ball,
                    keeper_temporary.angle_ball,striker_3_temporary.x_ball[0],striker_3_temporary.y_ball[0],striker_2_temporary.x_ball[0],
                    striker_2_temporary.y_ball[0],keeper_temporary.x_ball[0],keeper_temporary.y_ball[0],FIELDUDP,TEAMUDP,formationModeUDP,
                    markingModeUDP);

//            sprintf(buffer_send,"%d,%d,%d,%d,%d,%d,%d\n",ref1,ref2,ref3,FIELDUDP,TEAMUDP,formationModeUDP,markingModeUDP);

            sendto(sockfd, buffer_send, strlen(buffer_send), 0, (struct sockaddr *) &cliaddr, len);
            qDebug() << buffer_send;
        }
    }
}

void UDP::updateUDPSendStatus(int u, int v, int w, int x, int y, int z, int aa, int ab, int ac, int ad, int ae, int af, int ag, int ah,
                              int ai, int aj, int ak, int al, int am, int an, int ao, int ap)
{
    striker_3_temporary.coor_x[2] = u;
    striker_3_temporary.coor_y[2] = v;
    striker_2_temporary.coor_x[2] = w;
    striker_2_temporary.coor_y[2] = x;
    keeper_temporary.coor_x[2] = y;
    keeper_temporary.coor_y[2] = z;
    striker_3_temporary.coor_x[4] = aa;
    striker_3_temporary.coor_y[4] = ab;
    striker_2_temporary.coor_x[4] = ac;
    striker_2_temporary.coor_y[4] = ad;
    keeper_temporary.coor_x[4] = ae;
    keeper_temporary.coor_y[4] = af;
    striker_3_temporary.yaw = ag;
    striker_2_temporary.yaw = ah;
    keeper_temporary.yaw = ai;
    FIELDUDP = aj;
    TEAMUDP = ak;
    formationModeUDP = al;
    markingModeUDP = am;
    ref1 = an;
    ref2 = ao;
    ref3 = ap;

    qDebug() << ref1 << ref2 << ref3;
    emit UDPStatusUpdated();
}

void UDP::parsingData(char input[], int &out1, int &out2, int &out3, int &out4, int &out5, int &out6, int &out7, int &out8, int &out9,
        int &out10, int &out11, int &out12, int &out13, int &out14, int &out15, int &out16, int &out17, int &out18, int &out19, int &out20)
{
    pry3 = strtok(input, ",");
    while (pry3 != 0 && pcounts <= 20)
    {
        if (pcounts == 1) out1 = atof(pry3);
        else if (pcounts == 2) out2 = atof(pry3);
        else if (pcounts == 3) out3 = atof(pry3);
        else if (pcounts == 4) out4 = atof(pry3);
        else if (pcounts == 5) out5 = atof(pry3);
        else if (pcounts == 6) out6 = atof(pry3);
        else if (pcounts == 7) out7 = atof(pry3);
        else if (pcounts == 8) out8 = atof(pry3);
        else if (pcounts == 9) out9 = atof(pry3);
        else if (pcounts == 10) out10 = atof(pry3);
        else if (pcounts == 11) out11 = atof(pry3);
        else if (pcounts == 12) out12 = atof(pry3);
        else if (pcounts == 13) out13 = atof(pry3);
        else if (pcounts == 14) out14 = atof(pry3);
        else if (pcounts == 15) out15 = atof(pry3);
        else if (pcounts == 16) out16 = atof(pry3);
        else if (pcounts == 17) out17 = atof(pry3);
        else if (pcounts == 18) out18 = atof(pry3);
        else if (pcounts == 19) out19 = atof(pry3);
        else if (pcounts == 20) out20 = atof(pry3);

        pry3 = strtok (0, ",");
        pcounts++;
    }
    if (pcounts == 21) pcounts = 1;
}
