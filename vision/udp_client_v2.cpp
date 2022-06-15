/*
 Simple udp client
 
 to see ip server, compile this
 open terminal and compile : "ip addr show"
 
 find text like this below :
 "inet 10.26.153.229/23 brd 10.26.153.255 scope global wlan0"
 
 10.26.153.229 is server ip address !!
 
 */
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/video.hpp>
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <netdb.h>
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
#pragma GCC diagnostic ignored "-Wwrite-strings"

#define PI 3.14159265
//#define SERVER "172.16.210.1" 
//#define SERVER "10.26.56.92"
#define SERVER "192.168.0.101" 
// #define SERVER "127.0.0.1"
#define BUFLEN 512  //Max length of buffer
#define PORT 6363   //The port on which to send data

static const char* portName = "/dev/video0";		//localhost
// static const char* portName = "/dev/ttyUSB0";		//TTL BIRU
static const char* portName1 = portName;				//TTL BIRU

int STRIKER_2 = 1;
int STRIKER_3 = 2;
int KEEPER = 3;
int PROGRAM_UNTUK = STRIKER_2;

int CYAN = 1;
int MAGENTA = 2;
int TEAM = 0;

FILE* serial_rcv;
FILE* serial_send;

//konfersi nilai BaseStation ke MK
double pengali_A[3];
double pengali_B[3];
double penambah_C[3];
double penambah_D[3];

double x_real_min[3] = {-38,0,450};
double x_real_max[3] = {0,450,488};
double y_real_min[3] = {-76,0,600};
double y_real_max[3] = {0,600,676};

double x_BS_min[3] = {0,70,620};
double x_BS_max[3] = {70,620,690};
double y_BS_min[3] = {0,34,448};
double y_BS_max[3] = {34,448,483};

//=== RESET ===//
int Header_reset;

int A,B; //for PIPE
int C,D; //for Receive UDP
int mode_marking = 0;
int mode_formasi[2];
int temp_formasi = -1;
int Jarak_Bola_Robot_1_ke_2;
int Jarak_Bola_Robot_1_ke_3;
int Jarak_Bola_Robot_2_ke_1;
int Jarak_Bola_Robot_2_ke_3;
int Jarak_Bola_Robot_3_ke_1;
int Jarak_Bola_Robot_3_ke_2;
int Jarak_Bola_Robot3;
int Jarak_Bola_Robot2;
int X,Y,Z,W;
int nilai_xreal;
int nilai_yreal;
int nilai_x, nilai_x1;
int nilai_y, nilai_y1;
int awal;
int x_coor;
int y_coor;
int rawYaw;
int Volt;
int Proxi;

//------edit
int flag_wifi; //button baru
int dummy_pos1; //posisi dummy 1-6
int dummy_pos2; //posisi dummy 7-8
//------

const int corner_x_lawan = 0;
const int corner_y_lawan = 0;
const int kickoff_x_lawan = 120;
const int kickoff_y_lawan = 240;
const int goalkick_x_lawan = 120;
const int goalkick_y_lawan = 240;

char buff_send[512];
char send_main[512];
char send_odo[512];
char write_buffer[512];
char buff_feedback[512];
char buff_camera[512];
char message_mk[512];
char sendmk[512];
static const char * rcvString;

//=============================================================================//
//=======================Split String Version 2================================//
//=============================================================================//
//---------------------------------------var global usart

char *pry1;
char *pry2;
char *pry3;
char *res;

int pcount = 1;
int pcounts = 1;
int pcountss = 1;
int pc = 1;

int x_res[2];
int y_res[2];

struct robot
{
	int coor_x[3];
	int coor_y[3];
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
} striker_2, striker_3, keeper;

void Parsing_data(char input[],int &out1,int &out2,int &out3,int &out4,int &out5,int &out6,int &out7,int &out8)
{
    pry3 = strtok(input, ",");
    while (pry3 != 0 && pcounts <= 8)
    {
        if (pcounts == 1) out1 = atof(pry3);
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
        if (pcountss == 1) out1 = atof(pry1);
        else if (pcountss == 2) out2 = atof(pry1);        
        else if (pcountss == 3) out3 = atof(pry1);
        else if (pcountss == 4) out4 = atof(pry1);
        else if (pcountss == 5) out5 = atof(pry1);
        else if (pcountss == 6) out6 = atof(pry1);
//        else if (pcountss == 7) out7 = atof(pry1);
//        else if (pcountss == 8) out8 = atof(pry1);
        pry1 = strtok (0, ",");
        pcountss++;
    }
    if (pcountss == 7) pcountss = 1;
}

void Parsing_data2(char input[],int &out1,int &out2,int &out3,int &out4,int &out5,int &out6,int &out7,int &out8,int &out9,int &out10,int &out11,int &out12,int &out13,int &out14,int &out15,int &out16,int &out17,int &out18,int &out19,int &out20,int &out21,int &out22,int &out23,int &out24,int &out25,int &out26,int &out27,int &out28,int &out29,int &out30,int &out31,int &out32,int &out33)//,int &out34,int &out35,int &out36,int &out37,int &out38,int &out39,int &out40,int &out41)//,int &out42,int &out43,int &out44,int &out45,int &out46,int &out47)//,int &out48,int &out49,int &out50,int &out51)
{
    pry2 = strtok(input, ",");
    while (pry2 != 0 && pcount <= 33)
    {
        if (pcount == 1) out1 = atof(pry2);
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
		// else if (pcount == 34) out34 = atof(pry2);
		// else if (pcount == 35) out35 = atof(pry2);
//		else if (pcount == 36) out36 = atof(pry2);
//		else if (pcount == 37) out37 = atof(pry2);
//		else if (pcount == 38) out38 = atof(pry2);
//		else if (pcount == 39) out39 = atof(pry2);
//		else if (pcount == 40) out40 = atof(pry2);
//		else if (pcount == 41) out41 = atof(pry2);
//		else if (pcount == 42) out42 = atof(pry2);
//		else if (pcount == 43) out43 = atof(pry2);
//		else if (pcount == 44) out44 = atof(pry2);
//		else if (pcount == 45) out45 = atof(pry2);
//		else if (pcount == 46) out46 = atof(pry2);
//		else if (pcount == 47) out47 = atof(pry2);
//		else if (pcount == 48) out48 = atof(pry2);
//		else if (pcount == 49) out49 = atof(pry2);
//		else if (pcount == 50) out50 = atof(pry2);
//		else if (pcount == 51) out51 = atof(pry2);
        pry2 = strtok (0, ",");
        pcount++;
    }
    if (pcount == 34) pcount = 1;
}

