//#include <iostream>                                                                                    // include for debug
#include <opencv2/imgproc.hpp>
#include "xyVector.h"
#include "srvVctrs.h"

// Class for Facemark Vector

// Here we generate a vector that indicates the difference between the center of the image, and the center of each detected face.
// Because the robot head gimbal has a comparitively slow response time, its physical movement will integrate all of the face difference vectors together.
// This integration will enable the gimbal to atain an "average" position relative to any and all faces in the image.

XYVector::XYVector(std::vector<cv::Rect>& faces, double scale, cv::Mat& matFrame) : _faces(faces), _scale(scale), _matFrame(matFrame)       //  constructor
{                                                                                  
    //std::cout << "CREATING instance of xyVector at " << this << std::endl;
    SrvVctrs srvVctrs;
    cv::Scalar grn = cv::Scalar(0, 255, 0);                                                             // drawing tool color passed via Scalar for green
    cv::Scalar blu = cv::Scalar(255, 0, 0);                                                             // drawing tool color passed via Scalar for blue

    // Find the center of the image frame
    cv::Point frameCenter;
    frameCenter.x = cvRound(matFrame.cols * 0.5);
    frameCenter.y = cvRound(matFrame.rows * 0.5);
    
    // Below marks the center of our framed image
    cv::drawMarker(_matFrame, frameCenter, blu, 1, 50, 2, 8);
    
    cv::Point targetCenter;                                                                             // define the 2-D point for the target face
    for (size_t i = 0; i < faces.size(); i++) {                                                         // pick out the various faces stored in the vector
        cv::Rect r = faces[i];                                                                          // rectangle object from face recognition algorithm
        targetCenter.x = cvRound((r.x + r.width * 0.5) * _scale);                                       // round fp number to nearest integer
        targetCenter.y = cvRound((r.y + r.height * 0.5) * _scale);                                      // round fp number to nearest integer
        cv::arrowedLine(_matFrame, frameCenter, targetCenter, grn, 2, 8, 0, 0.1);                       // draw out the xyVector in green
    }
    srvVctrs.vectors(frameCenter, targetCenter, _matFrame);
}
XYVector::~XYVector(){                                                                                  // destructor
    //std::cout << "DELETING instance of xyVector at " << this << std::endl;
}

void XYVector::operator()() {}