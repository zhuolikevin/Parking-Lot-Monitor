/**************************************************
 * Project: parkMonitor
 * File: motionDetector.h
 * Testing Environment: Ubuntu Linux 12.04
 * Author: Zhuo Li (Kevin)
 * Last Update: 
 **************************************************/
#ifndef _MOTIONDETECTOR_H_
#define _MOTIONDETECTOR_H_

#include <iostream>
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>

#define VERTITHRESHOLD 20    // threshold for vertical surround checking
#define HORITHRESHOLD 30     // threshold for horizontal surround checking
#define SURRTHRESHOLD 350    // threshold for surrounding area checking

using namespace cv;
using namespace std;

class motionDetector{
private:
  Mat originMat;          //original image matrix for drawing
  Mat workingMat;         //detecting image matrix
  int min_x, max_x; 	    //detected object range in x	
  int min_y, max_y;		    //detected object range in y
  Point centerP;          //the center of detected object
public:
  motionDetector(Mat& frameMat, Mat& grayMat, int xmin, int xmax, int ymin, int ymax);
  //virtual ~motionDetector();
  void locateMotion();
  bool checkSurround(int j, int i);
  void objectDrawing();
  bool checkOccupied(Point vertex1, Point vertex2, Point vertex3, Point vertex4);

};

#endif