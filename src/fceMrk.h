#ifndef FCEMRK_H                                                                // make sure header is not already defined
#define FCEMRK_H                                                                // define header

//#include <iostream>                                                             // for debug
#include <opencv2/imgproc.hpp>

// Class for FaceMarking
class FaceMarking
{
    public:
        // constructor / destructor
        FaceMarking(std::vector<cv::Rect>& faces, double scale, cv::Mat& matFrame);
        ~FaceMarking();

        // function
        void operator()();
        
    private:
        std::vector<cv::Rect>& _faces;
        double _scale;
        cv::Mat& _matFrame;
};

#endif