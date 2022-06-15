#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/video/video.hpp>
#include <opencv2/highgui.hpp>
#include <opencv/highgui.h>
#include <opencv2/core.hpp>
#include <opencv/cv.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <netdb.h> 
#include <termios.h>
#include <fcntl.h>
#include <string.h>
#include <sstream>
#include <iostream>
#include <vector>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PI 		3.14159265
#define SERVER 	"192.168.43.33"
#define PORT 		8080  		//The port on which to send data
#define MAXLINE 	1024  		//Max length of buffer

//static const char* portName = "/dev/ttyUSB0";			//TTL BIRU
static const char* portName = "/dev/video1";
static const char* portName1 = portName;				//TTL BIRU

FILE* serial_rcv;
FILE* serial_send;

int serialPort; 	// File descriptor for serial port
int serialPort1; 	// File descriptor for serial port

int STRIKER_2 		= 1;
int STRIKER_3 		= 2;
int KEEPER 			= 3;
int PROGRAM_UNTUK 	= STRIKER_2;

int mode_lapangan = 0;
int mode_marking = 0;
int mode_formasi [2];

int CYAN 	= 1;
int MAGENTA = 2;
int TEAM 	= 1;

int awal;
int nilai_x 	= 0;
int nilai_x1 	= 0;
int nilai_y		= 0;
int nilai_y1	= 0;
int rawYaw		= 0;
int Volt		= 0;	
int Proxi		= 0;

char *pry1;
char *pry2;
char *pry3;
char *res;

int pcount 		= 1;
int pcounts 	= 1;
int pcountss 	= 1;
int count_send 	= 0;

int X, Y, Z;

char buff_rcv_mk	[MAXLINE];
char buff_camera	[MAXLINE];
char buff_send		[MAXLINE];
char buff_rcv		[MAXLINE]; 
char buffer			[MAXLINE];
char send_data		[MAXLINE];

int first	= 0;
int second	= 0;
int third	= 0;
int fourth	= 0; 
int fifth	= 0;
int sixth	= 0;
int seventh = 0;
int eight 	= 0;
int Data1	= 0;
int Data2 	= 0;
int Data3 	= 0;

int kickoff = 0;
int mode_dribble = 0;

//Konversi nilai BS ke MK
double pengali_A[3];
double pengali_B[3];
double penambah_C[3];
double penambah_D[3];

double x_real_min[3] = {-80,0,800};
double x_real_max[3] = {0,800,880};
double y_real_min[3] = {-80,0,1200};
double y_real_max[3] = {0,1200,1280};

double x_BS_min[3] = {0,40,658};
double x_BS_max[3] = {40,658,696};
double y_BS_min[3] = {0,32,445};
double y_BS_max[3] = {32,445,472};

static const char * rcvString;

struct robot
{
	int coor_x[5];
	int coor_y[5];
	int x_or[4];
	int y_or[4];
	int x_ball[3];
	int y_ball[3];
	int Volt[2];
	int Proxi[2];
	int distance_ball[3];
	float x_mk_pos;
	float y_mk_pos;
	float x_mk_reset;
	float y_mk_reset;
	int x_cm[2];
	int y_cm[2];
	double x_cm_send;
	double y_cm_send;
	int angle_ball[2];
	int angle_obs;
	int jarak_obs;	
	double area_ball;
	double odo_ball[4];
	int corner_x_lawan[3];
	int corner_y_lawan[3];
	int goalkick_x_lawan[3];
	int goalkick_y_lawan[3];
	int kickoff_x_lawan[3];
	int kickoff_y_lawan[3];
	int dropball_x_lawan[3];
	int dropball_y_lawan[3];
	int penalty_x_lawan[3];
	int penalty_y_lawan[3];
	int freekick_x_lawan[3];
	int freekick_y_lawan[3];
	int penalty_x_kita[3];
	int penalty_y_kita[3];
	int reset_x[2];
	int reset_y[2];
	int yaw[3];
	int reset_yaw[2];
	int attack;
	int defend;
	int deathball[2];
	int arah_tendang;
	int reset_tuas;
	int condition;
	int condition_laptop;
	
} striker_2, striker_3, keeper;

void die(const char *s)
{
    perror(s);
    exit(1);
}

void Parsing_data(char input[],int &out1,int &out2,int &out3,int &out4,int &out5,int &out6,int &out7,int &out8)
{
    pry3 = strtok(input, ",");
    while (pry3 != 0 && pcounts <= 8)
    {
        if (pcounts == 1) 	   out1 = atof(pry3);
        else if (pcounts == 2) out2 = atof(pry3);        
        else if (pcounts == 3) out3 = atof(pry3);
        else if (pcounts == 4) out4 = atof(pry3);
        else if (pcounts == 5) out5 = atof(pry3);
		else if (pcounts == 6) out6 = atof(pry3);
        else if (pcounts == 7) out7 = atof(pry3);
		else if (pcounts == 8) out8 = atof(pry3);

        pry3 = strtok (0, ",");
        pcounts++;
    }
    if (pcounts == 9) pcounts = 1;
}

