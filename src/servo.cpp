#include <iostream>                                                                             // include for debug
#include <iomanip>
#include <opencv2/imgproc.hpp>
#include "srvVctrs.h"
#include "servo.h"
#include "raii.h"

// Class for gimbal pan tilt servos
Servo::Servo(){                                                                                 // constructor
    //std::cout << "CREATING instance of Servo at " << this << std::endl;
}                                                                                   
Servo::~Servo(){                                                                                // destructor
    //std::cout << "DELETING instance of Servo at " << this << std::endl;
}                                                                                   

// Here we pull apart the face difference vector and turn it into an "x" vector and a "y" vector. 
// The "x" vector gets translated into a servo pulse width number (pulse width in ms) which can be used to adjust the gimbal pan.
// The "y" vector gets translated into a servo pulse width number (pulse width in ms) which can be used to adjust the gimbal tilt.
// Because you don't have gimbal attached to your Udacity Workspace, I will indicate these vector values with white lines on the image frame.

// Function for x and y vector placement
void Servo::pwms(cv::Point target, cv::Mat& matFrame) 
{
    // Now we calculate a representative pulse width for each vector
    // The gimbal at a position of full left or full up has a pulse width of 1.0ms
    // The gimgal at a position of full right or full down has a pulse width of 2.0ms
    // The gimbal at a center position has a pulse width of 1.5ms
    int imgWidth = matFrame.cols;
    int imgHeight = matFrame.rows;

    // First we calculate for the gimbal's pan position
    float x_pos = target.x;
    float pwx = position<float>(target.x);                                                      // wherever the x location comes from, force it into a float
    if (x_pos != 0)
        pwx = ((x_pos / imgWidth) - 0.5) + 1.5;
    else {
        pwx = 1.5;                                                                              // if we loose contact, go back to center position 
        int x_location = (imgWidth / 2) - 150;
        int y_location = imgHeight - (imgHeight / 10);
        cv::putText(matFrame, "Face Target Lost!", cv::Point(x_location, y_location), cv::FONT_HERSHEY_COMPLEX_SMALL, 1.5, cv::Scalar(0, 0, 255), 1, true);
        cv::putText(matFrame, "Returning to center position.", cv::Point(x_location - 100, y_location + 40), cv::FONT_HERSHEY_COMPLEX_SMALL, 1.5, cv::Scalar(0, 0, 255), 1, true);
    }                                                                                 

    if (pwx > 2.0)                                                                              // put some safety limits on the scan
        pwx = 2.0;
    if (pwx < 1.0)
        pwx = 1.0;

    // Now we calculate for the gimbal's tilt position
    float y_pos = target.y;
    float pwy = position<float>(target.y);                                                      // wherever the y location comes from, force it into a float
    if (y_pos != 0)
        pwy = ((y_pos / imgHeight) - 0.5) + 1.5;
    else
        pwy = 1.5;                                                                              // if we loose contact, go back to centr position

    if (pwy > 2.0)                                                                              // put some safety limits on the tilt
        pwy = 2.0;
    if (pwy < 1.0)
        pwy = 1.0;

    // Now that we have the values we need for the gimbal servo pulse widths, we need to send them out.
    // Because you have no gimbals attached to your computer, I will visually send out these values for your observation.
    std::ostringstream panPwm;
    panPwm << std::setprecision(3) << std::fixed << pwx;
    std::string PanPwmS(panPwm.str());
    PanPwmS += " ms";

    cv::putText(matFrame, "PAN PWM Value", cv::Point(30, 30), cv::FONT_HERSHEY_COMPLEX_SMALL, 1.5, cv::Scalar(255, 255, 255), 1, true);
    cv::putText(matFrame, PanPwmS, cv::Point(30, 70), cv::FONT_HERSHEY_DUPLEX, 1.5, cv::Scalar(255, 255, 255), 1, true);

    std::ostringstream tiltPwm;
    tiltPwm << std::setprecision(3) << std::fixed << pwy;
    std::string tiltPwmS(tiltPwm.str());
    tiltPwmS += " ms";

    cv::putText(matFrame, "TILT PWM Value", cv::Point(625, 30), cv::FONT_HERSHEY_COMPLEX_SMALL, 1.5, cv::Scalar(255, 255, 255), 1, true);
    cv::putText(matFrame, tiltPwmS, cv::Point(625, 70), cv::FONT_HERSHEY_DUPLEX, 1.5, cv::Scalar(255, 255, 255), 1, true);

    // So in the future when I do have gimbals attached to my motherboard (Raspberry Pi)
    // Set up data to move out to a piece of dedicated PWM silicon on embedded board
    // For now, let's pretend that the existance of the RAII class is to help me "message" my X and Y values, (i.e.) make real-world tweeks and adjustments
    RAII objX(pwx);                                                                             // make an object
    Servo::pwmRegX(std::move(objX));                                                            // move that object via move semantics

    Servo::pwmRegY(Servo::uniquePointer(pwy));                                                  // create a smart pointer and move it to the function
}

void Servo::pwmRegX(RAII objX)
{
    float pwmX = objX.data();                                                                   // get data from moved object
    // write this data to ficticious I/O memory map location of the X axis PWM register
    //std::cout << "Pulse Width for PAN provided by the move of an object is = " << pwmX << "                 "; // sudo "write to PWM register"
}

void Servo::pwmRegY(std::unique_ptr<float> yPtr)                                                // use smart pointer to get and use data
{
    // write value from yPtr to ficticious I/O memory map location of Y axis PWM register
    //std::cout << "Pulse Width for TILT provided by the smart pointer is = " << *yPtr << std::endl;  // sudo "write to PWM register"
}

std::unique_ptr<float> Servo::uniquePointer(float pwy)                                          // make a smart pointer
{
    std::unique_ptr<float> yPtr(new float);                                                     // create a pointer on the stack
    *yPtr = pwy;                                                                                // assign the pointer a value
    return yPtr;
}