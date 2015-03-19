/**************************************************
 * Project: parkMonitor
 * File: frameHandler.h
 * Testing Environment: Ubuntu Linux 12.04
 * Author: Zhuo Li (Kevin)
 * Last Update: 
 **************************************************/
#ifndef _FRAMEHANDLER_H_
#define _FRAMEHANDLER_H_

#include <iostream>
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>

using namespace cv;
using namespace std;

class frameHandler{
private:
	VideoCapture capture;
	Mat FrameMat; 
  	Mat curGrayMat;
  	Mat bkGrayMat;
  	Mat frGrayMat;
public:
	frameHandler(VideoCapture& inputCapture);
	//virtual ~frameHandler();
	void handlerRun();
	void getBackground();
	void getForeground();
	bool checkSurround(Mat& inputMat, int j, int i);
};

#endif 