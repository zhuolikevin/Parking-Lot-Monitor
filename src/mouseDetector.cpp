/**************************************************
 * Project: parkMonitor
 * File: mouseDetector.cpp
 * Testing Environment: Ubuntu Linux 12.04
 * Author: Zhuo Li (Kevin)
 * Last Update: 
 **************************************************/
#include "mouseDetector.h"

Mat mouseDetector::workingMat;
int mouseDetector::n = TOTAL_POINTS;
vector<Point> mouseDetector::capturePoint = vector<Point>();

/*
mouseDetector::mouseDetector(Mat& inputMat){

}*/
/*
mouseDetector::~mouseDetector(){

}*/

void mouseDetector::onMouse(int event, int x, int y, int, void*){
	//namedWindow("test", CV_WINDOW_AUTOSIZE);
	//imshow("test", mouseDetector::workingMat);
	Point pt;
	if (event == CV_EVENT_LBUTTONDOWN){
		pt.x = x;
		pt.y = y;
		cout << "Point" << TOTAL_POINTS + 1 - n << "(" << x << "," << y << ")" << endl;
		mouseDetector::capturePoint.push_back(pt);
        mouseDetector::n--;
        //circle(mouseDetector::workingMat,pt,2,Scalar(0,0,255), 5);
        if(n==0){
	       cvDestroyAllWindows();
        }
	}
}

void mouseDetector::setMat(Mat& inputMat){
	mouseDetector::workingMat = inputMat;
}

vector<Point> mouseDetector::getPoint(){
	return capturePoint;
}

