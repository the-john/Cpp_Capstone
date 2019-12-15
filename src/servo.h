#ifndef SERVO_H                                                                     // make sure header is not already defined
#define SERVO_H                                                                     // define header

//#include <iostream>                                                               // for debug
#include <opencv2/highgui.hpp>
#include "srvVctrs.h"
#include "raii.h"

// Class for Pan and Tilt gimbal servo pulse widths
class Servo : SrvVctrs                                                              // Make a child class of SrvVctrs 
{
    public:
        // constructor / destructor
        Servo();
        ~Servo();

        // getter and setter
        cv::Point frame() { return frame_; }
        void frame(cv::Point frame) { frame_ = frame; }
        cv::Point target() { return target_; }
        void target(cv::Point target) { target_ = target; }

        // function
        void pwms(cv::Point target, cv::Mat& matFrame);
        void pwmRegX(RAII obj);
        void pwmRegY(std::unique_ptr<float> yPtr);
        std::unique_ptr<float> uniquePointer(float pwy);

    private:
        cv::Point frame_;
        cv::Point target_;

};

// Template for the calculated position of the servo; can accept integers, floats, doubles, whatever.
template <typename num> num position(num pos) { return pos; }

#endif