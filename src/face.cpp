#include <iostream>                                                                                         
#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include "face.h"
#include "fceMrk.h"
#include "xyVector.h"
#include "img.h"

// Class for face detection
Face::Face(){                                                                                               // constructor
    std::cout << "CREATING instance of Face at " << this << std::endl;
}
Face::~Face(){                                                                                              // destructor
    std::cout << "DELETING instance of Face at " << this << std::endl;
}
Face::Face(const Face &source) {                                                                            // copy constructor
    _frame = source._frame;
    std::cout << "COPYING content of instance " << &source << " to instance " << this << std::endl;
}
/*
Face::Face &operator=(const Face &source) {                                                                 // copy assignment operator
    std::cout << "ASSIGNING content of instance " << &source << " to instance " << this << std::endl;
    if (this == &source)
        return *this;
    _frame = source._frame;
    return *this;
}
*/
Face::Face(Face &&source) {                                                                                 // move constructor
    std::cout << "MOVING constructor instance " << &source << " to instance " << this << std::endl;
    _frame = source._frame;
    source._frame.release();
}
/*
Face::Face &operator=(Face &&source) {                                                                      // move assignment operator
    std::cout << "MOVING assignment instance " << &source << " to instance " << this << std::endl;
    if (this == &source)
        return *this;
    source._frame.release();
    return *this;
}
*/

void Face::getFrame(cv::VideoCapture &cap, cv::CascadeClassifier& cascade)
{
    while (1) {                                                                                             // run until end of video or user command to stop
        cap.read(_frame);                                                                                    // read a new frame from the video file
        //std::cout << "Made it into getFrame ######################################################" << std::endl;
        if (Frame().empty()) {                                                                                // end of video found, exit the program
            std::cout << "I found the end of the video... " << std::endl;
            std::cout << "Ending the program." << std::endl;
            break;
        }        
            
        cv::Mat frameClone = Frame().clone();                                                                 // make an image clone for face detection use
            
        Face::detect(cascade);                                                                  // find faces and mark them  
        if (Face::checkUserInput() == 1)                                                                    // see if user wants to break out of this code
            break;
    }
}                                                                                   

void Face::detect(cv::CascadeClassifier& cascade) 
{
    FaceMarking faceMarking;
    XYVector xyVector;
    // std::vector<cv::Rect> faces;
    cv::Mat grayImg;
    cv::Mat shrinkImg;

    cv::cvtColor(_frame, grayImg, cv::COLOR_BGR2GRAY);                                                  // convert to gray scale
    // Recude the size of the gray image by "fx" and feed that to the face detection algorithm; a reduced size will compute MUCH faster
    double fx = 1 / scale();
    cv::resize(grayImg, shrinkImg, cv::Size(), fx, fx, cv::INTER_LINEAR);                                   // resize the grayscale image, nearest-neighbor interpolation
    cv::equalizeHist(shrinkImg, shrinkImg);                                                                 // increase contrast via histogram equalization
    cascade.detectMultiScale(shrinkImg, faces, 1.1, 2, 0|cv::CASCADE_SCALE_IMAGE, cv::Size(50, 80));        // detect faces of different sizes useing cascade classifier (30, 30)

    faceMarking.crossHair(faces, scale(), _frame);                                                      // place a cross hair on the middle of the face
    xyVector.faceVector(faces, scale(), _frame);                                                        // show offset vector from center of image to center of face

    showImg(_frame);
}

void Face::detect(Error error)
{
    std::cout << "Cannot open the video file!" << std::endl;
    std::cout << "Shutting down program.  Press any key to exit." << std::endl;
    std::cin.get();                                                                                         // wait for any key press
    std::exit;
}

int Face::checkUserInput() {
    // Breaking the while loop via user command
    char c = (char)cv::waitKey(10);
    if (c == 27 || c =='q' || c == 'Q') {                                                                   // key entry of 'esc', 'q', or 'Q'
        std::cout << "Killing program as per keyboard command." << std::endl;
        return 1;
    }
    else
        return 0;
}
