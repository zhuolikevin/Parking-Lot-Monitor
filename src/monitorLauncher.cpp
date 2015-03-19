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

#define PI 3.1415926

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

    
  //get the frames per seconds of the video
  double fps = capture.get(CV_CAP_PROP_FPS); 
  cout << "Frame per seconds : " << fps << endl;

  //create windows
  namedWindow("Vedio",CV_WINDOW_AUTOSIZE); 
  namedWindow("Edges",CV_WINDOW_AUTOSIZE);
  //namedWindow("background", CV_WINDOW_AUTOSIZE);
  //namedWindow("foreground", CV_WINDOW_AUTOSIZE);

  Mat EdgeMat;
  Mat FrameMat;
  Mat BkMat;
  Mat FrMat;
  Mat curGrayMat;

  // read the first frame for background detection
  capture >> FrameMat;

  cvtColor(FrameMat, BkMat, CV_BGR2GRAY);
  cvtColor(FrameMat, FrMat, CV_BGR2GRAY);
  GaussianBlur(BkMat, EdgeMat, Size(17,17), 1.7, 1.7);
  Canny(EdgeMat, EdgeMat, 400, 300, 3);
  threshold(EdgeMat, EdgeMat, 60, 255.0, CV_THRESH_BINARY);
/*
  vector<Vec2f> lines;  
  //调用函数  
  HoughLines(EdgeMat,lines,1,PI/180,80);  
  //展示结果的图像  
  Mat result;  
  //EdgeMat.copyTo(result);  
  cout<<"共检测出线："<<lines.size()<<"条"<<std::endl;  
  //画出结果  
  vector<Vec2f>::const_iterator it = lines.begin();  
  while(it != lines.end()){  
    float rho = (*it)[0];  
    float theta=(*it)[1];  
    if(theta < PI/4. || theta > 3. *PI / 4.){  
        //接近于垂直线条  
        Point pt1(rho/cos(theta),0);  
        Point pt2((rho-EdgeMat.rows*sin(theta))/cos(theta),EdgeMat.rows);  
        line(EdgeMat,pt1,pt2,Scalar(255),1);  
    }else{  
        //接近于水平线  
        Point pt1(0,rho/sin(theta));  
        Point pt2(EdgeMat.cols,(rho-EdgeMat.cols*cos(theta))/sin(theta));  
        line(EdgeMat,pt1,pt2,Scalar(255),1);  
    }  
    ++it;  
  }  
*/
  //imshow("Edges", EdgeMat);
  //imshow("Edges", result);

  while(capture.read(FrameMat)){

      cvtColor(FrameMat, curGrayMat, CV_BGR2GRAY);
      absdiff(curGrayMat, BkMat, FrMat);
      /*
      vector<Vec2f>::const_iterator it = lines.begin(); 
      while(it != lines.end()){  
        float rho = (*it)[0];  
        float theta=(*it)[1];  
        if(theta < PI/4. || theta > 3. *PI / 4.){  
          //接近于垂直线条  
          Point pt1(rho/cos(theta),0);  
          Point pt2((rho-EdgeMat.rows*sin(theta))/cos(theta),EdgeMat.rows);  
          line(FrameMat,pt1,pt2,Scalar(255),1);  
        }else{  
          //接近于水平线  
          Point pt1(0,rho/sin(theta));  
          Point pt2(EdgeMat.cols,(rho-EdgeMat.cols*cos(theta))/sin(theta));  
          line(FrameMat,pt1,pt2,Scalar(255),1);  
        }  
        ++it;  
      }   
      */
      Point pt1(325, 368);
      Point pt2(680, 115);
      Point pt3(532, 460);
      Point pt4(876, 183);
      line(FrameMat, pt1, pt2, Scalar(255,0,0), 5);
      line(FrameMat, pt1, pt3, Scalar(255,0,0), 5);
      line(FrameMat, pt3, pt4, Scalar(255,0,0), 5);
      line(FrameMat, pt2, pt4, Scalar(255,0,0), 5);

      imshow("Vedio", FrameMat); 
      //imshow("background", BkMat);
      //imshow("foreground", FrMat);
      
      //wait for 'esc' key press for 30 ms. If 'esc' key is pressed, break loop
      if(waitKey(30) == 27){
        cout << "esc key is pressed by user" << endl; 
        break; 
      //}
    }

    //cvtColor(FrameMat, edges, CV_BGR2GRAY);

    //


    //

    //

    //imshow("Edges", edges);
    
  }

  return 0;
  /*

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
