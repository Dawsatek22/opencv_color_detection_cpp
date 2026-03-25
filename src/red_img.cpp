
// this is the code to put bounding boxes on red objects

//below are the basic header
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

int main()
{
    // below is path to the img file
    cv::String const path = "/home/d22/Documents/cv_projects/opencv_colordetection_cpp/images/opencv-logo.png";

    cv::Mat img = cv::imread(path, cv::IMREAD_COLOR); // reads the file
    // then resize the img to make it more visble on the scrren
    cv::Mat re_img;
    cv::resize(img,re_img,cv::Size(600,600));
    // checks if the img is empty
    if (re_img.empty()) {
        std::cerr << "Could not read image: " << path << '\n';
        return 1;
    }
    // now creates the hsv object for hsv colorspaces
    cv::Mat hsv;
    cv::cvtColor(img, hsv, cv::COLOR_BGR2HSV); // converts the color for hsv

    // Red wraps around hue=0, so use two ranges.
    cv::Scalar lower_color1(0, 150, 127);
    cv::Scalar upper_color1(10, 255, 255);
    cv::Scalar lower_color2(170, 150, 127);
    cv::Scalar upper_color2(180, 255, 255);

    cv::Mat mask1, mask2, mask;
    cv::inRange(hsv, lower_color1, upper_color1, mask1);
    cv::inRange(hsv, lower_color2, upper_color2, mask2);
    mask = mask1 | mask2;

    // Clean noise before contour extraction.
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5));
    cv::erode(mask, mask, kernel);
    cv::dilate(mask, mask, kernel);

    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);


 // resize the mask
   cv::Mat re_mask;
   cv::resize(mask,re_mask,cv::Size(600,600));

// checks countour area
    for (std::size_t i = 0; i < contours.size(); ++i) {
        double const area = cv::contourArea(contours[i]);
        if (area <= 500) {
            continue;
        }
           // creates object for detecting color
        cv::Rect const box = cv::boundingRect(contours[i]);
       //  puts a rectangle on countour
        cv::rectangle(re_img, box, cv::Scalar(0, 0, 255), 2);
        // put the color name on the countour
        cv::putText(
            re_img,
            "Red",
            box.tl(),
            cv::FONT_HERSHEY_SIMPLEX,
            1.0,
            cv::Scalar(255, 230, 70),
            2
        );
    }
// nows the mask and the img
    cv::imshow("mask", mask);
    cv::imshow("detections", re_img);
    cv::waitKey(0);
    return 0;
}