void Parsing_data1(char input[],int &out1,int &out2,int &out3,int &out4,int &out5,int &out6)//,int &out7,int &out8)
{
    pry1 = strtok(input, ",");
    while (pry1 != 0 && pcountss <= 6)
    {
        if (pcountss == 1) 		out1 = atof(pry1);
        else if (pcountss == 2) out2 = atof(pry1);        
        else if (pcountss == 3) out3 = atof(pry1);
        else if (pcountss == 4) out4 = atof(pry1);
        else if (pcountss == 5) out5 = atof(pry1);
        else if (pcountss == 6) out6 = atof(pry1);
        pry1 = strtok (0, ",");
        pcountss++;
    }
    if (pcountss == 7) pcountss = 1;
}

void Parsing_data3(char input[],int &out1,int &out2,int &out3,int &out4,int &out5,int &out6, int &out7)//,int &out7,int &out8)
{
    pry1 = strtok(input, ",");
    while (pry1 != 0 && pcountss <= 7)
    {
        if (pcountss == 1) 		out1 = atof(pry1);
        else if (pcountss == 2) out2 = atof(pry1);        
        else if (pcountss == 3) out3 = atof(pry1);
        else if (pcountss == 4) out4 = atof(pry1);
        else if (pcountss == 5) out5 = atof(pry1);
        else if (pcountss == 6) out6 = atof(pry1);
		else if (pcountss == 7) out7 = atof(pry1);
        pry1 = strtok (0, ",");
        pcountss++;
    }
    if (pcountss == 8) pcountss = 1;
}

void Parsing_data2(char input[],int &out1,int &out2,int &out3,int &out4,int &out5,int &out6,int &out7,int &out8,int &out9,int &out10,int &out11,int &out12,int &out13,int &out14,int &out15,int &out16,int &out17,int &out18,int &out19,int &out20,int &out21,int &out22,int &out23,int &out24,int &out25,int &out26,int &out27,int &out28,int &out29,int &out30,int &out31,int &out32,int &out33, int&out34)
{
    pry2 = strtok(input, ",");
    while (pry2 != 0 && pcount <= 33)
    {
        if (pcount == 1) 	  out1 = atof(pry2);
        else if (pcount == 2) out2 = atof(pry2);        
        else if (pcount == 3) out3 = atof(pry2);
		else if (pcount == 4) out4 = atof(pry2);
		else if (pcount == 5) out5 = atof(pry2);
		else if (pcount == 6) out6 = atof(pry2);
		else if (pcount == 7) out7 = atof(pry2);
		else if (pcount == 8) out8 = atof(pry2);
		else if (pcount == 9) out9 = atof(pry2);
		else if (pcount == 10) out10 = atof(pry2);
		else if (pcount == 11) out11 = atof(pry2);
		else if (pcount == 12) out12 = atof(pry2);
		else if (pcount == 13) out13 = atof(pry2);
		else if (pcount == 14) out14 = atof(pry2);
		else if (pcount == 15) out15 = atof(pry2);
		else if (pcount == 16) out16 = atof(pry2);
		else if (pcount == 17) out17 = atof(pry2);
		else if (pcount == 18) out18 = atof(pry2);
		else if (pcount == 19) out19 = atof(pry2);
		else if (pcount == 20) out20 = atof(pry2);
		else if (pcount == 21) out21 = atof(pry2);
		else if (pcount == 22) out22 = atof(pry2);
		else if (pcount == 23) out23 = atof(pry2);
		else if (pcount == 24) out24 = atof(pry2);
		else if (pcount == 25) out25 = atof(pry2);
		else if (pcount == 26) out26 = atof(pry2);
		else if (pcount == 27) out27 = atof(pry2);
		else if (pcount == 28) out28 = atof(pry2);
		else if (pcount == 29) out29 = atof(pry2);
		else if (pcount == 30) out30 = atof(pry2);
		else if (pcount == 31) out31 = atof(pry2);
		else if (pcount == 32) out32 = atof(pry2);
		else if (pcount == 33) out33 = atof(pry2);
		else if (pcount == 34) out34 = atof(pry2);

        pry2 = strtok (0, ",");
        pcount++;
    }
    if (pcount == 34) pcount = 1;
}

