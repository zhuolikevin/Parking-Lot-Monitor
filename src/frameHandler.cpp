/**************************************************
 * Project: parkMonitor
 * File: frameHandler.cpp
 * Testing Environment: Ubuntu Linux 12.04
 * Author: Zhuo Li (Kevin)
 * Last Update: 
 **************************************************/
#include "frameHandler.h"

frameHandler::frameHandler(VideoCapture& inputCapture){
	capture = inputCapture;  
	//create windows
  	namedWindow("Vedio",CV_WINDOW_AUTOSIZE); 
}

void frameHandler::getBackground(){
	// read the first frame for background detection
  	capture >> FrameMat;
  	cvtColor(FrameMat, bkGrayMat, CV_BGR2GRAY);
}

void frameHandler::handlerRun(){
	while(capture.read(FrameMat)){
		getForeground();
	/*
    cvtColor(FrameMat, curGrayMat, CV_BGR2GRAY);
    absdiff(curGrayMat, bkGrayMat, frGrayMat);
    threshold(frGrayMat, frGrayMat, 35, 255, CV_THRESH_BINARY);
	*/
    int min_x = frGrayMat.cols, max_x = 0;
    int min_y = frGrayMat.rows, max_y = 0;
    // loop over image and detect changes
    for(int j = 0; j < frGrayMat.rows; j+=2){ // height
      for(int i = 0; i < frGrayMat.cols; i+=2){ // width
        // check if at pixel (j,i) intensity is equal to 255
        if(frGrayMat.at<unsigned char>(j,i) == 255){
            if(checkSurround(frGrayMat, j, i)){
              if(min_x>i) min_x = i;
              if(max_x<i) max_x = i;
              if(min_y>j) min_y = j;
              if(max_y<j) max_y = j;
            }
        }
      }
    }
    
    Point x(min_x,min_y);
    Point y(max_x,max_y);
    Rect rect(x,y);
    rectangle(FrameMat,rect,Scalar(0,255,255),5);

    // highlight the parking lot area
    Point pt1(325, 368);
    Point pt2(680, 115);
    Point pt3(532, 460);
    Point pt4(876, 183);
    line(FrameMat, pt1, pt2, Scalar(255,0,0), 5);
    line(FrameMat, pt1, pt3, Scalar(255,0,0), 5);
    line(FrameMat, pt3, pt4, Scalar(255,0,0), 5);
    line(FrameMat, pt2, pt4, Scalar(255,0,0), 5);


    imshow("Vedio", FrameMat); 
      
    //wait for 'esc' key press for 30 ms. If 'esc' key is pressed, break loop
    if(waitKey(30) == 27){
      cout << "esc key is pressed by user" << endl; 
      break; 
    }
    
  }
}

void frameHandler::getForeground(){
	cvtColor(FrameMat, curGrayMat, CV_BGR2GRAY);
    absdiff(curGrayMat, bkGrayMat, frGrayMat);
    threshold(frGrayMat, frGrayMat, 35, 255, CV_THRESH_BINARY);
}

bool frameHandler::checkSurround(Mat& inputMat, int j, int i){
	int pointCounter = 0;
  	int vertiThreshold = 20;
  	int horiThreshold = 30;
  	for(int m=max(0,j-vertiThreshold);m<min(inputMat.rows,j+horiThreshold);m+=2){
   		for(int n=max(0,i-horiThreshold);n<min(inputMat.cols,i+horiThreshold);n+=2){
      		if(inputMat.at<unsigned char>(m,n) == 255){
        		pointCounter++; 
      		}
    	}
  	}
  	return true ?(pointCounter >= 350):false;
}