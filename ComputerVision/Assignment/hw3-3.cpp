// need "opencv_world***.dll"  in working directory
// need "opencv_world***d.dll" in working directory
#include <iostream>
#include <algorithm>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

Mat img;

Mat SaltPepperNoise(Mat src, double noisePercentage) {
	int num = (int)(src.total() * noisePercentage);
	for (int i = 0; i < num; i++) {
		int x = rand() % src.cols;
		int y = rand() % src.rows;
		src.data[y * src.cols + x] = (i % 2) * 255;
	}
	return src;
}
Mat MedianFilter(Mat src, int kernelSize) {
	Mat dst(src.rows, src.cols, CV_8UC1);
	int n = kernelSize;
	int hn = n / 2;
	double dn = (double)n * n;
	int hdn = dn / 2;

	int bRows = src.rows - hn;
	int bCols = src.cols - hn;
	int idx;

	for (int i = 0; i < src.rows; i++)
		for (int j = 0; j < src.cols; j++) {
			int y = i < hn ? hn : i >= bRows ? bRows - 1 : i;
			int x = j < hn ? hn : j >= bCols ? bCols - 1 : j;

			vector<uchar> v;
			for (int di = -hn; di <= hn; di++)
				for (int dj = -hn; dj <= hn; dj++) {
					idx = (y + di - hn) * src.cols + (x + dj - hn);
					v.push_back(src.data[idx]);
				}
			sort(v.begin(), v.end());

			idx = i * src.cols + j;
			dst.data[idx] = v[hdn];
		}

	return dst;
}

int main()
{
	// 흑백으로 레나 읽기
	Mat noiseLena, lena = imread("Lena.png", IMREAD_GRAYSCALE);
	imshow("Original", lena);

	//imshow("5% SaltPepperNoise", noiseLena = SaltPepperNoise(lena, 0.05));
	//imshow("5% SaltPepperNoise & 3x3 MedianFilter", MedianFilter(noiseLena, 3));

	//imshow("10% SaltPepperNoise", noiseLena = SaltPepperNoise(lena, 0.10));
	//imshow("10% SaltPepperNoise & 3x3 MedianFilter", MedianFilter(noiseLena, 3));

	imshow("25% SaltPepperNoise", noiseLena = SaltPepperNoise(lena, 0.25));
	imshow("25% SaltPepperNoise & 3x3 MedianFilter", noiseLena = MedianFilter(noiseLena, 3));
	imshow("25% Noise > 3x3 Median > 5x5 Median", MedianFilter(noiseLena, 3));

	waitKey(0);
	return 0;
}