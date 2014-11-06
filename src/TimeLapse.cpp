#include "stdio.h"
#include "stdlib.h"
#include <opencv/highgui.h>
#include <opencv2/opencv.hpp>

char DEFAULT_OUTPUT_FODLER[] = ".";
int DEFAULT_TIME_INTERVAL = 1;

using namespace cv;
void writeOutputImage(Mat& image, char *folder, int fileNumber) {
	char path[1024] = {};
	sprintf(path, "%s/image%04d.jpg", folder, fileNumber);
	imwrite(path, image );
}

int main( int argc, char** argv )
{

	char *outputFolder = DEFAULT_OUTPUT_FODLER;
	int timeInterval = DEFAULT_TIME_INTERVAL;
	int currentFileCount = 1;

	// if(argc != 2)
	// {
	// 	printf("Usage: <timeInterval> <outputFolder>\n");
	// 	return -1;
	// }

	if(argc>1) outputFolder = argv[1];
	if(argc>2) sscanf(argv[2], "%d", &timeInterval);



	VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    namedWindow("preview", CV_WINDOW_AUTOSIZE);
    for(;;)
    {
        Mat frame;
        cap >> frame; // get a new frame from camera
        imshow("preview", frame);
       	writeOutputImage(frame, outputFolder, currentFileCount++);
        sleep(timeInterval);
	}
	return 0;
}