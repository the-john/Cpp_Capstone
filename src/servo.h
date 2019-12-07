#ifndef SERVO_H                                                                     // make sure header is not already defined
#define SERVO_H                                                                     // define header

//#include <iostream>                                                               // for debug
#include <opencv2/highgui.hpp>

// Function for cross hair placement
void servo(cv::Point frame, cv::Point target, cv::Mat& frameClone);

#endif