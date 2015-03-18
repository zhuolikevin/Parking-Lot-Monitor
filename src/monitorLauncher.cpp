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

    //capture.set(CV_CAP_PROP_POS_MSEC, 300); //start the video at 300ms
  //get the frames per seconds of the video
  double fps = capture.get(CV_CAP_PROP_FPS); 
  cout << "Frame per seconds : " << fps << endl;

  //create a window called "MyVideo"
  namedWindow("MyVideo",CV_WINDOW_AUTOSIZE); 

  while(1){
    Mat frame;

    // read a new frame from video
    bool bSuccess = capture.read(frame); 
    if (!bSuccess){
      cout << "Cannot read the frame from video file" << endl;
      break;
    }

    imshow("MyVideo", frame); //show the frame in "MyVideo" window

    //wait for 'esc' key press for 30 ms. If 'esc' key is pressed, break loop
    if(waitKey(30) == 27){
      cout << "esc key is pressed by user" << endl; 
      break; 
    }
  }

  return 0;
  /*
  //声明IplImage指针
  IplImage* pFrame = NULL; 
  IplImage* pFrImg = NULL;
  IplImage* pBkImg = NULL;
 
  CvMat* pFrameMat = NULL;
  CvMat* pFrMat = NULL;
  CvMat* pBkMat = NULL;
 
  CvCapture* pCapture = NULL;
 
  int nFrmNum = 0;
 
  //创建窗口
  cvNamedWindow("video", 1);
  cvNamedWindow("background",1);
  cvNamedWindow("foreground",1);
  //使窗口有序排列
  cvMoveWindow("video", 30, 0);
  cvMoveWindow("background", 360, 0);
  cvMoveWindow("foreground", 690, 0);
 
  // Check for command line input
  if(argc > 2 || argc == 1){
    cout << "Running format:" << argv[0] << " <videoFileName>" << endl;
    exit(0);
  }
 
  // Open the video file
  if(!(pCapture = cvCaptureFromFile(argv[1]))){
    cout << "Cannot find video " << argv[1] << endl;
    exit(0);
  }
 
  // Read from the video frame by frame
  while(pFrame = cvQueryFrame(pCapture)){
    nFrmNum++;
 
    // Initialization for the first frame
    if(nFrmNum == 1){
      pBkImg = cvCreateImage(cvSize(pFrame->width, pFrame->height),  IPL_DEPTH_8U,1);
	    pFrImg = cvCreateImage(cvSize(pFrame->width, pFrame->height),  IPL_DEPTH_8U,1);
 
	    pBkMat = cvCreateMat(pFrame->height, pFrame->width, CV_32FC1);
	    pFrMat = cvCreateMat(pFrame->height, pFrame->width, CV_32FC1);
	    pFrameMat = cvCreateMat(pFrame->height, pFrame->width, CV_32FC1);
 
	    //转化成单通道图像再处理
	    cvCvtColor(pFrame, pBkImg, CV_BGR2GRAY);
	    cvCvtColor(pFrame, pFrImg, CV_BGR2GRAY);
 
	    cvConvert(pFrImg, pFrameMat);
	    cvConvert(pFrImg, pFrMat);
	    cvConvert(pFrImg, pBkMat);
	  }else{
	    cvCvtColor(pFrame, pFrImg, CV_BGR2GRAY);
	    cvConvert(pFrImg, pFrameMat);
	    //高斯滤波先，以平滑图像
	    //cvSmooth(pFrameMat, pFrameMat, CV_GAUSSIAN, 3, 0, 0);
 
	    //当前帧跟背景图相减
	    cvAbsDiff(pFrameMat, pBkMat, pFrMat);
 
	    //二值化前景图
	    cvThreshold(pFrMat, pFrImg, 60, 255.0, CV_THRESH_BINARY);
 
	    //进行形态学滤波，去掉噪音  
	    //cvErode(pFrImg, pFrImg, 0, 1);
	    //cvDilate(pFrImg, pFrImg, 0, 1);
 
	    //更新背景
	    cvRunningAvg(pFrameMat, pBkMat, 0.003, 0);

	    //将背景转化为图像格式，用以显示
	    cvConvert(pBkMat, pBkImg);
 
	    //显示图像
	    cvShowImage("video", pFrame);
	    cvShowImage("background", pBkImg);
	    cvShowImage("foreground", pFrImg);
 
	    //如果有按键事件，则跳出循环
	    //此等待也为cvShowImage函数提供时间完成显示
	    //等待时间可以根据CPU速度调整
	    if( cvWaitKey(2) >= 0 )
        break;
    }
  }

  //销毁窗口
  cvDestroyWindow("video");
  cvDestroyWindow("background");
  cvDestroyWindow("foreground");
 
  //释放图像和矩阵
  cvReleaseImage(&pFrImg);
  cvReleaseImage(&pBkImg);
 
  cvReleaseMat(&pFrameMat);
  cvReleaseMat(&pFrMat);
  cvReleaseMat(&pBkMat);
 
  cvReleaseCapture(&pCapture);
 
  return 0;
  */
}
