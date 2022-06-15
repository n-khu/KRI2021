// Cek koneksi TTL
// dmesg | grep tty

#include "opencv2/features2d/features2d.hpp"
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/highgui.hpp>
#include <opencv/highgui.h>
#include <opencv2/core.hpp>
#include <opencv/cv.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <time.h>
#include <fcntl.h>
#include <math.h>
#include <string>
#include <netdb.h>
#include <arpa/inet.h>

#define idx		2
#define PI 		3.14159265
#define BUFLEN 	1024  	//Max length of buffer
#define PORT 	6363   	//The port on which to listen for incoming data
#define ON 		true
#define OFF 	false

#pragma GCC diagnostic ignored "-Wwrite-strings"

using namespace cv;
using namespace std;

// static const char * portname = "/dev/ttyUSB0";
// static const char * portname = "/dev/video0";
static const char * portname = "/dev/video2";

FILE *serial_send;

Mat img, imgGoalpost;
Mat hsv, hsvGoalpost, hsv_lapangan;
Mat hsv_lapangan2, result_lapangan2; //add
Mat field, field_omniball, mask, mask_ball, ball_front;
Mat obs, obs_ball, mask_obs, mask_ball2, mask_obsraw, mask_front, field_obs; //add
Mat hue, hue_lapangan;
Mat histomniball;
Mat histobs; //add
Mat histimg = Mat::zeros(160, 120, CV_8UC3);
Mat histimgobs = Mat::zeros(160, 120, CV_8UC3); //add
Mat backprojomniball, backprojball;
Mat backprojobs, backprojobs2;
Mat result, result2, result_lapangan, resultGoalpost;

float hranges[] 		= {0,180};
const float* phranges 	= hranges;

float hrangesobs[] 		= {0,180}; //add
const float* phrangesobs 	= hrangesobs; //add

const double resolutionWidth 	= 640;  //800; //640; 			// OMNI
const double resolutionHeight 	= 360;	//448; //360; 			// OMNI
const double newWidth 			= 320; 			// FRONT
const double newHeight 			= 240; 			// FRONT
const double FPS_KAMERA_OMNI 	= 30;
const double FPS_KAMERA_DEPAN 	= 30;

double refArea, area2, area3;
double panjang_x_omniball, panjang_y_omniball;
double panjang_x_obs, panjang_y_obs;

const string windowName1 = "Omni Camera";
const string windowName2 = "Front Camera";

int serialPort;

int LowH[20], LowS[20], LowV[20], HighH[20], HighS[20], HighV[20];

int lineX1 	= ( resolutionWidth / 2 ) + 20; 	// OMNI
int lineX2 	= ( resolutionWidth / 2 ) - 20;		// OMNI
int lineY1 	= ( resolutionHeight / 2 ) + 20;	// OMNI
int lineY2 	= ( resolutionHeight / 2 ) - 20;	// OMNI
int line2X1 = ( newWidth / 2 ) + 20;			// FRONT
int line2X2 = ( newWidth / 2 ) - 20;			// FRONT
int line2Y1 = ( newHeight / 2 ) + 20;			// FRONT
int line2Y2 = ( newHeight / 2 ) - 20;			// FRONT

int trackObject = OFF;
int field_x, field_y;
int largestIndex;
int counter = 0;
int p 		= 0;
int hsize 	= 16;	
int hsizeobs 	= 16; //add
const int MAX_NUM_OBJECTS = 50;
const int MIN_OBJECT_AREA = 190;
const int MAX_OBJECT_AREA = newWidth*newHeight;

bool show 						= true;
bool detectFlag 				= OFF;
bool calibrationBall 			= OFF;
bool calibrationField		 	= OFF;
bool calibrationObs		 	    = OFF;
bool calibBallWindow 			= false;
bool calibFieldWindow 			= false;
bool calibObsWindow  			= false;
bool calibrationMode 			= OFF;
bool calibrationModeGoalpost 	= OFF;
bool mouseIsDragging 			= OFF;
bool mouseMove 					= OFF;
bool rectangleSelected 			= OFF;
bool objectFound 				= OFF;

Point origin, origin_1, origin_2, origin_3;
Point SetPoint, SetPoint2;
Point initialClickPoint, currentMousePoint;

Rect selection, selection_1, selection_2, selection_3;
Rect rectangleROI;

char message[BUFLEN];
char *pry1;
char ch = 0;

vector<vector<Point> > contours_field; 
vector<vector<Point> > contours_ball;
vector<vector<Point> > contours_poly;	
vector<Rect> fieldbox;
vector<Vec4i> hierarchy;
vector<int> H_ROI, S_ROI, V_ROI;

struct camera
{
	float angle;
	double ball_area;
	double distToCm;
	float dist;
	int x_ball[5];
	int y_ball[5];
  	int vx_ball[3];
  	int vy_ball[3];
	float ball_radius;
  	float ball_radius_lap;
	double length_x;
	double length_y;
} 	omni, omniobs, depan;

double convertToCentimeter(double jarak)
{
	return -10400.72 + (554.8265*jarak) - (11.63941*pow(jarak,2)) + (0.1204982*pow(jarak,3)) - (0.0006156849*pow(jarak,4)) + (0.000001246209*pow(jarak,5));
}

const char* keys =
{
	  "{help h | | show help message}{@camera_number| 0 | camera number}"
	  "{help h | | show help message}{@camera_number1| 1 | camera number1}"	
};

//static void help()
//{
//    cout << "\nThis is a demo that shows mean-shift based tracking\n"
//            "You select a color objects such as an orange ball and it tracks it.\n"
//            "This reads from video camera (0 by default, or the camera number the user enters\n"
//            "Usage: ./APOLLO [camera number] [camera number1]\n";
//}

void Auto_detecting(Mat &img, Rect &shape, Point &asli)
{
    int x = resolutionWidth;
    int y = resolutionHeight;

    asli = Point(0,0);
    shape = Rect(asli.x,asli.y,x,y);
//  shape &= Rect(0, 0, img.cols, img.rows);

	trackObject = 1;
}


