// need "opencv_world***.dll"  in working directory
// need "opencv_world***d.dll" in working directory
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

Mat img;

int main()
{
	Mat in = imread("Lena.png");

	// cvtColor 함수로 변환
	Mat out1(in.rows, in.cols, CV_8UC3);
	cvtColor(in, out1, COLOR_BGR2YUV);

	// 직접 행렬 곱으로 변환
	Mat out2(in.rows, in.cols, CV_8UC3);
	int idx;
	uchar r, g, b, y, u, v;
	for (int i = 0; i < in.cols; i++)
		for (int j = 0; j < in.rows; j++) {
			idx = (i * in.cols + j) * 3;

			b = in.data[idx];
			g = in.data[idx + 1];
			r = in.data[idx + 2];

			y =  (0.257 * r) + (0.504 * g) + (0.098 * b) + 16;
			v =  (0.439 * r) - (0.368 * g) - (0.071 * b) + 128;
			u = -(0.148 * r) - (0.291 * g) + (0.439 * b) + 128;

			out2.data[idx] = y;
			out2.data[idx + 1] = u;
			out2.data[idx + 2] = v;
		}

	imshow("cvtColor", out1);
	imshow("MatrixConversion", out2);
	waitKey(0);
	return 0;
}