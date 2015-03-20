# parkMonitor #

> Application Name: parkMonitor

> Author Name: Zhuo Li (Kevin)

> Platform: Ubuntu Linux 12.04
 
> Late Updated: 

This is a simple application of parking lot monitor written in C++ based on OpenCV. It can read from the video file (can be replaced by camera) and decide the time period during which the parking space is occupied or not. The detected motion vehicle and parking space are highlighted in windows during the program running. A log file which record the parking lot information is saved.

## A. Running Instruction ##

The source codes are in `src/` directory and the testing video is in `res` directory. You can run the program as following:

1.	enter `src/` directory.
	
		$ cd src/

2.	compile the codes using the written Makefile.

		$ make

3.	clean up the intermediate object files.(Optional)

		$ make clean

4.	run the program.

		$ ./parkMonitor parking.avi

	Then you can see the car parking video. The blue line segments composed an area which records the parking space.(Currently we just define the space, and the later version should support an interface for user to define the space at the initialization stage) The yellow rectangle highlights the moving car and the green point is the center of the car.

5.	you can use your text editro to see the result log file.

		$ <your_editor> ../log/log.txt

## B. Structure of the Source Codes ##




