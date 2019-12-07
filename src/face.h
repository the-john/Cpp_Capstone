#ifndef FACE_H                                                                  // make sure header is not already defined
#define FACE_H                                                                  // define header

//#include <iostream>                                                           // for debugging
#include <opencv2/objdetect.hpp>

// Function for face detection
void detect(cv::Mat& frameClone, cv::CascadeClassifier& cascade, double scale);

#endif