#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void demo1(void) {
	Mat image = Mat::zeros(300, 600, CV_8UC3);
	circle(image, Point(250, 150), 100, Scalar(0, 255, 128), -100);
	circle(image, Point(350, 150), 100, Scalar(255, 255, 255), -100);
	imshow("Circles", image);
}

void demo2(void) 
{
	std::string path = "images/image1.jpeg";
	Mat img1 = imread(path, IMREAD_COLOR);
	imshow("Color", img1);

	Mat img2 = imread(path, IMREAD_GRAYSCALE);
	imshow("Gray Scale", img2);
}

void demo3(void)
{
	//** Read an image from file
	std::string path = "images/image2.png";
	Mat img1 = imread(path, IMREAD_COLOR);
	imshow("Image1", img1);

	//** Clone image
	Mat img2 = img1.clone();

	//** Resize image
	resize(img2, img2, cv::Size(img2.size().width/2., img2.size().height / 2));
	imshow("Image2", img2);

	//** Convert to gray scale
	Mat img3;
	cvtColor(img2, img3, COLOR_BGR2GRAY);
	imshow("Image3", img3);

	//** Canny edge detection
	Mat img4;
	Canny(img3, img4, 128, 128);
	imshow("Image4", img4);
}

int main()
{
	demo3();
	waitKey(0);
	return 0;
}