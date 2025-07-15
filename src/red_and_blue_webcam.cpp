
// This is a code to detect red and blue colors in with opencv and c++ with a camera.
// it not that accurate at the moment so it is stil in the  works
#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include<opencv2/opencv.hpp>
#include <string>
using namespace cv;
using namespace std;
char s = 's';

int main(){
// The minium and maximum values of red and blue colors.
int min_blue = (92,62,32);
int  max_blue=  (135,176,126);
    
int   min_red = (163,163,116);
int  max_red = (1,255,169);


VideoCapture cam(0);
Mat frame, red_threshold , blue_threshold;
Mat hsv_red;
Mat hsv_blue;

 
// Now checks if the camera is opened.
if (! cam.isOpened() ) {

cout << "camera is not open"<< '\n';

 {
        if( frame.empty() )
        {
            cout << "--(!) No captured frame -- Break!\n";
            
        {

        }}
 
    
      
 
    
 
 
    }
 

}
while ( cam.read(frame) ) {


  

// cv::COLOR_BGR2HSV did not detect anyting in c++ but it worked in python.
     cvtColor(frame,hsv_red,COLOR_BGRA2GRAY);
   cvtColor(frame,hsv_blue,COLOR_BGRA2GRAY);
// ranges colors.
   inRange(hsv_red,Scalar(min_red),Scalar(max_red),red_threshold);
   inRange(hsv_blue,Scalar(min_blue),Scalar(max_blue),blue_threshold);
// Creates countours red and blue. 
   vector<vector<Point>> red_contours;
   vector<vector<Point>> blue_contours;
   // Now finds contours. 
        findContours(red_threshold, red_contours, RETR_TREE, CHAIN_APPROX_SIMPLE);
 findContours(blue_threshold, blue_contours, RETR_TREE, CHAIN_APPROX_SIMPLE);
vector<Rect> boundingBox_red (red_contours.size());
 vector<Rect> boundingBox_blue(blue_contours.size());

        // detect red contours and labels colors with rectangle.
        for (size_t i = 0; i< red_contours.size(); i++ ) {
          if (contourArea(red_contours[i]) > 500) {
           boundingBox_red[i] = boundingRect(red_contours[i]);
           rectangle(frame, boundingBox_red[i].tl(), boundingBox_red[i].br(),Scalar(10,0,105), 2);
           putText(frame, "Red",boundingBox_red[i].tl(),1,1,Scalar(10,80,255), 2);
           cout << "The red contour value is:" << boundingBox_blue[i]  << '\n';
         } }
   

        // detect blue contours and labels colors with rectangle. 
        for (size_t i = 0; i< blue_contours.size(); i++ ) {
        if (contourArea(blue_contours[i]) > 500) {
           boundingBox_blue[i] = boundingRect(blue_contours[i]);
            rectangle(frame, boundingBox_blue[i].tl() ,boundingBox_blue[i].br(),Scalar(104,50,50),2);
         putText(frame, "blue", boundingBox_blue[i].tl(),1,1,Scalar(10,80,255), 2);
         cout << "The blue contour value is:" << boundingBox_blue[i] << '\n';
        } }
   

   imshow("red and blue detection",frame); // detect colors and open camera

if ( waitKey(1) == (s) ) { // s means stop showing window

    cam.release(); // releases camera.
 
}
}}
    