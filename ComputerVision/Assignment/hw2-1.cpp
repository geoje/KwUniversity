// need "opencv_world***.dll"  in working directory
// need "opencv_world***d.dll" in working directory
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

Mat img;

void PrintColorData(int x, int y) {
	int idx = (y * img.cols + x) * 3;
	printf("(%d, %d) %d, %d, %d\n", x, y,
		img.data[idx], img.data[idx + 1], img.data[idx + 2]);
}

int main()
{
	img = imread("20211021_163346.jpg");
	PrintColorData(0, 0);
	PrintColorData(1000, 2000);
	PrintColorData(444, 3590);

	return 0;
}