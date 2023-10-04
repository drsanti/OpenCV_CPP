#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat inp;

static void process(int th_val, void* usr_data)
{
	Mat bin;
	threshold(inp, bin, th_val, 255, THRESH_BINARY);
	imshow("04 bin", bin);

	Mat flood = bin.clone();
	floodFill(flood, cv::Point(0, 0), Scalar(255));
	imshow("05 flood", flood);

	Mat flood_inv;
	bitwise_not(flood, flood_inv);
	imshow("06 flood_inv", flood_inv);

	Mat output = (bin | flood_inv);
	imshow("output", output);
}

int main_ex02()
{
	string path = "images/coins.jpg";
	Mat src = imread(path, IMREAD_COLOR);
	imshow("01 original", src);

	Mat gry;
	cvtColor(src, gry, COLOR_BGR2GRAY);
	imshow("02 gray", gry);

	Mat blr;
	blur(gry, inp, Size(8, 8));
	imshow("03 blur", inp);


	namedWindow("output", WINDOW_AUTOSIZE);

	int th_val = 75;
	createTrackbar("Threshold", "output", &th_val, 255, process);

	waitKey(0);
	return 0;
}

