// need "opencv_world***.dll"  in working directory
// need "opencv_world***d.dll" in working directory
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

Mat img;

Mat GaussianNoise(Mat src, int stddev) {
	Mat noise(src.size(), CV_32SC1);
	Mat dst;

	randn(noise, 0, stddev);
	add(src, noise, dst, Mat(), CV_8U);

	return dst;
}
Mat SaltPepperNoise(Mat src, double noisePercentage) {
	int num = (int)(src.total() * noisePercentage);
	for (int i = 0; i < num; i++) {
		int x = rand() % src.cols;
		int y = rand() % src.rows;
		src.data[y * src.cols + x] = (i % 2) * 255;
	}
	return src;
}

int main()
{
	// 흑백으로 레나 읽기
	Mat lena = imread("Lena.png", IMREAD_GRAYSCALE);

	imshow("Original", lena);
	imshow("GaussianNoise", GaussianNoise(lena, 20));
	imshow("SaltPepperNoise", SaltPepperNoise(lena, 0.1));

	waitKey(0);
	return 0;
}