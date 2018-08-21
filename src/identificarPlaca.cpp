#include <opencv2/opencv.hpp>
#include <iostream>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <vector>
using namespace std;
using namespace cv;

int main(int argc, char **argv) {

ros::init(argc, argv, "joao"); //Define um nome para o "nó"
ros::NodeHandle nh; //Cria o "nó" 

cv::Mat img_ori= cv::imread("/home/robotica/JMJ/src/brasil/src/Placa.jpg"); // ler a imagem
//if (!img_ori.data) 
//{
//std::cout << "Image file not found\n";
//return 1;
//}

cv::Mat img_threshold; 
// threshold image limiar da imagem 
cv::cvtColor(img_ori, img_threshold, CV_BGR2GRAY); // transforma pra cinza
cv::threshold(img_threshold,img_threshold, 150, 225, CV_THRESH_BINARY_INV);

cv::Mat binary;
cv::erode(img_threshold,binary,cv::Mat(),cv::Point(-1,-1),2);
cv::dilate(img_threshold,binary,cv::Mat(),cv::Point(-1,-1),3);

//Procurando contorno
cv::Mat blur_out(img_threshold);
vector<vector<Point> > contours;

vector<Point> points;

findContours(blur_out, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);

// Approximate contours to polygons + get bounding rects 
vector<vector<Point> > contours_poly( contours.size() );
vector<Rect> boundRect( contours.size() );
vector<Point2f>center( contours.size() );
vector<float>radius( contours.size() );

for( int i = 0; i < contours.size(); i++ )
{
approxPolyDP( cv::Mat(contours[i]), contours_poly[i], 3, true );
boundRect[i] = cv::boundingRect( cv::Mat(contours_poly[i]) );
}

//Draw bounding rect
int x=1;
cv::Mat drawing(img_ori);
for( int i = 0; i< contours.size(); i++ )
{
    std::stringstream s;
    s << x;
    std::string str1 = s.str();
    cv::Scalar color = cv::Scalar(0,255,0);

    if(boundRect[i].height>2 && boundRect[i].width>1)
    {
    rectangle( drawing, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0 );
    cv::Rect region_of_interest = cv::Rect(boundRect[i].x,boundRect[i].y,boundRect[i].width,boundRect[i].height);
    cv:: Mat imageroi=binary(region_of_interest);

    std::stringstream ss;
    ss << i;
    std::string str = ss.str();
    const char *cstr = str.c_str();

//    cv::imwrite( str1+".jpg", imageroi );

//    cvNamedWindow(cstr,CV_WINDOW_AUTOSIZE);
//    imshow(str,imageroi);
    x++;
    }
}

imshow("Box",img_ori);

cvWaitKey(0);
ros::spin();// fica em loop, e só encerra com o Ctrl + C

return 0;

}
