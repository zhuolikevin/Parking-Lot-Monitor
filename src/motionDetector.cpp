/**************************************************
 * Project: parkMonitor
 * File: motionDetector.cpp
 * Testing Environment: Ubuntu Linux 12.04
 * Author: Zhuo Li (Kevin)
 * Last Update: 
 **************************************************/
#include "motionDetector.h"

motionDetector::motionDetector(Mat& frameMat, Mat& grayMat, int xmin, int xmax, int ymin, int ymax){
  originMat = frameMat;
  workingMat = grayMat;
  min_x = xmin;
  max_x = xmax;
  min_y = ymin;
  max_y = ymax;
}

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

bool motionDetector::checkSurround(int j, int i){
  int pointCounter = 0;
  int vertiThreshold = 20;
  int horiThreshold = 30;
  for(int m=max(0,j-vertiThreshold);m<min(workingMat.rows,j+horiThreshold);m+=2){
   	for(int n=max(0,i-horiThreshold);n<min(workingMat.cols,i+horiThreshold);n+=2){
      if(workingMat.at<unsigned char>(m,n) == 255){
        pointCounter++; 
      }
    }
  }
  return true ?(pointCounter >= 350):false;
}

void motionDetector::objectDrawing(){
  Point x(min_x,min_y);
  Point y(max_x,max_y);
  Rect rect(x,y);
  rectangle(originMat,rect,Scalar(0,255,255),5);
}