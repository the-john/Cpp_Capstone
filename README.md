# Human Face Tracking

In this project, I've built my own C++ applicaiton for my home robot.  My home robot has eyes which are small CCD cameras.  I would like the eyes of my robot to move around and actually look at an individual that it is engauged with.  The camera's are on gimbals, and can track the movement of face with this software.  The intent is to make my home robot more "life like" with its HMI.  

Because the robot has stereo vision (i.e. two eyes), it has the ability to do depth perception.  A depth perception algorithm (which is not part of this code), determines the closest face to the robot, and my home robot is to track that face.  So, for this code I only need to track a single face which currently represents the "closest face" once depth perception code is added.

To enable a review of this code and its functionality, I've included a short .mp4 video clip of myself moving my face around.  This video clip represents a live feed from a USB webcam.  So you can run this code without the need of having a USB webcame set up on your system.

## Program Structure and Behavior

The file and class structure of this program is shown below:

<p align="center">
    <img src="https://github.com/the-john/Cpp_Capstone/blob/master/models/program.jpg">
</p>

The program reads in a video file image (an .mp4 file).  (NOTE: a live feed from a USB webcam can readily replace the video file image.)  In an attempt to speed up the performance, a copy of the image is made and shrunk.  This shrunken image is then sent to a pre-defined and pre-trained face recogniton algorithm called haarcascade_frontalface_alt.xml.  The face recognition algorithm returns the presence of a face (if it can identify one) by giving coordinates to the location of that face in the image.  These face coordinates are used to determine the middle of the face, and a cross-hairs marker colored as red is drawn onto the middle of the face for identification and location purposes.

The code then makes a determination of how far away that marker is from the center of the image and then calculates "x" and "y" values that represent the markers location delta from the center of the image.  The "x" and "y" values are then translated into PWM (Pulse Width Modulation) values that can be sent to I/O to drive the physical positioning of a cheap RC Servo.  More details on the cheap RC Servo below.  Because hooking cheap RC Servos is currently not an option for you, I visually represent the cheap RC Servo pan and tilt values in milli-seconds pulse values which can be seen in the top left and right corners of the display accorndingly.  I also show vector arrows eminating from the center of the image that are colored white.

Details on how a cheap RC Servo works can be found [here](https://learn.sparkfun.com/tutorials/hobby-servo-tutorial/all):

Basically, you need to feed the RC Servo a PWM (Pulse Width Modulated) signal.  The signal needs to be at 50Hz (20ms intervals), where each intervals pulse needs to be anywhere from 1ms to 2ms in length.  A 1ms pulse width will position the RC Servo to its full clockwise position.  A 2ms pulse width will position the RC Servo to its full counter-clockwise position.  To get the RC Servo into it's center position, a 1.5ms pulse width is needed.  NOTE: Cheap RC Servos are not "super accurate" devices.  No two operate exactly the same way.  So, you will need to "tweak" the pulse widths specifically for each servo in the code if you want to get decent positioning.  Once you do this, the cheap RC Servo will remain fairly precise.

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./faceTrack`.

## Project Specifications

#### README Criteria
* A README with instructions is included with this project: **Done-**  
    * Refer to the top section of this README.

* The README indicates which project is chosen: **Done-**  
    * Refer to the top section of this README.

* Project rubric points: **Done-**  
    * You're currently reading it now.

#### Compiling and Testing Criteria
* Submission must compile and run: **Done-**

#### Loops, Functions, I/O Criteria
* Functions and control strucutures: **Done-**
    * Refer to main.cpp lines 69 (function call), 56 (while loop), 70 (control structure) 

* Reads file data & processes it:  **Done-**
    * Refer to main.cpp line 31

* Accept user input and process it:  **Done-**
    * Refer to main.cpp line 15

#### Object Oriented Programming
* Use Object Oriented Programming techniques: **Done-**
    * Please refer to the multiple routines under the /src folder compiled and working together in an OOP way

* Classes use access specifiers for class members: **Done-**
    * Please refer to srvVctrs.h lines 10 and 23

* Class constructors use member initialization lists:  **Done-**
    * Please refer to face.h line 11

* Class abstraction of implementation details: **Done-**
    * Please refer to face.h line 22

* Class encapsulate behavior:  **Done-**
    * Please refer to face.h line 29

* Classes follow inheritance hierarchy:  **Done-**
    * Please refer to servo.h line 9

* Overloaded functions: **Done-**
    * Please refer to main.cpp line 40 and 47
    * Please refer to face.h line 24 and 25
    * Please refer to face.cpp line 12 and 38

* Derived Class functions override virtual base class functions:  **Done-**
    * Please refer to srvVctrs.h lines 45 and 54
    * Please refer to srvVctrs.cpp lines 33 and 35

* Templates generalize functions in project:  **Done-**
    * Please refer to servo.h line 31
    * Please refer to servo.cpp lines 29 and 47

#### Memory Management Criteria
* Use of references in function declarations:  **Done-**
    * Please refer to face.cpp line 12

* Use destructors appropriately:  **Done-**
    * Please refer to face.cpp line 10

* Use RAII where approprate:  **Done-***
    * Please refer to raii.h and raii.cpp

* Follow the Rule of 5:  **Done-**
    * Please refer to raii.cpp

* Use move semantics:  **Done-**
    * Please refer to servo.cpp line 85

* Use smart pointers:  **Done-**
    * Please refer to servo.cpp line 87

#### Concurrency Criteria
* Use multithreading:  **Done-**
    * Please refer to face.cpp lines 52 and 55

* Use a promise and a future:

* Mutex or lock is used:

* Use condition variable:
