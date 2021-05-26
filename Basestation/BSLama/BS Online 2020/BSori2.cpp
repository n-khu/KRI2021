/*
 Simple udp server
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

#define BUFLEN 1024  //Max length of buffer
#define PORT 8080  //The port on which to listen for incoming data
#define PI 3.141592

using namespace cv;
using namespace std;

const int CYAN = 1;
const int MAGENTA = 2;

int TEAM = CYAN;

//konfersi nilai BaseStation ke MK
float pengali_A;
float pengali_B;
float penambah_C;
float penambah_D;

float y_real_min = -80;
float y_real_max = 980;
float x_real_min = -80;
float x_real_max = 680;

// double x_real_min[3] = {-38,0,450};
// double x_real_max[3] = {0,450,488};
// double y_real_min[3] = {-76,0,600};
// double y_real_max[3] = {0,600,676};

double x_BS_min[3] = {0,70,620};
double x_BS_max[3] = {70,620,690};
double y_BS_min[3] = {0,34,448};
double y_BS_max[3] = {34,448,483};


int flag_reset_2 = 0, flag_reset_3 = 0;
int ref2_temp, ref3_temp;
int Header=0, Data1=0,Data2=0;
int refbox1 = 0, refbox2 = 0, refbox3 = 0;
int ref1 = 0, ref2 = 0, ref3 = 0;
int referee = 1;
int p = 1;
int mode_marking = 0;
int mode_reset = 0;
int mode_formasi = 0;
int Robot_B = 0 ;
int Robot_A = 0 ;
int T = 0, V = 0, W = 0, X = 0,Y = 0, Z = 0, U = 0, YAW = 0, X_CM = 0, Y_CM = 0, VOLT = 0, TIMER = 0;
int A,B,C,D;
int x_ball=0, y_ball=0;
int striker1_mark = 0, striker2_mark = 0, keeper_mark = 0;
int Jarak_Bola_Robot3;
int Jarak_Bola_Robot2;
int Last_Jarak_Bola_Robot2 = 0;
int Last_Jarak_Bola_Robot3 = 0;
int mouse_x;
int mouse_y;
//static int counting = 0;	
// variabel mousehandler
int button_x[4];
int button_y[4];
int x_reset[3];
int y_reset[3];
int last_x[4];
int last_y[4];
bool pressbut = false;
bool resetbut = false;
bool resetodo = false;
//=================//
int counter = 0 ;
int count_to_noBall = 0;
int ia = 0;
int try1 = 0, try2 = 0, try3 = 0;
const int newWidth = 1200;
const int newHeight = 650;
double x_keeper = 41;
double y_keeper = 236;
const int KIRI = 1;
const int KIRI_TENGAH = 2;
const int TENGAH = 3;
const int TENGAH_KANAN = 4;
const int KANAN = 5;
int goalkick_x_lawan[3];
int goalkick_y_lawan[3];
int penalty_x_lawan[3];
int penalty_y_lawan[3];
int kickoff_x_lawan[3];
int kickoff_y_lawan[3];
int corner_x_lawan[3];
int corner_y_lawan[3];
int dropball_x_lawan[3];
int dropball_y_lawan[3];
int freekick_x_lawan[3];
int freekick_y_lawan[3];
int penalti_x_kita[3];
int penalti_y_kita[3];
const double pembagi_x = 1.44;
const double pembagi_y = 1.3056;

//------edit
int flag_wifi; //button baru
int dummy_pos1; //posisi dummy 1-3
int dummy_pos2; //posisi dummy 7-8
int dummy_pos3; //posisi dummy 4-6
int dummy_pos4; //posisi dummy keeper
//------

char buff_write[512];
char buff_read[1024];
char ch = 0;
//const char  *mode;
string mode;

const string window_name = "ENSPARTAN BASESTATION";

float OdoX = 0;
float OdoY = 0;

string refbox_cmd;
const int fontFace = FONT_HERSHEY_SIMPLEX;
const int fontFace_refbox = FONT_HERSHEY_SIMPLEX;
const int fontFace_robot = FONT_HERSHEY_SIMPLEX;
const int fontFace_formasi = FONT_HERSHEY_SIMPLEX;
double fontScale = 1.3;
double fontScale_refbox = 0.8;
double fontScale_robot = 1.3;
double fontScale_formasi = 1.3;
int thickness = 2;
int thickness_refbox = 2;
int thickness_robot = 2;
int thickness_formasi = 2;
int baseline = 0;

Mat fields, lapangan, newfields, symbol, newsymbol, simbol, lambang;
Mat result = Mat::zeros(newHeight, newWidth, CV_32FC3);

Point S2[2];

struct temporary{
	float coor_x[6];
	float coor_y[6];
	float dist_ball;
	float yaw_x;
	float yaw_y;
	int reset_x[5];
	int reset_y[5];
	int angle_ball;
	int mark;
	int POS_X;
	int POS_Y;
	int pos_X;
	int pos_Y;
	int pos_res_x;
	int pos_res_y;
	int x_ball[3];
	int y_ball[3];
	float yaw;
	float yaw_rad; 
} temp1, temp2, temp3;

struct robot
{
	float coor_x[6];
	float coor_y[6];
	float dist_ball;
	float yaw_x;
	float yaw_y;
	int volt[2];
	int x_cm[2];
	int y_cm[2];
	int reset_x[5];
	int reset_y[5];
	int angle_ball;
	int mark;
	int POS_X;
	int POS_Y;
	int pos_X;
	int pos_Y;
	int pos_res_x;
	int pos_res_y;
	int x_ball[3];
	int y_ball[3];
	float yaw;
	float yaw_rad;
	int reset_yaw[3];
	int target_x[0];
	int target_y[0]; 
	int timer;
} striker_2, striker_3, keeper;



void die(const char *s)
{
    perror(s);
    exit(1);
}

//=============================================================================//
//=======================Split String Version 2================================//
//=============================================================================//
//---------------------------------------var global usart
char *pry1, *pry2, *pry3;
int pcount = 1;
int pcounts = 1;
int pcountss = 1;

double calculate_x(double x)
{
	if (x >= 70 && x <= 655) x = (x - 70) * 0.8621;		//500			70 - 655
	else if (x < 70) x = (20 - (x / 3.5)) * -1;
	else x = ((x - 655) / 3.25) + 500;
	return x;
}

double calculate_y(double y)
{
	if (y >= 40 && y <= 430) y = (y - 40) * 0.8205;		//360
	else if (y < 40) y = (20 - (y / 2)) * -1;
	else y = ((y - 430) / 2) + 320;
	return y;
}

void koordinat(int a, int b, int c, int d, int e, int f)
{

	striker_3.coor_x[2] = a;
	striker_3.coor_y[2] = b;
	striker_2.coor_x[2] = c;
	striker_2.coor_y[2] = d;
	keeper.coor_x[2] = e;
	keeper.coor_y[2] = f;
}

void print_txt(Mat& img, const string& name, int marking)
{
	Size textSize = getTextSize(name, fontFace_refbox, fontScale_refbox, thickness_refbox, &baseline);
	baseline += thickness_refbox / thickness_refbox-5;
	Point textOrg((img.cols - textSize.width)/18, (img.rows + textSize.height)/1.14);
	Scalar uniform1 = Scalar(255,0,0);
	Scalar uniform2 = Scalar(100,0,255);
	Scalar uniform3 = Scalar(0,255,0);
	Scalar uniform;

	if (marking == 1) 
	{
		uniform = uniform1; 
		rectangle(img, Point(30-20,40+298), Point(30+120,40+338), uniform, CV_FILLED);
		putText(img, name, textOrg, fontFace_refbox, fontScale_refbox, Scalar::all(255), thickness_refbox, CV_AA);
	}
	else if (marking == 2) 
	{
		uniform = uniform2; 
		rectangle(img, Point(30-20,40+298), Point(30+120,40+338), uniform, CV_FILLED);
		putText(img, name, textOrg, fontFace_refbox, fontScale_refbox, Scalar::all(255), thickness_refbox, CV_AA);
	}
	else 
	{
		uniform = uniform3;
		rectangle(img, Point(30-20,40+298), Point(30+120,40+338), uniform, CV_FILLED);
		putText(img, name, textOrg, fontFace_refbox, fontScale_refbox, Scalar::all(0), thickness_refbox, CV_AA);
	}
}

void print_mode(Mat& img, const string& name)
{
	Size textSize = getTextSize(name, fontFace, fontScale, thickness, &baseline);
	baseline += thickness / thickness-5;
	Point textOrg((img.cols - textSize.width)/2, (img.rows + textSize.height)/1.15);
	rectangle(img, Point(30+170,40+301), Point(30+245,40+341), Scalar(100,0,255), CV_FILLED);
	putText(img, name, textOrg, fontFace, fontScale, Scalar::all(0), thickness, CV_AA);
}

void print_robot(Mat& img, const string& name, int marking)
{
	Size textSize = getTextSize(name, fontFace_robot, fontScale_robot, thickness_robot, &baseline);
	baseline += thickness_robot / thickness_robot-5;
	Point textOrg((img.cols - textSize.width)/1.14, (img.rows + textSize.height)/1.15);
	if (marking == 1 || marking == 2 || marking == 3 || marking == 4)
	{
		rectangle(img, Point(30+338,40+298), Point(30+400,40+338), Scalar(0,100,0), CV_FILLED);
		putText(img, name, textOrg, fontFace_robot, fontScale_robot, Scalar::all(0), thickness_robot, CV_AA);
	}
	else 
	{
		rectangle(img, Point(30+338,40+298), Point(30+400,40+338), Scalar::all(0), CV_FILLED);
		putText(img, name, textOrg, fontFace_robot, fontScale_robot, Scalar::all(0), thickness_robot, CV_AA);
	}
}

void print_formasi(Mat& img, const string& name, int marking)
{
	Size textSize = getTextSize(name, fontFace_formasi, fontScale_formasi, thickness_formasi, &baseline);
	baseline += thickness_formasi / thickness_formasi-5;
	if (marking == 1 || marking == 2 || marking == 3 || marking == 4)
	{
		Point textOrg((img.cols - textSize.width)/1.038, (img.rows + textSize.height)/3.36);
		rectangle(img, textOrg + Point(0, baseline), textOrg + Point(textSize.width, -textSize.height-5), Scalar(0,0,0), CV_FILLED);
		putText(img, name, textOrg, fontFace_formasi, fontScale_formasi, Scalar::all(255), thickness_formasi, CV_AA);
	}
	else
	{
		Point textOrg((img.cols - textSize.width)/1.04, (img.rows + textSize.height)/3.36);
		rectangle(img, textOrg + Point(0, baseline), textOrg + Point(textSize.width, -textSize.height-5), Scalar::all(0), CV_FILLED);
		putText(img, name, textOrg, fontFace_formasi, fontScale_formasi, Scalar::all(0), thickness_formasi, CV_AA);
	}
}

void mouseHandler(int event, int x, int y, int flags, void* param)
{       
    if (flags == EVENT_FLAG_LBUTTON && pressbut == false && resetbut == false)
    {
        Point*p = (Point*)param;
		p->x = x;
		p->y = y;
		button_x[2] = x;
		button_y[2] = y;
		if ((button_x[2] > 709 && (button_y[2] >= 0 || button_y[2] < 650)) || ((button_x[2] >= 0  && button_x[2] < 709)&& button_y[2] > 485)){ 
			pressbut = true;
			flag_reset_3 = 0;
			flag_reset_2 = 0;
		}
		else 
		{
			pressbut = false;
			resetbut = true;
			flag_reset_3 = 1;
		}
		if (resetbut == true)
		{
			resetodo = true;
			x_reset[0] = button_x[2];
			y_reset[0] = button_y[2];
		}
		last_x[0] = button_x[2];
		last_y[0] = button_y[2];
		last_x[1] = x_reset[0];
		last_y[1] = y_reset[0];
    }
    if (flags == EVENT_FLAG_MBUTTON && pressbut == false && resetbut == false)
    {
        Point*p = (Point*)param;
		p->x = x;
		p->y = y;
		button_x[2] = x;
		button_y[2] = y;
		if ((button_x[2] > 709 && (button_y[2] > 0 || button_y[2] < 650)) || ((button_x[2] > 0  && button_x[2] < 709)&& button_y[2] > 485)){ 
			pressbut = true;
			flag_reset_3 = 0;
			flag_reset_2 = 0;
		}
		else 
		{
			pressbut = false;
			resetbut = true;
			flag_reset_2 = 1;
		}
		if (resetbut == true)
		{
			resetodo = true;
			x_reset[1] = button_x[2];
			y_reset[1] = button_y[2];
		}
		last_x[0] = button_x[2];
		last_y[0] = button_y[2];
		last_x[2] = x_reset[1];
		last_y[2] = y_reset[1];
    }
    if (event == EVENT_MOUSEMOVE && (pressbut == true || pressbut == false) && (resetbut == true || resetbut == false))
    {
	  	Point*p = (Point*)param;	
		p->x = x;
		p->y = y;
		button_x[2] = x;
		button_y[2] = y;
		x_reset[0] = x;
		y_reset[0] = y;
		x_reset[1] = x;
		y_reset[1] = y;
		pressbut = false;
		resetbut = false;
		button_x[2] = last_x[0];
		button_y[2] = last_y[0];
		x_reset[0] = last_x[1];
		y_reset[0] = last_y[1];
		x_reset[1] = last_x[2];
		y_reset[1] = last_y[2];
    }

	button_x[0] = button_x[2];
	button_y[0] = button_y[2];
//	striker_3.reset_x[0] = x_reset[0] - 13; //-13 untuk lapangan tidak di 0,0
//	striker_3.reset_y[0] = y_reset[0] - 13;
//	striker_2.reset_x[0] = x_reset[1] - 13;
//	striker_2.reset_y[0] = y_reset[1] - 13;
//	if (striker_2.reset_x[0] < 0) striker_2.reset_x[0] = 0;
//	if (striker_2.reset_y[0] < 0) striker_2.reset_y[0] = 0;
//	if (striker_3.reset_x[0] < 0) striker_3.reset_x[0] = 0;
//	if (striker_3.reset_y[0] < 0) striker_3.reset_y[0] = 0;
//	if (striker_2.reset_x[0] > 696) striker_2.reset_x[0] = 696;
//	if (striker_2.reset_y[0] > 472) striker_2.reset_y[0] = 472;
//	if (striker_3.reset_x[0] > 696) striker_3.reset_x[0] = 696;
//	if (striker_3.reset_y[0] > 472) striker_3.reset_y[0] = 472;
	
	striker_3.coor_x[5] = x_reset[0] - 13; //-13 untuk lapangan tidak di 0,0
	striker_3.coor_y[5] = y_reset[0] - 6;
	striker_2.coor_x[5] = x_reset[1] - 13;
	striker_2.coor_y[5] = y_reset[1] - 6;
	if (striker_2.coor_x[5] < 0) striker_2.coor_x[5] = 0;
	if (striker_2.coor_y[5] < 0) striker_2.coor_y[5] = 0;
	if (striker_3.coor_x[5] < 0) striker_3.coor_x[5] = 0;
	if (striker_3.coor_y[5] < 0) striker_3.coor_y[5] = 0;
	if (striker_2.coor_x[5] > 690) striker_2.coor_x[5] = 690;
	if (striker_2.coor_y[5] > 483) striker_2.coor_y[5] = 483;
	if (striker_3.coor_x[5] > 690) striker_3.coor_x[5] = 690;
	if (striker_3.coor_y[5] > 483) striker_3.coor_y[5] = 483;
}

void Parsing_data(char input[],int &out1,int &out2,int &out3)
{
    pry1 = strtok(input, ",");
    while (pry1 != 0 && pcounts <= 3)
    {
        if (pcounts == 1) out1 = atof(pry1);
        else if (pcounts == 2) out2 = atof(pry1);
        else if (pcounts == 3) out3 = atof(pry1);
        pry1 = strtok (0, ",");
        pcounts++;
    }
    if (pcounts == 4) pcounts = 1;
}

void Parsing_data2(char input[], int &out1, int &out2, int &out3, int &out4, int &out5,int &out6,int &out7, int &out8,int &out9,int &out10,int &out11, int &out12)
{
    pry2 = strtok(input, ",");
    while (pry2 != 0 && pcountss <= 12)
    {
        if (pcountss == 1) out1 = atof(pry2);
        else if (pcountss == 2) out2 = atof(pry2);        
        else if (pcountss == 3) out3 = atof(pry2);
	else if (pcountss == 4) out4 = atof(pry2);
	else if (pcountss == 5) out5 = atof(pry2);
	else if (pcountss == 6) out6 = atof(pry2);
	else if (pcountss == 7) out7 = atof(pry2);
	else if (pcountss == 8) out8 = atof(pry2);
	else if (pcountss == 9) out9 = atof(pry2);
	else if (pcountss == 10) out10 = atof(pry2);
	else if (pcountss == 11) out11 = atof(pry2);
	else if (pcountss == 12) out12 = atof(pry2);
        pry2 = strtok (0, ",");
        pcountss++;
    }
    if (pcountss == 13) pcountss = 1;
}

void Parsing_data3(char input[],int &out1,int &out2,int &out3,int &out4,int &out5, int &out6, int &out7, int &out8, int&out9)
{
    pry3 = strtok(input, ",");
    while (pry3 != 0 && pcount <= 9)
    {
        if (pcount == 1) out1 = atof(pry3);
        else if (pcount == 2) out2 = atof(pry3);        
        else if (pcount == 3) out3 = atof(pry3);
		else if (pcount == 4) out4 = atof(pry3);
		else if (pcount == 5) out5 = atof(pry3);
		else if (pcount == 6) out6 = atof(pry3);
		else if (pcount == 7) out7 = atof(pry3);
		else if (pcount == 8) out8 = atof(pry3);
		else if (pcount == 9) out9 = atof(pry3);
        pry3 = strtok (0, ",");
        pcount++;
    }
    if (pcount == 10) pcount = 1;
}

//=============================================================================//
//=============================================================================//

int main(int argc, char **argv)
{
    //================================FIFO INIT==================================//

    int fd;
    
    static const char * dataaddr = "/tmp/RDWR"; //alamat sesuai dengan yang dibuat writernya
    mkfifo(dataaddr, 0666);
    
   	fd = open(dataaddr, O_RDWR | O_NDELAY | O_NOCTTY | O_NONBLOCK | O_ASYNC);
    
    //===============================UDP INIT======================================//

    struct sockaddr_in si_me, si_other;
    socklen_t slen = sizeof(si_other) ;
    int s;
    char buf[BUFLEN];
    char message[BUFLEN];
    
    //create a UDP socket
    if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        die("socket");
    }
    
    fcntl(s , F_SETFL , O_NONBLOCK, O_NDELAY);
    
    // zero out the structure
    memset((char *) &si_me, 0, sizeof(si_me));
    
    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(PORT);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);
    
    //bind socket to port
    if (bind(s , (struct sockaddr*)&si_me, sizeof(si_me) ) == -1)
    {
        die("bind");
    }

	//===================== DRAW A FOOTBALL MAP SKETCH ====================//

	
	String lapang("/home/nizzah/kri2021/BASESTATION/lap2020.jpg"); // by default
    if (argc > 1)
    {
        lapang = argv[1];
    }

    fields = imread (lapang, IMREAD_COLOR); // Read the file

    if (fields.empty())                     // Check for invalid input
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }

	// //===================== DRAW UB SYMBOL IN MAP SKETCH ==================//

	String logo("/home/nizzah/kri2021/BASESTATION/lambang-robotika.png"); // by default
    if (argc > 1)
    {
        logo = argv[1];
    }

    simbol = imread (logo, IMREAD_COLOR); // Read the file

    if (simbol.empty())                     // Check for invalid input
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }

 	symbol = Mat::zeros(200,240,CV_32FC3);
	Mat rob = Mat::zeros(400,480,CV_32FC3);
	Mat formation = Mat::zeros(130,720,CV_32FC3);
	Mat Reset = Mat::zeros(240,720,CV_32FC3);

	resize(fields, newfields, cvSize(690,483));
	newfields.convertTo(lapangan, CV_32FC3, 1/255.0);
	resize(simbol, newsymbol, cvSize(newWidth-960,newHeight/3));
	newsymbol.convertTo(lambang, CV_32FC3, 1/255.0);

//	lapangan.copyTo(result(Rect(13, 13, lapangan.cols, lapangan.rows)));

	rectangle(symbol, Point(5,5), Point(75,65), Scalar(255,0,0), CV_FILLED);
	rectangle(symbol, Point(5,70), Point(75,130), Scalar(255,0,0), CV_FILLED);  
	rectangle(symbol, Point(5,135), Point(75,195), Scalar(255,0,0), CV_FILLED);

	rectangle(symbol, Point(85,5), Point(155,65), Scalar(255,0,0), CV_FILLED);    
	rectangle(symbol, Point(85,70), Point(155,130), Scalar(255,0,0), CV_FILLED);    
	rectangle(symbol, Point(85,135), Point(155,195), Scalar(255,0,0), CV_FILLED);    

	rectangle(symbol, Point(165,5), Point(235,65), Scalar(255,0,0), CV_FILLED);    
	rectangle(symbol, Point(165,70), Point(235,130), Scalar(255,0,0), CV_FILLED);    
	rectangle(symbol, Point(165,135), Point(235,195), Scalar(255,0,0), CV_FILLED);    

	rectangle(symbol, Point(15,10), Point(65,60), CV_RGB(255,0,0), CV_FILLED);
	rectangle(symbol, Point(15,75), Point(65,125), CV_RGB(255,0,0), CV_FILLED);  
	rectangle(symbol, Point(15,140), Point(65,190), CV_RGB(255,0,0), CV_FILLED);

	rectangle(symbol, Point(95,10), Point(145,60), CV_RGB(255,0,0), CV_FILLED);    
	rectangle(symbol, Point(95,75), Point(145,125), CV_RGB(255,0,0), CV_FILLED);    
	rectangle(symbol, Point(95,140), Point(145,190), CV_RGB(255,0,0), CV_FILLED);    

	rectangle(symbol, Point(175,10), Point(225,60), CV_RGB(255,0,0), CV_FILLED);    
	rectangle(symbol, Point(175,75), Point(225,125), CV_RGB(255,0,0), CV_FILLED);    
	rectangle(symbol, Point(175,140), Point(225,190), CV_RGB(255,0,0), CV_FILLED);   

	line(rob, Point(0,5), Point(480,5), CV_RGB(100,50,250),2,8,0);
	//rectangle(rob, Point(5,5), Point(88,88), Scalar(0,255,0), CV_FILLED);    
	putText(rob, format("HADES (R1)"), Point(15,35+4), FONT_HERSHEY_SIMPLEX, 0.8, Scalar(0,255,0), 1);
	putText(rob, format("ARES (R2)"), Point(160+15,35+4), FONT_HERSHEY_SIMPLEX, 0.8, Scalar(0,255,0), 1);
	putText(rob, format("KEEPER"), Point(320+30,35+4), FONT_HERSHEY_SIMPLEX, 0.8, Scalar(0,255,0), 1);

	line(rob, Point(0,5), Point(0,400), CV_RGB(255,255,255), 2,8,0);
	line(rob, Point(160,5), Point(160,400),CV_RGB(255,255,255),2,8,0);
	line(rob, Point(320,5), Point(320,400),CV_RGB(255,255,255),2,8,0);
	line(rob, Point(320,5), Point(320,400), CV_RGB(255,255,255),2,8,0);
	line(rob, Point(0,55), Point(480,55), CV_RGB(255,255,255),2,8,0);    
	line(rob, Point(480,5), Point(480,400), CV_RGB(255,255,255),2,8,0);    
	line(rob, Point(0,398), Point(480,398), CV_RGB(255,255,255),2,8,0);  

	putText(rob, format("R Ball"), Point(5+0,40+37), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);
	putText(rob, format(": "), Point(5+45,40+37), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);
	putText(rob, format("R Ball"), Point(5+160,40+37), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);
	putText(rob, format(": "), Point(5+205,40+37), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);
	putText(rob, format("R Ball"), Point(5+320,40+37), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);
	putText(rob, format(": "), Point(5+365,40+37), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);

	line(rob, Point(0,85), Point(480,85), CV_RGB(255,255,255), 2,8,0);    
	
	putText(rob, format("Positioning"), Point(5+0,40+65), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);
	putText(rob, format(": "), Point(5+83,40+65), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);
	putText(rob, format("Positioning"), Point(5+160,40+65), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);
	putText(rob, format(": "), Point(5+243,40+65), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);
	putText(rob, format("Positioning"), Point(5+320,40+65), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);
	putText(rob, format(": "), Point(5+403,40+65), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);

	line(rob, Point(0,113), Point(480,113), CV_RGB(255,255,255), 2,8,0);    

	putText(rob, format("Crnt Pos"), Point(5+0,40+93), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);
	putText(rob, format(": "), Point(5+70,40+93), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);
	putText(rob, format("Crnt Pos"), Point(5+160,40+93), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);
	putText(rob, format(": "), Point(5+230,40+93), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);
	putText(rob, format("Crnt Pos"), Point(5+320,40+93), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);
	putText(rob, format(": "), Point(5+390,40+93), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);

	line(rob, Point(0,141), Point(480,141), CV_RGB(255,255,255), 2,8,0);    

	putText(rob, format("Reset"), Point(5+0,40+121), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);
	putText(rob, format(": "), Point(5+47,40+121), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);
	putText(rob, format("Reset"), Point(5+160,40+121), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);
	putText(rob, format(": "), Point(5+207,40+121), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);
	putText(rob, format("Reset"), Point(5+320,40+121), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);
	putText(rob, format(": "), Point(5+367,40+121), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);

	line(rob, Point(0,169), Point(480,169), CV_RGB(255,255,255), 2,8,0);    

	putText(rob, format("Angle Ball"), Point(5+0,40+149), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);
	putText(rob, format(": "), Point(5+73,40+149), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);
	putText(rob, format("Angle Ball"), Point(5+160,40+149), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);
	putText(rob, format(": "), Point(5+233,40+149), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);
	putText(rob, format("Angle Ball"), Point(5+320,40+149), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);
	putText(rob, format(": "), Point(5+393,40+149), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);

	line(rob, Point(0,197), Point(480,197), CV_RGB(255,255,255), 2,8,0);
	
	putText(rob, format("YAW"), Point(5+0,40+177), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);
	putText(rob, format(": "), Point(5+47,40+177), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);
	putText(rob, format("YAW"), Point(5+160,40+177), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);
	putText(rob, format(": "), Point(5+207,40+177), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);
	putText(rob, format("YAW"), Point(5+320,40+177), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);  
	putText(rob, format(": "), Point(5+367,40+177), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);
	
	line(rob, Point(0,225), Point(480,225), CV_RGB(255,255,255), 2,8,0);
	
	putText(rob, format("reset_YAW"), Point(5+0,40+205), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);
	putText(rob, format(": "), Point(5+80,40+205), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);
	putText(rob, format("reset_YAW"), Point(5+160,40+205), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);
	putText(rob, format(": "), Point(5+240,40+205), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);
	putText(rob, format("reset_YAW"), Point(5+320,40+205), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);  
	putText(rob, format(": "), Point(5+400,40+205), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);
	
	line(rob, Point(0,251), Point(480,251), CV_RGB(255,255,255), 2,8,0);
	
	putText(rob, format("dummy"), Point(5+0,40+231), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);
	putText(rob, format(": "), Point(5+57,40+231), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);
	putText(rob, format("dummy"), Point(5+160,40+231), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);
	putText(rob, format(": "), Point(5+217,40+231), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);
	putText(rob, format("dummy"), Point(5+320,40+231), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);  
	putText(rob, format(": "), Point(5+377,40+231), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);

	line(rob, Point(0,280), Point(480,280), CV_RGB(255,255,255), 2,8,0);

	putText(rob, format("Status"), Point(5+0,40+259), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);
	putText(rob, format(": "), Point(5+51,40+259), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);
	putText(rob, format("Status"), Point(5+160,40+259), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);
	putText(rob, format(": "), Point(5+211,40+259), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);
	putText(rob, format("Status"), Point(5+320,40+259), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);      
	putText(rob, format(": "), Point(5+371,40+259), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);

	line(rob, Point(0,308), Point(480,308), CV_RGB(255,255,255), 2,8,0);
	
	putText(rob, format("Volt"), Point(5+0,40+287), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);
	putText(rob, format(": "), Point(5+51,40+287), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);
	putText(rob, format("Volt"), Point(5+160,40+287), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);
	putText(rob, format(": "), Point(5+211,40+287), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);
	putText(rob, format("Volt"), Point(5+320,40+287), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);      
	putText(rob, format(": "), Point(5+371,40+287), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);

	line(rob, Point(0,336), Point(480,336), CV_RGB(255,255,255), 2,8,0);

	putText(rob, format("REFBOX"), Point(5+40,40+317), FONT_HERSHEY_PLAIN, 1.2, CV_RGB(255,255,255), 1);
	putText(rob, format("MODE"), Point(5+210,40+317), FONT_HERSHEY_PLAIN, 1.2, CV_RGB(255,255,255), 1);
	putText(rob, format("LAPANGAN"), Point(5+185,40+333), FONT_HERSHEY_PLAIN, 1.2, CV_RGB(255,255,255), 1);
	putText(rob, format("ROBOT"), Point(5+365,40+317), FONT_HERSHEY_PLAIN, 1.2, CV_RGB(255,255,255), 1);

	putText(formation, format("KEEPER"), Point(5,40), FONT_HERSHEY_PLAIN, 1.5, CV_RGB(255,255,255), 2);

	rectangle(formation, Point(240+40,10), Point(240+100,55), CV_RGB(0,0,255), CV_FILLED);    
	rectangle(formation, Point(240+130,10), Point(240+190,55), CV_RGB(0,0,255), CV_FILLED);    
	rectangle(formation, Point(240+220,10), Point(240+280,55), CV_RGB(0,0,255), CV_FILLED);
	rectangle(formation, Point(240+310,10), Point(240+370,55), CV_RGB(0,0,255), CV_FILLED);      

	rectangle(formation, Point(240+45,15), Point(240+95,50), CV_RGB(255,0,0), CV_FILLED);    
	rectangle(formation, Point(240+135,15), Point(240+185,50), CV_RGB(255,0,0), CV_FILLED);    
	rectangle(formation, Point(240+225,15), Point(240+275,50), CV_RGB(255,0,0), CV_FILLED);
	rectangle(formation, Point(240+315,15), Point(240+365,50), CV_RGB(255,0,0), CV_FILLED);   

	putText(formation, format("1"), Point(240+55,49), FONT_HERSHEY_PLAIN, 3, Scalar(0,0,0), 2);
	putText(formation, format("2"), Point(240+145,49), FONT_HERSHEY_PLAIN, 3, Scalar(0,0,0), 2);
	putText(formation, format("3"), Point(240+232,49), FONT_HERSHEY_PLAIN, 3, Scalar(0,0,0), 2);
	putText(formation, format("R"), Point(240+325,49), FONT_HERSHEY_PLAIN, 3, Scalar(0,0,0), 2);

	line(formation, Point(640,0), Point(640,65), CV_RGB(255,255,255), 2,8,0);

	putText(formation, format("ROBOT REPAIR"), Point(5,105), FONT_HERSHEY_PLAIN, 1.5, CV_RGB(255,255,255), 2);

	rectangle(formation, Point(240+40,75), Point(240+110,120), Scalar(255,0,0), CV_FILLED);
	rectangle(formation, Point(240+140,75), Point(240+210,120), Scalar(255,0,0), CV_FILLED);    
	rectangle(formation, Point(240+240,75), Point(240+310,120), Scalar(255,0,0), CV_FILLED);        
	rectangle(formation, Point(240+340,75), Point(240+410,120), Scalar(255,0,0), CV_FILLED);    

	rectangle(formation, Point(240+45,80), Point(240+105,115), CV_RGB(200,255,0), CV_FILLED);
	rectangle(formation, Point(240+145,80), Point(240+205,115), CV_RGB(200,255,0), CV_FILLED);
	rectangle(formation, Point(240+245,80), Point(240+305,115), CV_RGB(200,255,0), CV_FILLED);
	rectangle(formation, Point(240+345,80), Point(240+405,115), CV_RGB(200,255,0), CV_FILLED);

	putText(formation, format("ALL"), Point(240+48,75+35), FONT_HERSHEY_PLAIN, 2, Scalar(0,0,0), 2);
	putText(formation, format("S2"), Point(240+155,75+35), FONT_HERSHEY_PLAIN, 2, Scalar(0,0,0), 2);
	putText(formation, format("S3"), Point(240+255,75+35), FONT_HERSHEY_PLAIN, 2, Scalar(0,0,0), 2);
	putText(formation, format("GK"), Point(240+353,75+35), FONT_HERSHEY_PLAIN, 2, Scalar(0,0,0), 2);

	line(formation, Point(0,1), Point(720,1), CV_RGB(255,255,255), 2,8,0);
	line(formation, Point(0,0), Point(0,130), CV_RGB(255,255,255), 2,8,0);
	line(formation, Point(0,65), Point(720,65), CV_RGB(255,255,255), 2,8,0);
	line(formation, Point(240,0), Point(240,130), CV_RGB(255,255,255), 2,8,0);
	line(formation, Point(0,128), Point(720,128), CV_RGB(255,255,255), 2,8,0);

	//printf("Waiting for data...");
    fflush(stdout);

	int count = 0;
	
	// Perhitungan variabel konfersi
	pengali_A = 690/(y_real_max - y_real_min);
	pengali_B = 483/(x_real_max - x_real_min);

	penambah_C = -(pengali_A*x_real_min);
	penambah_D = -(pengali_B*y_real_min);	

	// for(int d = 0;d < 3;d++){
	// 	pengali_A[d] = x_BS_max[d]/(x_real_max[d] - x_real_min[d]);
	// 	pengali_B[d] = y_BS_max[d]/(y_real_max[d] - y_real_min[d]);

	// 	penambah_C[d] = -(pengali_A[d]*x_real_min[d]);	
	// 	penambah_D[d] = -(pengali_B[d]*y_real_min[d]);	
	// }
	
	striker_2.reset_yaw[0] = 0;
	striker_3.reset_yaw[0] = 0;
	keeper.reset_yaw[0] = 0;

    while (ch != 27)
    {
		count++;
		if (count == 16) count = 0;
        counter++ ;
        if (counter == 10) counter = 0;

		namedWindow(window_name, CV_WINDOW_AUTOSIZE);
		setMouseCallback(window_name, mouseHandler, &p);

        //===============FIFO FUNCTION FOR TCP====================//        

		if (referee != 0 && counter > 0) // && counter <= 4) //	7
		{
			memset(buff_read, '\0', sizeof(buff_read));
			read(fd, buff_read, sizeof(buff_read));	   
			Parsing_data(buff_read, refbox1, refbox2, refbox3);    

			ref1 = refbox1;
			ref2 = refbox2;
			ref3 = refbox3;
			
			if(ref2 != ref2_temp || ref3 != ref3_temp){
				striker_2.coor_x[5] = 0;
				striker_2.coor_y[5] = 0;
				striker_3.coor_x[5] = 0;
				striker_3.coor_y[5] = 0;
				ref2_temp = ref2;
				ref3_temp = ref3;	
				flag_reset_2 = 0;	
				flag_reset_3 = 0;
			}
			
		}
//		if(ch != -1) printf("%c", ch);
		switch(ch){
				
				case 'a' :
					striker_2.reset_yaw[0]-=1;
					break;
				case 'd' :
					striker_2.reset_yaw[0]+=1;
					break;
				case 'w' :
					striker_3.reset_yaw[0]+=1;
					break;
				case 's' :
					striker_3.reset_yaw[0]-=1;
					break;
				case 'q' :
					keeper.reset_yaw[0]+=1;
					break;
				case 'z' :
					keeper.reset_yaw[0]-=1;
					break;
				case 'p' :
					referee = 0;
					ref1 = 2;
					ref2 = 0;
					ref3 = 4;
					flag_reset_2 = 1;	
					flag_reset_3 = 1;
					break;
					
				case '2' :
					referee = 0;
					ref1 = 2;
					ref2 = 0;
					ref3 = 2;
					break;
				case '3' :
					referee = 0;
					ref1 = 2;
					ref2 = 0;
					ref3 =1;
					break;

				case '1' :
					referee = 1;
					break;
				//edit : start-stop-reset
				case 'j' : 		//start
					flag_wifi = 1;
					break;
				case 'k' :		//stop
					flag_wifi = 2;
					break;
				case 'l' :		//eset
					flag_wifi = 3;
					break;
		}

        //==========RECEIVE FUNCTION FOR UDP CLIENT===============//


        
//		if (count%2 != 0)// && count <= 14)
		for(int a = 0;a < 10;a++)
		{
			memset(buf, '\0', sizeof(buf));
			recvfrom(s, buf, sizeof(buf), 0, (struct sockaddr *) &si_other, &slen);
			// printf("%s\n", buf);
			Parsing_data2(buf, T, U, V, W, X, Y, Z, YAW, Y_CM, X_CM, VOLT, TIMER);
			
			if (T == 111)		//HADES
			{
				striker_2.coor_x[0] = U;		
				striker_2.coor_y[0] = V;		
				striker_2.dist_ball = W;
				striker_2.angle_ball = X;
				striker_2.y_ball[0] = Z;
				striker_2.x_ball[0] = Y;
				striker_2.yaw = YAW;
				striker_2.x_cm[0] = X_CM;
				striker_2.y_cm[0] = Y_CM;
				striker_2.volt[0] = VOLT;		
				striker_2.timer = TIMER;		
				striker_2.mark = 1;
			}
			if (T == 222)		//ARES
			{
				striker_3.coor_x[0] = U;
				striker_3.coor_y[0] = V;
				striker_3.dist_ball = W;
				striker_3.angle_ball = X;
				striker_3.y_ball[0] = Z;
				striker_3.x_ball[0] = Y;
				striker_3.yaw = YAW;
				striker_3.x_cm[0] = X_CM;
				striker_3.y_cm[0] = Y_CM;
				striker_3.volt[0] = VOLT;
				striker_3.timer = TIMER;
				striker_3.mark = 1;
			}
			if (T == 333)		//KEEPER
			{
				keeper.coor_x[0] = U;
				keeper.coor_y[0] = V;
				keeper.dist_ball = W;
				keeper.angle_ball = X;
				keeper.y_ball[0] = Z;
				keeper.x_ball[0] = Y;
				keeper.yaw = YAW;
				keeper.mark = 1;
			}
			// p	rintf("%d,%d\n", striker_2.timer, striker_3.timer);
			striker_2.yaw_rad = PI*((striker_2.yaw - 90)/180);
			striker_3.yaw_rad = PI*((striker_3.yaw - 90)/180);
			keeper.yaw_rad = PI*(keeper.yaw/180);
			
			striker_2.x_cm[1] = striker_2.x_cm[0];
			striker_2.y_cm[1] = striker_2.y_cm[0];
			striker_3.x_cm[1] = striker_3.x_cm[0];
			striker_3.y_cm[1] = striker_3.y_cm[0];
			
			striker_2.volt[1] = striker_2.volt[0];
			striker_3.volt[1] = striker_3.volt[0];
						
			switch (TEAM)
			{
				
				
				case CYAN: 
				{					
					if (ref1 == 2 && ref2 == 3 && ref3 == 1) { koordinat(170,157,170,314,TENGAH,80); }
					else if(ref1 == 2 && ref2 == 0 && ref3 == 4){ 
						if (mode_marking == 8) koordinat(380,410,310,410,TENGAH,80);
						else if (mode_marking == 7) koordinat(60,360,60,410,TENGAH,80);
						else koordinat(380,410,310,410,TENGAH,80);
					}																																// Welcome
					else if (ref1 == 2 && ref2 == 0 && ref3 == 3) 																																																	// Dropped Ball
					{ 
						if(mode_formasi == 2 || mode_formasi == 3){
							if (mode_marking == 2) { koordinat(195,248,250,137,KIRI,50); dropball_x_lawan[0] = 160; dropball_y_lawan[0] = 400; }														// mode = ATE
							else if (mode_marking == 5) { koordinat(195,311,250,240,TENGAH,80); dropball_x_lawan[0] = 160; dropball_y_lawan[0] = 400; }									// mode = TTE
							else if (mode_marking == 8) { koordinat(195,248,250,343,KANAN,50); dropball_x_lawan[0] = 160; dropball_y_lawan[0] = 400; }										// mode = BTE
							else if (mode_marking == 1) { koordinat(300,195,105,137,TENGAH,80); dropball_x_lawan[0] = 160; dropball_y_lawan[0] = 400; }									// mode = AKI
							else if (mode_marking == 4) { koordinat(300,115,105,240,TENGAH,80); dropball_x_lawan[0] = 160; dropball_y_lawan[0] = 400; }									// mode = TKI
							else if (mode_marking == 7) { koordinat(300,283,105,343,TENGAH,80); dropball_x_lawan[0] = 160; dropball_y_lawan[0] = 400; }									// mode = BKI
							else if (mode_marking == 3) { koordinat(252,248,252,137,KIRI,50); dropball_x_lawan[0] = 160; dropball_y_lawan[0] = 400; }												// mode = AKA
							else if (mode_marking == 6) { koordinat(252,313,252,240,TENGAH,80); dropball_x_lawan[0] = 160; dropball_y_lawan[0] = 400; }									// mode = TKA
							else if (mode_marking == 9) { koordinat(252,248,252,343,KANAN,50); dropball_x_lawan[0] = 160; dropball_y_lawan[0] = 400; }										// mode = BKA
							else { koordinat(195,311,250,240,TENGAH,80); dropball_x_lawan[0] = 160; dropball_y_lawan[0] = 400; }
		
						} else {
						
							if (mode_marking == 2) { koordinat(250,137,195,248,KIRI,50); dropball_x_lawan[0] = 160; dropball_y_lawan[0] = 400; }														// mode = ATE
							else if (mode_marking == 5) { koordinat(250,240,195,311,TENGAH,80); dropball_x_lawan[0] = 160; dropball_y_lawan[0] = 400; }									// mode = TTE
							else if (mode_marking == 8) { koordinat(250,343,195,248,KANAN,50); dropball_x_lawan[0] = 160; dropball_y_lawan[0] = 400; }										// mode = BTE
							else if (mode_marking == 1) { koordinat(105,137,300,195,TENGAH,80); dropball_x_lawan[0] = 160; dropball_y_lawan[0] = 400; }									// mode = AKI
							else if (mode_marking == 4) { koordinat(105,240,300,115,TENGAH,80); dropball_x_lawan[0] = 160; dropball_y_lawan[0] = 400; }									// mode = TKI
							else if (mode_marking == 7) { koordinat(105,343,300,283,TENGAH,80); dropball_x_lawan[0] = 160; dropball_y_lawan[0] = 400; }									// mode = BKI
							else if (mode_marking == 3) { koordinat(252,137,252,248,KIRI,50); dropball_x_lawan[0] = 160; dropball_y_lawan[0] = 400; }												// mode = AKA
							else if (mode_marking == 6) { koordinat(252,240,252,313,TENGAH,80); dropball_x_lawan[0] = 160; dropball_y_lawan[0] = 400; }									// mode = TKA
							else if (mode_marking == 9) { koordinat(252,343,252,248,KANAN,50); dropball_x_lawan[0] = 160; dropball_y_lawan[0] = 400; }										// mode = BKA
							else { koordinat(280,240,195,311,TENGAH,80); dropball_x_lawan[0] = 160; dropball_y_lawan[0] = 400; }
						}
						
					}
					else if (ref1 == 2 && ref2 == 1 && ref3 == 3) 																																																	// Kickoff kita
					{
						if (mode_formasi == 1 || mode_formasi == 2) koordinat(265,195,231,313,TENGAH,80);																												// formasi A & B
						else if (mode_formasi == 3 || mode_formasi == 4) koordinat(295,155,295,215,TENGAH,80);		 																								// formasi C & D
						else koordinat(315,195,231,313,TENGAH,80);		 																																				
					}
					else if (ref1 == 2 && ref2 == 2 && ref3 == 3) 																																																	// Kickoff lawan
					{ 
						if  (mode_marking == 5) { koordinat(232,214,232,265,TENGAH,80); kickoff_x_lawan[0] = 160; kickoff_y_lawan[0] = 250; }													// mode = TTE
						else if (mode_marking == 2) { koordinat(232,133,232,265,TENGAH,80); kickoff_x_lawan[0] = 160; kickoff_y_lawan[0] = 250; }											// mode = ATE
						else if (mode_marking == 8) { koordinat(232,340,232,265,TENGAH,80); kickoff_x_lawan[0] = 160; kickoff_y_lawan[0] = 250; }											// mode = BTE
						else { koordinat(232,214,232,265,TENGAH,80); kickoff_x_lawan[0] = 160; kickoff_y_lawan[0] = 250; }						
					}
					else if (ref1 == 2 && ref2 == 1 && ref3 == 4) 																																																	// Freekick kita
					{
					
								
						if(mode_formasi == 2 || mode_formasi == 3){
							if (mode_marking == 2) koordinat(270,210,310,137,TENGAH,80);																																						// mode = ATE
							else if (mode_marking == 5) koordinat(270,182,310,240,TENGAH,80);																																				// mode = TTE
							else if (mode_marking == 8) koordinat(270,260,310,343,TENGAH,80);																																				// mode = BTE
							else if (mode_marking == 1) koordinat(270,220,110,137,TENGAH,80);																																				// mode = AKI
							else if (mode_marking == 4) koordinat(270,182,110,240,TENGAH,80);																																				// mode = TKI
							else if (mode_marking == 7) koordinat(270,260,110,343,TENGAH,80);																																				// mode = BKI
							else if (mode_marking == 3) koordinat(270,210,510,137,TENGAH,80);																																				// mode = AKA
							else if (mode_marking == 6) koordinat(270,182,510,240,TENGAH,80);																																				// mode = TKA
							else if (mode_marking == 9) koordinat(270,260,510,343,TENGAH,80);																																				// mode = BKA
							else koordinat(270,210,110,137,TENGAH,80);
						} else {
						
							if (mode_marking == 2) koordinat(310,137,270,210,TENGAH,80);																																						// mode = ATE
							else if (mode_marking == 5) koordinat(310,240,270,182,TENGAH,80);																																				// mode = TTE
							else if (mode_marking == 8) koordinat(310,343,270,260,TENGAH,80);																																				// mode = BTE
							else if (mode_marking == 1) koordinat(110,137,270,220,TENGAH,80);																																				// mode = AKI
							else if (mode_marking == 4) koordinat(110,240,270,182,TENGAH,80);																																				// mode = TKI
							else if (mode_marking == 7) koordinat(110,343,270,260,TENGAH,80);																																				// mode = BKI
							else if (mode_marking == 3) koordinat(510,137,270,210,TENGAH,80);																																				// mode = AKA
							else if (mode_marking == 6) koordinat(510,240,270,182,TENGAH,80);																																				// mode = TKA
							else if (mode_marking == 9) koordinat(510,343,270,260,TENGAH,80);																																				// mode = BKA
							else koordinat(110,135,270,210,TENGAH,80);	
							
						}
					}
					else if (ref1 == 2 && ref2 == 2 && ref3 == 4) 																																																	// Freekick lawan
					{
						if (mode_marking == 2) { koordinat(220,190,160,270,KIRI,50); freekick_x_lawan[0] = 160; freekick_y_lawan[0] = 500; }														// mode = ATE
						else if (mode_marking == 5) { koordinat(267,234,232,255,TENGAH,80); freekick_x_lawan[0] = 160; freekick_y_lawan[0] = 500; }										// mode = TTE
						else if (mode_marking == 8) { koordinat(220,274,160,200,KANAN,50); freekick_x_lawan[0] = 160; freekick_y_lawan[0] = 500; }										// mode = BTE
						else if (mode_marking == 1) { koordinat(105,147,270,240,TENGAH,80); freekick_x_lawan[0] = 160; freekick_y_lawan[0] = 500; }										// mode = AKI
						else if (mode_marking == 4) { koordinat(105,235,270,240,TENGAH,80); freekick_x_lawan[0] = 160; freekick_y_lawan[0] = 500; }										// mode = TKI
						else if (mode_marking == 7) { koordinat(105,323,270,240,TENGAH,80); freekick_x_lawan[0] = 160; freekick_y_lawan[0] = 500; }										// mode = BKI
						else if (mode_marking == 3) { koordinat(330,147,182,253,TENGAH,80); freekick_x_lawan[0] = 160; freekick_y_lawan[0] = 500; }										// mode = AKA
						else if (mode_marking == 6) { koordinat(330,235,182,253,TENGAH,80);	freekick_x_lawan[0] = 160; freekick_y_lawan[0] = 500; }									// mode = TKA
						else if (mode_marking == 9) { koordinat(330,323,182,217,TENGAH,80); freekick_x_lawan[0] = 160; freekick_y_lawan[0] = 500; }										// mode = BKA
						else { koordinat(330,147,182,253,TENGAH,80); freekick_x_lawan[0] = 160; freekick_y_lawan[0] = 500; }
					}
					else if (ref1 == 2 && ref2 == 1 && ref3 == 6) koordinat(344,161,230,287,TENGAH,80);																														// Throwin kita
					else if (ref1 == 2 && ref2 == 2 && ref3 == 6) koordinat(344,161,230,287,TENGAH,80);																														// Throwin lawan
					else if (ref1 == 2 && ref2 == 1 && ref3 == 8) 																																																	// Penalti kita	
					{
						if (mode_formasi == 2 || mode_formasi == 3)
						{
							if (mode_marking == 9) { koordinat(164,74,280,235,TENGAH,80); penalti_x_kita[0] = 178; penalti_y_kita[0] = 520; } 															// mode = BKA
							else if (mode_marking == 6) { koordinat(164,74,280,235,TENGAH,80); penalti_x_kita[0] = 160; penalti_y_kita[0] = 520; }													// mode = TKA
							else if (mode_marking == 3) { koordinat(164,74,280,235,TENGAH,80); penalti_x_kita[0] = 142; penalti_y_kita[0] = 520; } 												// mode = AKA
							else { koordinat(164,74,280,235,TENGAH,80); penalti_x_kita[0] = 160; penalti_y_kita[0] = 520; }
						}
						else
						{
							if (mode_marking == 9) { koordinat(280,235,164,396,TENGAH,80); penalti_x_kita[0] = 178; penalti_y_kita[0] = 520; } 														// mode = BKA
							else if (mode_marking == 6) { koordinat(280,235,164,396,TENGAH,80); penalti_x_kita[0] = 160; penalti_y_kita[0] = 520; }												// mode = TKA
							else if (mode_marking == 3) { koordinat(280,235,164,396,TENGAH,80); penalti_x_kita[0] = 142; penalti_y_kita[0] = 520; } 												// mode = AKA
							else { koordinat(280,235,164,396,TENGAH,80); penalti_x_kita[0] = 160; penalti_y_kita[0] = 520; }
						}
					}
					else if (ref1 == 2 && ref2 == 2 && ref3 == 8) 																																																	// Penalti lawan
					{ 
						if (mode_marking == 1) { koordinat(486,64,486,402,KIRI,15); penalty_x_lawan[0] = 160; penalty_y_lawan[0] = 400; }															// mode = AKI
						else if (mode_marking == 4) { koordinat(486,64,486,402,TENGAH,80); penalty_x_lawan[0] = 160; penalty_y_lawan[0] = 400; }											// mode = TKI
						else if (mode_marking == 7) { koordinat(486,64,486,402,KANAN,15); penalty_x_lawan[0] = 160; penalty_y_lawan[0] = 400; }											// mode = BKI
						else { koordinat(486,64,486,402,TENGAH,80); penalty_x_lawan[0] = 160; penalty_y_lawan[0] = 400; }	
					}
					else if (ref1 == 2 && ref2 == 1 && ref3 == 7)									// Corner kita
					{
						if (mode_formasi == 2 || mode_formasi == 3){
						
							if (mode_marking == 3) koordinat(345,241,670,20,TENGAH,80);						// mode = AKA
							else if (mode_marking == 9) koordinat(345,241,670,463,TENGAH,80);					// mode = BKA
							else koordinat(345,241,670,20,TENGAH,80);																			
						
						} else {
						
							if (mode_marking == 3) koordinat(670,20,345,241,TENGAH,80);						// mode = AKA
							else if (mode_marking == 9) koordinat(670,463,345,241,TENGAH,80);					// mode = BKA
							else koordinat(670,20,345,241,TENGAH,80);																				
						
						}
					}
					else if (ref1 == 2 && ref2 == 2 && ref3 == 7) 																																																	// Corner lawan
					{
						if (mode_marking == 1) { koordinat(180,140,285,193,KIRI,40); corner_x_lawan[1] = 0; corner_y_lawan[1] = 40, corner_x_lawan[0] = 0; corner_y_lawan[0] = 0; }							// mode = AKI		
						else if (mode_marking == 7) { koordinat(180,330,285,277,KANAN,40); corner_x_lawan[1] = 320; corner_y_lawan[1] = 0; corner_x_lawan[0] = 320; corner_y_lawan[0] = 0; } 	// mode = BKI
						else { koordinat(180,140,285,193,TENGAH,80); corner_x_lawan[1] = 320; corner_y_lawan[1] = 0; corner_x_lawan[0] = 320; corner_y_lawan[0] = 40; }
					}
					else if (ref1 == 2 && ref2 == 1 && ref3 == 5) 				// Goalkick kita
					{
						if(mode_formasi == 2 || mode_formasi == 3){
							
							if (mode_marking == 1) koordinat(225,335,110,135,TENGAH,80);																																						// mode = AKI
							else if (mode_marking == 4) koordinat(250,182,110,240,TENGAH,80);																																				// mode = TKI
							else if (mode_marking == 7) koordinat(225,135,110,342,TENGAH,80);																																				// mode = BKI
							else koordinat(225,335,110,135,TENGAH,80);
						
						} else {
						
							if (mode_marking == 1) koordinat(110,135,225,335,TENGAH,80);																																						// mode = AKI
							else if (mode_marking == 4) koordinat(110,240,250,182,TENGAH,80);																																				// mode = TKI
							else if (mode_marking == 7) koordinat(110,342,225,135,TENGAH,80);																																				// mode = BKI
							else koordinat(110,135,225,335,TENGAH,80);
						
						}
					}
					else if (ref1 == 2 && ref2 == 2 && ref3 == 5) 																																																	// Goalkick lawan
					{
						if (mode_marking == 3) { koordinat(220,190,160,270,TENGAH,80); goalkick_x_lawan[0] = 300; goalkick_y_lawan[0] = 500; }												// mode = AKA
						else if (mode_marking == 9) { koordinat(220,274,160,200,TENGAH,80); goalkick_x_lawan[0] = 120; goalkick_y_lawan[0] = 500; }									// mode = BKA
						else { koordinat(220,190,160,270,TENGAH,80); goalkick_x_lawan[0] = 300; goalkick_y_lawan[0] = 500; }	
					}
					else if (ref1 == 2 && ref2 == 1 && ref3 == 14) { koordinat(210,234,210,286,TENGAH,80); kickoff_x_lawan[0] = 160; kickoff_y_lawan[0] = 250; }					// Goal Kita
					else if (ref1 == 2 && ref2 == 2 && ref3 == 14) koordinat(315,255,231,313,TENGAH,80);																													// Goal Lawan
					else if (ref1 == 2 && ref2 == 1 && ref3 == 15) koordinat(280,235,195,311,TENGAH,80); 																													// SubGoal Kita
					else if (ref1 == 2 && ref2 == 2 && ref3 == 15) koordinat(280,235,195,311,TENGAH,80); 																													// SubGoal Lawan
					}; break;
				}
}

//		striker_3.coor_x[4] < 696 ? striker_3.coor_x[4]++ : striker_3.coor_x[4] = 0;
//		striker_3.coor_y[4] < 472 ? striker_3.coor_y[4]++ : striker_3.coor_y[4] = 0;

//		striker_2.coor_x[4] = 696;
//		striker_2.coor_y[4] = 472;

		// striker_2.coor_x[4] = (int)striker_2.x_cm[0];
		// striker_2.coor_y[4] = (int)striker_2.y_cm[0];
		// striker_3.coor_x[4] = (int)striker_3.x_cm[0];
		// striker_3.coor_y[4] = (int)striker_3.y_cm[0];

		striker_2.coor_x[4] = (int)striker_2.coor_x[0];
		striker_2.coor_y[4] = (int)striker_2.coor_y[0];
		striker_3.coor_x[4] = (int)striker_3.coor_x[0];
		striker_3.coor_y[4] = (int)striker_3.coor_y[0];
		
		striker_2.reset_yaw[1] = striker_2.reset_yaw[0];
		striker_3.reset_yaw[1] = striker_3.reset_yaw[0];
		keeper.reset_yaw[1] = keeper.reset_yaw[0];
		
		if(striker_2.reset_yaw[1] < 0) striker_2.reset_yaw[1]+=360;
		if(striker_2.reset_yaw[1] > 360) striker_2.reset_yaw[1]-=360;
		
		if(striker_3.reset_yaw[1] < 0) striker_3.reset_yaw[1]+=360;
		if(striker_3.reset_yaw[1] > 360) striker_3.reset_yaw[1]-=360;
		
		if(keeper.reset_yaw[1] < 0) keeper.reset_yaw[1]+=360;
		if(keeper.reset_yaw[1] > 360) keeper.reset_yaw[1]-=360;
		
	// //coba real to px--------------------------------------------------------------------------------------------------------------------//

	// 	striker_2.coor_x[6] = (int)striker_2.coor_x[0];
	// 	striker_2.coor_y[6] = (int)striker_2.coor_y[0];
	// 	striker_3.coor_x[6] = (int)striker_3.coor_x[0];
	// 	striker_3.coor_y[6] = (int)striker_3.coor_y[0];

	// 	//hades
	// 	if(striker_2.coor_x[4] < x_BS_min[1]) 
	// 			striker_2.coor_x[6] = (pengali_A[0] * striker_2.coor_x[6]) + penambah_C[0];

	// 	else if(striker_2.coor_x[4] >= x_BS_min[1] && striker_2.coor_x[1] <= x_BS_max[1]) 
	// 			striker_2.coor_x[6] = (pengali_A[1] * striker_2.coor_x[6]) + penambah_C[1];

	// 	else if(striker_2.coor_x[4] > x_BS_max[1]) 
	// 			striker_2.coor_x[6] = (pengali_A[2] * striker_2.coor_x[6]) + penambah_C[2];

	// 	if(striker_2.coor_y[4] < y_BS_min[1]) 
	// 			striker_2.coor_y[6] = (pengali_B[0] * striker_2.coor_y[6]) + penambah_D[0];

	// 	else if(striker_2.coor_y[4] >= y_BS_min[1] && striker_2.coor_y[1] <= y_BS_max[1]) 
	// 			striker_2.coor_y[6] = (pengali_B[1] * striker_2.coor_y[6]) + penambah_D[1];

	// 	else if(striker_2.coor_y[4] > y_BS_max[1])
	// 			striker_2.coor_y[6] = (pengali_B[2] * striker_2.coor_y[6]) + penambah_D[2];

	// 	//ares
	// 	if(striker_3.coor_x[4] < x_BS_min[1]) 
	// 			striker_3.coor_x[6] = (pengali_A[0] * striker_3.coor_x[6]) + penambah_C[0];

	// 	else if(striker_3.coor_x[4] >= x_BS_min[1] && striker_3.coor_x[1] <= x_BS_max[1]) 
	// 			striker_3.coor_x[6] = (pengali_A[1] * striker_3.coor_x[6]) + penambah_C[1];

	// 	else if(striker_3.coor_x[4] > x_BS_max[1]) 
	// 			striker_3.coor_x[6] = (pengali_A[2] * striker_3.coor_x[6]) + penambah_C[2];


	// 	if(striker_3.coor_y[4] < y_BS_min[1]) 
	// 			striker_3.coor_y[6] = (pengali_B[0] * striker_3.coor_y[6]) + penambah_D[0];

	// 	else if(striker_3.coor_y[4] >= y_BS_min[1] && striker_3.coor_y[1] <= y_BS_max[1]) 
	// 			striker_3.coor_y[6] = (pengali_B[1] * striker_3.coor_y[6]) + penambah_D[1];

	// 	else if(striker_3.coor_y[4] > y_BS_max[1])
	// 			striker_3.coor_y[6] = (pengali_B[2] * striker_3.coor_y[6]) + penambah_D[2];
		
	// 	striker_2.coor_x[4] = (int)striker_2.coor_x[6];
	// 	striker_2.coor_y[4] = (int)striker_2.coor_y[6];
	// 	striker_3.coor_x[4] = (int)striker_3.coor_x[6];
	// 	striker_3.coor_y[4] = (int)striker_3.coor_y[6];

	// //end coba------------------------------------------------------------------------
		
		if ((ref1 == 2 && ref2 == 0 && (ref3 == 1 || ref3 == 2)) || (ref1 == 0 && ref2 == 0 && ref3 == 0))
		{ 
			striker_2.coor_x[2] = 0;
			striker_2.coor_y[2] = 0;
			striker_3.coor_x[2] = 0;
			striker_3.coor_y[2] = 0;
			keeper.coor_x[3] = 0;
			keeper.coor_y[3] = 0;
			flag_reset_2 = 0;
			flag_reset_3 = 0;
			
		}
		else
		{
			keeper.coor_x[3] = x_keeper;
			//====================================================================================//
			if (keeper.coor_x[2] == KANAN) keeper.coor_y[3] = y_keeper - keeper.coor_y[2];
			else if (keeper.coor_x[2] == KIRI) keeper.coor_y[3] = y_keeper + keeper.coor_y[2];
			else keeper.coor_y[3] = y_keeper;
						
		}	
		if (resetodo == true)
		{
			switch (mode_reset) //Posisi reset saat repair
			{
				case 1 : 	{
									striker_2.reset_x[0] = 0;
									striker_2.reset_y[0] = 406;
									striker_3.reset_x[0] = 0;
									striker_3.reset_y[0] = 65;
									keeper.reset_x[0] = 2;
									keeper.reset_y[0] = 2;
				}; break;
				case 2 :	{
									striker_2.reset_x[0] = 0;
									striker_2.reset_y[0] = 406;	
									keeper.reset_x[0] = 2;
									keeper.reset_y[0] = 0;
								}; break;
				case 3 :	{
									striker_3.reset_x[0] = 0;
									striker_3.reset_y[0] = 65;
									keeper.reset_x[0] = 2;
									keeper.reset_y[0] = 0;
								}; break;
				case 4 :	{
									keeper.reset_x[0] = 2;
									keeper.reset_y[0] = 2;
								}; break;
				default : {
									striker_2.reset_x[0] = striker_2.reset_x[0];
									striker_2.reset_y[0] = striker_2.reset_y[0];
									striker_3.reset_x[0] = striker_3.reset_x[0];
									striker_3.reset_y[0] = striker_3.reset_y[0];
									keeper.reset_x[0] = 2;
									keeper.reset_y[0] = 0;
								}; break;
			}
			striker_2.reset_x[1] = striker_2.reset_x[0];
			striker_2.reset_y[1] = striker_2.reset_y[0];
			striker_3.reset_x[1] = striker_3.reset_x[0];
			striker_3.reset_y[1] = striker_3.reset_y[0];

		}
		else 
		{
//			if(TEAM == MAGENTA){
//				striker_3.reset_x[1] = 696;
//				striker_3.reset_y[1] = 472;
//				striker_2.reset_x[1] = 696;
//				striker_2.reset_y[1] = 472;
//			}
//			else {
				striker_3.reset_x[1] = 0;
				striker_3.reset_y[1] = 0;
				striker_2.reset_x[1] = 0;
				striker_2.reset_y[1] = 0;
//				striker_2.coor_x[5] = 0;
//				striker_2.coor_y[5] = 0;
//				striker_3.coor_x[5] = 0;
//				striker_3.coor_y[5] = 0;
//			}
		}

		if (ref1 == 2 && ref2 == 0 && (ref3 == 1 || ref3== 2 || ref3 == 3)) resetodo = true;
		else if (ref1== 2 && ref2 == 1 && ref3 != 0) resetodo = true;
		else if (ref1 == 2 && ref2 == 2 && ref3 != 0) resetodo = true;
		else if (ref1 == 2 && ref2 == 3 && ref3 == 1) resetodo = true;
		else if (ref1 == 0 && ref2 == 0 && ref3 == 0) resetodo = true;
		else resetodo = false;

		striker_3.reset_x[2] = striker_3.reset_x[0];
		striker_3.reset_y[2] = striker_3.reset_y[0];
		striker_2.reset_x[2] = striker_2.reset_x[0];
		striker_2.reset_y[2] = striker_2.reset_y[0];

		if (ref1 == 2 && ref2 == 0 && ref3 == 1)
		{

			striker_2.reset_x[2] = 0;
			striker_2.reset_y[2] = 0;
			striker_3.reset_x[2] = 0;
			striker_3.reset_y[2] = 0;
			striker_2.coor_x[5] = 0;
			striker_2.coor_y[5] = 0;
			striker_3.coor_x[5] = 0;
			striker_3.coor_y[5] = 0;
		}

		
		
		if (count == 8)lapangan.copyTo(result(Rect(13, 6, lapangan.cols, lapangan.rows)));
//		if (count > 0)
//		{
			
								
			if(TEAM == MAGENTA){
				
				
				striker_2.coor_x[2] = 690 - striker_2.coor_x[2];
				striker_2.coor_y[2] = 483 - striker_2.coor_y[2];
				striker_3.coor_x[2] = 690 - striker_3.coor_x[2];
				striker_3.coor_y[2] = 483 - striker_3.coor_y[2];
				
				striker_2.coor_x[4] = 690 - striker_2.coor_x[4];
				striker_2.coor_y[4] = 483 - striker_2.coor_y[4];
				striker_3.coor_x[4] = 690 - striker_3.coor_x[4];
				striker_3.coor_y[4] = 483 - striker_3.coor_y[4];
				
				//=== YAW STRIKER 2 ===//
				striker_2.yaw_x = striker_2.coor_x[1]-(11*cos(striker_2.yaw_rad));
				striker_2.yaw_y = striker_2.coor_y[1]-(11*sin(striker_2.yaw_rad));
				
				//=== YAW STRIKER 3 ===//
				striker_3.yaw_x = striker_3.coor_x[1]-(11*cos(striker_3.yaw_rad));
				striker_3.yaw_y = striker_3.coor_y[1]-(11*sin(striker_3.yaw_rad));
				
				//=== YAW KEEPER ===//
				keeper.yaw_x = keeper.coor_x[1]-(11*cos(keeper.yaw_rad));
				keeper.yaw_y = keeper.coor_y[1]-(11*sin(keeper.yaw_rad));
		
			} else if (TEAM == CYAN){
				striker_2.coor_y[2] = 483 - striker_2.coor_y[2];
				striker_3.coor_y[2] = 483 - striker_3.coor_y[2];
					
				striker_3.coor_y[4] = 483 - striker_3.coor_y[4];
				striker_2.coor_y[4] = 483 - striker_2.coor_y[4];
				
				//=== YAW STRIKER 2 ===//
				striker_2.yaw_x = striker_2.coor_x[1]+(11*cos(striker_2.yaw_rad));
				striker_2.yaw_y = striker_2.coor_y[1]+(11*sin(striker_2.yaw_rad));					
				
				//=== YAW STRIKER 3 ===//
				striker_3.yaw_x = striker_3.coor_x[1]+(11*cos(striker_3.yaw_rad));
				striker_3.yaw_y = striker_3.coor_y[1]+(11*sin(striker_3.yaw_rad));										
				
				//=== YAW KEEPER ===//
				keeper.yaw_x = keeper.coor_x[1]+(11*cos(keeper.yaw_rad));
				keeper.yaw_y = keeper.coor_y[1]+(11*sin(keeper.yaw_rad));			
			}
			
			
			//============================== STRIKER_2 POSISI SEKARANG ==================================//
			//xy_origin
			striker_2.coor_x[4] - 14 < 0 ? striker_2.pos_X = 0 : striker_2.pos_X = striker_2.coor_x[4] - 14;
			striker_2.coor_y[4] - 14 < 0 ? striker_2.pos_Y = 0 : striker_2.pos_Y = striker_2.coor_y[4] - 14;
			//xy_origin_1
			striker_2.coor_x[4] > 676 ? striker_2.pos_X = 662 : striker_2.pos_X = striker_2.pos_X;
			striker_2.coor_y[4] > 469 ? striker_2.pos_Y = 455 : striker_2.pos_Y = striker_2.pos_Y;
			
			striker_2.pos_X == 0 ? striker_2.coor_x[1] = striker_2.coor_x[4] : striker_2.coor_x[1] = 14;
			striker_2.pos_Y == 0 ? striker_2.coor_y[1] = striker_2.coor_y[4] : striker_2.coor_y[1] = 14;
			striker_2.coor_x[4] > 676 ? striker_2.coor_x[1] = striker_2.coor_x[4] - 662 : 0;
			striker_2.coor_y[4] > 469 ? striker_2.coor_y[1] = striker_2.coor_y[4] - 455 : 0;
			//============================================================================================//
			
			
			//============================== STRIKER_3 POSISI SEKARANG ===================================//								
			//xy_origin
			striker_3.coor_x[4] - 14 < 0 ? striker_3.pos_X = 0 : striker_3.pos_X = striker_3.coor_x[4] - 14;
			striker_3.coor_y[4] - 14 < 0 ? striker_3.pos_Y = 0 : striker_3.pos_Y = striker_3.coor_y[4] - 14;
			//xy_origin_1
			striker_3.coor_x[4] > 676 ? striker_3.pos_X = 662 : striker_3.pos_X = striker_3.pos_X;
			striker_3.coor_y[4] > 469 ? striker_3.pos_Y = 455 : striker_3.pos_Y = striker_3.pos_Y;
			
			striker_3.pos_X == 0 ? striker_3.coor_x[1] = striker_3.coor_x[4] : striker_3.coor_x[1] = 14;
			striker_3.pos_Y == 0 ? striker_3.coor_y[1] = striker_3.coor_y[4] : striker_3.coor_y[1] = 14;
			striker_3.coor_x[4] > 676 ? striker_3.coor_x[1] = striker_3.coor_x[4] - 662 : 0;
			striker_3.coor_y[4] > 469 ? striker_3.coor_y[1] = striker_3.coor_y[4] - 455 : 0;
			//============================================================================================//
			
			
			//=================================== STRIKER_2 POSITIONING =======================================//
			if(flag_reset_2 == 1){ 
				striker_2.coor_x[2] = striker_2.coor_x[5];
				striker_2.coor_y[2] = striker_2.coor_y[5];
			}
			
			//xy_origin_POSITIONING
			striker_2.coor_x[2] - 14 < 0 ? striker_2.POS_X = 0 : striker_2.POS_X = striker_2.coor_x[2] - 14;
			striker_2.coor_y[2] - 14 < 0 ? striker_2.POS_Y = 0 : striker_2.POS_Y = striker_2.coor_y[2] - 14;
			//xy_origin_1_POSITIONING
			striker_2.coor_x[2] > 676 ? striker_2.POS_X = 662 : striker_2.POS_X = striker_2.POS_X;
			striker_2.coor_y[2] > 469 ? striker_2.POS_Y = 455 : striker_2.POS_Y = striker_2.POS_Y;
			
			striker_2.POS_X == 0 ? striker_2.coor_x[3] = striker_2.coor_x[2] : striker_2.coor_x[3] = 14;
			striker_2.POS_Y == 0 ? striker_2.coor_y[3] = striker_2.coor_y[2] : striker_2.coor_y[3] = 14;
			striker_2.coor_x[2] > 676 ? striker_2.coor_x[3] = striker_2.coor_x[2] - 662 : 0;
			striker_2.coor_y[2] > 469 ? striker_2.coor_y[3] = striker_2.coor_y[2] - 455 : 0;
			//=================================================================================================//
			
			
			//=================================== STRIKER_3 POSITIONING =======================================//
			if(flag_reset_3 == 1){ 
				striker_3.coor_x[2] = striker_3.coor_x[5];
				striker_3.coor_y[2] = striker_3.coor_y[5];
			}
			
			//xy_origin_POSITIONING
			striker_3.coor_x[2] - 14 < 0 ? striker_3.POS_X = 0 : striker_3.POS_X = striker_3.coor_x[2] - 14;
			striker_3.coor_y[2] - 14 < 0 ? striker_3.POS_Y = 0 : striker_3.POS_Y = striker_3.coor_y[2] - 14;
			//xy_origin_1_POSITIONING
			striker_3.coor_x[2] > 676 ? striker_3.POS_X = 662 : striker_3.POS_X = striker_3.POS_X;
			striker_3.coor_y[2] > 469 ? striker_3.POS_Y = 455 : striker_3.POS_Y = striker_3.POS_Y;
			
			striker_3.POS_X == 0 ? striker_3.coor_x[3] = striker_3.coor_x[2] : striker_3.coor_x[3] = 14;
			striker_3.POS_Y == 0 ? striker_3.coor_y[3] = striker_3.coor_y[2] : striker_3.coor_y[3] = 14;
			striker_3.coor_x[2] > 676 ? striker_3.coor_x[3] = striker_3.coor_x[2] - 662 : 0;
			striker_3.coor_y[2] > 469 ? striker_3.coor_y[3] = striker_3.coor_y[2] - 455 : 0;
			//=================================================================================================//
			
			
			
			//======================================= STRIKER_2 RESET =======================================//
			//xy_origin_RESET
			striker_2.reset_x[1] - 14 < 0 ? striker_2.pos_res_x = 0 : striker_2.pos_res_x = striker_2.reset_x[1] - 14;
			striker_2.reset_y[1] - 14 < 0 ? striker_2.pos_res_y = 0 : striker_2.pos_res_y = striker_2.reset_y[1] - 14;
			//xy_origin_1_RESET
			striker_2.reset_x[1] > 676 ? striker_2.pos_res_x = 662 : striker_2.pos_res_x = striker_2.pos_res_x;
			striker_2.reset_y[1] > 469 ? striker_2.pos_res_y = 455 : striker_2.pos_res_y = striker_2.pos_res_y;
			
			striker_2.pos_res_x == 0 ? striker_2.reset_x[2] = striker_2.reset_x[1] : striker_2.reset_x[2] = 14;
			striker_2.pos_res_y == 0 ? striker_2.reset_y[2] = striker_2.reset_y[1] : striker_2.reset_y[2] = 14;
			striker_2.reset_x[1] > 676 ? striker_2.reset_x[2] = striker_2.reset_x[1] - 662 : 0;
			striker_2.reset_y[1] > 469 ? striker_2.reset_y[2] = striker_2.reset_y[1] - 455 : 0;
			
			striker_2.reset_y[2] = (striker_2.reset_x[1] - penambah_C)/pengali_A;
			striker_2.reset_x[2] = (striker_2.reset_y[1] - penambah_D)/pengali_B;
			//=================================================================================================//
			
			
			//======================================= STRIKER_3 RESET =========================================//
			//xy_origin_RESET
			striker_3.reset_x[1] - 14 < 0 ? striker_3.pos_res_x = 0 : striker_3.pos_res_x = striker_3.reset_x[1] - 14;
			striker_3.reset_y[1] - 14 < 0 ? striker_3.pos_res_y = 0 : striker_3.pos_res_y = striker_3.reset_y[1] - 14;
			//xy_origin_1_RESET
			striker_3.reset_x[1] > 676 ? striker_3.pos_res_x = 662 : striker_3.pos_res_x = striker_3.pos_res_x;
			striker_3.reset_y[1] > 469 ? striker_3.pos_res_y = 455 : striker_3.pos_res_y = striker_3.pos_res_y;
			
			striker_3.pos_res_x == 0 ? striker_3.reset_x[2] = striker_3.reset_x[1] : striker_3.reset_x[2] = 20;
			striker_3.pos_res_y == 0 ? striker_3.reset_y[2] = striker_3.reset_y[1] : striker_3.reset_y[2] = 20;
			striker_3.reset_x[1] > 676 ? striker_3.reset_x[2] = striker_3.reset_x[1] - 662 : 0;
			striker_3.reset_y[1] > 469 ? striker_3.reset_y[2] = striker_3.reset_y[1] - 455 : 0;
			//==================================================================================================//
			
//			if(TEAM == MAGENTA){
//				striker_2.reset_x[1] = 696 - striker_2.reset_x[1];
//				striker_2.reset_y[1] = 472 - striker_2.reset_y[1];
//				striker_3.reset_x[1] = 696 - striker_3.reset_x[1];				
//				striker_3.reset_y[1] = 472 - striker_3.reset_y[1];
////				keeper.reset_x[1] = 696 - keeper.reset_x[1];
////				keeper.reset_y[1] = 472 - keeper.reset_y[1];			
//			}
			Mat image_temp1_S2_RESET = lapangan(Rect(striker_2.pos_res_x, striker_2.pos_res_y, 28, 28)).clone();
			Mat image_temp1_S3_RESET = lapangan(Rect(striker_3.pos_res_x, striker_3.pos_res_y, 28, 28)).clone();
			
			Mat image_temp1_S2_POS = lapangan(Rect(striker_2.POS_X, striker_2.POS_Y, 28, 28)).clone();
			Mat image_temp1_S3_POS = lapangan(Rect(striker_3.POS_X, striker_3.POS_Y, 28, 28)).clone();
						
			Mat image_temp1_S2 = lapangan(Rect(striker_2.pos_X, striker_2.pos_Y, 28, 28)).clone();
			Mat image_temp1_S3 = lapangan(Rect(striker_3.pos_X, striker_3.pos_Y, 28, 28)).clone();
			
			Mat image_temp2 = symbol(Rect(0, 0, symbol.cols, symbol.rows)).clone();
			Mat image_temp3 = lambang(Rect(0, 0, lambang.cols, lambang.rows)).clone();
			Mat image_temp4 = rob(Rect(0, 0, rob.cols, rob.rows)).clone();
			Mat image_temp5 = formation(Rect(0, 0, formation.cols, formation.rows)).clone();
			namedWindow(window_name, CV_WINDOW_AUTOSIZE);
			setMouseCallback(window_name, mouseHandler, &p);

			if(TEAM == MAGENTA){
			
				putText(image_temp4, format("%d", (int)striker_2.dist_ball), Point(5+54,40+37), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1); 
				putText(image_temp4, format("%d", (int)striker_3.dist_ball), Point(5+214,40+37), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);
				putText(image_temp4, format("%d", (int)keeper.dist_ball), Point(5+374,40+37), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);
	
				putText(image_temp4, format("%d,%d", 483 - (int)striker_2.coor_y[2], 690 - (int)striker_2.coor_x[2]), Point(5+92,40+65), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1); //POSITIONING
				putText(image_temp4, format("%d,%d", 483 - (int)striker_3.coor_y[2], 690 - (int)striker_3.coor_x[2]), Point(5+252,40+65), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1); //POSITIONING
				putText(image_temp4, format("%d,%d", (int)keeper.coor_y[2], (int)keeper.coor_x[2]), Point(5+412,40+65), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1); //POSITIONING
	
				putText(image_temp4, format("%d,%d", 483 - (int)striker_2.coor_y[4], 690 - (int)striker_2.coor_x[4]), Point(5+80,40+93), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);//POSISI SAAT INI
				putText(image_temp4, format("%d,%d", 483 - (int)striker_3.coor_y[4], 690 - (int)striker_3.coor_x[4]), Point(5+240,40+93), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);//POSISI SAAT INI
				putText(image_temp4, format("%d,%d", (int)keeper.coor_y[1], (int)keeper.coor_x[1]), Point(5+400,40+93), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);//POSISI SAAT INI
	
				putText(image_temp4, format("%d,%d", 483 - striker_2.reset_y[1], 690 - striker_2.reset_x[1]), Point(5+55,40+121), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);//RESET
				putText(image_temp4, format("%d,%d", 483 - striker_3.reset_y[1], 690 - striker_3.reset_x[1]), Point(5+215,40+121), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);//RESET
				putText(image_temp4, format("%d,%d", keeper.reset_x[1], keeper.reset_y[1]), Point(5+375,40+121), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);//RESET
			
			} else if (TEAM == CYAN){
			
				putText(image_temp4, format("%d", (int)striker_2.dist_ball), Point(5+54,40+37), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1); 
				putText(image_temp4, format("%d", (int)striker_3.dist_ball), Point(5+214,40+37), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);
				putText(image_temp4, format("%d", (int)keeper.dist_ball), Point(5+374,40+37), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);
	
				putText(image_temp4, format("%d,%d", 483 - (int)striker_2.coor_y[2], (int)striker_2.coor_x[2]), Point(5+92,40+65), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1); //POSITIONING
				putText(image_temp4, format("%d,%d", 483 - (int)striker_3.coor_y[2], (int)striker_3.coor_x[2]), Point(5+252,40+65), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1); //POSITIONING
				putText(image_temp4, format("%d,%d", (int)keeper.coor_y[2], (int)keeper.coor_x[2]), Point(5+412,40+65), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1); //POSITIONING
	
				putText(image_temp4, format("%d,%d", 483 - (int)striker_2.coor_y[4], (int)striker_2.coor_x[4]), Point(5+80,40+93), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);//POSISI SAAT INI
				putText(image_temp4, format("%d,%d", 483 - (int)striker_3.coor_y[4], (int)striker_3.coor_x[4]), Point(5+240,40+93), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);//POSISI SAAT INI
				putText(image_temp4, format("%d,%d", (int)keeper.coor_y[1], (int)keeper.coor_x[1]), Point(5+400,40+93), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);//POSISI SAAT INI
			
				putText(image_temp4, format("%d,%d", 483 - striker_2.reset_y[1], striker_2.reset_x[1]), Point(5+55,40+121), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);//RESET
				putText(image_temp4, format("%d,%d", 483 - striker_3.reset_y[1], striker_3.reset_x[1]), Point(5+215,40+121), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);//RESET
				putText(image_temp4, format("%d,%d", keeper.reset_x[1], keeper.reset_y[1]), Point(5+375,40+121), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);//RESET
			}
			putText(image_temp4, format("%d", striker_2.angle_ball), Point(5+80,40+149), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);//SUDUT BOLA
			putText(image_temp4, format("%d", striker_3.angle_ball), Point(5+240,40+149), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);//SUDUT BOLA
			putText(image_temp4, format("%d", keeper.angle_ball), Point(5+400,40+149), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);//SUDUT BOLA
			
			putText(image_temp4, format("%d", (int)striker_2.yaw), Point(5+55,40+177), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);//YAW
			putText(image_temp4, format("%d", (int)striker_3.yaw), Point(5+215,40+177), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);//YAW
			putText(image_temp4, format("%d", (int)keeper.yaw), Point(5+375,40+177), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);    //YAW			

			putText(image_temp4, format("%d", striker_2.reset_yaw[1]), Point(5+90,40+205), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);//RESET_YAW
			putText(image_temp4, format("%d", striker_3.reset_yaw[1]), Point(5+250,40+205), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);//RESET_YAW
			putText(image_temp4, format("%d", keeper.reset_yaw[1]), Point(5+410,40+205), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);//RESET_YAW			

			// putText(image_temp4, format("%d,%d", striker_2.x_ball[0], striker_2.y_ball[0]), Point(5+67,40+231), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);//JARAK BOLA
			// putText(image_temp4, format("%d,%d", striker_3.x_ball[0], striker_3.y_ball[0]), Point(5+227,40+231), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);//JARAK BOLA
			// putText(image_temp4, format("%d,%d", keeper.x_ball[0], keeper.y_ball[0]), Point(5+387,40+231), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);    //JARAK BOLA

			putText(image_temp4, format("%d,%d,%d", dummy_pos1, dummy_pos2, dummy_pos3), Point(5+67,40+231), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);//posisi dummy1
			putText(image_temp4, format("%d,%d,%d", dummy_pos1, dummy_pos2, dummy_pos3), Point(5+227,40+231), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);//posisi dummy2
			putText(image_temp4, format("%d,%d", keeper.x_ball[0], keeper.y_ball[0]), Point(5+387,40+231), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);    //JARAK BOLA

	  		if (striker_2.mark == 1) putText(image_temp4, format("CONNECTED"), Point(5+59,40+259), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);
			else putText(image_temp4, format("ERROR"), Point(5+59,40+259), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);
			if (striker_3.mark == 1) putText(image_temp4, format("CONNECTED"), Point(5+219,40+259), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);
			else putText(image_temp4, format("ERROR"), Point(5+219,40+259), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);
			if (keeper.mark == 1) putText(image_temp4, format("CONNECTED"), Point(5+379,40+259), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);    
			else putText(image_temp4, format("ERROR"), Point(5+379,40+259), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);

			putText(image_temp4, format("%d", striker_2.volt[1]), Point(5+67,40+287), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);//TEGANGAN SOLENOID
			putText(image_temp4, format("%d", striker_3.volt[1]), Point(5+227,40+287), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);//TEGANGAN SOLENOID
			putText(image_temp4, format("%d", keeper.volt[1]), Point(5+387,40+287), FONT_HERSHEY_PLAIN, 0.9, CV_RGB(255,255,255), 1);    //TEGANGAN SOLENOID

//			ellipse(image_temp1, Point(striker_2.y_ball[1],striker_2.x_ball[1]), Size(7,7), 0,0,360, Scalar(0,0,255), CV_FILLED); //BALL
//			ellipse(image_temp1, Point(striker_3.y_ball[1],striker_3.x_ball[1]), Size(7,7), 0,0,360, Scalar(0,0,255), CV_FILLED);	//BALL

			ellipse(image_temp1_S2_RESET, Point(striker_2.reset_x[2],striker_2.reset_y[2]), Size(13,13), 0,0,360, CV_RGB(100,255,0), CV_FILLED); //RESET
			putText(image_temp1_S2_RESET, format("1"), Point((striker_2.reset_x[2]-6), (striker_2.reset_y[2]+6)), FONT_HERSHEY_SCRIPT_SIMPLEX, 0.6, Scalar(0,0,0), 1);		 
			ellipse(image_temp1_S3_RESET, Point(striker_3.reset_x[2],striker_3.reset_y[2]), Size(13,13), 0,0,360, CV_RGB(100,255,0), CV_FILLED); //RESET
			putText(image_temp1_S3_RESET, format("2"), Point((striker_3.reset_x[2]-6),(striker_3.reset_y[2]+6)), FONT_HERSHEY_SCRIPT_SIMPLEX, 0.6, Scalar(0,0,0), 1);

			ellipse(image_temp1_S3, Point((int)striker_3.coor_x[1], (int)striker_3.coor_y[1]), Size(13,13), 0,0,360, Scalar(255,0,0), CV_FILLED); //POSISI SAAT INI
			putText(image_temp1_S3, format("2"), Point((int)(striker_3.coor_x[1]-6),(int)(striker_3.coor_y[1]+6)), FONT_HERSHEY_SCRIPT_SIMPLEX, 0.6, Scalar(255,255,255), 1);
			ellipse(image_temp1_S2, Point(striker_2.coor_x[1], striker_2.coor_y[1]), Size(13,13), 0,0,360, Scalar(255,0,0), CV_FILLED); //POSISI SAAT INI
			putText(image_temp1_S2, format("1"), Point(striker_2.coor_x[1]-6, striker_2.coor_y[1]+6), FONT_HERSHEY_SCRIPT_SIMPLEX, 0.6, Scalar(255,255,255), 1);		 			
//			ellipse(image_temp1, Point((int)keeper.coor_x[4], (int)keeper.coor_y[4]), Size(13,13), 0,0,360, Scalar(255,0,0), CV_FILLED); //POSISI SAAT INI
//			putText(image_temp1, format("1"), Point((int)(keeper.coor_x[4]-6), (int)(keeper.coor_y[4]+6)), FONT_HERSHEY_SCRIPT_SIMPLEX, 0.6, Scalar(255,255,255), 1);
//			
			
			ellipse(image_temp1_S2, Point((int)striker_2.yaw_x, (int)striker_2.yaw_y), Size(4,4), 0,0,360, Scalar(120,0,255), CV_FILLED); //YAW
			ellipse(image_temp1_S3, Point((int)striker_3.yaw_x, (int)striker_3.yaw_y), Size(4,4), 0,0,360, Scalar(120,0,255), CV_FILLED); //YAW
//			ellipse(image_temp1, Point((int)keeper.yaw_x, (int)keeper.yaw_y), Size(4,4), 0,0,360, Scalar(120,0,255), CV_FILLED); //YAW
			
			ellipse(image_temp1_S3_POS, Point((int)striker_3.coor_x[3], (int)striker_3.coor_y[3]), Size(13,13), 0,0,360, Scalar(0,0,0), CV_FILLED); //POSISI TUJUAN
			putText(image_temp1_S3_POS, format("2"), Point((int)(striker_3.coor_x[3]-6), (int)(striker_3.coor_y[3]+6)), FONT_HERSHEY_SCRIPT_SIMPLEX, 0.6, Scalar(255,255,255), 1);		 						
			ellipse(image_temp1_S2_POS, Point((int)striker_2.coor_x[3], (int)striker_2.coor_y[3]), Size(13,13), 0,0,360, Scalar(0,0,0), CV_FILLED); //POSISI TUJUAN
			putText(image_temp1_S2_POS, format("1"), Point((int)(striker_2.coor_x[3]-6), (int)(striker_2.coor_y[3]+6)), FONT_HERSHEY_SCRIPT_SIMPLEX, 0.6, Scalar(255,255,255), 1);		 


			if (ref1 == 2 && ref2 == 0 && ref3 == 1) {refbox_cmd = "START"; print_txt(image_temp4, refbox_cmd, ref2); }
			else if (ref1 == 2 && ref2 == 0 && ref3 == 2) { refbox_cmd = "STOP"; print_txt(image_temp4, refbox_cmd, ref2); }
			else if (ref1 == 2 && ref2 == 0 && ref3 == 3) { refbox_cmd = "DROPBALL"; print_txt(image_temp4, refbox_cmd, ref2); }
			else if (ref1 == 2 && ref2 == 0 && ref3 == 4) { refbox_cmd = "PARKING"; print_txt(image_temp4, refbox_cmd, ref2); }
			else if (ref1 == 2 && ref2 == 0 && ref3 == 5) { refbox_cmd = "1ST HALF"; print_txt(image_temp4, refbox_cmd, ref2); }
			else if (ref1 == 2 && ref2 == 0 && ref3 == 6) { refbox_cmd = "2ND HALF"; print_txt(image_temp4, refbox_cmd, ref2); }
			else if (ref1 == 2 && ref2 == 0 && ref3 == 7) { refbox_cmd = "1ST OVER"; print_txt(image_temp4, refbox_cmd, ref2); }
			else if (ref1 == 2 && ref2 == 0 && ref3 == 8) { refbox_cmd = "2ND OVER"; print_txt(image_temp4, refbox_cmd, ref2); }
			else if (ref1 == 2 && ref2 == 0 && ref3 == 9) { refbox_cmd = "END GAME"; print_txt(image_temp4, refbox_cmd, ref2); }
			else if (ref1 == 2 && ref2 == 0 && ref3 == 10) { refbox_cmd = "GAMEOVER"; print_txt(image_temp4, refbox_cmd, ref2); }
			else if (ref1 == 2 && ref2 == 0 && ref3 == 11) { refbox_cmd = "HALFTIME"; print_txt(image_temp4, refbox_cmd, ref2); }
			else if (ref1 == 2 && ref2 == 1 && ref3 == 3) { refbox_cmd = "KICKOFF"; print_txt(image_temp4, refbox_cmd, ref2); }
			else if (ref1 == 2 && ref2 == 1 && ref3 == 4) { refbox_cmd = "FREEKICK"; print_txt(image_temp4, refbox_cmd, ref2); }
			else if (ref1 == 2 && ref2 == 1 && ref3 == 5) { refbox_cmd = "GOALKICK"; print_txt(image_temp4, refbox_cmd, ref2); }
			else if (ref1 == 2 && ref2 == 1 && ref3 == 6) { refbox_cmd = "THROWIN"; print_txt(image_temp4, refbox_cmd, ref2); }
			else if (ref1 == 2 && ref2 == 1 && ref3 == 7) { refbox_cmd = "CORNER"; print_txt(image_temp4, refbox_cmd, ref2); }
			else if (ref1 == 2 && ref2 == 1 && ref3 == 8) { refbox_cmd = "PENALTY"; print_txt(image_temp4, refbox_cmd, ref2); }
			else if (ref1 == 2 && ref2 == 1 && ref3 == 9) { refbox_cmd = "REPAIR"; print_txt(image_temp4, refbox_cmd, ref2); }
			else if (ref1 == 2 && ref2 == 1 && ref3 == 10) { refbox_cmd = "REPAIR IN"; print_txt(image_temp4, refbox_cmd, ref2); }
			else if (ref1 == 2 && ref2 == 1 && ref3 == 11) { refbox_cmd = "YELLOW CARD"; print_txt(image_temp4, refbox_cmd, ref2); }
			else if (ref1 == 2 && ref2 == 1 && ref3 == 12) { refbox_cmd = "2 YELLOW CARD"; print_txt(image_temp4, refbox_cmd, ref2); }
			else if (ref1 == 2 && ref2 == 1 && ref3 == 13) { refbox_cmd = "RED CARD"; print_txt(image_temp4, refbox_cmd, ref2); }
			else if (ref1 == 2 && ref2 == 1 && ref3 == 14) { refbox_cmd = "GOAL"; print_txt(image_temp4, refbox_cmd, ref2); }
			else if (ref1 == 2 && ref2 == 1 && ref3 == 15) { refbox_cmd = "SUBGOAL"; print_txt(image_temp4, refbox_cmd, ref2); }
			else if (ref1 == 2 && ref2 == 2 && ref3 == 3) { refbox_cmd = "KICKOFF"; print_txt(image_temp4, refbox_cmd, ref2); }
			else if (ref1 == 2 && ref2 == 2 && ref3 == 4) { refbox_cmd = "FREEKICK"; print_txt(image_temp4, refbox_cmd, ref2); }
			else if (ref1 == 2 && ref2 == 2 && ref3 == 5) { refbox_cmd = "GOALKICK"; print_txt(image_temp4, refbox_cmd, ref2); }
			else if (ref1 == 2 && ref2 == 2 && ref3 == 6) { refbox_cmd = "THROWIN"; print_txt(image_temp4, refbox_cmd, ref2); }
			else if (ref1 == 2 && ref2 == 2 && ref3 == 7) { refbox_cmd = "CORNER"; print_txt(image_temp4, refbox_cmd, ref2); }
			else if (ref1 == 2 && ref2 == 2 && ref3 == 8) { refbox_cmd = "PENALTY"; print_txt(image_temp4, refbox_cmd, ref2); }
			else if (ref1 == 2 && ref2 == 2 && ref3 == 9) { refbox_cmd = "REPAIR"; print_txt(image_temp4, refbox_cmd, ref2); }
			else if (ref1 == 2 && ref2 == 2 && ref3 == 10) { refbox_cmd = "REPAIR IN"; print_txt(image_temp4, refbox_cmd, ref2); }
			else if (ref1 == 2 && ref2 == 2 && ref3 == 11) { refbox_cmd = "YELLOW CARD"; print_txt(image_temp4, refbox_cmd, ref2); }
			else if (ref1 == 2 && ref2 == 2 && ref3 == 12) { refbox_cmd = "2 YELLOW CARD"; print_txt(image_temp4, refbox_cmd, ref2); }
			else if (ref1 == 2 && ref2 == 2 && ref3 == 13) { refbox_cmd = "RED CARD"; print_txt(image_temp4, refbox_cmd, ref2); }
			else if (ref1 == 2 && ref2 == 2 && ref3 == 14) { refbox_cmd = "GOAL"; print_txt(image_temp4, refbox_cmd, ref2); }
			else if (ref1 == 2 && ref2 == 2 && ref3 == 15) { refbox_cmd = "SUBGOAL"; print_txt(image_temp4, refbox_cmd, ref2); }
			else if (ref1 == 2 && ref2 == 3 && ref3 == 1) { refbox_cmd = "WELCOME"; print_txt(image_temp4, refbox_cmd, ref2); }
			else if (ref1 == 2 && ref2 == 3 && ref3 == 2) { refbox_cmd = "START 1ST"; print_txt(image_temp4, refbox_cmd, ref2); }
			else if (ref1 == 2 && ref2 == 3 && ref3 == 3) { refbox_cmd = "START 2ND"; print_txt(image_temp4, refbox_cmd, ref2); }
			else if (ref1 == 2 && ref2 == 3 && ref3 == 4) { refbox_cmd = "world state"; print_txt(image_temp4, refbox_cmd, ref2); }
			else if (ref1 == 2 && ref2 == 3 && ref3 == 5) { refbox_cmd = "RESET"; print_txt(image_temp4, refbox_cmd, ref2); }
			else if (ref1 == 2 && ref2 == 3 && ref3 == 6) { refbox_cmd = "TEST ON"; print_txt(image_temp4, refbox_cmd, ref2); }
			else if (ref1 == 2 && ref2 == 3 && ref3 == 7) { refbox_cmd = "TEST OFF"; print_txt(image_temp4, refbox_cmd, ref2); }
			else if (flag_wifi == 1) { refbox_cmd = "start"; print_txt(image_temp4, refbox_cmd, ref2); }
			else if (flag_wifi == 2) { refbox_cmd = "stop"; print_txt(image_temp4, refbox_cmd, ref2); }
			else if (flag_wifi == 3) { refbox_cmd = "restart"; print_txt(image_temp4, refbox_cmd, ref2); }

			if (pressbut == true)
			{
				button_x[1] = button_x[0];
				button_y[1] = button_y[0];
				// if (button_x[1] >= 725 && button_x[1] <= 795 && button_y[1] >= 5 && button_y[1] <= 65) { mode = "aki"; mode_marking = 1; print_mode(rob, mode); }
				// else if (button_x[1] >= 725 && button_x[1] <= 795 && button_y[1] >= 70 && button_y[1] <= 130) { mode = "tki"; mode_marking = 4; print_mode(rob, mode); }
				// else if (button_x[1] >= 725 && button_x[1] <= 795 && button_y[1] >= 135 && button_y[1] <= 195) { mode = "bki"; mode_marking = 7; print_mode(rob, mode); }
				// else if (button_x[1] >= 805 && button_x[1] <= 875 && button_y[1] >= 5 && button_y[1] <= 65) { mode = "ate"; mode_marking = 2; print_mode(rob, mode); }
				// else if (button_x[1] >= 805 && button_x[1] <= 875 && button_y[1] >= 70 && button_y[1] <= 130) { mode = "tte"; mode_marking = 5; print_mode(rob, mode); }
				// else if (button_x[1] >= 805 && button_x[1] <= 875 && button_y[1] >= 135 && button_y[1] <= 195) { mode = "bte"; mode_marking = 8; print_mode(rob, mode); }
				// else if (button_x[1] >= 885 && button_x[1] <= 955 && button_y[1] >= 5 && button_y[1] <= 65) { mode = "aka"; mode_marking = 3; print_mode(rob, mode); }
				// else if (button_x[1] >= 885 && button_x[1] <= 955 && button_y[1] >= 70 && button_y[1] <= 130) { mode = "tka"; mode_marking = 6; print_mode(rob, mode); }
				// else if (button_x[1] >= 885 && button_x[1] <= 955 && button_y[1] >= 135 && button_y[1] <= 195) { mode = "bka"; mode_marking = 9; print_mode(rob, mode); }
			
				//--------------- edit button untuk posisi dummy

				if (button_x[1] >= 725 && button_x[1] <= 795 && button_y[1] >= 5 && button_y[1] <= 65) { mode = "3"; mode_marking = 1; print_mode(rob, mode); dummy_pos1=3;}
				else if (button_x[1] >= 725 && button_x[1] <= 795 && button_y[1] >= 70 && button_y[1] <= 130) { mode = "2"; mode_marking = 4; print_mode(rob, mode); dummy_pos1=2;}
				else if (button_x[1] >= 725 && button_x[1] <= 795 && button_y[1] >= 135 && button_y[1] <= 195) { mode = "1"; mode_marking = 7; print_mode(rob, mode); dummy_pos1=1;}
				else if (button_x[1] >= 805 && button_x[1] <= 875 && button_y[1] >= 5 && button_y[1] <= 65) { mode = "7"; mode_marking = 2; print_mode(rob, mode); dummy_pos2=7;}
				else if (button_x[1] >= 805 && button_x[1] <= 875 && button_y[1] >= 70 && button_y[1] <= 130) { mode = "8"; mode_marking = 5; print_mode(rob, mode); dummy_pos2=8;}
				else if (button_x[1] >= 805 && button_x[1] <= 875 && button_y[1] >= 135 && button_y[1] <= 195) { mode = "rst"; mode_marking = 8; print_mode(rob, mode); dummy_pos1=0; dummy_pos2=0,dummy_pos3=0;} //reset posisi dummy
				else if (button_x[1] >= 885 && button_x[1] <= 955 && button_y[1] >= 5 && button_y[1] <= 65) { mode = "6"; mode_marking = 3; print_mode(rob, mode); dummy_pos3=6;}
				else if (button_x[1] >= 885 && button_x[1] <= 955 && button_y[1] >= 70 && button_y[1] <= 130) { mode = "5"; mode_marking = 6; print_mode(rob, mode); dummy_pos3=5;}
				else if (button_x[1] >= 885 && button_x[1] <= 955 && button_y[1] >= 135 && button_y[1] <= 195) { mode = "4"; mode_marking = 9; print_mode(rob, mode); dummy_pos3=4;}
			

				else if (button_x[1] >= 280 && button_x[1] <= 350 && button_y[1] >= 570 && button_y[1] <= 615) { mode = "All"; mode_reset = 1; print_robot(rob, mode, mode_reset); }
				else if (button_x[1] >= 380 && button_x[1] <= 450 && button_y[1] >= 570 && button_y[1] <= 615) { mode = "S2"; mode_reset = 2; print_robot(rob, mode, mode_reset); }
				else if (button_x[1] >= 480 && button_x[1] <= 550 && button_y[1] >= 570 && button_y[1] <= 615) { mode = "S3"; mode_reset = 3; print_robot(rob, mode, mode_reset); }
				else if (button_x[1] >= 580 && button_x[1] <= 650 && button_y[1] >= 570 && button_y[1] <= 615) { mode = "GK"; mode_reset = 4; print_robot(rob, mode, mode_reset); }
				else if (((button_x[1] >= 241 && button_x[1] <= 279) || (button_x[1] >= 651 && button_x[1] <= 720) || (button_x[1] >= 351 && button_x[1] <= 379) || (button_x[1] >= 451 && button_x[1] <= 479) || (button_x[1] >= 551 && button_x[1] <= 579)) && (button_y[1] >= 540 && button_y[1] <= 600)) { mode_reset = 0; print_robot(rob, "All", mode_reset); }

				else if (button_x[1] >= 280 && button_x[1] <= 340 && button_y[1] >= 505 && button_y[1] <= 550) { mode = "1"; mode_formasi = 1; print_formasi(formation, mode, mode_formasi); dummy_pos4=1; }
				else if (button_x[1] >= 370 && button_x[1] <= 430 && button_y[1] >= 505 && button_y[1] <= 550) { mode = "2"; mode_formasi = 2; print_formasi(formation, mode, mode_formasi); dummy_pos4=2; }
				else if (button_x[1] >= 460 && button_x[1] <= 520 && button_y[1] >= 505 && button_y[1] <= 550) { mode = "3"; mode_formasi = 3; print_formasi(formation, mode, mode_formasi); dummy_pos4=3; }
				else if (button_x[1] >= 550 && button_x[1] <= 610 && button_y[1] >= 505 && button_y[1] <= 550) { mode = "0"; mode_formasi = 4; print_formasi(formation, mode, mode_formasi); dummy_pos4=0; }
				else 
				{ 
					mode = mode;
					mode_marking = 0; 
					mode_formasi = 0; print_formasi(formation, "E", mode_formasi);
				}
			}

			if(TEAM == MAGENTA){
				
				striker_2.reset_x[1] = 690 - striker_2.reset_x[1];
				striker_2.reset_y[1] = 483 - striker_2.reset_y[1];
				striker_3.reset_x[1] = 690 - striker_3.reset_x[1];
				striker_3.reset_y[1] = 483 - striker_3.reset_y[1];
				
				striker_2.coor_x[2] = 690 - striker_2.coor_x[2];
				striker_2.coor_y[2] = 483 - striker_2.coor_y[2];
				striker_3.coor_x[2] = 690 - striker_3.coor_x[2];
				striker_3.coor_y[2] = 483- striker_3.coor_y[2];
				
				striker_2.coor_x[4] = 690 - striker_2.coor_x[4];
				striker_2.coor_y[4] = 483 - striker_2.coor_y[4];
				striker_3.coor_x[4] = 690 - striker_3.coor_x[4];
				striker_3.coor_y[4] = 483 - striker_3.coor_y[4];
		
			}
			
			image_temp1_S3_RESET.copyTo(result(Rect(striker_3.pos_res_x+13, striker_3.pos_res_y+6, 28, 28)));	
			image_temp1_S2_RESET.copyTo(result(Rect(striker_2.pos_res_x+13, striker_2.pos_res_y+6, 28, 28)));
			image_temp1_S3_POS.copyTo(result(Rect(striker_3.POS_X+13, striker_3.POS_Y+6, 28, 28)));	
			image_temp1_S2_POS.copyTo(result(Rect(striker_2.POS_X+13, striker_2.POS_Y+6, 28, 28)));
			image_temp1_S3.copyTo(result(Rect(striker_3.pos_X+13, striker_3.pos_Y+6, 28, 28)));
			image_temp1_S2.copyTo(result(Rect(striker_2.pos_X+13, striker_2.pos_Y+6, 28, 28)));
			image_temp2.copyTo(result(Rect(720, 0, symbol.cols, symbol.rows)));
			image_temp3.copyTo(result(Rect(960, 0, lambang.cols, lambang.rows)));
			image_temp4.copyTo(result(Rect(720, 225, rob.cols, rob.rows)));
			image_temp5.copyTo(result(Rect(0, 495, formation.cols, formation.rows)));
//		}
 		//==========SENDING DATA WIFI & JARAK FOR UDP CLIENT=======//

		//Data Wi-Fi
		if (counter == 0 || counter == 1 || counter == 4 || counter == 5) // (counter == 8 || counter == 9)
		{
		
//			memset(message, 0, sizeof(message));
//			sprintf(message,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n", 
//			ref1, ref2, ref3, (int)striker_3.coor_x[2], (int)striker_3.coor_y[2], (int)striker_2.coor_x[2], (int)striker_2.coor_y[2], /*(int)keeper.coor_x[2], (int)keeper.coor_y[2],*/ 
//			(int)striker_3.coor_x[4], (int)striker_3.coor_y[4], (int)striker_2.coor_x[4], (int)striker_2.coor_y[4],/* (int)keeper.coor_x[1], (int)keeper.coor_y[1],*/ (int)striker_2.yaw, 
//			(int)striker_3.yaw, (int)keeper.yaw, (int)striker_2.dist_ball, (int)striker_3.dist_ball, goalkick_x_lawan[0], goalkick_y_lawan[0], corner_x_lawan[0], corner_y_lawan[0], 
//			corner_x_lawan[1], corner_y_lawan[1], kickoff_x_lawan[0], kickoff_y_lawan[0], dropball_x_lawan[0], dropball_y_lawan[0], striker_3.reset_x[1], striker_3.reset_y[1], striker_2.reset_x[1], 
//			striker_2.reset_y[1], penalty_x_lawan[0], penalty_y_lawan[0], freekick_x_lawan[0], freekick_y_lawan[0], striker_2.x_ball[0], striker_2.y_ball[0], TEAM, mode_marking, striker_3.x_ball[0], 
//			striker_3.y_ball[0], keeper.reset_x[1], keeper.reset_y[1], mode_formasi, penalti_x_kita[0], penalti_y_kita[0], striker_3.reset_yaw[1], striker_2.reset_yaw[1]);//, keeper.reset_yaw[1]);
////			/*%d,%d,%d,%d,%d*/



			sprintf(message,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,1,1,%d,%d,%d,%d,%d,%d,%d\n", 
			ref1, ref2, ref3, 
			(int)striker_3.coor_x[0], (int)striker_3.coor_y[0], 
			(int)striker_2.coor_x[0], (int)striker_2.coor_y[0], 
			(int)flag_wifi, 
			(int)striker_3.coor_x[4], (int)striker_3.coor_y[4], 
			(int)striker_2.coor_x[4], (int)striker_2.coor_y[4],
			dummy_pos1, dummy_pos2, dummy_pos3, dummy_pos4, 
			(int)striker_2.yaw, (int)striker_3.yaw,
			(int)striker_2.dist_ball, (int)striker_3.dist_ball, 
			striker_3.reset_x[1], striker_3.reset_y[1],
			striker_2.reset_x[1], striker_2.reset_y[1], 
			TEAM, mode_marking, mode_formasi, 
			striker_3.x_cm[1], striker_3.y_cm[1], 
			striker_2.x_cm[1], striker_2.y_cm[1],
			striker_2.timer, striker_3.timer);
			 //printf("%s\n", message);
