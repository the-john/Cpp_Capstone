//#include <iostream>                                                                                   // include for debug
#include <opencv2/highgui.hpp>
#include "img.h"

// Function for cross hair placement
void showImg(cv::Mat& frameClone) 
{
    cv::imshow("Robot Face Detection & Tracking", frameClone);                                          // show marked image
}