#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat inp;

void add_text(Mat image, Rect rect, string text) {
	int x = rect.x + (rect.width - text.size() * 10) / 3; // Center horizontally
	int y = rect.y + rect.height / 1.8;
	cv::putText(image, text, cv::Point(x, y), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(0x00,0xFF, 0xFF), 2);
}


void draw_contours(vector<vector<Point> > contours, Mat output) {
	vector<Vec4i> hierarchy;
	for (size_t i = 0; i < contours.size(); i++) {
		drawContours(output, contours, (int)i, Scalar(0xFF, 0xFF, 0xFF), 2, LINE_8, hierarchy, 0);
	}
}

void draw_boundings_with_area(vector<vector<Point> > contours, Mat output) {
	Rect rect;
	for (size_t i = 0; i < contours.size(); i++) {
		rect = boundingRect(contours[i]);
		rectangle(output, rect, Scalar(0x00, 0xFF, 0x00), 2);
		add_text(output, rect, to_string(rect.area()));
	}
}



static void process(int th_val, void* usr_data)
{
	
	Mat bin;
	threshold(inp, bin, th_val, 255, THRESH_BINARY);

	Mat flood = bin.clone();
	floodFill(flood, cv::Point(0, 0), Scalar(255));

	Mat flood_inv;
	bitwise_not(flood, flood_inv);

	Mat binary = (bin | flood_inv);
	imshow("binary", binary);


	Mat contourImg;
	Canny(binary, contourImg, th_val, th_val * 2);

	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	findContours(contourImg, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE);
	
	Mat outputImg = Mat::zeros(contourImg.size(), CV_8UC3);
	draw_contours(contours, outputImg);
	draw_boundings_with_area(contours, outputImg);
	
	cv::putText(outputImg, to_string(contours.size()) + " objects detected", cv::Point(20, 60), FONT_HERSHEY_SIMPLEX, 1, Scalar(0,0,0xFF ), 2);
	
	
	imshow("outputImg", outputImg);


}

int main()
{
	string path = "images/coins.jpg";
	Mat src = imread(path, IMREAD_COLOR);

	Mat gry;
	cvtColor(src, gry, COLOR_BGR2GRAY);

	Mat blr;
	blur(gry, inp, Size(8, 8));

	namedWindow("binary", WINDOW_AUTOSIZE);

	int th_val = 75;
	createTrackbar("Threshold", "binary", &th_val, 255, process);

	waitKey(0);
	return 0;
}






/*Mat drawing = Mat::zeros(dst.size(), CV_8UC3);
RNG rng(123);
for (size_t i = 0; i < contours.size(); i++)
{
	Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
	drawContours(drawing, contours, (int)i, color, 2, LINE_8, hierarchy, 0);
}
imshow("output2", drawing);*/












/*
Canny(dst, dst, th_val, th_val * 2);

vector<vector<Point> > contours;
vector<Vec4i> hierarchy;
findContours(dst, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

Mat drawing = Mat::zeros(dst.size(), CV_8UC3);
RNG rng(123);
for (size_t i = 0; i < contours.size(); i++)
{
	Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
	drawContours(drawing, contours, (int)i, color, 2, LINE_8, hierarchy, 0);
}
imshow("output", drawing);
*/