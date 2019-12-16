//#include <iostream>                                                                                         // include for debug
#include <opencv2/imgproc.hpp>
#include <thread>
#include "fceMrk.h"

// Class for FaceMarking
FaceMarking::FaceMarking(std::vector<cv::Rect>& faces, double scale, cv::Mat& matFrame) : _faces(faces), _scale(scale), _matFrame(matFrame)     // constructor
{                                                                                 
    //std::cout << "CREATING instance of FaceMarking at " << this << std::endl;
    for (size_t i = 0; i < _faces.size(); i++) {                                                            // pick out the various faces stored in the vector
        cv::Rect r = _faces[i];                                                                             // rectangle object from face recognition algorithm
        
        //std::vector<cv::Rect> nestedBoxes;                                                                // rectangles to box faces in image
        cv::Point center;                                                                                   // the definition for a 2-D point in the image
        cv::Scalar red = cv::Scalar(0, 0, 255);                                                             // drawing tool color passed via Scalar for red
        center.x = cvRound((r.x + r.width * 0.5) * _scale);                                                 // round fp number to nearest integer
        center.y = cvRound((r.y + r.height * 0.5) * _scale);                                                // round fp number to nearest integer
        cv::drawMarker(_matFrame, center, red, 0, 30, 2, 8);                                                // draw cross-hairs where robot should be looking
    }
}
FaceMarking::~FaceMarking(){                                                                                // destructor
    //std::cout << "DELETING instance of FaceMarking at " << this << std::endl;
}

void FaceMarking::operator()() {}
