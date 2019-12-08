//#include <iostream>                                                                                       // include for debug
#include <iomanip>
#include <opencv2/imgproc.hpp>
#include "img.h"
#include "srvVctrs.h"
#include "servo.h"

// Class for gimbal pan tilt servos
SrvVctrs::SrvVctrs(){}
SrvVctrs::~SrvVctrs(){}

// Here we pull apart the face difference vector and turn it into an "x" vector and a "y" vector. 
// The "x" vector gets translated into a servo pulse width number (pulse width in ms) which can be used to adjust the gimbal pan.
// The "y" vector gets translated into a servo pulse width number (pulse width in ms) which can be used to adjust the gimbal tilt.
// Because you don't have gimbal attached to your Udacity Workspace, I will indicate these vector values with white lines on the image frame.

// Function for x and y vector placement
void SrvVctrs::vectors(cv::Point frame, cv::Point target, cv::Mat& frameClone) 
{
    Servo servo;
    Yellow ylw;                                                                                             // drawing tool color passed via Scalar for yellow

    cv::Point x_vectorPtr;                                                                                  // create a vector for servo gimbal pan
    x_vectorPtr.x = target.x;
    x_vectorPtr.y = frame.y;
    
    cv::Point y_vectorPtr;                                                                                  // create a vector for servo gimbal tilt
    y_vectorPtr.x = frame.x;
    y_vectorPtr.y = target.y;

    if (target.x > 0)
        cv::arrowedLine(frameClone, frame, x_vectorPtr, ylw.color(), 2, 8, 0, 0.1);                         // draw out the x vector (yaw) in yellow
    if (target.y > 0)   
        cv::arrowedLine(frameClone, frame, y_vectorPtr, ylw.color(), 2, 8, 0, 0.1);                         // draw out the y vector (pitch) in yellow

    servo.pwms(target, frameClone);
}