//void Parsing_reset(char input[],int &out1,int &out2,int &out3,int &out4,int &out5)//,int &out48,int &out49,int &out50,int &out51)
//{
////		int out6;
//    pry2 = strtok(input, ",");
//    while (pry2 != 0 && pcount <= 47)
//    {
//        if (pcount == 1) out1 = atof(pry2);
//        else if (pcount == 2) out2 = atof(pry2);        
//        else if (pcount == 3) out3 = atof(pry2);
//				else if (pcount == 4) out4 = atof(pry2);
//				else if (pcount == 5) out5 = atof(pry2);
//				else if (pcount == 6) out6 = atof(pry2);
//				else if (pcount == 7) out6 = atof(pry2);
//				else if (pcount == 8) out6 = atof(pry2);
//				else if (pcount == 9) out6 = atof(pry2);
//		else if (pcount == 10) out6 = atof(pry2);
//		else if (pcount == 11) out6 = atof(pry2);
//		else if (pcount == 12) out6 = atof(pry2);
//		else if (pcount == 13) out6 = atof(pry2);
//		else if (pcount == 14) out6 = atof(pry2);
//		else if (pcount == 15) out6 = atof(pry2);
//		else if (pcount == 16) out6 = atof(pry2);
//		else if (pcount == 17) out6 = atof(pry2);
//		else if (pcount == 18) out6 = atof(pry2);
//		else if (pcount == 19) out6 = atof(pry2);
//		else if (pcount == 20) out6 = atof(pry2);
//		else if (pcount == 21) out6 = atof(pry2);
//		else if (pcount == 22) out6 = atof(pry2);
//		else if (pcount == 23) out6 = atof(pry2);
//		else if (pcount == 24) out6 = atof(pry2);
//		else if (pcount == 25) out6 = atof(pry2);
//		else if (pcount == 26) out6 = atof(pry2);
//		else if (pcount == 27) out6 = atof(pry2);
//		else if (pcount == 28) out6 = atof(pry2);
//		else if (pcount == 29) out6 = atof(pry2);
//		else if (pcount == 30) out6 = atof(pry2);
//		else if (pcount == 31) out6 = atof(pry2);
//		else if (pcount == 32) out6 = atof(pry2);
//		else if (pcount == 33) out6 = atof(pry2);
//		else if (pcount == 34) out6 = atof(pry2);
//		else if (pcount == 35) out6 = atof(pry2);
//		else if (pcount == 36) out6 = atof(pry2);
//		else if (pcount == 37) out6 = atof(pry2);
//		else if (pcount == 38) out6 = atof(pry2);
//		else if (pcount == 39) out6 = atof(pry2);
//		else if (pcount == 40) out6 = atof(pry2);
//		else if (pcount == 41) out6 = atof(pry2);
//		else if (pcount == 42) out6 = atof(pry2);
//		else if (pcount == 43) out6 = atof(pry2);
//		else if (pcount == 44) out6 = atof(pry2);
//		else if (pcount == 45) out6 = atof(pry2);
//		else if (pcount == 46) out6 = atof(pry2);
//		else if (pcount == 47) out6 = atof(pry2);
////		else if (pcount == 48) out48 = atof(pry2);
////		else if (pcount == 49) out49 = atof(pry2);
////		else if (pcount == 50) out50 = atof(pry2);
////		else if (pcount == 51) out51 = atof(pry2);
//        pry2 = strtok (0, ",");
//        pcount++;
//    }
//    if (pcount == 48) pcount = 1;
//}

//=============================================================================//
//=============================================================================//	

//=============================================================================//
// 								PIPE VARIABLE
//=============================================================================//

char buff_write[512];
char buff_read[1024];

int ia = 0;

//============================================================================//

int Header=0, Data1=0,Data2=0,mose_x=0,mose_y=0;
int Data3=0,Data4=0;
int Data_x=0,Data_y=0;
int first=0, second=0, third=0, fourth=0, fifth=0, sixth=0, seventh = 0, eight = 0;
int p = 1;
int odo_x1;
int odo_y1;
int odo_x2;
int odo_y2;
int odo_x3;
int odo_y3;
int pinMode;
int serialPort; // File descriptor for serial port
int serialPort1; // File descriptor for serial port

void die(const char *s)
{
    perror(s);
    exit(1);
}

