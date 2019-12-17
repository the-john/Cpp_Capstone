//#include <iostream>                                                                                     // include for debug
#include <opencv2/highgui.hpp>
#include "img.h"

// Class for displaying the final image
Img::Img(){}                                                                                            // constructor
Img::~Img(){                                                                                            // destructor
    //std::cout << _text << " destroyed" << std::endl;
}
Img::Img(std::string text) { _text = text; }

// Function to display the final resultant image
void Img::showImg(cv::Mat& matFrame)
{
    cv::imshow(_text, matFrame);                                                                        // show marked image with title
}