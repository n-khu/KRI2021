#include "cal.h"


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
	}
    
  	if (mouseMove) rectangle(frame, initialClickPoint, cv::Point(currentMousePoint.x, currentMousePoint.y), cv::Scalar(255,0,0), 1,8,0);
}

void clickAndDrag_Rectangle(int event, int x, int y, int flags, void* param)
{
    if (calibrationBall|| calibrationField)
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
        }      
    }    
}

