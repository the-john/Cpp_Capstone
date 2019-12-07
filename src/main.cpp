#include <iostream>
#include <opencv2/highgui.hpp>
#include "face.h"
//#include <chrono>                                                                     // for debugging
//#include <thread>                                                                     // for debugging

int checkUserInput();

int main(int argc, char* argv[])
{
    std::string cascadeName;
    //std::string nestedCascadeName;                                                    // for future eye detection coupled with motion tracking 
    cv::Mat frame;
        
    // Open the video file for reading
    cv::VideoCapture cap("../data/Smaller_Sample_Video.mp4");                           // read the image from the video file 
                                                                                        // NOTE: Udacity Workspace has no USB Webcam

    // Use this to scale the size of the image that we send to the face detection algorithm so that there is less to have to compute (program runs faster)
    double scale = 3;                                                                   // ############## Adjust as needed for performance #####################

    // Pull in pre-defined and pre-trained XML classifiers for identifying faces (re-use)
    // Haarcascades downloaded from https://github.com/opencv/opencv/tree/master/data/haarcascades
    // I saved these files in my project folder under /capstone/models/ and I use them from there
    cv::CascadeClassifier cascade;
    //cv::CascadeClassifier nestedCascade;
    // Now load the classifier from local folder
    cascade.load("../models/haarcascade_frontalface_alt.xml");
   
    // If opening the video file is not a success, exit program
    if (cap.isOpened() == false) {
        std::cout << "Cannot open the video file!" << std::endl;
        std::cout << "Shutting down program.  Press any key to exit." << std::endl;
        std::cin.get();                                                                 // wait for any key press
        return -1;
    }
    else
        std::cout << "Face Detection Started... " << std::endl;                         // everything is ready to start face detection

    if (cap.isOpened()) {
        while (1) {                                                                     // run until end of video or user command to stop
            cap.read(frame);                                                            // read a new frame from the video file
            
            if (frame.empty()) {                                                        // end of video found, exit the program
                std::cout << "I found the end of the video... " << std::endl;
                std::cout << "Ending the program." << std::endl;
                break;
            }        
            
            cv::Mat frameClone = frame.clone();                                         // make an image clone for face detection use
            
            detect(frameClone, cascade, scale);                                         // find faces and mark them
            
            if (checkUserInput() == 1)                                                  // see if user wants to break out of this code
                break;
        }
    }  
    else
        std::cout << "Could not open video file!" << std::endl;                         // notify terminal that video file did not load

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