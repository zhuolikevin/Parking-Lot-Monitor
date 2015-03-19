/**************************************************
 * Project: parkMonitor
 * File: monitorLauncher.h
 * Testing Environment: Ubuntu Linux 12.04
 * Author: Zhuo Li (Kevin)
 * Last Update: 
 **************************************************/
#ifndef _MONITORLAUNCHER_H_
#define _MONITORLAUNCHER_H_

#include <iostream>
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>

using namespace cv;
using namespace std;

class monitorLauncher{
private:
	VideoCapture capture;

public:
	monitorLauncher(char* inputVideo);
	virtual ~monitorLauncher();
	void run();
	bool checkSurround(Mat& inputMat, int j, int i);
};

#endif  