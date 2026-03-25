#include <iostream>
#include <vector>

#include <opencv2/opencv.hpp>

int main()
{
    cv::String const path =
        "/home/d22/Documents/cv_projects/opencv_colordetection_cpp/images/opencv-logo.png";

    cv::Mat img = cv::imread(path, cv::IMREAD_COLOR);
     
    cv::Mat re_img;
    cv::resize(img,re_img,cv::Size(1200,1200));
    if (re_img.empty()) {
        std::cerr << "Could not read image: " << path << '\n';
        return 1;
    }

    cv::Mat hsv;
    cv::cvtColor(re_img, hsv, cv::COLOR_BGR2HSV);

    // creates hsv values for detecting countours
    cv::Scalar lower_color1(6, 150, 2);
    cv::Scalar upper_color1(120, 255, 255);
    cv::Scalar lower_color2(134, 175, 125);
    cv::Scalar upper_color2(22, 255, 255);
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
        cv::rectangle(re_img, box, cv::Scalar(255, 0, 0), 2);
        // put the color name on the countour
        cv::putText(
            re_img,
            "Blue",
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