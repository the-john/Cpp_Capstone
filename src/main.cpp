//#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
//#include <chrono>                                                       // for debugging
//#include <thread>                                                       // for debugging

// Function for face detection
void detectAndDraw(cv::Mat& img, cv::CascadeClassifier& cascade, double scale);

//std::string cascadeName;
//std::string nestedCascadeName;

int main(int argc, char* argv[])
{
    std::string cascadeName;
    //std::string nestedCascadeName;
    cv::Mat frame;
        
    // Open the video file for reading
    cv::VideoCapture cap("../data/Smaller_Sample_Video.mp4");                           // read the image from the video file 
                                                                                        // NOTE: Udacity Workspace has no USB Webcam
    // Use this to scale the size of the image that we send to the face detection algorithm so that there is less to have to compute (program runs faster)
    double scale = 3;                                                                   // ###############################################################

    // Pull in pre-defined and pre-trained XML classifiers for identifying faces (re-use)
    // Haarcascades downloaded from https://github.com/opencv/opencv/tree/master/data/haarcascades
    // I saved these files in my project folder under /capstone/models/ and I use them from there
    cv::CascadeClassifier cascade;
    //cv::CascadeClassifier nestedCascade;
    // Now load the classifier from local folder
    cascade.load("../models/haarcascade_frontalface_alt.xml");
    //nestedCascade.load("../models/haarcascade_eye_tree_eyeglasses.xml");

    // If opening the video file is not a success, exit program
    if (cap.isOpened() == false) {
        std::cout << "Cannot open the video file!" << std::endl;
        std::cout << "Shutting down program.  Press any key to exit." << std::endl;
        std::cin.get();                                                                 //wait for any key press
        return -1;
    }
    else
        std::cout << "Face Detection Started... " << std::endl;

    if (cap.isOpened()) {
        while (1) {                                                                     // Run until end of video or user command to stop
            cap.read(frame);                                                            // read a new frame from the video file
            
            if (frame.empty()) {                                                        // end of video found, exit the program
                std::cout << "I found the end of the video... " << std::endl;
                std::cout << "Ending the program." << std::endl;
                break;
            }        
            
            cv::Mat frameClone = frame.clone();                                         // make an image clone for face detection use
            
            detectAndDraw(frameClone, cascade, scale);                                  // find faces and mark them
            
            // Breaking the while loop via user command
            char c = (char)cv::waitKey(10);
            if (c == 27 || c =='q' || c == 'Q') {                                       // key entry of 'esc', 'q', or 'Q'
                std::cout << "Killing program as per keyboard command." << std::endl;
                break;
            }
        }
    }  
    else
        std::cout << "Could not open video file!" << std::endl;                         // notify terminal that video file did not load

    return 0;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void detectAndDraw(cv::Mat& img, cv::CascadeClassifier& cascade, double scale) 
{
    std::vector<cv::Rect> faces;
    cv::Mat grayImg;
    cv::Mat shrinkImg;
        
    cv::cvtColor(img, grayImg, cv::COLOR_BGR2GRAY);                                                         // convert to gray scale
    // Recude the size of the gray image by "fx" and feed that to the face detection algorithm; a reduced size will compute MUCH faster
    double fx = 1 / scale;
    cv::resize(grayImg, shrinkImg, cv::Size(), fx, fx, cv::INTER_LINEAR);                                   // resize the grayscale image, nearest-neighbor interpolation
    cv::equalizeHist(shrinkImg, shrinkImg);                                                                 // increase contrast of smallImg via histogram equalization
    
    cascade.detectMultiScale(shrinkImg, faces, 1.1, 2, 0|cv::CASCADE_SCALE_IMAGE, cv::Size(50, 80));        // 30, 30; detect faces of different sizes useing cascade classifier
    
    for (size_t i = 0; i < faces.size(); i++) {                                                             // draw circles around the faces
        cv::Rect r = faces[i];                                                                              // rectangle object from face recognition algorithm
        
        //std::vector<cv::Rect> nestedBoxes;                                                                  // rectangles to box faces in image
        cv::Point center;                                                                                   // the definition for a 2-D point in the image
        cv::Scalar wht = cv::Scalar(255, 255, 255);                                                         // drawing tool color passed via Scalar for white
        cv::Scalar red = cv::Scalar(0, 0, 255);                                                             // drawing tool color passed via Scalar for red
        cv::Scalar blu = cv::Scalar(255, 0, 0);                                                             // drawing tool color passed via Scalar for blue
        int radius;                                                                                         // radius of circle to box faces in image

        //double aspect_ratio = (double)r.width / r.height;                                                   // calc aspect ratio of rectangle object via width and height
        
        //if (0.75 < aspect_ratio && aspect_ratio < 1.3) {
            center.x = cvRound((r.x + r.width * 0.5) * scale);                                              // round fp number to nearest integer
            center.y = cvRound((r.y + r.height * 0.5) * scale);                                             // round fp number to nearest integer
            //radius = cvRound((r.width + r.height) * 0.25 * scale);                                          // round fp number to nearest integer
            //cv::circle(img, center, radius, wht, 2, 8, 0);
            cv::drawMarker(img, center, red, 0, 20, 2, 8);                                                  // draw cross-hairs where robot should be looking
        //}
        //else
        //    cv::rectangle(img, cvPoint(cvRound(r.x * scale), cvRound(r.y * scale)), cvPoint(cvRound((r.x + r.width - 1) * scale), cvRound((r.y + r.height - 1) * scale)), blu, 3, 8, 0);
    }
    cv::imshow("Robot Face Detection & Tracking", img);                                                      // show marked image
}

//std::cout << "************************ MADE IT THIS FAR! **************************" << std::endl;        // for debugging
//std::chrono::seconds duration(3);
//std::this_thread::sleep_for(duration);