//			sprintf(message,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n", 
//			ref1, ref2, ref3, (int)striker_3.coor_x[2], (int)striker_3.coor_y[2], (int)striker_2.coor_x[2], (int)striker_2.coor_y[2], /*(int)keeper.coor_x[2], (int)keeper.coor_y[2],*/ 
//			(int)striker_3.coor_x[4], (int)striker_3.coor_y[4], (int)striker_2.coor_x[4], (int)striker_2.coor_y[4],/* (int)keeper.coor_x[1], (int)keeper.coor_y[1],*/ (int)striker_2.yaw, 
//			(int)striker_3.yaw, (int)keeper.yaw, (int)striker_2.dist_ball, (int)striker_3.dist_ball, goalkick_x_lawan[0], goalkick_y_lawan[0], corner_x_lawan[0], corner_y_lawan[0], 
//			corner_x_lawan[1], corner_y_lawan[1], kickoff_x_lawan[0], kickoff_y_lawan[0], dropball_x_lawan[0], dropball_y_lawan[0], //striker_3.reset_x[1], striker_3.reset_y[1], striker_2.reset_x[1], striker_2.reset_y[1], 
//			penalty_x_lawan[0], penalty_y_lawan[0], freekick_x_lawan[0], freekick_y_lawan[0], striker_2.x_ball[0], striker_2.y_ball[0], TEAM, mode_marking, striker_3.x_ball[0], 
//			striker_3.y_ball[0], 
//			//keeper.reset_x[1], keeper.reset_y[1], 
//			mode_formasi, penalti_x_kita[0], penalti_y_kita[0], striker_3.reset_yaw[1], striker_2.reset_yaw[1]);//, keeper.reset_yaw[1]);
//			/*%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d*/
			sendto(s, message, strlen(message), 0, (struct sockaddr*) &si_other, slen);
		}
//		if (counter == 2 || counter == 3 || counter == 6 || counter == 7){
////		
//			memset(message, 0, sizeof(message));
//			sprintf(message,"23,%d,%d,%d,%d", striker_3.reset_x[1], striker_3.reset_y[1], striker_2.reset_x[1], striker_2.reset_y[1]);

//			
//		}
//		sendto(s, message, strlen(message), 0, (struct sockaddr*) &si_other, slen);
//		printf("RESET = %d,%d\n", striker_3.reset_x[1], striker_3.reset_y[1]);
		ch = waitKey(1);
		imshow(window_name, result);
    }
    
    close(fd);    
    unlink(dataaddr);    
    close(s);    
    return (0);
}
