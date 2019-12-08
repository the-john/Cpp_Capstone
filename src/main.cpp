#include <iostream>
#include <opencv2/highgui.hpp>
#include "face.h"
//#include <chrono>                                                                     // for debugging
//#include <thread>                                                                     // for debugging

int checkUserInput();

int main(int argc, char* argv[])
{
    Face face;
    std::string cascadeName;
    //std::string nestedCascadeName;                                                    // for future eye detection coupled with motion tracking 
    cv::Mat frame;
        
    // Open the video file for reading
    //cv::VideoCapture cap("");                                                         // for testing                                                         // read the image from the video file 
    cv::VideoCapture cap("../data/Smaller_Sample_Video.mp4");                                                                                    // NOTE: Udacity Workspace has no USB Webcam
    // Pull in pre-defined and pre-trained XML classifiers for identifying faces (re-use)
    // Haarcascades downloaded from https://github.com/opencv/opencv/tree/master/data/haarcascades
    // I saved these files in my project folder under /capstone/models/ and I use them from there
    cv::CascadeClassifier cascade;
    //cv::CascadeClassifier nestedCascade;
    // Now load the classifier from local folder
    cascade.load("../models/haarcascade_frontalface_alt.xml");
    
    if (cap.isOpened()) {
        std::cout << "Face Detection has Started..." << std::endl;
        while (1) {                                                                     // run until end of video or user command to stop
            cap.read(frame);                                                            // read a new frame from the video file
            
            if (frame.empty()) {                                                        // end of video found, exit the program
                std::cout << "I found the end of the video... " << std::endl;
                std::cout << "Ending the program." << std::endl;
                break;
            }        
            
            cv::Mat frameClone = frame.clone();                                         // make an image clone for face detection use
            
            face.detect(frameClone, cascade);                                           // find faces and mark them
            
            if (checkUserInput() == 1)                                                  // see if user wants to break out of this code
                break;
        }
    }  
    else {
        face.detect(Error());                                                           // unable to pull in a video image
    }                                                                                   // notify terminal that video file did not load

    return 0;
}

int checkUserInput() {
    // Breaking the while loop via user command
    char c = (char)cv::waitKey(10);
    if (c == 27 || c =='q' || c == 'Q') {                                               // key entry of 'esc', 'q', or 'Q'
        std::cout << "Killing program as per keyboard command." << std::endl;
        return 1;
    }
    else
        return 0;
}





////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//std::cout << "************************ MADE IT THIS FAR! **************************" << std::endl;        // for debugging
//std::chrono::seconds duration(3);
//std::this_thread::sleep_for(duration);


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////