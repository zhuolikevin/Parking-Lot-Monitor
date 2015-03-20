/**************************************************
 * Project: parkMonitor
 * File: motionDetector.cpp
 * Testing Environment: Ubuntu Linux 12.04
 * Author: Zhuo Li (Kevin)
 * Last Update: 
 **************************************************/
#include "motionDetector.h"

/* constructor */
motionDetector::motionDetector(Mat& frameMat, Mat& grayMat, int xmin, int xmax, int ymin, int ymax){
  originMat = frameMat;
  workingMat = grayMat;
  min_x = xmin;
  max_x = xmax;
  min_y = ymin;
  max_y = ymax;
}

/* locate the moving object */
void motionDetector::locateMotion(){
  // loop over image and detect changes
  for(int j = 0; j < workingMat.rows; j+=2){ // height
    for(int i = 0; i < workingMat.cols; i+=2){ // width
      // check if at pixel (j,i) intensity is equal to 255
      if(workingMat.at<unsigned char>(j,i) == 255){
        if(checkSurround(j, i)){
          if(min_x>i) min_x = i;
          if(max_x<i) max_x = i;
          if(min_y>j) min_y = j;
          if(max_y<j) max_y = j;
        }
      }  
    }   
  }
}

/* check surrounding, only when there are enough surroungding moving pixels will this be the object*/
bool motionDetector::checkSurround(int j, int i){
  int pointCounter = 0;
  for(int m=max(0,j-VERTITHRESHOLD);m<min(workingMat.rows,j+VERTITHRESHOLD);m+=2){
   	for(int n=max(0,i-HORITHRESHOLD);n<min(workingMat.cols,i+HORITHRESHOLD);n+=2){
      if(workingMat.at<unsigned char>(m,n) == 255){
        pointCounter++; 
      }
    }
  }
  return true ?(pointCounter >= SURRTHRESHOLD):false;
}

/* find out if the moving object is in the parking space */
bool motionDetector::checkOccupied(Point vertex1, Point vertex2, Point vertex3, Point vertex4){
  //cout << "(" << centerP.x << "," << centerP.y << ")" << endl;
  if(((centerP.x - vertex3.x) * (vertex4.y - vertex3.y) + (vertex4.x - vertex3.x) * vertex3.y \
  	   >= centerP.y * (vertex4.x - vertex3.x)) && \
  	 ((centerP.x - vertex1.x) * (vertex2.y - vertex1.y) + (vertex2.x - vertex1.x) * vertex1.y \
  	   <= centerP.y * (vertex2.x - vertex1.x)) && \
  	 ((centerP.x - vertex3.x) * (vertex1.y - vertex3.y) + (vertex1.x - vertex3.x) * vertex3.y \
  	   <= centerP.y * (vertex1.x - vertex3.x)) && \
  	 ((centerP.x - vertex4.x) * (vertex2.y - vertex4.y) + (vertex2.x - vertex4.x) * vertex4.y \
  	   >= centerP.y * (vertex2.x - vertex4.x)) && \
  	 (centerP.x != workingMat.cols/2 && centerP.y != workingMat.rows/2)){
  	return true;
  }else{
  	return false;
  }
}

/* draw the center and a rectangle for the moving object */
void motionDetector::objectDrawing(){
  centerP.x = (min_x + max_x) / 2;
  centerP.y = (min_y + max_y) / 2;
  if (centerP.x != workingMat.cols/2 && centerP.y != workingMat.rows/2){
  	circle(originMat, centerP, 1, Scalar(0,255,0), 5);

  	Point x(min_x,min_y);
  	Point y(max_x,max_y);
  	Rect rect(x,y);
  	rectangle(originMat,rect,Scalar(0,255,255),5);
  }
}