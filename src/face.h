#ifndef FACE_H                                                                      // make sure header is not already defined
#define FACE_H                                                                      // define header

//#include <iostream>                                                                 // for debugging
#include <opencv2/objdetect.hpp>
#include <mutex>

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
        cv::Mat Frame() { return _frame; }
        cv::Mat Frame(cv::Mat frame) { _frame = frame; }

        // functions
        void detect(cv::CascadeClassifier& cascade);                               
        void detect(Error error);
        void getFrame(cv::VideoCapture &cap, cv::CascadeClassifier& cascade);
        int checkUserInput();
        
    private:
        // Use this to scale the size of the image that we send to the face detection algorithm so that there is less to have to compute (program runs faster)
        double scale_ = 2.0;                                                        // ############## Adjust as needed for performance #####################
        cv::Mat _frame;                                                             // image frame to be shared with EVERYBODY!      
        std::mutex _mutex;
};

#endif