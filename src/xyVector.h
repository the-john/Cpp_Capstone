#ifndef XYVECTOR_H                                                                  // make sure header is not already defined
#define XYVECTOR_H                                                                  // define header

//#include <iostream>                                                                 // for debug
#include <opencv2/imgproc.hpp>

// Class for Facemark Vector
class XYVector
{
    public:
        // constructor / destructor
        XYVector(std::vector<cv::Rect>& faces, double scale, cv::Mat& matFrame);
        ~XYVector();

        // function
        void operator()();

    private:
        std::vector<cv::Rect>& _faces;
        double _scale;
        cv::Mat& _matFrame;
};

#endif