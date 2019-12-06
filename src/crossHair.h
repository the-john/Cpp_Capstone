#ifndef CROSSHAIR_H                                                             // make sure header is not already defined
#define CROSSHAIR_H                                                             // define header

#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>

// Function for cross hair placement
void crossHair(std::vector<cv::Rect>& faces, double scale, cv::Mat img);

#endif