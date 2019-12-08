#ifndef FACE_H                                                                  // make sure header is not already defined
#define FACE_H                                                                  // define header

#include <iostream>                                                             // for debugging
#include <opencv2/objdetect.hpp>

class Error {};

// Class for face detection
class Face 
{
    public:  
        std::vector<cv::Rect> faces;
        int num = 0;

        // constructor / desctructor
        Face();
        ~Face();

        // getter and setter
        double scale() { return scale_; }
        void scale(double scale) { scale_ = scale; }

        void detect(cv::Mat& frameClone, cv::CascadeClassifier& cascade);
        void detect(Error error);

    private:
        // Use this to scale the size of the image that we send to the face detection algorithm so that there is less to have to compute (program runs faster)
        double scale_ = 3;                                                      // ############## Adjust as needed for performance #####################
        
};

#endif