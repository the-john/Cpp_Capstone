//#include <iostream>                                                                                         // for debugging
#include <opencv2/objdetect.hpp>
#include "face.h"
#include "crossHair.h"
#include "xyVector.h"
#include "img.h"

void detect(cv::Mat& frameClone, cv::CascadeClassifier& cascade, double scale) 
{
    std::vector<cv::Rect> faces;
    cv::Mat grayImg;
    cv::Mat shrinkImg;
        
    cv::cvtColor(frameClone, grayImg, cv::COLOR_BGR2GRAY);                                                  // convert to gray scale

    // Recude the size of the gray image by "fx" and feed that to the face detection algorithm; a reduced size will compute MUCH faster
    double fx = 1 / scale;

    cv::resize(grayImg, shrinkImg, cv::Size(), fx, fx, cv::INTER_LINEAR);                                   // resize the grayscale image, nearest-neighbor interpolation
    cv::equalizeHist(shrinkImg, shrinkImg);                                                                 // increase contrast of smallImg via histogram equalization
    
    cascade.detectMultiScale(shrinkImg, faces, 1.1, 2, 0|cv::CASCADE_SCALE_IMAGE, cv::Size(50, 80));        // detect faces of different sizes useing cascade classifier (30, 30)
    
    crossHair(faces, scale, frameClone);                                                                    // place a cross hair on the middle of the face
    xyVector(faces, scale, frameClone);                                                                     // show offset vector from center of image to center of face
    
    showImg(frameClone);
}
