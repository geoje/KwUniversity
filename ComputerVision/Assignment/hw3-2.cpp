// C:\opencv\build\x64\vc15\bin\opencv_world***[d].dll
// need "opencv_world***.dll"  in working directory
// need "opencv_world***d.dll" in working directory
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
typedef vector<vector<double>> matrix;

Mat img;

Mat SmoothingFilter(Mat input, int kernelSize) {
	Mat output(input.rows, input.cols, CV_8UC1);
	int n = kernelSize;
	int hn = (n - 1) / 2;
	double dn = (double)n * n;

	int bRows = input.rows - hn;
	int bCols = input.cols - hn;
	int idx;

	for (int i = 0; i < input.rows; i++)
		for (int j = 0; j < input.cols; j++) {
			// Boundary
			if (i < hn || j < hn || i >= bRows || j >= bCols) {
				idx = i * input.cols + j;
				output.data[idx] = input.data[idx];
			}
			// Inner
			else {
				double avg = 0;
				for (int di = 0; di < n; di++)
					for (int dj = 0; dj < n; dj++) {
						idx = (i + di - hn) * input.cols + (j + dj - hn);
						avg += input.data[idx] / dn;
					}
				idx = i * input.cols + j;
				output.data[idx] = max(0, min(255, (int)round(avg)));
			}
		}

	return output;
}
Mat GaussianNoise(Mat src, int stddev) {
	Mat noise(src.size(), CV_32SC1);
	Mat dst;

	randn(noise, 0, stddev);
	add(src, noise, dst, Mat(), CV_8U);

	return dst;
}

int main()
{
	// 흑백으로 레나 읽기
	Mat lena = imread("Lena.png", IMREAD_GRAYSCALE);

	imshow("Original", lena);

	imshow("10 GaussianNoise & 3x3 SmoothingFilter", SmoothingFilter(GaussianNoise(lena, 10), 3));
	imshow("20 GaussianNoise & 3x3 SmoothingFilter", SmoothingFilter(GaussianNoise(lena, 20), 3));
	imshow("30 GaussianNoise & 3x3 SmoothingFilter", SmoothingFilter(GaussianNoise(lena, 30), 3));

	imshow("10 GaussianNoise & 5x5 SmoothingFilter", SmoothingFilter(GaussianNoise(lena, 10), 5));
	imshow("20 GaussianNoise & 5x5 SmoothingFilter", SmoothingFilter(GaussianNoise(lena, 20), 5));
	imshow("30 GaussianNoise & 5x5 SmoothingFilter", SmoothingFilter(GaussianNoise(lena, 30), 5));

	waitKey(0);
	return 0;
}