int main(void)
{
	int counter	= 0;
	int counts 	= 0;
	int counters = 0;
	int count	= 0;	
	//int count2	= 0;

	int i = 0;

	//================================FIFO INIT==================================//

    int fd;
    
    static const char * dataaddr = "/tmp/KAMERA"; //alamat sesuai dengan yang dibuat writernya
    mkfifo(dataaddr, 0666);
    
   	fd = open(dataaddr, O_RDWR | O_NDELAY | O_NOCTTY | O_NONBLOCK | O_ASYNC);

    /*---------- Setting the Attributes of the serial port using termios structure --------- */
		
	struct termios SerialPortSettings;				/* Create the structure                          */

    serialPort  = open(portName, O_RDWR | O_NOCTTY | O_NDELAY  | O_NONBLOCK | O_ASYNC);
	serialPort1 = open(portName1, O_RDWR | O_NOCTTY | O_NDELAY  | O_NONBLOCK | O_ASYNC);

    tcgetattr(serialPort, &SerialPortSettings);		/* Get the current attributes of the Serial port */
	tcgetattr(serialPort1, &SerialPortSettings);	/* Get the current attributes of the Serial port */

    // Flush the buffer one more time.
    tcflush(serialPort, TCIOFLUSH);
	tcflush(serialPort1, TCIOFLUSH);

    cfsetispeed(&SerialPortSettings,B38400); 		/* Set Read  Speed as 9600                       */
    cfsetospeed(&SerialPortSettings,B38400); 		/* Set Write Speed as 9600                       */

    SerialPortSettings.c_cflag &= ~PARENB;   		/* Disables the Parity Enable bit(PARENB),So No Parity   */
    SerialPortSettings.c_cflag &= ~CSTOPB;   		/* CSTOPB = 2 Stop bits,here it is cleared so 1 Stop bit */
    SerialPortSettings.c_cflag &= ~CSIZE;	 		/* Clears the mask for setting the data size             */
    SerialPortSettings.c_cflag |=  CS8;      		/* Set the data bits = 8                                 */
	
    SerialPortSettings.c_cflag &= ~CRTSCTS;       	/* No Hardware flow Control                         */
    SerialPortSettings.c_cflag |= CREAD;
	SerialPortSettings.c_cflag |= CLOCAL; 			/* Enable receiver,Ignore Modem Control lines       */ 
				    
    // Now that we've populated our options structure, let's push it back to the system.
    tcsetattr(serialPort,TCSANOW, &SerialPortSettings);
	tcsetattr(serialPort1,TCSANOW, &SerialPortSettings);          

    // Flush the buffer one more time.
    tcflush(serialPort, TCIOFLUSH);
	tcflush(serialPort1, TCIOFLUSH);

    // Flush the buffer one more time.
    tcflush(serialPort, TCIFLUSH);
	tcflush(serialPort1, TCIFLUSH);

    tcflush(serialPort, TCOFLUSH);
	tcflush(serialPort1, TCOFLUSH);

    serial_send = fopen(portName1, "w");
    serial_rcv = fopen(portName, "r");
   
    if (serial_rcv == NULL) 	printf("Failed to open serial port\n");
  	if (serial_send == NULL) 	printf("Failed to open serial port\n");

	//===========================UDP INIT==============================//

//	int n;
    int sockfd;
	 
	struct sockaddr_in servaddr; 
	unsigned int len = sizeof(servaddr);
    
    // Creating socket file descriptor 
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) 
	{ 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
  
    memset(&servaddr, 0, sizeof(servaddr)); 
      
    // Filling server information 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(PORT); 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
      
    if (inet_aton(SERVER , &servaddr.sin_addr) == 0)
    {
        fprintf(stderr, "inet_aton() failed\n");
        exit(1);
    }

	// Odometry Calculation from BS to MK
	for(int d = 0;d < 3;d++)
	{
		pengali_A[d] = (y_BS_max[d] - y_BS_min[d])/(x_real_max[d] - x_real_min[d]);
		pengali_B[d] = (x_BS_max[d] - x_BS_min[d])/(y_real_max[d] - y_real_min[d]);

		penambah_C[d] = ((y_BS_max[d] + y_BS_min[d]) - (pengali_A[d]*(x_real_max[d] + x_real_min[d])))/2;		
		penambah_D[d] = ((x_BS_max[d] + x_BS_min[d]) - (pengali_B[d]*(y_real_max[d] + y_real_min[d])))/2;
	}	

	while(1)
	{
		i++;
		if (i == 100000)
		{
			i = 0;
			count += 1;
		}

		if (count == 120) count = 0;			//VIRTUAL ODO

		counts++;
		if(counts == 10) counts = 0;			//PENOMORAN PRINTF

		counter++;
		if (counter == 500) counter = 0;		//SENDTOBS, RCVBS, RCVCAM, 

		counters++;
		if(counters == 500) counters = 0;		//SENDTOMK, RCVMK

		//==========================RECEIVE FROM BASESTATION=========================//

		if (counter == 150)
		{
			memset(buff_rcv,'\0', sizeof(buff_rcv));
			recvfrom(sockfd, buff_rcv, MAXLINE, 0, (struct sockaddr *) &servaddr, &len) ;
			printf("%s\n",buff_rcv);

//		    Parsing_data3(buff_rcv, X, Y, Z, mode_lapangan, TEAM, mode_formasi[0], mode_marking);

			//==========================DISPLAY DATA=========================//

			if (Data1 == 1 && Data2 == 1 && Data3 == 0) 		rcvString = "WELCOME"; 			
			else if (Data1 == 1 && Data2 == 2 && Data3 == 0) 	rcvString = "START"; 
			else if (Data1 == 1 && Data2 == 3 && Data3 == 0) 	rcvString = "STOP"; 
			else if (Data1 == 1 && Data2 == 4 && Data3 == 0) 	rcvString = "RESET"; 
			else if (Data1 == 1 && Data2 == 5 && Data3 == 0) 	rcvString = "FIRST_HALF";
			else if (Data1 == 1 && Data2 == 6 && Data3 == 0) 	rcvString = "SECOND_HALF"; 
			else if (Data1 == 1 && Data2 == 7 && Data3 == 0) 	rcvString = "HALF_TIME"; 
			else if (Data1 == 1 && Data2 == 8 && Data3 == 0) 	rcvString = "END_GAME";
			else if (Data1 == 2 && Data2 == 1 && Data3 == 1) 	rcvString = "DROPPED_BALL";
			else if (Data1 == 2 && Data2 == 1 && Data3 == 2)	rcvString = "PARKING";        

			else if (Data1 == 2 && Data2 == 2 && Data3 == 1) 	rcvString = "KICKOFF_CYAN";    
			else if (Data1 == 2 && Data2 == 2 && Data3 == 2) 	rcvString = "FREEKICK_CYAN"; 
			else if (Data1 == 2 && Data2 == 2 && Data3 == 3) 	rcvString = "GOALKICK_CYAN"; 
			else if (Data1 == 2 && Data2 == 2 && Data3 == 4) 	rcvString = "THROWIN_CYAN"; 
			else if (Data1 == 2 && Data2 == 2 && Data3 == 5) 	rcvString = "CORNER_CYAN"; 
			else if (Data1 == 2 && Data2 == 2 && Data3 == 6) 	rcvString = "PENALTY_CYAN"; 
			else if (Data1 == 2 && Data2 == 2 && Data3 == 7) 	rcvString = "GOAL_CYAN";
			else if (Data1 == 2 && Data2 == 2 && Data3 == 8) 	rcvString = "REPAIR_IN_CYAN"; 
			else if (Data1 == 2 && Data2 == 2 && Data3 == 9) 	rcvString = "REPAIR_OUT_CYAN"; 
			
			else if (Data1 == 2 && Data2 == 3 && Data3 == 1) 	rcvString = "KICKOFF_MAGENTA";
			else if (Data1 == 2 && Data2 == 3 && Data3 == 2) 	rcvString = "FREEKICK_MAGENTA";
			else if (Data1 == 2 && Data2 == 3 && Data3 == 3) 	rcvString = "GOALKICK_MAGENTA";
			else if (Data1 == 2 && Data2 == 3 && Data3 == 4) 	rcvString = "THROWIN_MAGENTA";
			else if (Data1 == 2 && Data2 == 3 && Data3 == 5) 	rcvString = "CORNER_MAGENTA";
			else if (Data1 == 2 && Data2 == 3 && Data3 == 6) 	rcvString = "PENALTY_MAGENTA";
			else if (Data1 == 2 && Data2 == 3 && Data3 == 7) 	rcvString = "GOAL_MAGENTA"; 
			else if (Data1 == 2 && Data2 == 3 && Data3 == 8) 	rcvString = "REPAIR_IN_MAGENTA";
			else if (Data1 == 2 && Data2 == 3 && Data3 == 9) 	rcvString = "REPAIR_OUT_MAGENTA"; 
			
//			if (TEAM == CYAN) printf("\n%d. UDP_CLIENT %s -- RefBox = %d,%d -- %s -- Team = %s -- mode = %d,%d -- ", counts, SERVER, Data1, Data2, rcvString, "CYAN", mode_marking, mode_formasi[0]);
//			else if (TEAM == MAGENTA) printf("\n%d. UDP_CLIENT %s -- RefBox = %d,%d -- %s -- Team = %s -- mode = %d,%d -- ", counts, SERVER, Data1, Data2, rcvString, "MAGENTA", mode_marking, mode_formasi[0]);
//			else printf("\n%d. UDP_CLIENT %s -- RefBox = %d,%d -- %s -- Team = %s -- mode = %d,%d -- ", counts, SERVER, Data1, Data2, rcvString, "NONE", mode_marking, mode_formasi[0]);

//			if ((tcsetattr(serialPort,TCSANOW,&SerialPortSettings)) != 0) printf("ERROR / ");
//		   		else printf("RECEIVED / ");
//			if ((tcsetattr(serialPort1,TCSANOW,&SerialPortSettings)) != 0) printf("ERROR");
//		   		else printf("SENT");

//			if (PROGRAM_UNTUK == STRIKER_2)
//			{
//				printf("\n   STRIKER 2 --> Jarak,Sudut Bola = %d,%d -- Koordinat = %d,%d -- Positioning = %d,%d -- Bola = %d,%d -- YAW = %d", (int)striker_2.distance_ball[0], (int)striker_2.angle_ball[0], (int)nilai_x, (int)nilai_y, (int)nilai_x1, (int)nilai_y1, striker_2.x_or[2], striker_2.y_or[2],/* striker_2.x_ball[0], striker_2.y_ball[0],*/ striker_2.yaw[0]);
//				printf("\n   STRIKER 3 --> Jarak.Sudut Bola = %d,%d -- Koordinat = %d,%d -- Positioning = %d,%d -- Bola = %d,%d -- YAW = %d", (int)striker_3.distance_ball[2], (int)striker_3.angle_ball[2], (int)striker_3.coor_x[4], (int)striker_3.coor_y[4], (int)striker_3.coor_x[2], (int)striker_3.coor_y[2], striker_3.x_ball[2], striker_3.y_ball[2], striker_3.yaw[2]);
//				printf("\n   KEEPER --> Jarak,Sudut Bola = %d,%d -- Koordinat = %d,%d -- Positioning = %d,%d -- Bola = %d,%d\n", (int)keeper.distance_ball[2], (int)keeper.angle_ball[2], (int)keeper.coor_x[4], (int)keeper.coor_y[4], (int)keeper.coor_x[2], (int)keeper.coor_y[2], keeper.x_ball[2], keeper.y_ball[2]);
//			}
//			if (PROGRAM_UNTUK == STRIKER_3)
//			{
//				printf("\n   STRIKER 2 --> Jarak,Sudut Bola = %d,%d -- Koordinat = %d,%d -- Positioning = %d,%d -- Bola = %d,%d -- YAW = %d", (int)striker_2.distance_ball[2], (int)striker_2.angle_ball[2], (int)striker_2.coor_x[4], (int)striker_2.coor_y[4], (int)striker_2.coor_y[2], (int)striker_2.coor_x[2], (int)striker_2.x_ball[2], (int)striker_2.y_ball[2], striker_2.yaw[2]);
//				printf("\n   STRIKER 3 --> Jarak,Sudut Bola = %d,%d -- Koordinat = %d,%d -- Positioning = %d,%d -- Bola = %d,%d -- YAW = %d", (int)striker_3.distance_ball[0], (int)striker_3.angle_ball[0], (int)striker_3.x_or[0], (int)striker_3.y_or[0], (int)striker_3.coor_x[2], (int)striker_3.coor_x[2], (int)striker_3.x_or[2], (int)striker_3.y_or[2],/* (int)striker_3.x_ball[0], (int)striker_3.y_ball[0],*/ (int)striker_3.yaw[2]);
//				printf("\n   KEEPER --> Jarak,Sudut Bola = %d,%d -- Koordinat = %d,%d -- Positioning = %d,%d -- Bola = %d,%d\n", (int)keeper.distance_ball[2], (int)keeper.angle_ball[2], (int)keeper.coor_x[4], (int)keeper.coor_y[4], (int)keeper.coor_x[2], (int)keeper.coor_y[2], keeper.x_ball[2], keeper.y_ball[2]);
//			}
//			if (PROGRAM_UNTUK == KEEPER) 
//			{
//				printf("\n   STRIKER 2 --> Jarak,Sudut Bola = %d,%d -- Koordinat = %d,%d -- Positioning = %d,%d -- Bola = %d,%d -- YAW = %d", (int)striker_2.distance_ball[2], (int)striker_2.angle_ball[2], (int)striker_2.coor_x[4], (int)striker_2.coor_y[4], (int)striker_2.coor_y[2], (int)striker_2.coor_x[2], (int)striker_2.x_ball[2], (int)striker_2.y_ball[2], striker_2.yaw[2]);
//				printf("\n   STRIKER 3 --> Jarak.Sudut Bola = %d,%d -- Koordinat = %d,%d -- Positioning = %d,%d -- Bola = %d,%d -- YAW = %d", (int)striker_3.distance_ball[2], (int)striker_3.angle_ball[2], (int)striker_3.coor_x[4], (int)striker_3.coor_y[4], (int)striker_3.coor_x[2], (int)striker_3.coor_y[2], striker_3.x_ball[2], striker_3.y_ball[2], striker_3.yaw[2]);
//				printf("\n   KEEPER --> Jarak,Sudut Bola = %d,%d -- Koordinat = %d,%d -- Positioning = %d,%d -- Bola = %d,%d\n", (int)keeper.distance_ball[0], (int)keeper.angle_ball[0], (int)keeper.x_or[0], (int)keeper.y_or[0], (int)keeper.coor_x[2], (int)keeper.coor_y[2], keeper.x_or[2], keeper.y_or[2]);
//			}   
		} 

		//==========================PARSING DATA MK=========================//
		
		Parsing_data2(buff_rcv, X, Y, Z, striker_3.coor_x[2], striker_3.coor_y[2], striker_2.coor_x[2], striker_2.coor_y[2], keeper.coor_x[2], 			keeper.coor_y[2], striker_3.coor_x[4], striker_3.coor_y[4], striker_2.coor_x[4], striker_2.coor_y[4], keeper.coor_x[4],
	    keeper.coor_y[4], striker_3.yaw[2], striker_2.yaw[2], keeper.yaw[2], striker_3.distance_ball[2], striker_2.distance_ball[2],
		keeper.distance_ball[2], striker_3.angle_ball[2], striker_2.angle_ball[2], keeper.angle_ball[2], striker_3.x_ball[2],
		striker_3.y_ball[2], striker_2.x_ball[2], striker_2.y_ball[2], keeper.x_ball[2], keeper.y_ball[2], mode_lapangan, TEAM,
		mode_formasi[0], mode_marking);

		Data1 = X;
		Data2 = Y;
		Data3 = Z;

		if (Data1 == 1 && Data2 == 2 && Data3 == 0)
		{
			striker_3.coor_y[0] = striker_3.coor_x[0];
			striker_3.coor_x[0] = striker_3.coor_y[0];
			striker_2.coor_y[0] = striker_2.coor_x[0];
			striker_2.coor_x[0] = striker_2.coor_y[0];
			keeper.coor_x[0] = keeper.coor_x[0];
			keeper.coor_y[0] = keeper.coor_y[0];
		}		

		else
		{			
			striker_3.coor_x[0] = striker_3.coor_x[2];
			striker_3.coor_y[0] = striker_3.coor_y[2];
			striker_2.coor_x[0] = striker_2.coor_x[2];
			striker_2.coor_y[0] = striker_2.coor_y[2];
			keeper.coor_x[0] = keeper.coor_x[2];
			keeper.coor_y[0] = keeper.coor_y[2];
		}

		//==========================RECEIVE FROM MK=========================//

		if(counters %20 == 0)
		{
			memset(buff_rcv_mk, '\0', sizeof(buff_rcv_mk));			
			read(serialPort, &buff_rcv_mk, sizeof(buff_rcv_mk));
			Parsing_data(buff_rcv_mk, awal, nilai_x, nilai_y, nilai_x1, nilai_y1, rawYaw, Volt, Proxi);

			if (awal == 11)
			{
				if (PROGRAM_UNTUK == STRIKER_2)
				{			
			   		striker_2.x_or[0]  = nilai_x;							// odometry x robot
					striker_2.y_or[0]  = nilai_y;							// odometry y robot
					striker_2.x_or[2]  = nilai_x1;							// odometry x bola
					striker_2.y_or[2]  = nilai_y1;							// odometry y bola
					striker_2.yaw[0]   = rawYaw;
					striker_2.Volt[0]  = Volt;
					striker_2.Proxi[0] = Proxi;
				}
				else if (PROGRAM_UNTUK == STRIKER_3)
				{			
			   		striker_3.x_or[0]  = nilai_x;							// odometry x robot
					striker_3.y_or[0]  = nilai_y;							// odometry y robot
					striker_3.x_or[2]  = nilai_x1;							// odometry x bola
					striker_3.y_or[2]  = nilai_y1;							// odometry y bola
					striker_3.yaw[0]   = rawYaw;
					striker_3.Volt[0]  = Volt;
					striker_3.Proxi[0] = Proxi;
				}
				else if (PROGRAM_UNTUK == KEEPER)
				{
					keeper.x_or[0]     = nilai_x;							// odometry x robot					
					keeper.y_or[0]     = nilai_y;                           // odometry y robot
					keeper.x_or[2]     = nilai_x1;							// odometry x bola
					keeper.y_or[2]     = nilai_y1;							// odometry y bola
					keeper.yaw[0]      = rawYaw;
					keeper.Volt[0]     = Volt;
					keeper.Proxi[0]    = Proxi;
				}
			}
		}

		//==========================SEND TO MK=========================//

		if(counters %250 == 0)
		{
			//POSITIONING ST2
			if(striker_2.coor_x[0] < x_BS_min[1]) 
					striker_2.y_mk_pos = (striker_2.coor_x[0] - penambah_D[0])/pengali_B[0];

			else if(striker_2.coor_x[0] >= x_BS_min[1] && striker_2.coor_x[0] <= x_BS_max[1]) 
					striker_2.y_mk_pos = (striker_2.coor_x[0] - penambah_D[1])/pengali_B[1];

			else if(striker_2.coor_x[0] > x_BS_max[1]) 
					striker_2.y_mk_pos = (striker_2.coor_x[0] - penambah_D[2])/pengali_B[2];


			if(striker_2.coor_y[0] < y_BS_min[1]) 
					striker_2.x_mk_pos = (striker_2.coor_y[0] - penambah_C[0])/pengali_A[0];

			else if(striker_2.coor_y[0] >= y_BS_min[1] && striker_2.coor_y[0] <= y_BS_max[1]) 
					striker_2.x_mk_pos = (striker_2.coor_y[0] - penambah_C[1])/pengali_A[1];

			else if(striker_2.coor_y[0] > y_BS_max[0])
					striker_2.x_mk_pos = (striker_2.coor_y[0] - penambah_C[2])/pengali_A[2];

			//POSITIONING ST3
			if(striker_3.coor_x[0] < x_BS_min[1]) 
					striker_3.y_mk_pos = (striker_3.coor_x[0] - penambah_D[0])/pengali_B[0];

			else if(striker_3.coor_x[0] >= x_BS_min[1] && striker_3.coor_x[0] <= x_BS_max[1]) 
					striker_3.y_mk_pos = (striker_3.coor_x[0] - penambah_D[1])/pengali_B[1];

			else if(striker_3.coor_x[0] > x_BS_max[1]) 
					striker_3.y_mk_pos = (striker_3.coor_x[0] - penambah_D[2])/pengali_B[2];


			if(striker_3.coor_y[0] < y_BS_min[1]) 
					striker_3.x_mk_pos = (striker_3.coor_y[0] - penambah_C[0])/pengali_A[0];

			else if(striker_3.coor_y[0] >= y_BS_min[1] && striker_3.coor_y[0] <= y_BS_max[1]) 
					striker_3.x_mk_pos = (striker_3.coor_y[0] - penambah_C[1])/pengali_A[1];

			else if(striker_3.coor_y[0] > y_BS_max[1]) 
					striker_3.x_mk_pos = (striker_3.coor_y[0] - penambah_C[2])/pengali_A[2];
			
			//POSITIONING GK

			if (PROGRAM_UNTUK == STRIKER_2)
			{
				if (count_send == 100) count_send = 0;
				++count_send;
				
				if(count_send == 5)
					fprintf(serial_send, "%d,%d,%d,0\n", Data1, Data2, Data3);
				
//				else if(count_send == 10)
//					fprintf(serial_send, "4,1,%d,%d,%d,%d\n", (int)keeper.distance_ball[2], (int)keeper.angle_ball[2], (int)keeper.jarak_obs, (int)keeper.angle_obs);

				else if(count_send == 15)
					fprintf(serial_send, "4,2,%d,%d,%d,%d\n", (int)striker_2.distance_ball[0], (int)striker_2.angle_ball[0], (int)striker_2.jarak_obs, (int)striker_2.angle_obs);

//				else if(count_send == 20)
//					fprintf(serial_send, "4,3,%d,%d,%d,%d\n", (int)striker_3.distance_ball[2], (int)striker_3.angle_ball[2], (int)striker_3.jarak_obs, (int)striker_3.angle_obs);

//				else if(count_send == 25)
//					fprintf(serial_send, "5,1,%d,%d,%d,%d\n", (int)keeper.coor_x[4], (int)keeper.coor_y[4], (int)keeper.condition, (int)keeper.condition_laptop);

				else if(count_send == 30)
					fprintf(serial_send, "5,2,%d,%d,%d,%d\n", (int)striker_2.coor_x[4], (int)striker_2.coor_y[4], (int)striker_2.condition, (int)striker_2.condition_laptop);

//				else if(count_send == 35)
//					fprintf(serial_send, "5,3,%d,%d,%d,%d\n", (int)striker_3.coor_x[4], (int)striker_3.coor_y[4], (int)striker_3.condition, (int)striker_3.condition_laptop);

				else if(count_send == 40)
					fprintf(serial_send, "99,1,%d,%d,%d,%d\n", (int)striker_2.attack, (int)striker_2.defend, (int)striker_2.deathball[0], (int)striker_2.deathball[1]);

				else if(count_send == 45)
					fprintf(serial_send, "99,2,%d,%d,%d,%d\n", (int)striker_2.arah_tendang, (int)striker_2.reset_yaw[0], (int)striker_2.reset_x[0], (int)striker_2.reset_y[0]);

				else if(count_send == 50)
					fprintf(serial_send, "99,3,%d,0,%d,%d\n", (int)striker_2.reset_tuas, (int)striker_2.x_mk_pos, (int)striker_2.y_mk_pos);

//				else if(count_send == 55)
//					fprintf(serial_send, "66,1,%d,%d,%d,%d\n", (int)striker_3.attack, (int)striker_3.defend, (int)striker_3.deathball[0], (int)striker_3.deathball[1]);

//				else if(count_send == 60)
//					fprintf(serial_send, "66,2,%d,%d,%d,%d\n", (int)striker_3.arah_tendang, (int)striker_3.reset_yaw[0], (int)striker_3.reset_x[0], (int)striker_3.reset_y[0]);

//				else if(count_send == 65)
//					fprintf(serial_send, "66,3,%d,0,%d,%d\n", (int)striker_3.reset_tuas, (int)striker_3.x_mk_pos, (int)striker_3.y_mk_pos);

				else if(count_send == 70)
					fprintf(serial_send, "69,%d,%d,%d,%d,0\n", (int)TEAM, (int)mode_formasi[0], (int)kickoff, (int)mode_dribble);

			}	

//			else if (PROGRAM_UNTUK == STRIKER_3)
//			{

//			}	

//			else if (PROGRAM_UNTUK == KEEPER)
//			{

//			}	
		}

		//==========================RECEIVE FROM LAPTOP / CAMERA=========================//

		if(counter == 200)
		{
			memset(buff_camera, '\0', sizeof(buff_camera));
			read(fd, buff_camera, sizeof(buff_camera));
			Parsing_data1(buff_camera, first, second, third, fourth, fifth, sixth);

			if (first == 98)										
			{
				if (PROGRAM_UNTUK == STRIKER_2)
				{
					striker_2.distance_ball[0] 	= second;
					striker_2.angle_ball[0] 	= third;
					striker_2.area_ball 		= fourth;
					striker_2.y_ball[0] 		= fifth;
					striker_2.x_ball[0] 		= sixth;
				}
				else if (PROGRAM_UNTUK == STRIKER_3)
				{
					striker_3.distance_ball[0] 	= second;
					striker_3.angle_ball[0] 	= third;
					striker_3.area_ball 		= fourth;
					striker_3.y_ball[0] 		= fifth;
					striker_3.x_ball[0] 		= sixth;
				}
				else if (PROGRAM_UNTUK == KEEPER)
				{
					keeper.distance_ball[0] 	= second;
					keeper.angle_ball[0] 		= third;
					keeper.area_ball 			= fourth;
					keeper.x_ball[0] 			= fifth;
					keeper.y_ball[0] 			= sixth;
				}
			}
		}

		//==========================SEND TO BASESTATION=========================//

		if (counter == 100)
		{
//						sprintf(buff_send, "90, %d, 300, %d, %d, %d, %d, %d, %d, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0\n", count + 480, count + 10, count + 15, count + 20, count + 25, count + 30, count + 35);  
//		    sendto(sockfd, buff_send, strlen(buff_send), MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr)); 

			if (PROGRAM_UNTUK == STRIKER_2)
			{
				if(striker_2.y_or[1] < y_BS_min[1]) 
						striker_2.x_cm_send = (striker_2.y_or[1] - penambah_C[0])/pengali_A[0];

				else if(striker_2.y_or[1] >= y_BS_min[1] && striker_2.y_or[1] <= y_BS_max[1]) //
						striker_2.x_cm_send = (striker_2.y_or[1] - penambah_C[1])/pengali_A[1];
		
				else if(striker_2.y_or[1] > y_BS_max[1]) 
						striker_2.x_cm_send = (striker_2.y_or[1] - penambah_C[2])/pengali_A[2];

				//----------------------------------------------------------------------------//

				if(striker_2.x_or[1] < x_BS_min[1]) 
						striker_2.y_cm_send = (striker_2.x_or[1] - penambah_D[0])/pengali_B[0];

				else if(striker_2.x_or[1] >= x_BS_min[1] && striker_2.x_or[1] <= x_BS_max[1]) 
						striker_2.y_cm_send = (striker_2.x_or[1] - penambah_D[1])/pengali_B[1];

				else if(striker_2.x_or[1] > x_BS_min[1]) 
						striker_2.y_cm_send = (striker_2.x_or[1] - penambah_D[2])/pengali_B[2];

				striker_2.Volt[1] = striker_2.Volt[0];
				
				striker_2.x_or[1] = striker_2.x_or[0];
				striker_2.y_or[1] = striker_2.y_or[0];
				
			}
			else if (PROGRAM_UNTUK == STRIKER_3){

				if(striker_3.y_or[1] < y_BS_min[1]) 
						striker_3.x_cm_send = (striker_3.y_or[1] - penambah_C[0])/pengali_A[0];

				else if(striker_3.y_or[1] >= y_BS_min[1] && striker_3.y_or[1] <= y_BS_max[1])
						striker_3.x_cm_send = (striker_3.y_or[1] - penambah_C[1])/pengali_A[1];
		
				else if(striker_3.y_or[1] > y_BS_max[1]) 
						striker_3.x_cm_send = (striker_3.y_or[1] - penambah_C[2])/pengali_A[2];

				//----------------------------------------------------------------------------//

				if(striker_3.x_or[1] < x_BS_min[1]) 
						striker_3.y_cm_send = (striker_3.x_or[1] - penambah_D[0])/pengali_B[0];

				else if(striker_3.x_or[1] >= x_BS_min[1] && striker_3.x_or[1] <= x_BS_max[1]) 
						striker_3.y_cm_send = (striker_3.x_or[1] - penambah_D[1])/pengali_B[1];

				else if(striker_3.x_or[1] > x_BS_max[1]) 
						striker_3.y_cm_send = (striker_3.x_or[1] - penambah_D[2])/pengali_B[2];

				striker_3.Volt[1] = striker_3.Volt[0];	

				striker_3.x_or[1] = striker_3.x_or[0];
				striker_3.y_or[1] = striker_3.y_or[0];

			}

			if (PROGRAM_UNTUK == STRIKER_2)
			{
				sprintf(buff_send, "30,%d,%d,%d,%d,%d,%d,%d,%d,%d\n", (int)striker_2.x_or[1], (int)striker_2.y_or[1], (int)striker_2.distance_ball[0], (int)striker_2.angle_ball[0], (int)striker_2.x_or[2], (int)striker_2.y_or[2], (int)striker_2.yaw[0], (int)striker_2.x_cm_send, (int)striker_2.y_cm_send);
				sendto(sockfd, buff_send, strlen(buff_send), MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));
				memset(buff_send,'\0', sizeof(buff_send));	
			}
			else if (PROGRAM_UNTUK == STRIKER_3)
			{
				sprintf(buff_send, "60,%d,%d,%d,%d,%d,%d,%d,%d,%d\n", (int)striker_3.x_or[1], (int)striker_3.y_or[1], (int)striker_3.distance_ball[0], (int)striker_3.angle_ball[0], (int)striker_3.x_or[2], (int)striker_3.y_or[2], (int)striker_3.yaw[0],(int)striker_3.x_cm_send, (int)striker_3.y_cm_send);
				sendto(sockfd, buff_send, strlen(buff_send), MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));
				memset(buff_send,'\0', sizeof(buff_send));	
			}
			else if (PROGRAM_UNTUK == KEEPER)
			{
				sprintf(buff_send, "90,%d,%d,%d,%d,%d,%d,%d,0,0\n", (int)keeper.x_or[0], (int)keeper.y_or[0], (int)keeper.distance_ball[0], (int)keeper.angle_ball[0], (int)keeper.x_or[2], (int)keeper.y_or[2], (int)keeper.yaw[0]);
				sendto(sockfd, buff_send, strlen(buff_send), MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));
				memset(buff_send,'\0', sizeof(buff_send));	
			}
		}
  }
    close(sockfd); 
    return 0; 
} 
