#ifndef IMG_H                                                                       // make sure header is not already defined
#define IMG_H                                                                       // define header

//#include <iostream>                                                                 // for debug
#include <opencv2/highgui.hpp>

// Class for displaying the final image
class Img
{
    public:
        Img();
        ~Img();
        Img(std::string text);

    // getter and setter
    std::string setText() { return _text; }
    void setText(std::string text) { _text = text; }

    // function
    void showImg(cv::Mat& matFrame);

    private:
        std::string _text;

};

#endif