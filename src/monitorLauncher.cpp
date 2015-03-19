/**************************************************
 * Project: parkMonitor
 * File: monitorLauncher.cpp
 * Testing Environment: Ubuntu Linux 12.04
 * Author: Zhuo Li (Kevin)
 * Last Update: 
 **************************************************/
#include "monitorLauncher.h"

/* application entry */
int main(int argc, char* argv[]){

  // Check for command line input
  if(argc > 2 || argc == 1){
    cout << "Running format:" << argv[0] << " <videoFileName>" << endl;
    exit(0);
  }

  /* new monitorLauncher object and run the monitor */
  monitorLauncher *Launcher = new monitorLauncher(argv[1]);
  Launcher->run();
  delete(Launcher);
  return 0;
}

/* constructor */
monitorLauncher::monitorLauncher(char* inputVideo){
  // add prefix to the video name
  string str(inputVideo);
  string prefix = "../res/";
  str = prefix + str;
  char* c = new char[str.length() + 1];
  strcpy(c, str.c_str());

  // open the video
  capture.open(str);
  if (!capture.isOpened()){
    cout << "Cannot open the video file" << endl;
    exit(0);
  }
}

/* run the launcher */
void monitorLauncher::run(){
  // new a frameHandler object to handle the frame
  frameHandler *handler = new frameHandler(capture);
  handler->getBackground();
  handler->handlerRun();
}

monitorLauncher::~monitorLauncher(){
  cout << "Parking lot monitor finished." << endl;
}