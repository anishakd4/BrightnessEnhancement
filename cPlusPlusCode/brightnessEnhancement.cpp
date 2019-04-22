#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main(){

    //Read image
    Mat image = imread("../assets/putin.jpg");
    
    Mat imageYcb;

    //Convert to YCrCb color space
    cvtColor(image, imageYcb, COLOR_BGR2YCrCb);

    //Convert to float32
    imageYcb.convertTo(imageYcb, CV_32F);

    vector<Mat> channels;

    //split into channels
    split(imageYcb, channels);

    //specify offset factor
    int beta = 100;

    //Add offset to the Y channel
    channels[0] = channels[0] + beta;
    
    //make sure the pixel values range between 0 and 255
    min(channels[0], 255, channels[0]);
    max(channels[0], 0, channels[0]);

    //merge the channels
    merge(channels, imageYcb);

    //convert back from float32
    imageYcb.convertTo(imageYcb, CV_8UC3);

    //convert back to BGR color space
    cvtColor(imageYcb, imageYcb, COLOR_YCrCb2BGR);

    //create windows to diplay images
    namedWindow("image", WINDOW_NORMAL);
    namedWindow("result", WINDOW_NORMAL);

    //Display windows
    imshow("image", image);
    imshow("result", imageYcb);

    //Press esc to exit the program
    waitKey(0);
    
    //close all the opened windows
    destroyAllWindows();

    return 0;
}