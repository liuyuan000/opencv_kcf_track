//
// Created by liuyuan on 2021/8/21.
//
#include <iostream>
#include <opencv2/opencv.hpp>
#include "kcftracker.hpp"

using namespace std;
using namespace cv;

int main(){

    Mat frame;
    Rect ROI;
    Rect result;
    int key;
    bool HOG = true;
    bool FIXEDWINDOW = false;
    bool MULTISCALE = true;
    bool LAB = false;

    VideoCapture capture("/home/liuyuan/CLionProjects/KCFcpp-master/video.mp4");
    VideoWriter outputVideo;
    Size S = Size((int) capture.get(CAP_PROP_FRAME_WIDTH),    // Acquire input size
                  (int) capture.get(CAP_PROP_FRAME_HEIGHT));
    outputVideo.open("/home/liuyuan/CLionProjects/KCFcpp/result01.mp4", VideoWriter::fourcc('M', 'J', 'P', 'G'), capture.get(CAP_PROP_FPS), S, true);

    capture.read(frame);
    ROI = selectROI(frame);
    cout<< ROI<<endl;

    KCFTracker tracker(HOG, FIXEDWINDOW, MULTISCALE, LAB);
    tracker.init( ROI, frame );

    while (capture.isOpened()){
        capture.read(frame);
        if(frame.empty())
            break;
        result = tracker.update(frame);
        rectangle( frame, Point( result.x, result.y ), Point( result.x+result.width, result.y+result.height), Scalar( 0, 255, 255 ), 1, 8 );
        outputVideo << frame;
        imshow("video", frame);
        key = waitKey(10);
        if(key==27)
            break;
    }
    capture.release();
    outputVideo.release();
    destroyAllWindows();
}
