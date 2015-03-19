CFLAGS = -Wall -g -I/usr/local/include/opencv -I/usr/local/include/opencv2 -L/usr/local/lib/ -lopencv_core -lopencv_highgui -lopencv_imgproc 

# These are other liblinks of opencv unused here
#-lopencv_ml -lopencv_video -lopencv_features2d -lopencv_calib3d -lopencv_objdetect -lopencv_contrib -lopencv_legacy -lopencv_stitching 

all: parkMonitor

parkMonitor: monitorLauncher.o frameHandler.o motionDetector.o
	g++ -o parkMonitor monitorLauncher.o frameHandler.o motionDetector.o ${CFLAGS}

motionDetector.o: motionDetector.cpp motionDetector.h
	g++ -c motionDetector.cpp ${CFLAGS}

frameHandler.o: frameHandler.cpp frameHandler.h motionDetector.h
	g++ -c frameHandler.cpp ${CFLAGS}

monitorLauncher.o: monitorLauncher.cpp monitorLauncher.h frameHandler.h
	g++ -c monitorLauncher.cpp ${CFLAGS}

clean:
	rm -rf *.o
