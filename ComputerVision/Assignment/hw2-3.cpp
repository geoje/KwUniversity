// need "opencv_world***.dll"  in working directory
// need "opencv_world***d.dll" in working directory
#include <cmath>
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
typedef vector<vector<double>> matrix;

Mat img;

// coeff cols, rows are 2n+1.
Mat Filter_8UC1(Mat input, matrix coeff) {
	Mat output(input.rows, input.cols, CV_8UC1);
	int n = coeff.size();
	int hn = (n - 1) / 2;

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
						avg += input.data[idx] * coeff[di][dj];
					}
				idx = i * input.cols + j;
				output.data[idx] = max(0, min(255, (int)round(avg)));
			}
		}

	return output;
}

int main()
{
	Mat in = imread("Lena.png");

	// Èæ¹é º¯È¯
	Mat gray(in.rows, in.cols, CV_8UC1);
	cvtColor(in, gray, COLOR_BGR2GRAY);
	imshow("Gray", gray);

	// Èå¸®°Ô
	imshow("Moving Average", Filter_8UC1(gray,
		{{1.0 / 9, 1.0 / 9, 1.0 / 9},
		 {1.0 / 9, 1.0 / 9, 1.0 / 9},
		 {1.0 / 9, 1.0 / 9, 1.0 / 9}}));

	// ¶óÇÃ¶ó½Ã¾È ÇÊÅÍ
	imshow("Laplacian1", Filter_8UC1(gray,
		{{0, 1, 0},
		 {1, -4, 1},
		 {0, 1, 0}}));
	imshow("Laplacian2", Filter_8UC1(gray,
		{{0, -1, 0},
		 {-1, 4, -1},
		 {0, -1, 0}}));
	imshow("Laplacian3", Filter_8UC1(gray,
		{{1, 1, 1},
		 {1, -8, 1},
		 {1, 1, 1}}));
	imshow("Laplacian4", Filter_8UC1(gray,
		{{-1, -1, -1},
		 {-1, 8, -1},
		 {-1, -1, -1}}));

	// »þÇÁ´×
	imshow("Sharpening1", Filter_8UC1(gray,
		{{0, -1, 0},
		 {-1, 5, -1},
		 {0, -1, 0}}));
	imshow("Sharpening2", Filter_8UC1(gray,
		{{-1, -1, -1},
		 {-1, 9, -1},
		 {-1, -1, -1}}));

	waitKey(0);
	return 0;
}