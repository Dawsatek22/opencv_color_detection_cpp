#include <iostream>
#include <vector>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

int main()
{
    cv::String const path =
        "/home/d22/Documents/cv_projects/opencv_colordetectionv2/src/baboon.jpg";

    cv::Mat img = cv::imread(path, cv::IMREAD_COLOR);
    if (img.empty()) {
        std::cerr << "Could not read image: " << path << '\n';
        return 1;
    }

    cv::Mat hsv;
    cv::cvtColor(img, hsv, cv::COLOR_BGR2HSV);

    // Red wraps around hue=0, so use two ranges.
    cv::Scalar lower_red1(0, 150, 127);
    cv::Scalar upper_red1(10, 255, 255);
    cv::Scalar lower_red2(170, 150, 127);
    cv::Scalar upper_red2(180, 255, 255);

    cv::Mat mask1, mask2, mask;
    cv::inRange(hsv, lower_red1, upper_red1, mask1);
    cv::inRange(hsv, lower_red2, upper_red2, mask2);
    mask = mask1 | mask2;

    // Clean noise before contour extraction.
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5));
    cv::erode(mask, mask, kernel);
    cv::dilate(mask, mask, kernel);

    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    for (std::size_t i = 0; i < contours.size(); ++i) {
        double const area = cv::contourArea(contours[i]);
        if (area <= 500) {
            continue;
        }

        cv::Rect const box = cv::boundingRect(contours[i]);
        cv::rectangle(img, box, cv::Scalar(0, 0, 255), 2);
        cv::putText(
            img,
            "Red",
            box.tl(),
            cv::FONT_HERSHEY_SIMPLEX,
            1.0,
            cv::Scalar(0, 0, 255),
            2
        );
    }

    cv::imshow("mask", mask);
    cv::imshow("detections", img);
    cv::waitKey(0);
    return 0;
}
