#ifndef CAMLIB_H
#define CAMLIB_H

// Cek koneksi TTL
// dmesg | grep tty

//======================================== OPENCV LIB ===========================================//

#include "opencv2/features2d/features2d.hpp"
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/highgui.hpp>
#include <opencv/highgui.h>
#include <opencv2/core.hpp>
#include <opencv/cv.h>

//======================================== C/C++ LIB ===========================================//

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

//====================================== ENSPARTAN LIB =========================================//

#include "cal/cal.h"

#define idx		2
#define PI 		3.14159265
#define BUFLEN 	1024  	//Max length of buffer
#define PORT 	6363   	//The port on which to listen for incoming data
#define ON 		true
#define OFF 	false

using namespace cv;
using namespace std;

#endif