int main(void)
{
	//================================FIFO INIT==================================//

    int fd;
    
    static const char * dataaddr = "/tmp/KAMERA"; //alamat sesuai dengan yang dibuat writernya
    mkfifo(dataaddr, 0666);
    
   	fd = open(dataaddr, O_RDWR | O_NDELAY | O_NOCTTY | O_NONBLOCK | O_ASYNC);

    /*---------- Setting the Attributes of the serial port using termios structure --------- */
		
    struct termios SerialPortSettings;	/* Create the structure                          */

    serialPort = open(portName, O_RDWR | O_NOCTTY | O_NDELAY  | O_NONBLOCK | O_ASYNC);
	serialPort1 = open(portName1, O_RDWR | O_NOCTTY | O_NDELAY  | O_NONBLOCK | O_ASYNC);

    tcgetattr(serialPort, &SerialPortSettings);	/* Get the current attributes of the Serial port */
	tcgetattr(serialPort1, &SerialPortSettings);	/* Get the current attributes of the Serial port */

    // Flush the buffer one more time.
    tcflush(serialPort, TCIOFLUSH);
	tcflush(serialPort1, TCIOFLUSH);

    cfsetispeed(&SerialPortSettings,B38400); /* Set Read  Speed as 9600                       */
    cfsetospeed(&SerialPortSettings,B38400); /* Set Write Speed as 9600                       */

    SerialPortSettings.c_cflag &= ~PARENB;   /* Disables the Parity Enable bit(PARENB),So No Parity   */
    SerialPortSettings.c_cflag &= ~CSTOPB;   /* CSTOPB = 2 Stop bits,here it is cleared so 1 Stop bit */
    SerialPortSettings.c_cflag &= ~CSIZE;	 /* Clears the mask for setting the data size             */
    SerialPortSettings.c_cflag |=  CS8;      /* Set the data bits = 8                                 */
	
    SerialPortSettings.c_cflag &= ~CRTSCTS;       /* No Hardware flow Control                         */
    SerialPortSettings.c_cflag |= CREAD;
    SerialPortSettings.c_cflag |= CLOCAL; /* Enable receiver,Ignore Modem Control lines       */ 
				    
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
   
    if (serial_rcv == NULL) printf("Failed to open serial port\n");
  	if (serial_send == NULL) printf("Failed to open serial port\n");

	//===========================UDP INIT==============================//

    struct sockaddr_in si_other; 
	unsigned int slen=sizeof(si_other);
    int s;
    char buff_rcv[BUFLEN];
    char rcv_mk[BUFLEN];
        
    if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        die("socket");
    }    
    
    fcntl( s , F_SETFL , O_NDELAY );    
    memset((char *) &si_other, 0, sizeof(si_other));
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(PORT);
    
    if (inet_aton(SERVER , &si_other.sin_addr) == 0)
    {
        fprintf(stderr, "inet_aton() failed\n");
        exit(1);
    }

	//================================================================//
	int count_send = 0;
	int count = 0;
	int counter=0;
	int bb = 0;
	int bc = 0;
	int bd = 0;
	int be = 0;

	int yaw_temp_3 = 0;
	int yaw_temp_2 = 0;

	//Perhitungan variabel konfersi

	for(int d = 0;d < 3;d++){
		pengali_A[d] = (y_BS_max[d] - y_BS_min[d])/(x_real_max[d] - x_real_min[d]);
		pengali_B[d] = (x_BS_max[d] - x_BS_min[d])/(y_real_max[d] - y_real_min[d]);

		penambah_C[d] = y_BS_max[d] - (pengali_A[d]*y_real_max[d]);
		penambah_D[d] = x_BS_max[d] - (pengali_B[d]*x_real_max[d]);
		// penambah_C[d] = ((y_BS_max[d] + y_BS_min[d]) - (pengali_A[d]*(x_real_max[d] + x_real_min[d])))/2;		
		// penambah_D[d] = ((x_BS_max[d] + x_BS_min[d]) - (pengali_B[d]*(y_real_max[d] + y_real_min[d])))/2;
	}

	striker_3.x_mk_reset = 0;
	striker_3.y_mk_reset = 0;
	striker_2.x_mk_reset = 0;
	striker_2.y_mk_reset = 0;
	
	int counter_ = 0;

	//========== COUNTER fprintf ============//
	int counter_S2_1 = 7;
	int counter_S2_2 = 2;
	int counter_S2_3 = 4;

	int counter_S3_1 = 7;
	int counter_S3_2 = 2;
	int counter_S3_3 = 4;
	//=====================================//

	int count_ = 0;
	float tempo_x = 0;
	float tempo_y = 0;

    while(1)
    {
		counter++;
		if (counter == 501) counter = 0;
		count++; 
		if (count == 10) count = 0;

		count_++;
		if (count_ == 20) count_ = 0;

		//==========================RECEIVE FUNCTION FOR REFBOX & ODOMETRY=========================//
		memset(buff_rcv,'\0', sizeof(buff_rcv));
        for(int p = 0;p < 5;p++)recvfrom(s, buff_rcv, BUFLEN, 0, (struct sockaddr *) &si_other, &slen) ;

//		Parsing_data2(buff_rcv, X, Y, Z, striker_3.coor_x[0], striker_3.coor_y[0], striker_2.coor_x[0], striker_2.coor_y[0], /*keeper.coor_x[0], keeper.coor_y[0],*/ striker_3.coor_x[2], striker_3.coor_y[2], striker_2.coor_x[2], striker_2.coor_y[2],/* keeper.coor_x[2], keeper.coor_y[2],*/ striker_2.yaw[0], striker_3.yaw[0], keeper.yaw[0], striker_2.distance_ball[0], striker_3.distance_ball[0], striker_2.goalkick_x_lawan[0], striker_2.goalkick_y_lawan[0], striker_3.corner_x_lawan[0], striker_3.corner_y_lawan[0], striker_2.corner_x_lawan[0], striker_2.corner_y_lawan[0], striker_2.kickoff_x_lawan[0], striker_2.kickoff_x_lawan[0], striker_2.dropball_x_lawan[0], striker_2.dropball_y_lawan[0], striker_3.reset_x[0], striker_3.reset_y[0], striker_2.reset_x[0], striker_2.reset_y[0], striker_2.penalty_x_lawan[0], striker_2.penalty_y_lawan[0], striker_2.freekick_x_lawan[0], striker_2.freekick_y_lawan[0], striker_2.x_ball[1], striker_2.y_ball[1],TEAM, mode_marking, striker_3.x_ball[1], striker_3.y_ball[1], keeper.reset_x[0], keeper.reset_y[0], mode_formasi, striker_2.penalty_x_kita[0], striker_2.penalty_y_kita[0], striker_3.reset_yaw[0], striker_2.reset_yaw[0]);


Parsing_data2(buff_rcv, X, Y, Z, striker_3.coor_x[0], striker_3.coor_y[0], striker_2.coor_x[0], striker_2.coor_y[0], flag_wifi, striker_3.coor_x[2], striker_3.coor_y[2], striker_2.coor_x[2], striker_2.coor_y[2], dummy_pos1, dummy_pos2, striker_2.yaw[0], striker_3.yaw[0], striker_2.distance_ball[0], striker_3.distance_ball[0], striker_3.reset_x[0], striker_3.reset_y[0], striker_2.reset_x[0], striker_2.reset_y[0], TEAM, mode_marking, striker_2.angle_ball[1], striker_3.angle_ball[1], striker_3.x_ball[1], striker_3.y_ball[1], mode_formasi[0], striker_3.x_cm[0], striker_3.y_cm[0], striker_2.x_cm[0], striker_2.y_cm[0]);

//fprintf(serial_send, "%d,%d,%d,0,%d\n", Header, Data1, Data2, mode_formasi);					//Send Odometry Field To Robot

//			if(counter%100 == 0)
//			Parsing_data2(buff_rcv, X, Y, Z, striker_3.coor_x[0], striker_3.coor_y[0], striker_2.coor_x[0], striker_2.coor_y[0], /*keeper.coor_x[0], keeper.coor_y[0],*/ striker_3.coor_x[2], striker_3.coor_y[2], striker_2.coor_x[2], striker_2.coor_y[2],/* keeper.coor_x[2], keeper.coor_y[2],*/ striker_2.yaw[0], striker_3.yaw[0], keeper.yaw[0], striker_2.distance_ball[0], striker_3.distance_ball[0], striker_2.goalkick_x_lawan[0], striker_2.goalkick_y_lawan[0], striker_3.corner_x_lawan[0], striker_3.corner_y_lawan[0], striker_2.corner_x_lawan[0], striker_2.corner_y_lawan[0], striker_2.kickoff_x_lawan[0], striker_2.kickoff_x_lawan[0], striker_2.dropball_x_lawan[0], striker_2.dropball_y_lawan[0], /*striker_3.reset_x[0], striker_3.reset_y[0], striker_2.reset_x[0], striker_2.reset_y[0],*/ striker_2.penalty_x_lawan[0], striker_2.penalty_y_lawan[0], striker_2.freekick_x_lawan[0], striker_2.freekick_y_lawan[0], striker_2.x_ball[1], striker_2.y_ball[1],TEAM, mode_marking, striker_3.x_ball[1], striker_3.y_ball[1],/* keeper.reset_x[0], keeper.reset_y[0],*/ mode_formasi, striker_2.penalty_x_kita[0], striker_2.penalty_y_kita[0], striker_3.reset_yaw[0], striker_2.reset_yaw[0]);
//			if(counter%300 == 0){
//				Parsing_reset(buff_rcv, Header_reset, x_res[0], y_res[0], x_res[1], y_res[1]);
//				if(Header_reset == 23){
//					striker_3.reset_x[0] = x_res[0];
//					striker_3.reset_y[0] = y_res[0];
//					striker_2.reset_x[0] = x_res[1];
//					striker_2.reset_y[0] = y_res[1];					
//	
//				}
//			}
//		if(buff_rcv != 0) printf("DATA = %s\n", buff_rcv);

		Header = 2;
	 	Data1 = Y;
	 	Data2 = Z;
		
		striker_3.x_cm[1] = striker_3.x_cm[0];
		striker_3.y_cm[1] = striker_3.y_cm[0];
		striker_2.x_cm[1] = striker_2.x_cm[0];
		striker_2.y_cm[1] = striker_2.y_cm[0];

		if (Header == 2 && Data1 == 0 && Data2 == 1)
		{
			striker_3.coor_y[1] = striker_3.coor_x[1];
			striker_3.coor_x[1] = striker_3.coor_y[1];
			striker_2.coor_y[1] = striker_2.coor_x[1];
			striker_2.coor_x[1] = striker_2.coor_y[1];
			keeper.coor_x[1] = keeper.coor_x[1];
			keeper.coor_y[1] = keeper.coor_y[1];
			
//			striker_3.reset_x[1] = 0;
//			striker_3.reset_y[1] = 0;
//			striker_2.reset_x[1] = 0;
//			striker_2.reset_y[1] = 0;
//			keeper.reset_x[1] = 0;
//			keeper.reset_y[1] = 0;

		}
		else
		{			
			striker_3.coor_x[1] = striker_3.coor_x[0];
			striker_3.coor_y[1] = striker_3.coor_y[0];
			striker_2.coor_x[1] = striker_2.coor_x[0];
			striker_2.coor_y[1] = striker_2.coor_y[0];
			keeper.coor_x[1] = keeper.coor_x[0];
			keeper.coor_y[1] = keeper.coor_y[0];

			striker_3.reset_x[1] = striker_3.reset_x[0];
			striker_3.reset_y[1] = striker_3.reset_y[0];
			striker_2.reset_x[1] = striker_2.reset_x[0];
			striker_2.reset_y[1] = striker_2.reset_y[0];
			keeper.reset_x[1] = keeper.reset_x[0];
			keeper.reset_y[1] = keeper.reset_y[0];
		}
		striker_3.kickoff_x_lawan[0] = striker_2.kickoff_x_lawan[0];
		striker_3.kickoff_y_lawan[0] = striker_2.kickoff_y_lawan[0];
		striker_3.goalkick_x_lawan[0] = striker_2.goalkick_x_lawan[0];
		striker_3.goalkick_y_lawan[0] = striker_2.goalkick_y_lawan[0];
		striker_3.dropball_x_lawan[0] = striker_2.dropball_x_lawan[0];
		striker_3.dropball_y_lawan[0] = striker_2.dropball_y_lawan[0];
		striker_3.penalty_x_lawan[0] = striker_2.penalty_x_lawan[0];
		striker_3.penalty_y_lawan[0] = striker_2.penalty_y_lawan[0];
		striker_3.freekick_x_lawan[0] = striker_2.freekick_x_lawan[0];
		striker_3.freekick_y_lawan[0] = striker_2.freekick_y_lawan[0];
		striker_3.penalty_x_kita[0] = striker_2.penalty_x_kita[0];
		striker_3.penalty_y_kita[0] = striker_2.penalty_y_kita[0];
		keeper.x_ball[1] = striker_2.x_ball[1];
		keeper.y_ball[1] = striker_2.y_ball[1];
		if (TEAM == 1) TEAM = CYAN;
		if (TEAM == 2) TEAM = MAGENTA;

		//---------------------RECEIVE ODOMETRY FROM DATA LAPTOP-----------------------//

		if (counter%20 == 0 )
		{			 
			memset(rcv_mk, '\0', sizeof(rcv_mk));			
			read(serialPort, &rcv_mk, sizeof(rcv_mk));
//			printf("S3---->>>%s", rcv_mk);
			Parsing_data(rcv_mk, awal, nilai_x, nilai_y, nilai_x1, nilai_y1, rawYaw, Volt, Proxi);
			
			
			if (awal == 12)
			{
				if (PROGRAM_UNTUK == STRIKER_2)
				{			
			   		striker_2.x_or[0] = nilai_x;							// odometry x robot
								striker_2.y_or[0] = nilai_y;							// odometry y robot
								striker_2.x_or[2] = nilai_x1;							// odometry x bola
								striker_2.y_or[2] = nilai_y1;							// odometry y bola
								striker_2.yaw[1] = rawYaw;
								striker_2.Volt[0] = Volt;
								striker_2.Proxi[0] = Proxi;
				}
				else if (PROGRAM_UNTUK == STRIKER_3)
				{			
			   		striker_3.x_or[0] = nilai_x;							// odometry x robot
								striker_3.y_or[0] = nilai_y;							// odometry y robot
								striker_3.x_or[2] = nilai_x1;							// odometry x bola
								striker_3.y_or[2] = nilai_y1;							// odometry y bola
								striker_3.yaw[1] = rawYaw;
								striker_3.Volt[0] = Volt;
								striker_3.Proxi[0] = Proxi;
				}
				else if (PROGRAM_UNTUK == KEEPER)
				{
								keeper.x_or[0] = nilai_x;
								keeper.y_or[0] = nilai_y;
								keeper.yaw[1] = rawYaw;
				}

				keeper.x_or[1] = keeper.x_or[0];
				keeper.y_or[1] = keeper.y_or[0];		
			}
		}

		if (counter%250 == 0)
		{
			//===== RESET =====//

//			if ((striker_3.reset_x[1] != bb) || (striker_3.reset_y[1] != bc))
//			{
//				striker_3.y_mk_reset = (striker_3.reset_x[1] - penambah_C)/pengali_A;
//				striker_3.x_mk_reset = (striker_3.reset_y[1] - penambah_D)/pengali_B;
//				bb = striker_3.reset_x[1];
//				bc = striker_3.reset_y[1];			
//			}
//			else
//			{
//				striker_3.y_mk_reset = 0;
//				striker_3.x_mk_reset = 0;
//			}


//			if ((striker_2.reset_x[1] != bd) || (striker_2.reset_y[1] != be))
//			{
//				striker_2.y_mk_reset = (striker_2.reset_x[1] - penambah_C)/pengali_A;
//				striker_2.x_mk_reset = (striker_2.reset_y[1] - penambah_D)/pengali_B;
//				bd = striker_2.reset_x[1];
//				be = striker_2.reset_y[1];
//			}
//			else
//			{
//				striker_2.y_mk_reset = 0;
//				striker_2.x_mk_reset = 0;
//			}

//			if(striker_3.reset_yaw[0] != yaw_temp_3) {
//				striker_3.reset_yaw[1] = striker_3.reset_yaw[0];
//				yaw_temp_3 = striker_3.reset_yaw[0];
//			}
//			else striker_3.reset_yaw[1] = 0;

//			if(striker_2.reset_yaw[0] != yaw_temp_2){
// 				striker_2.reset_yaw[1] = striker_2.reset_yaw[0];yaw_temp_2 = striker_2.reset_yaw[0];
//			}
//			else striker_2.reset_yaw[1] = 0;


			//===== POSITIONING STRIKER_2 =====//
		
			if(striker_2.coor_x[1] < x_BS_min[1]) 
					// striker_2.y_mk_pos = (striker_2.coor_x[1] - penambah_D[0])/pengali_B[0];
					striker_2.y_mk_pos = (pengali_B[0]*striker_2.coor_x[1]) + penambah_D[0];

			else if(striker_2.coor_x[1] >= x_BS_min[1] && striker_2.coor_x[1] <= x_BS_max[1]) 
					// striker_2.y_mk_pos = (striker_2.coor_x[1] - penambah_D[1])/pengali_B[1];
					striker_2.y_mk_pos = (pengali_B[1]*striker_2.coor_x[1]) + penambah_D[1];
			else if(striker_2.coor_x[1] > x_BS_max[1]) 
					// striker_2.y_mk_pos = (striker_2.coor_x[1] - penambah_D[2])/pengali_B[2];
					striker_2.y_mk_pos = (pengali_B[2]*striker_2.coor_x[1]) + penambah_D[2];

			if(striker_2.coor_y[1] < y_BS_min[1]) 
					// striker_2.x_mk_pos = (striker_2.coor_y[1] - penambah_C[0])/pengali_A[0];
					striker_2.x_mk_pos = (pengali_B[0]*striker_2.coor_y[1]) + penambah_D[0];
			else if(striker_2.coor_y[1] >= y_BS_min[1] && striker_2.coor_y[1] <= y_BS_max[1]) 
					// striker_2.x_mk_pos = (striker_2.coor_y[1] - penambah_C[1])/pengali_A[1];
					striker_2.x_mk_pos = (pengali_B[1]*striker_2.coor_y[1]) + penambah_D[1];
			else if(striker_2.coor_y[1] > y_BS_max[1])
					// striker_2.x_mk_pos = (striker_2.coor_y[1] - penambah_C[2])/pengali_A[2];
					striker_2.x_mk_pos = (pengali_B[2]*striker_2.coor_y[1]) + penambah_D[2];

			//===== POSITIONING STRIKER_3 =====//
			if(striker_3.coor_x[1] < x_BS_min[1]) 
					striker_3.y_mk_pos = (striker_3.coor_x[1] - penambah_D[0])/pengali_B[0];

			else if(striker_3.coor_x[1] >= x_BS_min[1] && striker_3.coor_x[1] <= x_BS_max[1]) 
					striker_3.y_mk_pos = (striker_3.coor_x[1] - penambah_D[1])/pengali_B[1];

			else if(striker_3.coor_x[1] > x_BS_max[1]) 
					striker_3.y_mk_pos = (striker_3.coor_x[1] - penambah_D[2])/pengali_B[2];


			if(striker_3.coor_y[1] < y_BS_min[1]) 
					striker_3.x_mk_pos = (striker_3.coor_y[1] - penambah_C[0])/pengali_A[0];

			else if(striker_3.coor_y[1] >= y_BS_min[1] && striker_3.coor_y[1] <= y_BS_max[1]) 
					striker_3.x_mk_pos = (striker_3.coor_y[1] - penambah_C[1])/pengali_A[1];

			else if(striker_3.coor_y[1] > y_BS_max[1]) 
					striker_3.x_mk_pos = (striker_3.coor_y[1] - penambah_C[2])/pengali_A[2];
			

			mode_formasi[1] = mode_formasi[0];

			if (PROGRAM_UNTUK == STRIKER_2) 
			{
				
				if (count_send == 20) count_send = 0;
				++count_send;
				
				if (TEAM == CYAN)
				{
					if (Header == 2 && Data1 == 2 && Data2 == 3) 				//kickoff lawan
					{ 
						striker_3.coor_y[1] = striker_2.kickoff_x_lawan[0];
						striker_3.coor_x[1] = striker_2.kickoff_y_lawan[0];
					}
					else if (Header == 2 && Data1 == 2 && Data2 == 7) 		//corner lawan
					{
						striker_3.coor_y[1] = striker_2.corner_x_lawan[0];
 						striker_3.coor_x[1] = striker_2.corner_y_lawan[0]; 
					}
					else if (Header == 2 && Data1 == 2 && Data2 == 5) 		//goalkick lawan
					{ 
						striker_3.coor_y[1] = striker_2.goalkick_x_lawan[0];
						striker_3.coor_x[1] = striker_2.goalkick_y_lawan[0];
					}
					else if (Header == 2 && Data1 == 2 && Data2 == 8) 		//penalty lawan
					{ 
						striker_3.coor_y[1] = striker_2.penalty_x_lawan[0];
						striker_3.coor_x[1] = striker_2.penalty_y_lawan[0];
					}
					else if (Header == 2 && Data1 == 2 && Data2 == 4) 		//freekick lawan
					{ 
						striker_3.coor_y[1] = striker_2.freekick_x_lawan[0];
						striker_3.coor_x[1] = striker_2.freekick_y_lawan[0];
					}
					else if (Header == 2 && Data1 == 0 && Data2 == 3) 		//dropball
					{ 
						striker_3.coor_y[1] = striker_2.dropball_x_lawan[0];
						striker_3.coor_x[1] = striker_2.dropball_y_lawan[0];
					}
					else if (Header == 2 && Data1 == 1 && Data2 == 8)		//penalti kita
					{
						striker_3.coor_y[1] = striker_2.penalty_x_kita[0];
						striker_3.coor_x[1] = striker_2.penalty_y_kita[0];
					}
					
					
					if(count_send % counter_S2_1 == 0)fprintf(serial_send, "%d,%d,%d,%d,0\n", Header, Data1, Data2, mode_formasi[1]);					//Send Odometry Field To Robot
					if(count_ > 15){
						if(count_send % counter_S2_2 == 0){
							fprintf(serial_send, "13,%d,%d,%d,%d,%d\n",(int)striker_2.x_mk_pos, (int)striker_2.y_mk_pos, (int)striker_3.coor_x[1], (int)striker_3.coor_y[1], flag_wifi);
							fprintf(serial_send, "90,%d,%d\n", dummy_pos1, dummy_pos2);}
						tempo_x = striker_3.coor_x[1];
						tempo_y = striker_3.coor_y[1];
					} else {
						if(count_send % counter_S2_2 == 0){
							fprintf(serial_send, "13,%d,%d,%d,%d,%d\n", (int)striker_2.x_mk_pos, (int)striker_2.y_mk_pos, (int)tempo_x, (int)tempo_y,flag_wifi);
							fprintf(serial_send, "90,%d,%d\n", dummy_pos1, dummy_pos2);}
					}
					if(count_send % counter_S2_3 == 0)fprintf(serial_send, "11,%d,%d,%d,%d\n", (int)striker_3.distance_ball[0], (int)striker_3.angle_ball[1], (int)striker_3.x_ball[1], (int)striker_3.y_ball[1]);
//					if(striker_2.x_mk_reset != 0 || striker_2.y_mk_reset != 0)fprintf(serial_send, "16,%d,%d,%d,%d\n", (int)striker_3.x_mk_reset, (int)striker_3.y_mk_reset, (int)striker_2.x_mk_reset, (int)striker_2.y_mk_reset);
//					if(striker_2.reset_yaw[1] != 0) fprintf(serial_send, "18,%d,%d\n", striker_3.reset_yaw[1], striker_2.reset_yaw[1]);
//					fprintf(serial_send, "17,%d,%d\n", (int)striker_2.angle_obs, (int)striker_2.jarak_obs);
				}
				/*else if (TEAM == MAGENTA)
				{
					if (Header == 2 && Data1 == 1 && Data2 == 3) 				//kickoff lawan
					{ 
						striker_3.coor_y[1] = striker_2.kickoff_x_lawan[0];
						striker_3.coor_x[1] = striker_2.kickoff_y_lawan[0];
					}
					else if (Header == 2 && Data1 == 1 && Data2 == 7)		//corner lawan
					{ 
						striker_3.coor_y[1] = striker_2.corner_x_lawan[0];
						striker_3.coor_x[1] = striker_2.corner_y_lawan[0];
					}
					else if (Header == 2 && Data1 == 1 && Data2 == 5)		//goalkick lawan 
					{ 
						striker_3.coor_y[1] = striker_2.goalkick_x_lawan[0];
						striker_3.coor_x[1] = striker_2.goalkick_y_lawan[0];
					}
					else if (Header == 2 && Data1 == 1 && Data2 == 8)		//penalti lawan 
					{ 
						striker_3.coor_y[1] = striker_2.penalty_x_lawan[0];
						striker_3.coor_x[1] = striker_2.penalty_y_lawan[0];
					}
					else if (Header == 2 && Data1 == 1 && Data2 == 4)		//freekick lawan
					{ 
						striker_3.coor_y[1] = striker_2.freekick_x_lawan[0];
						striker_3.coor_x[1] = striker_2.freekick_y_lawan[0];
					}
					else if (Header == 2 && Data1 == 0 && Data2 == 3) 		//dropball
					{ 
						striker_3.coor_y[1] = striker_2.dropball_x_lawan[0];
						striker_3.coor_x[1] = striker_2.dropball_y_lawan[0];
					}
					else if (Header == 2 && Data1 == 2 && Data2 == 8)		//penalti kita
					{
						striker_3.coor_y[1] = striker_2.penalty_x_kita[0];
						striker_3.coor_x[1] = striker_2.penalty_y_kita[0];
					}
					if(count_send % counter_S2_1 == 0)fprintf(serial_send, "%d,%d,%d,%d,0\n", Header, Data1, Data2, mode_formasi[1]);					//Send Odometry Field To Robot
					if(count_ > 15){
						if(count_send % counter_S2_2 == 0)fprintf(serial_send, "13,%d,%d,%d,%d,%d\n", (int)striker_2.x_mk_pos, (int)striker_2.y_mk_pos, (int)striker_3.coor_x[1], (int)striker_3.coor_y[1],striker_3.yaw[1]);
						tempo_x = striker_3.coor_x[1];
						tempo_y = striker_3.coor_y[1];
					} else {
						if(count_send % counter_S2_2 == 0)fprintf(serial_send, "13,%d,%d,%d,%d,%d\n", (int)striker_2.x_mk_pos, (int)striker_2.y_mk_pos, (int)tempo_x, (int)tempo_y, striker_3.yaw[1]);
					}
					if(count_send % counter_S2_3 == 0)fprintf(serial_send, "11,%d,%d,%d,%d\n", (int)striker_3.distance_ball[0], (int)striker_3.angle_ball[1], (int)striker_3.x_ball[1], (int)striker_3.y_ball[1]);
//					if(striker_2.x_mk_reset != 0 || striker_2.y_mk_reset != 0)fprintf(serial_send, "16,%d,%d,%d,%d\n", (int)striker_3.x_mk_reset, (int)striker_3.y_mk_reset, (int)striker_2.x_mk_reset, (int)striker_2.y_mk_reset);
//					if(striker_2.reset_yaw[1] != 0) fprintf(serial_send, "18,%d,%d\n", striker_3.reset_yaw[1], striker_2.reset_yaw[1]);
//					fprintf(serial_send, "17,%d,%d\n", (int)striker_2.angle_obs, (int)striker_2.jarak_obs);
				}*/
			}
			else if (PROGRAM_UNTUK == STRIKER_3) 
			{
				if (TEAM == CYAN)
				{
					if (Header == 2 && Data1 == 2 && Data2 == 3) 				//kickoff lawan
					{ 
						striker_2.coor_y[1] = striker_3.kickoff_x_lawan[0];
						striker_2.coor_x[1] = striker_3.kickoff_y_lawan[0];
					}
					else if (Header == 2 && Data1 == 2 && Data2 == 7) 		//corner lawan
					{ 
						striker_2.coor_y[1] = striker_3.corner_x_lawan[0];
 						striker_2.coor_x[1] = striker_3.corner_y_lawan[0]; 
					}
					else if (Header == 2 && Data1 == 2 && Data2 == 5) 		//goalkick lawan
					{ 
						striker_2.coor_y[1] = striker_3.goalkick_x_lawan[0];
						striker_2.coor_x[1] = striker_3.goalkick_y_lawan[0];
					}
					else if (Header == 2 && Data1 == 2 && Data2 == 8) 		//penalty lawan
					{ 
						striker_2.coor_y[1] = striker_3.penalty_x_lawan[0];
						striker_2.coor_x[1] = striker_3.penalty_y_lawan[0];
					}
					else if (Header == 2 && Data1 == 2 && Data2 == 4) 		//freekick lawan
					{ 
						striker_2.coor_y[1] = striker_3.freekick_x_lawan[0];
						striker_2.coor_x[1] = striker_3.freekick_y_lawan[0];
					}
					else if (Header == 2 && Data1 == 0 && Data2 == 3) 		//dropball
					{ 
						striker_2.coor_y[1] = striker_3.dropball_x_lawan[0];
						striker_2.coor_x[1] = striker_3.dropball_y_lawan[0];
					}
					else if (Header == 2 && Data1 == 1 && Data2 == 8)		//penalti kita
					{
						striker_2.coor_y[1] = striker_3.penalty_x_kita[0];
						striker_2.coor_x[1] = striker_3.penalty_y_kita[0];
					}

					
					if(count_send % counter_S3_1 == 0)fprintf(serial_send, "%d,%d,%d,%d,0\n", Header, Data1, Data2, mode_formasi[1]); 				//Send Odometry Field To Robot
					if(count_ > 15){
						if(count_send % counter_S3_2 == 0){
							fprintf(serial_send, "13,%d,%d,%d,%d,%d\n",(int)striker_3.x_mk_pos, (int)striker_3.y_mk_pos,(int)striker_2.coor_x[1], (int)striker_2.coor_y[1],flag_wifi);
							fprintf(serial_send, "90,%d,%d\n", dummy_pos1, dummy_pos2);}
						tempo_x = striker_2.coor_x[1];
						tempo_y = striker_2.coor_y[1];
					} else {
						if(count_send % counter_S3_2 == 0){
							fprintf(serial_send, "13,%d,%d,%d,%d,%d\n",(int)striker_3.x_mk_pos, (int)striker_3.y_mk_pos, (int)tempo_x, (int)tempo_y, flag_wifi);
							fprintf(serial_send, "90,%d,%d\n", dummy_pos1, dummy_pos2);}
					}
					if(count_send % counter_S3_3 == 0)fprintf(serial_send, "11,%d,%d,%d,%d\n", (int)striker_2.distance_ball[0], (int)striker_2.angle_ball[1], (int)striker_2.x_ball[1], (int)striker_2.y_ball[1]);
//					if(striker_3.x_mk_reset != 0 || striker_3.y_mk_reset != 0)fprintf(serial_send, "16,%d,%d,%d,%d\n", (int)striker_3.x_mk_reset, (int)striker_3.y_mk_reset, (int)striker_2.x_mk_reset, (int)striker_2.y_mk_reset);
//					fprintf(serial_send, "17,%d,%d\n", (int)striker_3.angle_obs, (int)striker_3.jarak_obs);					
//					if(striker_3.reset_yaw[1] != 0) fprintf(serial_send, "18,%d,%d\n", striker_3.reset_yaw[1], striker_2.reset_yaw[1]);
				}
				else if (TEAM == MAGENTA)
				{
					if (Header == 2 && Data1 == 1 && Data2 == 3)					//kickoff lawan
					{ 
						striker_2.coor_y[1] = striker_3.kickoff_x_lawan[0];
						striker_2.coor_x[1] = striker_3.kickoff_y_lawan[0];
					}
					else if (Header == 2 && Data1 == 1 && Data2 == 7) 		//corner lawan
					{ 
						striker_2.coor_y[1] = striker_3.corner_x_lawan[0];
						striker_2.coor_x[1] = striker_3.corner_y_lawan[0];
					}
					else if (Header == 2 && Data1 == 1 && Data2 == 5)		//goalkick lawan
					{ 
						striker_2.coor_y[1] = striker_3.goalkick_x_lawan[0];
						striker_2.coor_x[1] = striker_3.goalkick_y_lawan[0];
					}
					else if (Header == 2 && Data1 == 1 && Data2 == 8) 		//penalti lawan
					{ 
						striker_2.coor_y[1] = striker_3.penalty_x_lawan[0];
						striker_2.coor_x[1] = striker_3.penalty_y_lawan[0];
					}
					else if (Header == 2 && Data1 == 1 && Data2 == 4) 		//freekick lawan
					{ 
						striker_2.coor_y[1] = striker_3.freekick_x_lawan[0];
						striker_2.coor_x[1] = striker_3.freekick_y_lawan[0];
					}
					else if (Header == 2 && Data1 == 0 && Data2 == 3) 		//dropball
					{ 
						striker_2.coor_y[1] = striker_3.dropball_x_lawan[0];
						striker_2.coor_x[1] = striker_3.dropball_y_lawan[0];
					}
					else if (Header == 2 && Data1 == 2 && Data2 == 8)		//penalti kita
					{
						striker_2.coor_y[1] = striker_3.penalty_x_kita[0];
						striker_2.coor_x[1] = striker_3.penalty_y_kita[0];
					}
					if(count_send % counter_S3_1 == 0)fprintf(serial_send, "%d,%d,%d,%d,0\n", Header, Data1, Data2, mode_formasi[1]); 				//Send Odometry Field To Robot
					if(count_ > 15){
						if(count_send % counter_S3_2 == 0){
							fprintf(serial_send, "13,%d,%d,%d,%d,%d\n", (int)striker_3.x_mk_pos, (int)striker_3.y_mk_pos,(int)striker_2.x_or[1], (int)striker_2.y_or[1], striker_2.yaw[1]);
							fprintf(serial_send, "90,%d,%d\n", dummy_pos1, dummy_pos2);}
						tempo_x = striker_2.x_or[1];
						tempo_y = striker_2.y_or[1];
					} else {
						if(count_send % counter_S3_2 == 0){
							fprintf(serial_send, "13,%d,%d,%d,%d,%d\n", (int)striker_3.x_mk_pos, (int)striker_3.y_mk_pos, (int)tempo_x, (int)tempo_y, striker_2.yaw[1]);
							fprintf(serial_send, "90,%d,%d\n", dummy_pos1, dummy_pos2);}
					}
					if(count_send % counter_S3_3 == 0)fprintf(serial_send, "11,%d,%d,%d,%d\n", (int)striker_2.distance_ball[0], (int)striker_2.angle_ball[1], (int)striker_2.x_ball[1], (int)striker_2.y_ball[1]);
//					if(striker_3.x_mk_reset != 0 || striker_3.y_mk_reset != 0)fprintf(serial_send, "16,d,%d,%d,%d\n", (int)striker_3.x_mk_reset, (int)striker_3.y_mk_reset, (int)striker_2.x_mk_reset, (int)striker_2.y_mk_reset);
//					fprintf(serial_send, "17,%d,%d\n", (int)striker_3.angle_obs, (int)striker_3.jarak_obs);					
//					if(striker_3.reset_yaw[1] != 0) fprintf(serial_send, "18,%d,%d\n", striker_3.reset_yaw[1], striker_2.reset_yaw[1]);
				}
			}
			else if (PROGRAM_UNTUK == KEEPER) 
			{
				if (TEAM == CYAN)
				{
					fprintf(serial_send, "%d,%d,%d,0,0\n", Header, Data1, Data2); 				//Send Odometry Field To Robot
					fprintf(serial_send, "13,%d,%d,%d,%d\n", (int)keeper.coor_y[1], (int)keeper.coor_x[1], (int)keeper.coor_y[2], (int)keeper.coor_x[2]);
					fprintf(serial_send, "16,%d,%d,0,0\n", keeper.reset_x[1], keeper.reset_y[1]);
				}
				else if (TEAM == MAGENTA)
				{
					fprintf(serial_send, "%d,%d,%d,0,0\n", Header, Data1, Data2); 				//Send Odometry Field To Robot
					fprintf(serial_send, "13,%d,%d,%d,%d\n", (int)keeper.coor_y[1], (int)keeper.coor_x[1], (int)keeper.coor_y[2], (int)keeper.coor_x[2]);
					fprintf(serial_send, "16,%d,%d,0,0\n", keeper.reset_x[1], keeper.reset_y[1]);
				}
			}
		}

		//==============================================================================//
		//===========================PIPE FUNCTION FOR ODO ROBOT=======================//	
	
		//---------------------RECEIVE ODOMETRY FROM DATA LAPTOP-----------------------//

		if (count >= 0 && count <= 3)
		{
			memset(buff_camera, '\0', sizeof(buff_camera));
			read(fd, buff_camera, sizeof(buff_camera));
			Parsing_data1(buff_camera, first, second, third, fourth, fifth, sixth);
//			memset(buff_camera, '\0', sizeof(buff_camera));

			if (first == 98)										
			{
				if (PROGRAM_UNTUK == STRIKER_2)
				{
					striker_2.distance_ball[1] = second;
					striker_2.angle_ball[0] = third;
					striker_2.area_ball = fourth;
					striker_2.y_ball[0] = fifth;
					striker_2.x_ball[0] = sixth;
//					striker_2.jarak_obs = eight;
//					striker_2.angle_obs = seventh;
				}
				else if (PROGRAM_UNTUK == STRIKER_3)
				{
					striker_3.distance_ball[1] = second;
					striker_3.angle_ball[0] = third;
					striker_3.area_ball = fourth;
					striker_3.y_ball[0] = fifth;
					striker_3.x_ball[0] = sixth;
//					striker_3.jarak_obs = eight;
//					striker_3.angle_obs = seventh;
				}
				else if (PROGRAM_UNTUK == KEEPER)
				{
					keeper.distance_ball[1] = second;
					keeper.angle_ball[0] = third;
					keeper.area_ball = fourth;
					keeper.x_ball[0] = fifth;
					keeper.y_ball[0] = sixth;
				}
			}
//				striker_2.Proxi[1] = striker_2.Proxi[0];
				if(striker_2.Proxi[0] == 1){
					striker_2.distance_ball[1] = 5;
				} else {
					striker_2.distance_ball[1] = striker_2.distance_ball[1];
				}

//				striker_3.Proxi[1] = striker_3.Proxi[0];
				if(striker_3.Proxi[0] == 1){
					striker_3.distance_ball[1] = 5;
				} else {
					striker_3.distance_ball[1] = striker_3.distance_ball[1];
				}
		}

//		if (count == 7 || count == 8)	//> 3= 4 && count <= 6)
//		{
//			sprintf(buff_feedback, "26,%d,%d,%d,%d\n", striker_2.x_or[1], striker_2.y_or[1], striker_3.x_or[1], striker_3.y_or[1]);
//			write(fd, buff_feedback, sizeof(buff_feedback));
//		}

		
		//---------------------------------------------------------------------------------------------------------//

		if (count == 5) //&& count <= 9)
		{

			if (PROGRAM_UNTUK == STRIKER_2){

				if(striker_2.y_or[1] < y_BS_min[1]) //-80 ~ 0
						striker_2.x_cm_send = (striker_2.y_or[1] - penambah_C[0])/pengali_A[0];

				else if(striker_2.y_or[1] >= y_BS_min[1] && striker_2.y_or[1] <= y_BS_max[1]) //
						striker_2.x_cm_send = (striker_2.y_or[1] - penambah_C[1])/pengali_A[1];
		
				else if(striker_2.y_or[1] > y_BS_max[1]) 
						striker_2.x_cm_send = (striker_2.y_or[1] - penambah_C[2])/pengali_A[2];

				

				if(striker_2.x_or[1] < x_BS_min[1]) 
						striker_2.y_cm_send = (striker_2.x_or[1] - penambah_D[0])/pengali_B[0];

				else if(striker_2.x_or[1] >= x_BS_min[1] && striker_2.x_or[1] <= x_BS_max[1]) 
						striker_2.y_cm_send = (striker_2.x_or[1] - penambah_D[1])/pengali_B[1];

				else if(striker_2.x_or[1] > x_BS_min[1]) 
						striker_2.y_cm_send = (striker_2.x_or[1] - penambah_D[2])/pengali_B[2];

				striker_2.Volt[1] = striker_2.Volt[0];
				
				striker_2.x_or[1] = striker_2.x_or[0];
				striker_2.y_or[1] = striker_2.y_or[0];

//				striker_2.x_ball[1] = striker_2.x_or[2];
//				striker_2.y_ball[1] = striker_2.y_or[2];
				
			}
			else if (PROGRAM_UNTUK == STRIKER_3){

				if(striker_3.y_or[1] < y_BS_min[1]) 
						striker_3.x_cm_send = (striker_3.y_or[1] - penambah_C[0])/pengali_A[0];

				else if(striker_3.y_or[1] >= y_BS_min[1] && striker_3.y_or[1] <= y_BS_max[1])
						striker_3.x_cm_send = (striker_3.y_or[1] - penambah_C[1])/pengali_A[1];
		
				else if(striker_3.y_or[1] > y_BS_max[1]) 
						striker_3.x_cm_send = (striker_3.y_or[1] - penambah_C[2])/pengali_A[2];

				

				if(striker_3.x_or[1] < x_BS_min[1]) 
						striker_3.y_cm_send = (striker_3.x_or[1] - penambah_D[0])/pengali_B[0];

				else if(striker_3.x_or[1] >= x_BS_min[1] && striker_3.x_or[1] <= x_BS_max[1]) 
						striker_3.y_cm_send = (striker_3.x_or[1] - penambah_D[1])/pengali_B[1];

				else if(striker_3.x_or[1] > x_BS_max[1]) 
						striker_3.y_cm_send = (striker_3.x_or[1] - penambah_D[2])/pengali_B[2];

				striker_3.Volt[1] = striker_3.Volt[0];	

				striker_3.x_or[1] = striker_3.x_or[0];
				striker_3.y_or[1] = striker_3.y_or[0];

//				striker_3.x_ball[1] = striker_3.x_or[2];
//				striker_3.y_ball[1] = striker_3.y_or[2];

			}
			
			if (PROGRAM_UNTUK == STRIKER_2)
			{
				sprintf(buff_send, "111,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n", striker_2.x_or[1], striker_2.y_or[1], (int)striker_2.distance_ball[1], (int)striker_2.angle_ball[0], striker_2.x_or[2], striker_2.y_or[2], striker_2.yaw[1], (int)striker_2.x_mk_pos, (int)striker_2.y_mk_pos,striker_2.Volt[1]);
				sendto(s, buff_send, strlen(buff_send), 0, (struct sockaddr *) &si_other, slen);
				memset(buff_send,'\0', sizeof(buff_send));	
			}
			else if (PROGRAM_UNTUK == STRIKER_3)
			{
				sprintf(buff_send, "222,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n", striker_3.x_or[1], striker_3.y_or[1], (int)striker_3.distance_ball[1], (int)striker_3.angle_ball[0], striker_3.x_or[2], striker_3.y_or[2], striker_3.yaw[1], (int)striker_3.x_mk_pos, (int)striker_3.y_mk_pos, striker_3.Volt[1]);
				sendto(s, buff_send, strlen(buff_send), 0, (struct sockaddr *) &si_other, slen);
				memset(buff_send,'\0', sizeof(buff_send));	
			}
			else if (PROGRAM_UNTUK == KEEPER)
			{
				sprintf(buff_send, "333,%d,%d,%d,%d,%d,%d\n", keeper.x_or[1], keeper.y_or[1], (int)keeper.distance_ball[1], (int)keeper.angle_ball[0], keeper.x_ball[0], keeper.y_ball[0]);
				sendto(s, buff_send, strlen(buff_send), 0, (struct sockaddr *) &si_other, slen);
				memset(buff_send,'\0', sizeof(buff_send));	
			}
		}
		
		//======================================================//

		if (Header == 2 && Data1 == 0 && Data2 == 1) rcvString = "START"; 
		else if (Header == 2 && Data1 == 0 && Data2 == 2) rcvString = "STOP"; 
		else if (Header == 2 && Data1 == 0 && Data2 == 3) rcvString = "DROPPED_BALL"; 
		else if (Header == 2 && Data1 == 0 && Data2 == 4) rcvString = "PARKING";
		else if (Header == 2 && Data1 == 0 && Data2 == 5) rcvString = "FIRST_HALF"; 
		else if (Header == 2 && Data1 == 0 && Data2 == 6) rcvString = "SECOND_HALF"; 
		else if (Header == 2 && Data1 == 0 && Data2 == 7) rcvString = "FIRST_HALF_OVERTIME";
		else if (Header == 2 && Data1 == 0 && Data2 == 8) rcvString = "SECOND_HALF_OVERTIME";
		else if (Header == 2 && Data1 == 0 && Data2 == 9) rcvString = "END_GAME";        
		else if (Header == 2 && Data1 == 0 && Data2 == 10) rcvString = "GAMEOVER";    
		else if (Header == 2 && Data1 == 1 && Data2 == 3) rcvString = "KICKOFF_CYAN"; 
		else if (Header == 2 && Data1 == 1 && Data2 == 4) rcvString = "FREEKICK_CYAN"; 
		else if (Header == 2 && Data1 == 1 && Data2 == 5) rcvString = "GOALKICK_CYAN"; 
		else if (Header == 2 && Data1 == 1 && Data2 == 6) rcvString = "THROWIN_CYAN"; 
		else if (Header == 2 && Data1 == 1 && Data2 == 7) rcvString = "CORNER_CYAN"; 
		else if (Header == 2 && Data1 == 1 && Data2 == 8) rcvString = "PENALTY_CYAN";
		else if (Header == 2 && Data1 == 1 && Data2 == 9) rcvString = "REPAIR_OUT_CYAN"; 
		else if (Header == 2 && Data1 == 1 && Data2 == 10) rcvString = "REPAIR_IN_CYAN"; 
		else if (Header == 2 && Data1 == 1 && Data2 == 11) rcvString = "YELLOW_CARD_CYAN";
		else if (Header == 2 && Data1 == 1 && Data2 == 12) rcvString = "DOUBLE_YELLOW_CARD_CYAN";
		else if (Header == 2 && Data1 == 1 && Data2 == 13) rcvString = "RED_CARD_CYAN";
		else if (Header == 2 && Data1 == 1 && Data2 == 14) rcvString = "GOAL_CYAN";
		else if (Header == 2 && Data1 == 1 && Data2 == 15) rcvString = "SUBGOAL_CYAN";
		else if (Header == 2 && Data1 == 2 && Data2 == 3) rcvString = "KICKOFF_MAGENTA";
		else if (Header == 2 && Data1 == 2 && Data2 == 4) rcvString = "FREEKICK_MAGENTA"; 
		else if (Header == 2 && Data1 == 2 && Data2 == 5) rcvString = "GOALKICK_MAGENTA";
		else if (Header == 2 && Data1 == 2 && Data2 == 6) rcvString = "THROWIN_MAGENTA"; 
		else if (Header == 2 && Data1 == 2 && Data2 == 7) rcvString = "CORNER_MAGENTA"; 
		else if (Header == 2 && Data1 == 2 && Data2 == 8) rcvString = "PENALTY_MAGENTA";
		else if (Header == 2 && Data1 == 2 && Data2 == 9) rcvString = "REPAIR_OUT_MAGENTA";
		else if (Header == 2 && Data1 == 2 && Data2 == 10) rcvString = "REPAIR_IN_MAGENTA";
		else if (Header == 2 && Data1 == 2 && Data2 == 11) rcvString = "YELLOW_CARD_MAGENTA";
		else if (Header == 2 && Data1 == 2 && Data2 == 12) rcvString = "DOUBLE_YELLOW_CARD_MAGENTA";
		else if (Header == 2 && Data1 == 2 && Data2 == 13) rcvString = "RED_CARD_MAGENTA";
		else if (Header == 2 && Data1 == 2 && Data2 == 14) rcvString = "GOAL_MAGENTA";
		else if (Header == 2 && Data1 == 2 && Data2 == 15) rcvString = "SUBGOAL_MAGENTA";
		else if (Header == 2 && Data1 == 3 && Data2 == 1) rcvString = "WELCOME";
		else if (Header == 2 && Data1 == 3 && Data2 == 2) rcvString = "START FIRST HALF"; 
		else if (Header == 2 && Data1 == 3 && Data2 == 3) rcvString = "START SECOND HALF";
		else if (Header == 2 && Data1 == 3 && Data2 == 4) rcvString = "WORLD_STATE";
		else if (Header == 2 && Data1 == 3 && Data2 == 5) rcvString = "RESET";
		else if (Header == 2 && Data1 == 3 && Data2 == 6) rcvString = "TESTMODE_ON";
		else if (Header == 2 && Data1 == 3 && Data2 == 7) rcvString = "TESMODE_OFF";

		if (TEAM == CYAN) printf("\n%d. UDP_CLIENT %s -- RefBox = %d,%d,%d -- %s -- Team = %s -- mode = %d,%d -- ", count, SERVER, Header, Data1, Data2, rcvString, "CYAN", mode_marking, mode_formasi[1]);
		else if (TEAM == MAGENTA) printf("\n%d. UDP_CLIENT %s -- RefBox = %d,%d,%d -- %s -- Team = %s -- mode = %d,%d -- ", count, SERVER, Header, Data1, Data2, rcvString, "MAGENTA", mode_marking, mode_formasi[1]);
		else printf("\n%d. UDP_CLIENT %s -- RefBox = %d,%d,%d -- %s -- Team = %s -- mode = %d,%d -- ", count, SERVER, Header, Data1, Data2, rcvString, "CYAN", mode_marking, mode_formasi[1]);

		if ((tcsetattr(serialPort,TCSANOW,&SerialPortSettings)) != 0) printf("ERROR / ");
	   		else printf("RECEIVED / ");
		if ((tcsetattr(serialPort1,TCSANOW,&SerialPortSettings)) != 0) printf("ERROR");
	   		else printf("SENT");

		if (PROGRAM_UNTUK == STRIKER_2)
		{
			printf("\n   STRIKER 2 --> Jarak,Sudut Bola = %d,%d -- Koordinat = %d,%d -- Positioning = %d,%d -- Dummy = %d,%d -- YAW = %d", (int)striker_2.distance_ball[1], (int)striker_2.angle_ball[0], (int)striker_2.x_or[1], (int)striker_2.y_or[1], (int)striker_2.coor_y[1], (int)striker_2.coor_x[1], dummy_pos1, dummy_pos2, /* striker_2.x_ball[0], striker_2.y_ball[0],*/ flag_wifi);
			printf("\n   STRIKER 3 --> Jarak.Sudut Bola = %d,%d -- Koordinat = %d,%d -- Positioning = %d,%d -- Dummy = %d,%d -- YAW = %d\n", (int)striker_3.distance_ball[0], (int)striker_3.angle_ball[0], (int)striker_3.coor_x[1], (int)striker_3.coor_y[1], (int)striker_3.coor_y[1], (int)striker_3.coor_x[1], dummy_pos1, dummy_pos2, flag_wifi);
//				printf("\n   A[%d],B[%d],C[%d],D[%d] = %.2f | %.2f | %.2f | %.2f\n", 0, 0, 0, 0, pengali_A[0], pengali_B[0], penambah_C[0],penambah_D[0]);
				printf("   FORMASI = %d\n", mode_formasi[1]);
		}
		if (PROGRAM_UNTUK == STRIKER_3)
		{
			printf("\n   STRIKER 2 --> Jarak,Sudut Bola = %d,%d -- Koordinat = %d,%d -- Positioning = %d,%d -- Dummy = %d,%d -- YAW = %d", (int)striker_2.distance_ball[0], (int)striker_2.angle_ball[1], (int)striker_2.coor_x[1], (int)striker_2.coor_y[1], (int)striker_2.coor_y[1], (int)striker_2.coor_x[1], dummy_pos1, dummy_pos2, striker_2.yaw[0]);
			printf("\n   STRIKER 3 --> Jarak,Sudut Bola = %d,%d -- Koordinat = %d,%d -- Positioning = %d,%d -- Dummy = %d,%d -- YAW = %d\n", (int)striker_3.distance_ball[1], (int)striker_3.angle_ball[0], (int)striker_3.x_or[1], (int)striker_3.y_or[1], (int)striker_3.coor_y[1], (int)striker_3.coor_x[1], dummy_pos1, dummy_pos2,/* (int)striker_3.x_ball[0], (int)striker_3.y_ball[0],*/ (int)striker_3.yaw[1]);
//			printf("\n   A[%d],B[%d],C[%d],D[%d] = %.2f | %.2f | %.2f | %.2f |\n", 1, 0, 1, 0, pengali_A[1], pengali_B[0], penambah_C[1],penambah_D[0]);
			printf("   FORMASI = %d\n", mode_formasi[1]);
		}
		if (PROGRAM_UNTUK == KEEPER) 
		{
			printf("\n   KEEPER --> Jarak,Sudut Bola = %d,%d -- Koordinat = %d,%d -- Positioning = %d,%d -- Bola = %d,%d", (int)keeper.distance_ball[1], (int)keeper.angle_ball[0], (int)keeper.coor_x[2], (int)keeper.coor_y[2], (int)keeper.coor_y[1], (int)keeper.coor_x[1], keeper.x_ball[0], keeper.y_ball[0]);
			printf("\n   KEEPER --> Jarak,Sudut Bola = %d,%d -- Koordinat = %d,%d -- Positioning = %d,%d -- Bola = %d,%d\n", (int)keeper.distance_ball[1], (int)keeper.angle_ball[0], keeper.x_or[1], keeper.y_or[1], (int)keeper.coor_y[1], (int)keeper.coor_x[1], keeper.x_ball[1], keeper.y_ball[1]);
		}

		//======================================================//
	}   

	close(fd);
	unlink(dataaddr);
	fclose(serial_send);
	fclose(serial_rcv);    
	close(s);
	close(serialPort);
	close(serialPort1);
    return (0);
}

