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
    
    // create promise and future
    std::promise<cv::Scalar> blu;
    std::future<cv::Scalar> ftr = blu.get_future();

    // start thread and pass promise as the argument
    std::thread b(XYVector::setColorBlue, std::move(blu));                                              // start thread to make a blue color for drawing tool

    // Find the center of the image frame
    cv::Point frameCenter;
    frameCenter.x = cvRound(_matFrame.cols * 0.5);
    frameCenter.y = cvRound(_matFrame.rows * 0.5);
    
    // thread barrier
    b.join();

    // Below marks the center of our framed image
    cv::drawMarker(_matFrame, frameCenter, ftr.get(), 1, 50, 2, 8);
    
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

void XYVector::setColorBlue(std::promise<cv::Scalar> && blu)
{
    cv::Scalar clr = cv::Scalar(255, 0, 0);                                                             // set color to blue
    blu.set_value(clr);
}