//https://raw.githubusercontent.com/kylehounslow/opencv-tuts/master/auto-colour-filter/AutoColourFilter.cpp
void recordHSV_Values(cv::Mat frame, cv::Mat hsv_frame)
{
	if (rectangleSelected && !mouseMove)
  	{
		if (H_ROI.size() > 0) H_ROI.clear();
      	if (S_ROI.size() > 0) S_ROI.clear();
      	if (V_ROI.size() > 0) V_ROI.clear();
      	if (rectangleROI.width < 1 || rectangleROI.height < 1) 
	  	cout << "Drag Bentuk KOTAK ! Jangan Garis !" << endl;
      	else
		{
  	  		for (int i = rectangleROI.x; i < rectangleROI.x + rectangleROI.width; i++)
	    	{
      		  	for (int j = rectangleROI.y; j < rectangleROI.y + rectangleROI.height; j++)
				{
				  	H_ROI.push_back((int)hsv_frame.at<cv::Vec3b>(j, i)[0]);
				    S_ROI.push_back((int)hsv_frame.at<cv::Vec3b>(j, i)[1]);
				    V_ROI.push_back((int)hsv_frame.at<cv::Vec3b>(j, i)[2]);
				}
        	}
     	}

      	if (p == 0) printf("\t// Untuk Bola Terang \n");
		if (p == 2) printf("\t// Untuk Lapangan Terang \n");
		if (p == 4) printf("\t// Untuk Obstacle Terang \n"); //add

		rectangleSelected = false;

		if (calibrationBall)
		{
	  		if (H_ROI.size() > 0)
			{
	    		LowH[0] = *std::min_element(H_ROI.begin(), H_ROI.end());
	      		HighH[0] = *std::max_element(H_ROI.begin(), H_ROI.end());
				printf("\tLowH[%d] = %d;\n", p, LowH[0]);
				printf("\tHighH[%d] = %d;\n", p, HighH[0]);
	    	}
	    	if (S_ROI.size() > 0)
			{
	    		LowS[0] = *std::min_element(S_ROI.begin(), S_ROI.end());
	    		HighS[0] = *std::max_element(S_ROI.begin(), S_ROI.end());
				printf("\tLowS[%d] = %d;\n", p, LowS[0]);
				printf("\tHighS[%d] = %d;\n", p, HighS[0]);
	    	}
			if (V_ROI.size() > 0)
			{
		  		LowV[0] = *std::min_element(V_ROI.begin(), V_ROI.end());
		  		HighV[0] = *std::max_element(V_ROI.begin(), V_ROI.end());
				printf("\tLowV[%d] = %d;\n", p, LowV[0]);
				printf("\tHighV[%d] = %d;\n", p, HighV[0]);
		  		printf("\n");
			}
		}

		if (calibrationField)
		{
	  		if (H_ROI.size() > 0)
			{
	  			LowH[2] = *std::min_element(H_ROI.begin(), H_ROI.end());
      			HighH[2] = *std::max_element(H_ROI.begin(), H_ROI.end());
				printf("\tLowH[%d] = %d;\n", p, LowH[2]);
				printf("\tHighH[%d] = %d;\n", p, HighH[2]);
	    	}
	    	if (S_ROI.size() > 0)
			{
	      		LowS[2] = *std::min_element(S_ROI.begin(), S_ROI.end());
	      		HighS[2] = *std::max_element(S_ROI.begin(), S_ROI.end());
				printf("\tLowS[%d] = %d;\n", p, LowS[2]);
				printf("\tHighS[%d] = %d;\n", p, HighS[2]);
	    	}
	    	if (V_ROI.size() > 0)
			{
	      		LowV[2] = *std::min_element(V_ROI.begin(), V_ROI.end());
	      		HighV[2] = *std::max_element(V_ROI.begin(), V_ROI.end());
				printf("\tLowV[%d] = %d;\n", p, LowV[2]);
				printf("\tHighV[%d] = %d;\n", p, HighV[2]);
	      		printf("\n");
	    	}
		}

		if (calibrationObs)
		{
	  		if (H_ROI.size() > 0)
			{
	  			LowH[4] = *std::min_element(H_ROI.begin(), H_ROI.end());
      			HighH[4] = *std::max_element(H_ROI.begin(), H_ROI.end());
				printf("\tLowH[%d] = %d;\n", p, LowH[4]);
				printf("\tHighH[%d] = %d;\n", p, HighH[4]);
	    	}
	    	if (S_ROI.size() > 0)
			{
	      		LowS[4] = *std::min_element(S_ROI.begin(), S_ROI.end());
	      		HighS[4] = *std::max_element(S_ROI.begin(), S_ROI.end());
				printf("\tLowS[%d] = %d;\n", p, LowS[4]);
				printf("\tHighS[%d] = %d;\n", p, HighS[4]);
	    	}
	    	if (V_ROI.size() > 0)
			{
	      		LowV[4] = *std::min_element(V_ROI.begin(), V_ROI.end());
	      		HighV[4] = *std::max_element(V_ROI.begin(), V_ROI.end());
				printf("\tLowV[%d] = %d;\n", p, LowV[4]);
				printf("\tHighV[%d] = %d;\n", p, HighV[4]);
	      		printf("\n");
	    	}
		}

		if (calibrationBall) 
		{
      		p = p+1;
			if (p == 1) printf("\t// Untuk Bola Gelap \n");
			if (p > 1) p = 1;
		}
		if (calibrationField) 
		{
			p = p+1;
			if (p == 3) printf("\t// Untuk Lapangan Gelap \n");
			if (p > 3) p = 3;
		}
		if (calibrationObs) 
		{
			p = p+1;
			if (p == 5) printf("\t// Untuk Lapangan Gelap \n");
			if (p > 5) p = 5;
		}
	}
    
  	if (mouseMove) rectangle(frame, initialClickPoint, cv::Point(currentMousePoint.x, currentMousePoint.y), cv::Scalar(255,0,0), 1,8,0);
}

void clickAndDrag_Rectangle(int event, int x, int y, int flags, void* param)
{
    if (calibrationBall|| calibrationField || calibrationObs)
    {
        if (event == CV_EVENT_LBUTTONDOWN && !mouseIsDragging)
        {
            initialClickPoint = cv::Point(x, y);
            mouseIsDragging = true;
        }
        if (event == CV_EVENT_MOUSEMOVE && mouseIsDragging)
        {
            currentMousePoint = cv::Point(x, y);
            mouseMove = true;
        }
        if (event == CV_EVENT_LBUTTONUP && mouseIsDragging)
        {
            rectangleROI = Rect(initialClickPoint, currentMousePoint);
            mouseIsDragging = false;
            mouseMove = false;
            rectangleSelected = true;
        }
        if (event == CV_EVENT_RBUTTONDOWN)
		{
			if (calibrationBall)
			{
		        LowH[0] = 0;
		        LowS[0] = 0;
		        LowV[0] = 0;
		        HighH[0] = 255;
		        HighS[0] = 255;
		        HighV[0] = 255;
		        p = 0;
			}
			if (calibrationField)
			{
		        LowH[2] = 0;
		        LowS[2] = 0;
		        LowV[2] = 0;
		        HighH[2] = 255;
		        HighS[2] = 255;
		        HighV[2] = 255;
		        p = 2;
			}
			if (calibrationObs)
			{
		        LowH[4] = 0;
		        LowS[4] = 0;
		        LowV[4] = 0;
		        HighH[4] = 255;
		        HighS[4] = 255;
		        HighV[4] = 255;
		        p = 4;
			}
        }      
    }    
}


void Trackbar_ThreshBallField(char win_thresh[], int index)
{
	createTrackbar("LowH", win_thresh, &LowH[index], 255);
	createTrackbar("HighH", win_thresh, &HighH[index], 255);
	createTrackbar("LowS", win_thresh, &LowS[index], 255);
	createTrackbar("HighS", win_thresh, &HighS[index], 255);
	createTrackbar("LowV", win_thresh, &LowV[index] ,255);
	createTrackbar("HighV", win_thresh, &HighV[index], 255);
}

