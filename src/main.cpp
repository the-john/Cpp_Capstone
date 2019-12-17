#include <iostream>
#include <thread>
#include <string>                   
#include <mutex>                    
#include <condition_variable>       
#include <opencv2/highgui.hpp>
#include "face.h"

int checkUserInput();
std::mutex m;                       
std::condition_variable conVar;     
std::string data;                   
bool ready = false;                 
bool processed = false;             

void sysData()
{
    // Wait until request comes in
    std::unique_lock<std::mutex> lk(m);
    conVar.wait(lk, []{ return ready; });

    // Get the number of CPU cores available in this system (just for fun)
    unsigned int nCores = std::thread::hardware_concurrency();
    // Get the thread ID for the main program (just for fun) to the terminal
    std::cout << "The ""main"" Thread ID is " << data << std::endl;                     // notify terminal of main() thread ID

    data = std::to_string(nCores);
    // Now we send the data gathered here back to main()
    processed = true;

    // Now we unlock
    lk.unlock();
    conVar.notify_one();
}

int main(int argc, char* argv[])
{
    Face face;
    std::string cascadeName;
    std::string tID;
    //std::string nestedCascadeName;                                                    // for future eye detection coupled with motion tracking 
            
    // Open the video file for reading
    cv::VideoCapture cap("../data/Smaller_Sample_Video.mp4");                           // read the image from the video file 
                                                                                        // NOTE: Udacity Workspace has no USB Webcam
    // Pull in pre-defined and pre-trained XML classifiers for identifying faces (re-use)
    // Haarcascades downloaded from https://github.com/opencv/opencv/tree/master/data/haarcascades
    // I saved these files in my project folder under /capstone/models/ and I use them from there
    cv::CascadeClassifier cascade;
    //cv::CascadeClassifier nestedCascade;                                              // for future eye detection coupled with motion tracking
    // Now load the classifier from local folder
    cascade.load("../models/haarcascade_frontalface_alt.xml");

    // Get thread ID for this main() thread and turn it into a string
    auto mainID = std::this_thread::get_id();
    std::stringstream ss;
    ss << mainID;
    std::string mainIDstring = ss.str();

    // Example of me sending and recieveing data from a thread via condition variable
    std::thread inf(sysData);                                                           // start thread
    data = mainIDstring;
    // Send data to the sysData thread
    {
        std::lock_guard<std::mutex> lk(m);
        ready = true;
    }
    conVar.notify_one();

    // Wait for sysData thread
    {
        std::unique_lock<std::mutex> lk(m);
        conVar.wait(lk, []{ return processed; });
    }
    // Received data from the sysData thread
    std::cout << "This machine has " << data << " cores available" << std::endl;        // notify terminal of the number of CPU cores from condition variable
    
    inf.join();                                                                         // end of thread


    if (cap.isOpened()) {                                                               // let's get to it
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