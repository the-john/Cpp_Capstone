#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "crossHair.h"

// Function for cross hair placement
void crossHair(std::vector<cv::Rect>& faces, double scale, cv::Mat frameClone) 
{
    

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
            cv::drawMarker(frameClone, center, red, 0, 30, 2, 8);                                                  // draw cross-hairs where robot should be looking
        //}
        //else
        //    cv::rectangle(img, cvPoint(cvRound(r.x * scale), cvRound(r.y * scale)), cvPoint(cvRound((r.x + r.width - 1) * scale), cvRound((r.y + r.height - 1) * scale)), blu, 3, 8, 0);
    }

    cv::imshow("Robot Face Detection & Tracking", frameClone);                                                      // show marked image
}