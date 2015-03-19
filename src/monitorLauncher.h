#ifndef _MONITORLAUNCHER_H_
#define _MONITORLAUNCHER_H_

#include <iostream>
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>

class monitorLauncher{
private:
	char* videoName;
	
public:
	monitorLauncher(char* inputVideo);
	virtual ~monitorLauncher();
	void run();
};

#endif 