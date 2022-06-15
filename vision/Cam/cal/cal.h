#ifndef CAL_H
#define CAL_H

#include "../camLib.h"

#define ON 		true
#define OFF 	false

using namespace cv;
using namespace std;

int LowH[20], LowS[20], LowV[20], HighH[20], HighS[20], HighV[20];

int p 		= 0;

bool show 						= true;
bool detectFlag 				= OFF;
bool calibrationBall 			= OFF;
bool calibrationField		 	= OFF;
bool calibBallWindow 			= false;
bool calibFieldWindow 			= false;
bool calibrationMode 			= OFF;
bool calibrationModeGoalpost 	= OFF;
bool mouseIsDragging 			= OFF;
bool mouseMove 					= OFF;
bool rectangleSelected 			= OFF;
bool objectFound 				= OFF;

Rect rectangleROI;

vector<int> H_ROI, S_ROI, V_ROI;

Point initialClickPoint, currentMousePoint;

void recordHSV_Values(cv::Mat frame, cv::Mat hsv_frame);
void clickAndDrag_Rectangle(int event, int x, int y, int flags, void* param);

#endif