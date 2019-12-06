#ifndef FACE_H                                                                  // make sure header is not already defined
#define FACE_H                                                                  // define header

//#include <iostream>
#include <opencv2/objdetect.hpp>
//#include <opencv2/highgui.hpp>
//#include <opencv2/imgproc.hpp>

// Function for face detection
void detect(cv::Mat img, cv::CascadeClassifier& cascade, double scale);

#endif