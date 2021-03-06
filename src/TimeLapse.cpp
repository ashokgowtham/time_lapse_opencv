#include "stdio.h"
#include "string.h"
#include "unistd.h"
#include <opencv/highgui.h>
#include <opencv2/opencv.hpp>

char DEFAULT_OUTPUT_FODLER[] = ".";
int DEFAULT_TIME_INTERVAL = 1;
int DEFAULT_CAMERA = 0;

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
    int cameraId = DEFAULT_CAMERA;
    int currentFileCount = 1;
    bool writeVideo = false;
    int outputVideoFps = 24;

    printf("Usage: <[image]|video> <outputFolder[\".\"]> <timeInterval[1]> <camera[0]>\nRunning with defaults...\n");

    if(argc>1) writeVideo = strcmp(argv[1],"video")==0;
    if(argc>2) outputFolder = argv[2];
    if(argc>3) sscanf(argv[3], "%d", &timeInterval);
    if(argc>4) sscanf(argv[4], "%d", &cameraId);


    Mat frame;
    //open input
    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    //open output
    VideoWriter outputVideo;    // Open the output
    if(writeVideo)
    {
        cap >> frame;               // get a new frame from camera to determine output video size
        outputVideo.open("./videoFile.mp4", -1, outputVideoFps, frame.size(), true);
        if (!outputVideo.isOpened())
        {
            printf("Could not open the output video for write.\n");
            return -1;
        }
    }
    namedWindow("preview", CV_WINDOW_AUTOSIZE);
    for(;;)
    {
        cap >> frame; // get a new frame from camera
        imshow("preview", frame);
        if (writeVideo)
        {
            outputVideo << frame;
        }
        else
        {
            writeOutputImage(frame, outputFolder, currentFileCount++);
        }
        if(waitKey(27) >= 0) break;
        sleep(timeInterval);
    }
    return 0;
}