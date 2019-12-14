#include <iostream>
#include <opencv2/highgui.hpp>
#include "face.h"

int checkUserInput();

int main(int argc, char* argv[])
{
    Face face;
    std::string cascadeName;
    //std::string nestedCascadeName;                                                    // for future eye detection coupled with motion tracking 
    //cv::Mat frame;
        
    // Open the video file for reading
    cv::VideoCapture cap("../data/Smaller_Sample_Video.mp4");                           // read the image from the video file 
                                                                                        // NOTE: Udacity Workspace has no USB Webcam
    // Pull in pre-defined and pre-trained XML classifiers for identifying faces (re-use)
    // Haarcascades downloaded from https://github.com/opencv/opencv/tree/master/data/haarcascades
    // I saved these files in my project folder under /capstone/models/ and I use them from there
    cv::CascadeClassifier cascade;
    //cv::CascadeClassifier nestedCascade;
    // Now load the classifier from local folder
    cascade.load("../models/haarcascade_frontalface_alt.xml");
    
    if (cap.isOpened()) {
        std::cout << "Face Detection has Started..." << std::endl;
        face.getFrame(cap, cascade);
    }  
    else {
        face.detect(Error());                                                           // unable to pull in a video image
    }                                                                                   // notify terminal that video file did not load
    return 0;
}






////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//#include <chrono>                                                                                         // for debugging
//#include <thread>                                                                                         // for debugging

//std::cout << "************************ MADE IT THIS FAR! **************************" << std::endl;        // for debugging
//std::chrono::seconds duration(3);
//std::this_thread::sleep_for(duration);


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////