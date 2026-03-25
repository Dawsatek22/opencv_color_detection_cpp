// this is a code to detect thered contours with camera
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

int main() {
    
    VideoCapture  cam(0); // to capture the video
    Mat frame ; // object we are gonna read

 

 
   while (true) {

cam.read(frame); // reads frame
// checks if camera is opened
if(!cam.isOpened()){
break;
}
  // Red wraps around hue=0, so use two ranges.
    cv::Scalar lower_color1(0, 150, 127);
    cv::Scalar upper_color1(10, 255, 255);
    cv::Scalar lower_color2(170, 150, 127);
    cv::Scalar upper_color2(180, 255, 255);


Mat mask1 ,mask2, mask, hsv;
cvtColor(frame , hsv, cv::COLOR_BGR2HSV);
inRange(hsv,lower_color1,upper_color1,mask1);
inRange(hsv,lower_color1,upper_color2,mask2);
mask = mask1 | mask2;

    // Clean noise before contour extraction.
    
Mat kernel = getStructuringElement(MORPH_ELLIPSE,Size(5,5));

    cv::erode(mask, mask, kernel);
    cv::dilate(mask, mask, kernel);

    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);



  
// checks countour area
    for (std::size_t i = 0; i < contours.size(); ++i) {
        double const area = cv::contourArea(contours[i]);
        if (area <= 500) {
            continue;
        }
           // creates object for detecting color
        cv::Rect const box = cv::boundingRect(contours[i]);
       //  puts a rectangle on countour
        cv::rectangle(frame, box, cv::Scalar(0, 0, 255), 2);
        // put the color name on the countour
        cv::putText(
            frame,
            "red",
            box.tl(),
            cv::FONT_HERSHEY_SIMPLEX,
            1.0,
            cv::Scalar(255, 230, 70),
            2
        );
    }

 imshow("test1",frame);
 imshow("mask",mask);
if (waitKey(1) == ('q')) {
  break;
  destroyAllWindows();
}

}
}