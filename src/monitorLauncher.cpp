/**************************************************
 * Project: parkMonitor
 * File: monitorLauncher.cpp
 * Testing Environment: Ubuntu Linux 12.04
 * Author: Zhuo Li (Kevin)
 * Last Update: 
 **************************************************/
 
#include <stdio.h>
#include <iostream>
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>

using namespace std;
using namespace cv;
 
int main(int argc, char* argv[]){

  // Check for command line input
  if(argc > 2 || argc == 1){
    cout << "Running format:" << argv[0] << " <videoFileName>" << endl;
    exit(0);
  }

  // open the video file for reading
  VideoCapture capture(argv[1]); 
  if (!capture.isOpened()){
    cout << "Cannot open the video file" << endl;
    exit(0);
  }

  //create windows
  namedWindow("Vedio",CV_WINDOW_AUTOSIZE); 
  namedWindow("motion", CV_WINDOW_AUTOSIZE);
  //namedWindow("next", CV_WINDOW_AUTOSIZE);

  Mat FrameMat; 
  //Mat prevGrayMat;
  //Mat nextGrayMat;
  Mat curGrayMat;
  Mat bkGrayMat;
  Mat frGrayMat;

  Mat d1, d2, motionMat;

  // Erode kernel
  Mat kernel_ero = getStructuringElement(MORPH_RECT, Size(2,2));

  // read the first frame for background detection
  capture >> FrameMat;
  cvtColor(FrameMat, bkGrayMat, CV_BGR2GRAY);

  
  while(capture.read(FrameMat)){

    cvtColor(FrameMat, curGrayMat, CV_BGR2GRAY);
    absdiff(curGrayMat, bkGrayMat, frGrayMat);
    threshold(frGrayMat, frGrayMat, 35, 255, CV_THRESH_BINARY);
    imshow("motion", frGrayMat);
    //imshow("next", bkGrayMat);
    int number_of_changes = 0;
    int min_x = motionMat.cols, max_x = 0;
    int min_y = motionMat.rows, max_y = 0;
    // loop over image and detect changes
    for(int j = 0; j < motionMat.rows; j+=2){ // height
      for(int i = 0; i < motionMat.cols; i+=2){ // width
        // check if at pixel (j,i) intensity is equal to 255
        // this means that the pixel is different in the sequence
        // of images (prev_frame, current_frame, next_frame)
        if(motionMat.at<unsigned char>(j,i) == 255){
            number_of_changes++;
            if(min_x>i) min_x = i;
            if(max_x<i) max_x = i;
            if(min_y>j) min_y = j;
            if(max_y<j) max_y = j;
        }
      }
    }
    //cout << number_of_changes <<endl;
    if(number_of_changes){
      //check if not out of bounds
      if(min_x-10 > 0) min_x -= 10;
      if(min_y-10 > 0) min_y -= 10;
      if(max_x+10 < motionMat.cols-1) max_x += 10;
      if(max_y+10 < motionMat.rows-1) max_y += 10;
      // draw rectangle round the changed pixel
      Point x(min_x,min_y);
      Point y(max_x,max_y);
      Rect rect(x,y);
      //Mat cropped = result(rect);
      //cropped.copyTo(result_cropped);
      rectangle(FrameMat,rect,Scalar(0,255,255),5);
    }

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

  return 0;
}
