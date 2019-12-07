#ifndef XYVECTOR_H                                                                  // make sure header is not already defined
#define XYVECTOR_H                                                                  // define header

//#include <iostream>                                                               // for debug
#include <opencv2/imgproc.hpp>

// Function for cross hair placement
void xyVector(std::vector<cv::Rect>& faces, double scale, cv::Mat& frameClone);

#endif