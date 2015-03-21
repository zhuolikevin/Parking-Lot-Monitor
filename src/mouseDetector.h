/**************************************************
 * Project: parkMonitor
 * File: mouseDetector.h
 * Testing Environment: Ubuntu Linux 12.04
 * Author: Zhuo Li (Kevin)
 * Last Update: 
 **************************************************/
#ifndef _MOUSEDETECTOR_H_
#define _MOUSEDETECTOR_H_

#include <iostream>
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>

#define TOTAL_POINTS 4

using namespace cv;
using namespace std;

class mouseDetector{
public:
	static Mat workingMat;			     // working matrix
	static vector<Point> capturePoint;   // detected 
	static int n;                        // click times
public:
	//mouseDetector(Mat& inputMat);
	//virtual ~mouseDetector();
	static void onMouse(int event, int x, int y, int, void*);
	static vector<Point> getPoint();
	static void setMat(Mat& inputMat);
};

#endif