void morphology(Mat &thresh)
{
	dilate	(thresh, thresh, getStructuringElement(MORPH_RECT,Size(11,11)));
	erode	(thresh, thresh, getStructuringElement(MORPH_RECT,Size(7,7)));
	dilate	(thresh, thresh, getStructuringElement(MORPH_RECT,Size(11,11)));
}

void morphology_obstacle(Mat &thresh)
{
	dilate	(thresh, thresh, getStructuringElement(MORPH_RECT,Size(5,5)));
	erode	(thresh, thresh, getStructuringElement(MORPH_RECT,Size(3,3)));
	dilate	(thresh, thresh, getStructuringElement(MORPH_RECT,Size(5,5)));
}

void morphology_lapangan(Mat &thresh)
{
	erode	(thresh, thresh, getStructuringElement(MORPH_RECT,Size(9,9)));
	erode	(thresh, thresh, getStructuringElement(MORPH_RECT,Size(8,8)));
	dilate	(thresh, thresh, getStructuringElement(MORPH_RECT,Size(9,9)));
	erode	(thresh, thresh, getStructuringElement(MORPH_RECT,Size(9,9)));
	dilate	(thresh, thresh, getStructuringElement(MORPH_RECT,Size(3,3)));
}

int main (int argc, char **argv)
{
	// Untuk Bola Terang 
	LowH[0] = 5;
	HighH[0] = 9;
	LowS[0] = 220;
	HighS[0] = 255;
	LowV[0] = 164;
	HighV[0] = 225;

	// Untuk Bola Gelap 
	LowH[1] = 4;
	HighH[1] = 9;
	LowS[1] = 214;
	HighS[1] = 255;
	LowV[1] = 107;
	HighV[1] = 224;

	// Untuk Lapangan Terang 
	LowH[2] = 0;
	HighH[2] = 178;
	LowS[2] = 0;
	HighS[2] = 202;
	LowV[2] = 0;
	HighV[2] = 210;

	// Untuk Lapangan Gelap 
	LowH[3] = 0;
	HighH[3] = 179;
	LowS[3] = 0;
	HighS[3] = 255;
	LowV[3] = 0;
	HighV[3] = 238;

	//add Untuk Obstacle Terang 
	LowH[4] = 5;
	HighH[4] = 9;
	LowS[4] = 220;
	HighS[4] = 255;
	LowV[4] = 164;
	HighV[4] = 225;

	//add Untuk Obstacle Gelap 
	LowH[5] = 4;
	HighH[5] = 9;
	LowS[5] = 214;
	HighS[5] = 255;
	LowV[5] = 107;
	HighV[5] = 224;



	LowH[2] < LowH[3] ? LowH[2] = LowH[2] : LowH[2] = LowH[3];
	LowS[2] < LowS[3] ? LowS[2] = LowS[2] : LowS[2] = LowS[3];
	LowV[2] < LowV[3] ? LowV[2] = LowV[2] : LowV[2] = LowV[3];
	HighH[2] < HighH[3] ? HighH[2] = HighH[3] : HighH[2] = HighH[2];
	HighS[2] < HighS[3] ? HighS[2] = HighS[3] : HighS[2] = HighS[2];	
	HighV[2] < HighV[3] ? HighV[2] = HighV[3] : HighV[2] = HighV[2];

	LowH[0] < LowH[1] ? LowH[0] = LowH[0] : LowH[0] = LowH[1];
	LowS[0] < LowS[1] ? LowS[0] = LowS[0] : LowS[0] = LowS[1];
	LowV[0] < LowV[1] ? LowV[0] = LowV[0] : LowV[0] = LowV[1];
	HighH[0] < HighH[1] ? HighH[0] = HighH[1] : HighH[0] = HighH[0];
	HighS[0] < HighS[1] ? HighS[0] = HighS[1] : HighS[0] = HighS[0];	
	HighV[0] < HighV[1] ? HighV[0] = HighV[1] : HighV[0] = HighV[0];

	//add
	LowH[4] < LowH[5] ? LowH[4] = LowH[4] : LowH[4] = LowH[5];
	LowS[4] < LowS[5] ? LowS[4] = LowS[4] : LowS[4] = LowS[5];
	LowV[4] < LowV[5] ? LowV[4] = LowV[4] : LowV[4] = LowV[5];
	HighH[4] < HighH[5] ? HighH[4] = HighH[5] : HighH[4] = HighH[4];
	HighS[4] < HighS[5] ? HighS[4] = HighS[5] : HighS[4] = HighS[4];	
	HighV[4] < HighV[5] ? HighV[4] = HighV[5] : HighV[4] = HighV[4];

	//================================FIFO INIT==================================//

   	int fd;
    
	static const char * dataaddr = "/tmp/KAMERA"; //alamat sesuai dengan yang dibuat writernya
	mkfifo(dataaddr, 0666);
    
   	fd = open(dataaddr, O_RDWR | O_NDELAY | O_NOCTTY | O_NONBLOCK | O_ASYNC);

  	serial_send = fopen(portname, "w");
   
    /*------------- Setting the Attributes of the serial port using termios structure ------------- */
		
    struct termios SerialPortSettings;				/* Create the structure                          */
    serialPort = open(portname, O_RDWR | O_NOCTTY | O_NDELAY  | O_NONBLOCK | O_ASYNC);  
    tcgetattr(serialPort, &SerialPortSettings);		/* Get the current attributes of the Serial port */

    // Flush the buffer one more time.
    tcflush(serialPort, TCIOFLUSH);

	cfsetispeed(&SerialPortSettings, B38400); 		/* Set Read  Speed as 9600                       */
    cfsetospeed(&SerialPortSettings, B38400); 		/* Set Write Speed as 9600                       */

    SerialPortSettings.c_cflag &= ~PARENB;   		/* Disables the Parity Enable bit(PARENB),So No Parity   */
    SerialPortSettings.c_cflag &= ~CSTOPB;   		/* CSTOPB = 2 Stop bits,here it is cleared so 1 Stop bit */
    SerialPortSettings.c_cflag &= ~CSIZE;	 		/* Clears the mask for setting the data size             */
    SerialPortSettings.c_cflag |=  CS8;      		/* Set the data bits = 8                                 */
		
    SerialPortSettings.c_cflag &= ~CRTSCTS;       	/* No Hardware flow Control                         */
    SerialPortSettings.c_cflag |= CREAD;
    SerialPortSettings.c_cflag |= CLOCAL; 			/* Enable receiver,Ignore Modem Control lines       */ 
				    
    // Now that we've populated our options structure, let's push it back to the system.
    tcsetattr(serialPort,TCSANOW, &SerialPortSettings);     

    // Flush the buffer one more time.
    tcflush(serialPort, TCIOFLUSH);

    // Flush the buffer one more time.
    tcflush(serialPort, TCIFLUSH);

//	serial_send = fopen(portname, "w");

	if (serial_send == 0) printf("Failed to open serial port\n");
	fflush(stdout);

	//================================OPEN CAMERA==================================//

	VideoCapture cap;

	// >>>>> Camera Settings
	if (!cap.open(idx))
	{
	    cout << "Webcam first not connected.\n" << "Please verify\n";
	    return EXIT_FAILURE;
	}

   	cap.set(CV_CAP_PROP_FRAME_WIDTH, resolutionWidth);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, resolutionHeight);
	cap.set(CV_CAP_PROP_FPS, FPS_KAMERA_OMNI);

	// VideoWriter video("CAM.avi",CV_FOURCC('M','J','P','G'),60,Size(resolutionWidth,resolutionHeight),true);
			// cap.set(CV_CAP_PROP_AUTOFOCUS, 1);
			// cap.set(28, 105);
		// mouseIsDragging = false;
		// mouseMove = false;
    	// rectangleSelected = false;

	SetPoint.x = resolutionWidth / 2;
	SetPoint.y = resolutionHeight / 2;
	SetPoint2.x = (resolutionWidth / 2);
	SetPoint2.y = resolutionHeight / 2;
	

	Mat close_rect 		= Mat::zeros(resolutionHeight, resolutionWidth, CV_8UC3);
	Mat close_circle 	= Mat::zeros(resolutionHeight, resolutionWidth, CV_8UC3);

	circle(close_circle, SetPoint, (resolutionWidth/2.8), Scalar(255,255,255), -1);
	rectangle(close_rect, Point(resolutionWidth/2 -60, resolutionHeight/2 -75), Point(resolutionWidth/2 +60, resolutionHeight/2 +75), Scalar(255,255,255), -1);
	
	namedWindow(windowName1, CV_WINDOW_AUTOSIZE);
	namedWindow(windowName2, CV_WINDOW_AUTOSIZE);
	// namedWindow("CIRCLE", CV_WINDOW_AUTOSIZE);
	// namedWindow("Threshold Bola", CV_WINDOW_AUTOSIZE); 
	// namedWindow("Threshold Lapangan", CV_WINDOW_AUTOSIZE); 
	// namedWindow("Threshold Obs", CV_WINDOW_AUTOSIZE); 
	while (ch != 27)
	{
		//================================KEYBOARD EVENTS==================================//

		if (ch == 'p') show = false;
		if (ch == 'o') show = true;
		if (ch == 'q') 
		{
		    calibrationBall = true;
		    printf("\n \n calibrationBall = ON \n \n");
			p = 0;
		}
  		if (ch == 'a') 
		{
		    calibrationBall = false;
		    printf("\n \n calibrationBall = OFF \n \n");
		}
		if (ch == 'w') 
		{
		    calibrationField = true;
		    printf("\n \n calibrationField = ON \n \n");
			p = 2;
		}
  		if (ch == 's') 
		{
		    calibrationField = false;
		    printf("\n \n calibrationField = OFF \n \n");
		}
		if (ch == 'e') //add
		{
		    calibrationObs = true;
		    printf("\n \n calibrationObs = ON \n \n");
			p = 4;
		}
  		if (ch == 'd') //add
		{
		    calibrationObs = false;
		    printf("\n \n calibrationObs = OFF \n \n");
		}
		//================================FIRST PROCESS CAMERA==================================//

		cap >> img; 

		if (img.empty())
		{
			cout <<  "Could not open or find the image" << endl ;
			break;
		} 

		img.copyTo(result);	

		Mat close_circle1 	= Mat::zeros(resolutionHeight, resolutionWidth, CV_8UC3);
		Mat close_circle2 	= Mat::zeros(resolutionHeight, resolutionWidth, CV_8UC3);
		Mat sort_field 		= Mat::zeros(resolutionHeight, resolutionWidth, CV_8UC3);
		
		// BLACK CIRCLE OMNI
		circle(close_circle1, SetPoint2, (resolutionWidth/3.8), Scalar(255,255,255), -1);
//		ellipse(close_circle1, SetPoint, Size(resolutionWidth/2.5, resolutionWidth/2.5), 350, 0, 200, Scalar(255,255,255), -1);
		bitwise_and(close_circle1, result, result2);
		result_lapangan = result2.clone();

		if (calibrationBall || calibrationField || calibrationObs) //add
		{
			cvtColor(result_lapangan, hsv_lapangan, COLOR_BGR2HSV);
			recordHSV_Values(result_lapangan, hsv_lapangan);		
		}

		setMouseCallback(windowName1, clickAndDrag_Rectangle, &result_lapangan);			
		cvtColor(result, hsv, COLOR_BGR2HSV);

		// MASK BALL
		inRange(hsv, Scalar(LowH[0], LowS[0], MIN(LowV[0],HighV[0])), Scalar(HighH[0], HighS[0], MAX(LowV[0],HighV[0])), mask);
//		inRange(hsv, Scalar(LowH[1], LowS[1], MIN(LowV[1],HighV[1])), Scalar(HighH[1], HighS[1], MAX(LowV[1],HighV[1])), bola_2);
//		addWeighted(bola_1, 1.0, bola_2, 1.0, 0.0, mask);
		GaussianBlur(mask, mask, Size(15,15), 0, 0);
		morphology(mask);

		// ADD OBS
		inRange(hsv, Scalar(LowH[4], LowS[4], MIN(LowV[4],HighV[4])), Scalar(HighH[4], HighS[4], MAX(LowV[4],HighV[4])), obs);
		GaussianBlur(obs, obs, Size(15,15), 0, 0);
		morphology_obstacle(obs);

		// FIELD
		inRange(hsv, Scalar(LowH[2], LowS[2], MIN(LowV[2],HighV[2])), Scalar(HighH[2], HighS[2], MAX(LowV[2],HighV[2])), field);	
		threshold(field, field, 20, 255, THRESH_BINARY);
		GaussianBlur(field, field, Size(27,27), 0, 0);
		morphology_lapangan(field);

		// DISPLAY
		if (calibrationBall) 
		{
			Trackbar_ThreshBallField("Threshold Bola", 0); 
			imshow("Threshold Bola", mask); 
			calibBallWindow = true;
		}

		if (calibrationField) 
		{
			Trackbar_ThreshBallField("Threshold Lapangan", 2);
			imshow("Threshold Lapangan", field); 
			calibFieldWindow = true;
		}
		
		if (calibrationObs) 
		{
			Trackbar_ThreshBallField("Threshold Obstacle", 4);
			imshow("Threshold Obstacle", obs); 
			calibObsWindow = true;
		}

		if (!calibrationBall && calibBallWindow) 
		{
			destroyWindow("Threshold Bola"); 
			calibBallWindow = false;
		}
		if (!calibrationField && calibFieldWindow) 
		{
			destroyWindow("Threshold Lapangan"); 
			calibFieldWindow = false;
		}
		if (!calibrationObs && calibObsWindow) 
		{
			destroyWindow("Threshold Obstacle"); 
			calibObsWindow = false;
		}

		Auto_detecting(result, selection, origin);		      

		if (!calibrationBall && !calibrationField && !calibrationObs)
		{                						 	
			counter++;
			if (counter == 50) counter = 1;		

			if (trackObject == ON)
        	{	
				int ch[] = {0, 0};	
//				printf("\n%d. ", counter);	
				
				// CONTOURS
				// Cari kontur lapangan dan obstacle -> contours_field & contours_obstacle
				findContours(field, contours_field, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0,0));


				// FIND THE CONVEX HULL OBJECT FOR EACH CONTOUR
				// Bikin vector point baru hull dengan size contours_field
				// https://www.learnopencv.com/convex-hull-using-opencv-in-python-and-c/
				vector<vector<Point> > hull(contours_field.size());
	   			for (size_t i = 0; i < contours_field.size(); i++)
				{
					convexHull(Mat(contours_field[i]), hull[i], false); 
				}

				// MOMENTS TO GET AVERAGE IMAGE PIXEL INTENSITIES
				// https://www.learnopencv.com/find-center-of-blob-centroid-using-opencv-cpp-python/
				for (size_t i = 0; i < hull.size(); i++)
				{ 	
					Moments oMoments_field = moments(hull[i]);
					double Area_field = oMoments_field.m00;				   
						
					field_x = oMoments_field.m10 / Area_field;
					field_y = oMoments_field.m01 / Area_field;	

					Rect field_box;
					field_box = boundingRect(hull[i]);
					fieldbox.push_back(field_box);

					for (size_t j = 0; j < hull[i].size(); j++)
					{																								
	        			Point lapangan_hijau;
	          	  		lapangan_hijau.x = fieldbox[j].x + fieldbox[j].width / 2;
	            		lapangan_hijau.y = fieldbox[j].y + fieldbox[j].height / 2;                                               
	
						field_x = (int)hull[i][j].x;
						field_y = (int)hull[i][j].y;												
					}

					if (Area_field > 0)
					{
						drawContours(sort_field, hull, i, Scalar(255,255,255), CV_FILLED, 8, vector<Vec4i>(), 1, Point());
					}
				}

				if (contours_field.size() <= 0) rectangle(sort_field, Point(0,0), Point(0,0), Scalar(255,255,255), CV_FILLED); 
				
				bitwise_and(sort_field, result_lapangan, result_lapangan);				
				cvtColor(result_lapangan, hsv_lapangan, COLOR_BGR2HSV);

				// OBS ADD for calc
				inRange(hsv_lapangan, Scalar(LowH[4], LowS[4], MIN(LowV[4],HighV[4])), Scalar(HighH[4], HighS[4], MAX(LowV[4],HighV[4])), mask_obs);
				
				// mask_ball2 = field_omniball.clone();
				// mask_obsraw = hsv_lapangan.clone();
				// // mask_obsraw.setTo(Scalar(LowH[2], LowS[2], MIN(LowV[2],HighV[2])), Scalar(HighH[2], HighS[2], MAX(LowV[2],HighV[2])));
				// // mask_ball2.setTo(Scalar(LowH[0], LowS[0], MIN(LowV[0],HighV[0])), Scalar(HighH[0], HighS[0], MAX(LowV[0],HighV[0])));
				// mask_obs = mask_obsraw - mask_ball;
				// // mask_obsraw = mask_ball.clone();
				// // // mask_obs = ~mask_obsraw;
				// // cvtColor(mask_obsraw, mask_obsraw, COLOR_BGR2GRAY);
				// // cvtColor(mask_ball2, mask_ball2, COLOR_BGR2GRAY);
				// // bitwise_or(mask_obsraw, mask_ball2, mask_obs, mask_obs);
				// // bitwise_not(result_lapangan2, mask_obsraw, mask_ball2);
				// // Mat close_circle3 	= Mat::zeros(resolutionHeight, resolutionWidth, CV_8UC3);
				// // circle(close_circle3, SetPoint, (resolutionWidth/2.8), Scalar(0,0,0), -1);
				// // bitwise_and(mask_obsraw, close_circle3, mask_obsraw);				
				// // cvtColor(result_lapangan, hsv_lapangan, COLOR_BGR2HSV);
				// mask_obs = ~mask_ball2;
				GaussianBlur(mask_obs, mask_obs, Size(9,9), 0, 0);
				morphology_obstacle(mask_obs);
				namedWindow("inverse matrix", CV_WINDOW_AUTOSIZE);
				imshow("inverse matrix", mask_obs);
				
				// if(!calibrationObs)
				// {
				// 	field_obs = hsv_lapangan.clone();
				// 	Mat close_circle2 = Mat::zeros(resolutionHeight, resolutionWidth, CV_8UC3);
				// 	circle(close_circle2, SetPoint, (resolutionWidth/4.5), Scalar(255,255,255), -1);
				// 	bitwise_and(close_circle2, field_obs, field_obs);
				// 	close_rect = Mat::zeros(resolutionHeight, resolutionWidth, CV_8UC3);
				// 	rectangle(close_rect, Point(resolutionWidth/2 - 60, resolutionHeight/2 - 75), Point(resolutionWidth/2 + 60, resolutionHeight/2 + 75) , Scalar(255,255,255), -1);
				// 	bitwise_not(close_rect, close_rect);
				// 	bitwise_and(close_rect, field_obs, field_obs);
				// 	bitwise_and(close_circle, field_obs, field_obs);
				
				// 	inRange(field_obs, Scalar(LowH[4], LowS[4], MIN(LowV[4],HighV[4])), Scalar(HighH[4], HighS[4], MAX(LowV[4],HighV[4])), obstacle);
				// 	GaussianBlur(obstacle, obstacle, Size(7,7), 0, 0);
				// 	morphology_obstacle(obstacle);
				// 	GaussianBlur(obstacle, obstacle, Size(11,11), 0, 0);					
				// 	threshold(obstacle, obstacle, 57, 255, THRESH_BINARY);
				// }
				
				// DRAW SQUARE AND POINT CENTRE
				line(result_lapangan, Point(lineX1,lineY1), Point(lineX1, lineY2),CV_RGB(100,50,250),2,3,0);
				line(result_lapangan, Point(lineX2,lineY1), Point(lineX2, lineY2),CV_RGB(100,50,250),2,3,0);
				line(result_lapangan, Point(lineX1,lineY1), Point(lineX2, lineY1),CV_RGB(100,50,250),2,3,0);
				line(result_lapangan, Point(lineX1,lineY2), Point(lineX2, lineY2),CV_RGB(100,50,250),2,3,0);
				circle(result_lapangan, SetPoint, 4, CV_RGB(255,100,50), -1);	

				// BALL
				inRange(hsv_lapangan, Scalar(LowH[0], LowS[0], MIN(LowV[0],HighV[0])), Scalar(HighH[0], HighS[0], MAX(LowV[0],HighV[0])), mask_ball);
				GaussianBlur(mask_ball, mask_ball, Size(9,9), 0, 0);
				morphology(mask_ball);

				
				// FIELD
				inRange(hsv_lapangan, Scalar(LowH[2], LowS[2], MIN(LowV[2],HighV[2])), Scalar(HighH[2], HighS[2], MAX(LowV[2],HighV[2])), field_omniball);	
				GaussianBlur(field_omniball, field_omniball, Size(13,13), 0, 0);
				dilate(field_omniball, field_omniball, getStructuringElement(MORPH_ELLIPSE, Size(11,11)));


				Auto_detecting(result_lapangan, selection_1, origin_1);
				Auto_detecting(result_lapangan, selection_2, origin_2);	
				Auto_detecting(result_lapangan, selection_3, origin_3);

				// MIXCHANNEL, CALCHIST, NORMALIZE, CALCBACKPROJECT
				hue_lapangan.create(hsv_lapangan.size(), hsv_lapangan.depth());
				// mixChannels(const Mat* src, size_t nsrcs, Mat* dst, size_t ndsts, const int* fromTo, size_t npairs)
				// https://docs.opencv.org/2.4/modules/core/doc/operations_on_arrays.html
			  	mixChannels(&hsv_lapangan, 1, &hue_lapangan, 1, ch, 1);		
				// Mat (const Mat &m, const Rect &roi)
				Mat roiomniball(hue_lapangan, selection_1), omniballroi(mask_ball, selection_1);
				Mat roiobs(hue_lapangan, selection_3), obsroi(mask_obs, selection_3); //add
				// https://docs.opencv.org/2.4/doc/tutorials/imgproc/histograms/histogram_calculation/histogram_calculation.html
				// calcHist(const Mat* images, int nimages, const int* channels, InputArray mask, OutputArray hist, int dims, const int* histSize, const float** ranges, bool uniform=true, bool accumulate=false 
				calcHist(&roiomniball, 1, 0, omniballroi, histomniball, 1, &hsize, &phranges);
				calcHist(&roiobs, 1, 0, obsroi, histobs, 1, &hsizeobs, &phrangesobs); //add
				// normalize(input, output, lower limit, upper limit to normalize the values of histogram, types of normalization);
				normalize(histomniball, histomniball, 0, 255, NORM_MINMAX);
				normalize(histobs, histobs, 0, 255, NORM_MINMAX); //add

//				Mat fieldroi(hue_lapangan, selection_2), roifield(field_omniball, selection_2);
//				calcHist(&fieldroi, 1, 0, roifield, histfield, 1, &hsize, &phranges);
//				normalize(histfield, histfield, 0, 255, NORM_MINMAX);

				// DISPLAY THE HISTOGRAM IN BLOCK
				Mat buf(1, hsize, CV_8UC3);
				histimg 	= Scalar::all(0);		    
				int binW 	= histimg.cols / hsize;
				for (int i 	= 0; i < hsize; i++)
				buf.at<Vec3b>(i) = Vec3b(saturate_cast<uchar>(i*180./hsize), 255, 255);

				//add				
				Mat bufobs(1, hsizeobs, CV_8UC3);
				histimgobs 	= Scalar::all(0);		    
				int binWobs 	= histimgobs.cols / hsizeobs;
				for (int ii 	= 0; ii < hsizeobs; ii++)
				bufobs.at<Vec3b>(ii) = Vec3b(saturate_cast<uchar>(ii*180./hsizeobs), 255, 255);

				cvtColor(buf, buf, COLOR_HSV2BGR);			

				for (int i = 0; i < hsize; i++)
				{	
					int val_omniball = saturate_cast<int>(histomniball.at<float>(i)*histimg.rows/255);
//					int val_field 	 = saturate_cast<int>(histfield.at<float>(i)*histimg.rows/255);
					rectangle(histimg, Point(i*binW,histimg.rows), Point((i+1)*binW,histimg.rows - val_omniball), Scalar(buf.at<Vec3b>(i)), -1, 8);
//					rectangle(histimg, Point(i*binW,histimg.rows), Point((i+1)*binW,histimg.rows - val_field), Scalar(buf.at<Vec3b>(i)), -1, 8);

					int val_obs = saturate_cast<int>(histobs.at<float>(i)*histimgobs.rows/255); //add
					rectangle(histimgobs, Point(i*binWobs,histimgobs.rows), Point((i+1)*binWobs,histimgobs.rows - val_obs), Scalar(bufobs.at<Vec3b>(i)), -1, 8); //add
				}

				// BACKPROJECTION FOR CAMSHIFT
				// https://docs.opencv.org/2.4/modules/imgproc/doc/histograms.html?highlight=calcbackproject
				// https://docs.opencv.org/3.4/da/d7f/tutorial_back_projection.html
				calcBackProject(&hue_lapangan, 1, 0, histomniball, backprojomniball, &phranges);						
				backprojomniball &= mask_ball;
				calcBackProject(&hue_lapangan, 1, 0, histobs, backprojobs, &phrangesobs);	//add					
				backprojobs &= mask_obs;					//add

				// http://eric-yuan.me/continuously-adaptive-shift/
				// RotatedRect CamShift(InputArray probImage, Rect& window, TermCriteria criteria)		
				// CamShift is a tracking algorithm, which is based on MeanShift algorithm.
				// What camShift do is nothing but do meanShift in every single frame of a video, and record the results we got by meanShift.
				// CamShift functions to find an object center, size, and orientation.	                        
				RotatedRect trackBox_omniball = CamShift(backprojomniball, selection_1, TermCriteria( CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 10, 1 ));
				RotatedRect trackBox_obs = CamShift(backprojobs, selection_3, TermCriteria( CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 10, 1 ));

//				calcBackProject(&hue_lapangan, 1, 0, histfield, backprojfield, &phranges);						
//				backprojfield &= field_omniball;							            
//				RotatedRect trackBox_field = CamShift(backprojfield, selection_2, TermCriteria( CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 10, 1 ));

				// FORMULAS FOR OMNIBALL
				omni.angle = atan2(SetPoint.y - trackBox_omniball.center.y, SetPoint.x - trackBox_omniball.center.x);
				omni.angle 	= 180 - (omni.angle * 180 / PI) - 271;

				if (omni.angle >= -271 && omni.angle <= 0) omni.angle += 360;
				
				panjang_x_omniball = SetPoint.x - trackBox_omniball.center.x;
				panjang_y_omniball = SetPoint.y - trackBox_omniball.center.y;	
				omni.dist 	   = sqrt((panjang_x_omniball * panjang_x_omniball) + (panjang_y_omniball * panjang_y_omniball));
				omni.distToCm  = convertToCentimeter(omni.dist);

				omni.ball_radius = trackBox_omniball.size.width / 2;
				omni.ball_area 	 = pow(omni.ball_radius,2) * PI;

				// FORMULAS FOR OBSTACLE //add
				omniobs.angle = atan2(SetPoint.y - trackBox_obs.center.y, SetPoint.x - trackBox_obs.center.x);
				omniobs.angle 	= 180 - (omniobs.angle * 180 / PI) - 271;

				if (omniobs.angle >= -271 && omniobs.angle <= 0) omniobs.angle += 360;
				
				panjang_x_obs = SetPoint.x - trackBox_obs.center.x;
				panjang_y_obs = SetPoint.y - trackBox_obs.center.y;	
				omniobs.dist 	   = sqrt((panjang_x_obs * panjang_x_obs) + (panjang_y_obs * panjang_y_obs));
				omniobs.distToCm  = convertToCentimeter(omniobs.dist);

				omniobs.ball_radius = trackBox_obs.size.width / 2;
				omniobs.ball_area 	 = pow(omniobs.ball_radius,2) * PI;

				if (trackBox_omniball.center.x >= 0 && trackBox_omniball.center.y >= 0) 
				{
					omni.x_ball[0] = trackBox_omniball.center.x;
					omni.y_ball[0] = trackBox_omniball.center.y;

					omni.x_ball[1] = omni.x_ball[0];
					omni.y_ball[1] = omni.y_ball[0];
	 			}

				if (trackBox_obs.center.x >= 0 && trackBox_obs.center.y >= 0) 
				{
					omni.x_ball[0] = trackBox_obs.center.x;
					omni.y_ball[0] = trackBox_obs.center.y;

					omniobs.x_ball[1] = omniobs.x_ball[0];
					omniobs.y_ball[1] = omniobs.y_ball[0];
	 			}

				if (trackBox_omniball.size.width > 0 || trackBox_omniball.size.height > 0)
				{	
					if (omni.ball_area > 0)
					{
						// DRAW LINE AND CIRCLE TO BALL
						circle(result_lapangan, Point(trackBox_omniball.center.x,trackBox_omniball.center.y),omni.ball_radius, CV_RGB(255,0,120), 2,8,0);
						circle(result_lapangan, Point(trackBox_omniball.center.x,trackBox_omniball.center.y), 2, CV_RGB(60,255,100),2,8,0);

						line(result_lapangan, SetPoint, Point(trackBox_omniball.center.x,trackBox_omniball.center.y), CV_RGB(255,20,120), 2,8,0);
						line(result_lapangan, Point(trackBox_omniball.center.x,trackBox_omniball.center.y-(int)omni.ball_radius), Point(trackBox_omniball.center.x,trackBox_omniball.center.y-(int)(omni.ball_radius/3)),CV_RGB(100,50,250),2,3,0);
						line(result_lapangan, Point(trackBox_omniball.center.x-(int)omni.ball_radius,trackBox_omniball.center.y), Point(trackBox_omniball.center.x-(int)(omni.ball_radius/3),trackBox_omniball.center.y),CV_RGB(100,50,250),2,3,0);
						line(result_lapangan, Point(trackBox_omniball.center.x,trackBox_omniball.center.y+(int)(omni.ball_radius/3)), Point(trackBox_omniball.center.x,trackBox_omniball.center.y+(int)omni.ball_radius),CV_RGB(100,50,250),2,3,0);
						line(result_lapangan, Point(trackBox_omniball.center.x+(int)(omni.ball_radius/3),trackBox_omniball.center.y), Point(trackBox_omniball.center.x+(int)omni.ball_radius,trackBox_omniball.center.y),CV_RGB(100,50,250),2,3,0);

						putText(result_lapangan, format("BALL"), Point(trackBox_omniball.center.x-(int)(omni.ball_radius*5.6),trackBox_omniball.center.y), FONT_HERSHEY_SIMPLEX, 0.5, CV_RGB(255,255,255), 1);
						putText(result_lapangan, format("ANGLE=%d", (int) omni.angle), Point(trackBox_omniball.center.x-(int)(omni.ball_radius*7),trackBox_omniball.center.y+12), FONT_HERSHEY_PLAIN, 0.8, CV_RGB(255,255,255), 1);
						putText(result_lapangan, format("DIST=%d", (int)omni.dist), Point(trackBox_omniball.center.x-(int)(omni.ball_radius*7),trackBox_omniball.center.y+24), FONT_HERSHEY_PLAIN, 0.8, CV_RGB(255,255,255), 1);

						printf("Angle,Jarak,Luas,X,Y Bola = %d,%d,%d,%d,%d |", (int)omni.angle, (int)omni.dist, (int)omni.ball_area, (int)omni.x_ball[1], (int)omni.y_ball[1]);

// //						fprintf(serial_send, "17,%d,%d,%d,%d\n", (int)theta_obs_send, (int)jarak_obstacle_send , (int)jarak_obs_x_cm, (int)jarak_obs_y_cm);
// 						fprintf(serial_send, "7,%d,%d,%d,%d\n", (int)omni.dist, (int)omni.angle, (int)omni.x_ball[1], (int)omni.y_ball[1]);
// 						sprintf(message, "98,%d,%d,%d,%d,%d\n", (int)omni.dist, (int)omni.angle, (int)omni.ball_area, (int)omni.x_ball[1], (int)omni.y_ball[1]);
// 						write(fd, message, sizeof(message));
					}
					else 
					{
						omni.angle 		= 0;
						omni.dist 		= 0;
						omni.ball_area 	= 0;
						omni.x_ball[1] 	= 0;
						omni.y_ball[1] 	= 0;

						printf("Angle,Jarak,Luas,X,Y Bola = %d,%d,%d,%d,%d |", (int)omni.angle, (int)omni.dist, (int)omni.ball_area, (int)omni.x_ball[1], (int)omni.y_ball[1]);

// //						fprintf(serial_send, "17,%d,%d,%d,%d\n", (int) theta_obs_send, (int)jarak_obstacle_send, (int)jarak_obs_x_cm, (int)jarak_obs_y_cm);
// 						fprintf(serial_send, "7,%d,%d,%d,%d\n", (int)omni.dist, (int)omni.angle, (int)omni.x_ball[1], (int)omni.y_ball[1]);
// 						sprintf(message, "98,%d,%d,%d,%d,%d\n", (int)omni.dist, (int)omni.angle, (int)omni.ball_area, (int)omni.x_ball[1], (int)omni.y_ball[1]);
// 						write(fd, message, sizeof(message));
					}
				}

				else 
				{
					omni.angle 		= 0;
					omni.dist 		= 0;
					omni.ball_area 	= 0;
					omni.x_ball[1] 	= 0;
					omni.y_ball[1] 	= 0;

					circle(result_lapangan, trackBox_omniball.center, omni.ball_radius, CV_RGB(255,0,0), 2,8,0);		
	
					printf("Angle,Jarak,Luas,X,Y Bola = %d,%d,%d,%d,%d |", (int)omni.angle, (int)omni.dist, (int)omni.ball_area, (int)omni.x_ball[1], (int)omni.y_ball[1]);

// //					fprintf(serial_send, "17,%d,%d,%d,%d\n", (int) theta_obs_send, (int)jarak_obstacle_send, (int)jarak_obs_x_cm, (int)jarak_obs_y_cm);
// 					fprintf(serial_send, "7,%d,%d,%d,%d\n", (int)omni.dist, (int)omni.angle, (int)omni.x_ball[1], (int)omni.y_ball[1]);
// 					sprintf(message, "98,%d,%d,%d,%d,%d\n", (int)omni.dist, (int)omni.angle, (int)omni.ball_area, (int)omni.x_ball[1], (int)omni.y_ball[1]);
// 					write(fd, message, sizeof(message));
				}

				//ADD DRAW OBS
				if (trackBox_obs.size.width > 0 || trackBox_obs.size.height > 0)
				{	
					if (omniobs.ball_area > 0)
					{
						// DRAW LINE AND CIRCLE TO BALL
						circle(result_lapangan, Point(trackBox_obs.center.x,trackBox_obs.center.y),omniobs.ball_radius, CV_RGB(255,0,120), 2,8,0);
						circle(result_lapangan, Point(trackBox_obs.center.x,trackBox_obs.center.y), 2, CV_RGB(60,255,100),2,8,0);

						line(result_lapangan, SetPoint, Point(trackBox_obs.center.x,trackBox_obs.center.y), CV_RGB(255,20,120), 2,8,0);
						line(result_lapangan, Point(trackBox_obs.center.x,trackBox_obs.center.y-(int)omniobs.ball_radius), Point(trackBox_obs.center.x,trackBox_obs.center.y-(int)(omniobs.ball_radius/3)),CV_RGB(100,50,250),2,3,0);
						line(result_lapangan, Point(trackBox_obs.center.x-(int)omniobs.ball_radius,trackBox_obs.center.y), Point(trackBox_obs.center.x-(int)(omniobs.ball_radius/3),trackBox_obs.center.y),CV_RGB(100,50,250),2,3,0);
						line(result_lapangan, Point(trackBox_obs.center.x,trackBox_obs.center.y+(int)(omniobs.ball_radius/3)), Point(trackBox_obs.center.x,trackBox_obs.center.y+(int)omniobs.ball_radius),CV_RGB(100,50,250),2,3,0);
						line(result_lapangan, Point(trackBox_obs.center.x+(int)(omniobs.ball_radius/3),trackBox_obs.center.y), Point(trackBox_obs.center.x+(int)omniobs.ball_radius,trackBox_obs.center.y),CV_RGB(100,50,250),2,3,0);

						putText(result_lapangan, format("OBSTACLE"), Point(trackBox_obs.center.x-(int)(omniobs.ball_radius*5.6),trackBox_obs.center.y), FONT_HERSHEY_SIMPLEX, 0.5, CV_RGB(255,255,255), 1);
						putText(result_lapangan, format("ANGLE=%d", (int) omniobs.angle), Point(trackBox_obs.center.x-(int)(omniobs.ball_radius*7),trackBox_obs.center.y+12), FONT_HERSHEY_PLAIN, 0.8, CV_RGB(255,255,255), 1);
						putText(result_lapangan, format("DIST=%d", (int)omniobs.dist), Point(trackBox_obs.center.x-(int)(omniobs.ball_radius*7),trackBox_obs.center.y+24), FONT_HERSHEY_PLAIN, 0.8, CV_RGB(255,255,255), 1);

						printf("Angle,Jarak,Luas,X,Y Bola = %d,%d,%d,%d,%d |", (int)omniobs.angle, (int)omniobs.dist, (int)omniobs.ball_area, (int)omniobs.x_ball[1], (int)omniobs.y_ball[1]);

// //						fprintf(serial_send, "17,%d,%d,%d,%d\n", (int)theta_obs_send, (int)jarak_obstacle_send , (int)jarak_obs_x_cm, (int)jarak_obs_y_cm);
// 						fprintf(serial_send, "7,%d,%d,%d,%d\n", (int)omniobs.dist, (int)omniobs.angle, (int)omniobs.x_ball[1], (int)omniobs.y_ball[1]);
// 						sprintf(message, "98,%d,%d,%d,%d,%d\n", (int)omniobs.dist, (int)omniobs.angle, (int)omniobs.ball_area, (int)omniobs.x_ball[1], (int)omniobs.y_ball[1]);
// 						write(fd, message, sizeof(message));
					}
					else 
					{
						omniobs.angle 		= 0;
						omniobs.dist 		= 0;
						omniobs.ball_area 	= 0;
						omniobs.x_ball[1] 	= 0;
						omniobs.y_ball[1] 	= 0;

						printf("Angle,Jarak,Luas,X,Y Bola = %d,%d,%d,%d,%d |", (int)omniobs.angle, (int)omniobs.dist, (int)omniobs.ball_area, (int)omniobs.x_ball[1], (int)omniobs.y_ball[1]);

// //						fprintf(serial_send, "17,%d,%d,%d,%d\n", (int) theta_obs_send, (int)jarak_obstacle_send, (int)jarak_obs_x_cm, (int)jarak_obs_y_cm);
// 						fprintf(serial_send, "7,%d,%d,%d,%d\n", (int)omniobs.dist, (int)omniobs.angle, (int)omniobs.x_ball[1], (int)omniobs.y_ball[1]);
// 						sprintf(message, "98,%d,%d,%d,%d,%d\n", (int)omniobs.dist, (int)omniobs.angle, (int)omniobs.ball_area, (int)omniobs.x_ball[1], (int)omniobs.y_ball[1]);
// 						write(fd, message, sizeof(message));
					}
				}

				else 
				{
					omniobs.angle 		= 0;
					omniobs.dist 		= 0;
					omniobs.ball_area 	= 0;
					omniobs.x_ball[1] 	= 0;
					omniobs.y_ball[1] 	= 0;

					circle(result_lapangan, trackBox_obs.center, omniobs.ball_radius, CV_RGB(255,0,0), 2,8,0);		
	
					printf("Angle,Jarak,Luas,X,Y Bola = %d,%d,%d,%d,%d |", (int)omniobs.angle, (int)omniobs.dist, (int)omniobs.ball_area, (int)omniobs.x_ball[1], (int)omniobs.y_ball[1]);

// //					fprintf(serial_send, "17,%d,%d,%d,%d\n", (int) theta_obs_send, (int)jarak_obstacle_send, (int)jarak_obs_x_cm, (int)jarak_obs_y_cm);
// 					fprintf(serial_send, "7,%d,%d,%d,%d\n", (int)omniobs.dist, (int)omniobs.angle, (int)omniobs.x_ball[1], (int)omniobs.y_ball[1]);
// 					sprintf(message, "98,%d,%d,%d,%d,%d\n", (int)omniobs.dist, (int)omniobs.angle, (int)omniobs.ball_area, (int)omniobs.x_ball[1], (int)omniobs.y_ball[1]);
// 					write(fd, message, sizeof(message));
				}

			} // PENUTUP TRACKOBJECT

			if ((tcsetattr(serialPort,TCSANOW,&SerialPortSettings)) != 0) printf(" ERROR\n");
	   		else printf(" SENT\n");
		} // PENUTUP CALIBRATIONMODE

		ch = waitKey(2);
		// video.write(result_lapangan);
		if(show)
		{
			imshow(windowName1, result_lapangan);
			// imshow("CIRCLE", close_circle1);
			imshow(windowName2, result);
		}
//		else destroyWindow(window_name1); 
//		imshow("garis", result_line);
//		imshow("ConvexHull", sort_field);
//		imshow("field_obs", field_obs);
//		imshow("Contour", ImgCont);
//		imshow("HSL_mask", HSL_mask);
//		imshow("Thresh", threshP);
//		imshow("Morph", dilate1);
//		imshow("gradient", grad);
//		imshow("gambar", close_rect);
//		imshow("Canny", edges);
//		imshow("Proses", Gauss2); 
	} // PENUTUP WHILE

	cap.release();
	close(fd);
	unlink(dataaddr);
	fclose(serial_send);
	return (0);
}
