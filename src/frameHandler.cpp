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
  	// get the foreground (the motion objects)
	getForeground();

	motionDetector *detector = new motionDetector(FrameMat, frGrayMat, frGrayMat.cols, 0, frGrayMat.rows, 0);
	
	detector->locateMotion();
	detector->objectDrawing();

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
