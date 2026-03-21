// required headers 
#include "opencv2/objdetect.hpp"
#include <iostream>
#include "opencv2/highgui.hpp"

#include "opencv2/imgproc.hpp"

#include "opencv2/videoio.hpp"

#include <opencv2/imgcodecs.hpp>

#include <string>

#include <vector>

#include <opencv2/core.hpp>

// namespaces to shorten the code
using namespace cv;

using namespace std;








int main(){


// below the img 
String path =  samples::findFile("/home/d22/Documents/cv_projects/opencv_colordetectionv2/src/redtest1.jpg"); // img to read
Mat img;

img   = imread(path,IMREAD_COLOR); // reading img



  Mat imghsv;
cvtColor(img,imghsv,COLOR_BGR2HSV);
Mat mask1, mask2, mask;
// minium and maximum value set.
Scalar lower_red1(0, 150, 127);
Scalar upper_red1(10, 255, 255);

Scalar lower_red2(170, 150, 127);
Scalar upper_red2(180, 255, 255);


// checks if the img is empty
if(img.empty())

    {   

cout << "Could not read the image: " << img << endl;

return 1;

    }

Mat background;



// hsv ranges are set
inRange(imghsv, lower_red1, upper_red1, mask1);
inRange(imghsv, lower_red2, upper_red2, mask2);
mask = mask1 | mask2;





vector < vector < Point>> contours;



vector <Rect>  redbox(contours.size());

Mat canny_out;

Canny(img,canny_out,100,100);




findContours(mask,contours,RETR_EXTERNAL,CHAIN_APPROX_SIMPLE);

// erode the img
  erode(mask, mask, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
// dilate the img
  dilate(mask, mask, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

// Draw contours and labels

for (size_t i = 0; i <  contours.size(); i++) {

if (contourArea(contours[i]) > 500) {
// here below on the redbox lies the exception.
redbox[i] = boundingRect(contours[i]);

rectangle(img, redbox[i].tl(), redbox[i].br(),Scalar(0, 0, 255), 2);

putText(img, "Red", redbox[i].tl(), cv::FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 255), 2);
cout << "Red_contours values " << contours.size() << endl;

            }

        }


// show img
imshow("mask",img);

waitKey(0);

destroyAllWindows();

}
