#ifndef SRVVCTRS_H                                                                     // make sure header is not already defined
#define SRVVCTRS_H                                                                     // define header

//#include <iostream>                                                               // for debug
#include <opencv2/highgui.hpp>
//#include <opencv2/imgproc.hpp>

// Class for Pan and Tilt gimbal servo vectors
class SrvVctrs
{
    public:
        // constructor / destructor
        SrvVctrs();
        ~SrvVctrs();

        // getter and setter
        cv::Point frame() { return frame_; }
        void frame(cv::Point frame) { frame_ = frame; }
        cv::Point target() { return target_; }
        void target(cv::Point target) { target_ = target; }
        
        void vectors(cv::Point frame, cv::Point target, cv::Mat& frameClone);

    private:
    cv::Point frame_;
    cv::Point target_;
};

class Mark
{
    public:
        //virtual cv::Scalar color() = 0;
        virtual cv::Scalar color() const = 0;                                 

    private:
        
};

class Yellow : public Mark
{
    public:
        int b = 0;
        int g = 255;
        int r = 255;
        cv::Scalar color() const override { return cv::Scalar(b, g, r); }
};

class White : public Mark
{
    public:
        int b = 255;
        int g = 255;
        int r = 255;
        cv::Scalar color() const override { return cv::Scalar(b, g, r); }
};

#endif