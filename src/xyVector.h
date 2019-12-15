#ifndef XYVECTOR_H                                                                  // make sure header is not already defined
#define XYVECTOR_H                                                                  // define header

//#include <iostream>                                                               // for debug
#include <opencv2/imgproc.hpp>

// Class for Facemark Vector
class XYVector
{
    public:
        // constructor / destructor
        XYVector();
        ~XYVector();

        // function
        void faceVector(std::vector<cv::Rect>& faces, double scale, cv::Mat& matFrame);

    private:

};

#endif