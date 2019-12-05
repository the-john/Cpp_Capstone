#include <opencv2/opencv.hpp>
#include <iostream>
//#include <thread>
//#include <chrono>

int main(int argc, char* argv[])
{
    //open the video file for reading
    cv::VideoCapture cap("../data/Smaller_Sample_Video.mp4"); 

    // if not success, exit program
    if (cap.isOpened() == false) {
        std::cout << "Cannot open the video file" << std::endl;
        std::cin.get(); //wait for any key press
        return -1;
    }

    //get the frames rate of the video
    double fps = cap.get(cv::CAP_PROP_FPS); 
    std::cout << "Frames per seconds : " << fps << std::endl;

    // get the number of frames in the video
    int frameNum = cap.get(cv::CAP_PROP_FRAME_COUNT);
    std::cout << "Total number of frames :" << frameNum << std::endl;  // this value should be 692

    // just for fun, edit the front of the video by cutting it off where I take off my glasses
    //int frameStart = frameNum / 12;
    //cap.set(CAP_PROP_POS_FRAMES, (frameStart));

    cv::String window_name = "My First OpenCV Video";

    cv::namedWindow(window_name, cv::WINDOW_NORMAL); //create a window

    while (true) {
        cv::Mat frame;
        bool bSuccess = cap.read(frame); // read a new frame from video 
        //std::this_thread::sleep_for(std::chrono::milliseconds(33));       // try to get video play at normal speed

        //Breaking the while loop at the end of the video
        if (bSuccess == false) {
            std::cout << "Found the end of the video" << std::endl;
            break;
        }

        //show the frame in the created window
        cv::imshow(window_name, frame);

        //wait for for 33.333 ms until any key is pressed.  
        //If the 'Esc' key is pressed, break the while loop.
        //If the any other key is pressed, continue the loop 
        //If any key is not pressed withing 10 ms, continue the loop
        if (cv::waitKey(33.333) == 27) {                                         // use the waitKey to slow the video to a normal rate; it was at 10
            std::cout << "Esc key is pressed by user. Stoppig the video" << std::endl;
            break;
        }
    }
    return 0;
}