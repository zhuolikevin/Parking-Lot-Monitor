/**************************************************
 * Project: parkMonitor
 * File: frameHandler.cpp
 * Testing Environment: Ubuntu Linux 12.04
 * Author: Zhuo Li (Kevin)
 * Last Update: 
 **************************************************/
#include "frameHandler.h"
#include "mouseDetector.h"

/* constructor */
frameHandler::frameHandler(VideoCapture& inputCapture){
  capture = inputCapture;  
  logFile.open("../log/log.txt");
  //create a window to show the result
  namedWindow("Vedio",CV_WINDOW_AUTOSIZE); 
}

/* destructor */
frameHandler::~frameHandler(){
	logFile.close();
}

/* get the background image */
void frameHandler::getBackground(){

  // read the first frame for background detection
  capture >> FrameMat;
  cvtColor(FrameMat, bkGrayMat, CV_BGR2GRAY);
}

/* handle the video frame by frame */
void frameHandler::handlerRun(){
  bool statusFlag = false;
  time_t now = time(0);
  char* dt = ctime(&now);
  logFile << "Vacant time from " << dt;
  clock_t unoccupiedStart = clock();
  clock_t occupiedStart;

  parkingPoint = mouseDetector::getPoint();

  // Here we temporarily use fixed parking space
  Point pt1(325, 368);
  Point pt2(680, 115);
  Point pt3(532, 460);
  Point pt4(876, 183);

  while(capture.read(FrameMat)){
  	// get the foreground (the motion objects)
	getForeground();



	motionDetector *detector = new motionDetector(FrameMat, frGrayMat, frGrayMat.cols, 0, frGrayMat.rows, 0);
	
	detector->locateMotion();
	detector->objectDrawing();
	//if (detector->checkOccupied(pt1, pt2, pt3, pt4)){
	if (detector->checkOccupied(parkingPoint.at(0), parkingPoint.at(1), parkingPoint.at(2), parkingPoint.at(3))){
    if(!statusFlag){       // this is the parking into transition
	  	statusFlag = true;
	  	occupiedStart = clock();
	  	double vacDuration = (clock() - unoccupiedStart) / (double) CLOCKS_PER_SEC;

	  	now = time(0);
	  	dt = ctime(&now);
	  	logFile << " to " << dt;
	  	logFile << "Duration: " << vacDuration << "s" << endl;
	  	logFile << "Occupied time from " << dt;
	  }
	}else{	                 // this is the leaving transition
	  if(statusFlag){
	  	statusFlag = false;
	  	unoccupiedStart = clock();
	  	double occDuration = (clock() - occupiedStart) / (double) CLOCKS_PER_SEC;
	  	
	  	now = time(0);
	  	dt = ctime(&now);
	  	logFile << " to " << dt;
	  	logFile << "Duration: " << occDuration << "s" << endl;
	  	logFile << "Vacant time from " << dt;
	  }
	}

    // highlight the parking lot area
    line(FrameMat, parkingPoint.at(0), parkingPoint.at(1), Scalar(255,0,0), 5);
    line(FrameMat, parkingPoint.at(0), parkingPoint.at(2), Scalar(255,0,0), 5);
    line(FrameMat, parkingPoint.at(2), parkingPoint.at(3), Scalar(255,0,0), 5);
    line(FrameMat, parkingPoint.at(1), parkingPoint.at(3), Scalar(255,0,0), 5);

    // show the frame
    imshow("Vedio", FrameMat); 
      
    //wait for 'esc' key press for 30 ms. If 'esc' key is pressed, break loop
    if(waitKey(30) == 27){
      cout << "esc key is pressed by user" << endl; 
      break; 
    }
    
  }

 
  double vacDuration = (clock() - unoccupiedStart) / (double) CLOCKS_PER_SEC;	  	
  now = time(0);
  dt = ctime(&now);
  logFile << " to " << dt;
  logFile << "Duration: " << vacDuration << "s" << endl;
}

/* get foreground (motion object) */
void frameHandler::getForeground(){
  cvtColor(FrameMat, curGrayMat, CV_BGR2GRAY);
  absdiff(curGrayMat, bkGrayMat, frGrayMat);
  threshold(frGrayMat, frGrayMat, 35, 255, CV_THRESH_BINARY);
}

void frameHandler::detectMouse(){
  cout << "Please select the parking space with 4 clicks..." << endl;
  mouseDetector::setMat(FrameMat);
  namedWindow("parkingSpaceSelection", CV_WINDOW_AUTOSIZE);
  setMouseCallback("parkingSpaceSelection", mouseDetector::onMouse, 0);
  imshow("parkingSpaceSelection", mouseDetector::workingMat);
  waitKey(0);
}