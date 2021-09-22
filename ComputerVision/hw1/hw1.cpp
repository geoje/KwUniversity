// need "opencv_world453.dll"  in working directory
// need "opencv_world453d.dll" in working directory
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

Mat BilinearInterpolation_8UC1(Mat input, int width, int height) {
	// ��꿡 �ʿ��� ���
	const double ratioH = (input.rows - 1.0) / height;
	const double ratioW = (input.cols - 1.0) / width;

	// �Է� �̹��� ���ȭ
	cvtColor(input, input, cv::COLOR_RGB2GRAY);

	// ��� �̹��� �ʱ�ȭ
	Mat output(height, width, CV_8UC1);

	// ���
	for (int i = 0; i < output.rows; i++)
		for (int j = 0; j < output.cols; j++) {
			int ii = (int)floor(i * ratioH); // input�� row
			int jj = (int)floor(j * ratioW); // input�� col

			double b = i * ratioH - (int)(i * ratioH), a = 1 - b;
			double p = j * ratioW - (int)(j * ratioW), q = 1 - p;

			uchar B = input.data[ii * input.cols + jj];
			uchar C = input.data[ii * input.cols + jj + 1];
			uchar A = input.data[(ii + 1) * input.cols + jj];
			uchar D = input.data[(ii + 1) * input.cols + jj + 1];

			output.data[i * width + j] = q * (b * A + a * B) + p * (b * D + a * C);
		}

	return output;
}
Mat BilinearInterpolation_8UC3(Mat input, int width, int height) {
	// ��꿡 �ʿ��� ���
	const double ratioH = (input.rows - 1.0) / height;
	const double ratioW = (input.cols - 1.0) / width;

	// ��� �̹��� �ʱ�ȭ
	Mat output(height, width, CV_8UC3);

	// ���
	for (int i = 0; i < output.rows; i++)
		for (int j = 0; j < output.cols; j++) {
			int ii = (int)floor(i * ratioH); // input�� row
			int jj = (int)floor(j * ratioW); // input�� col

			int bIdx = (ii * input.cols + jj) * 3;
			int cIdx = (ii * input.cols + jj + 1) * 3;
			int aIdx = ((ii + 1) * input.cols + jj) * 3;
			int dIdx = ((ii + 1) * input.cols + jj + 1) * 3;
			int outIdx = (i * output.cols + j) * 3;

			// 3���� �÷��� ���� �ݺ�
			for (int col = 0; col < 3; col++) {
				double b = i * ratioH - (int)(i * ratioH), a = 1 - b;
				double p = j * ratioW - (int)(j * ratioW), q = 1 - p;

				output.data[outIdx + col] =
					q * (b * input.data[aIdx + col] + a * input.data[bIdx + col]) +
					p * (b * input.data[dIdx + col] + a * input.data[cIdx + col]);
			}
		}

	return output;
}

Mat Rotation_8UC1(Mat input, double degree) {
	// ��꿡 �ʿ��� ���
	const double radian = degree * M_PI / 180.0;
	const double cc = cos(radian), ss = sin(-radian);
	const double cenY = input.rows / 2.0, cenX = input.cols / 2.0;

	// �Է� �̹��� ���ȭ
	cvtColor(input, input, cv::COLOR_RGB2GRAY);

	// ��� �̹��� �ʱ�ȭ
	Mat output(input.rows, input.cols, CV_8UC1);

	// ��� - ���������� �ݴ�� ȸ������ ���� ����������
	for (int i = 0; i < output.rows; i++)
		for (int j = 0; j < output.cols; j++) {
			int ii = (int)(cenY + ((double)i - cenY) * cc - ((double)j - cenX) * ss);
			int jj = (int)(cenX + ((double)i - cenY) * ss + ((double)j - cenX) * cc);
			if (ii >= 0 && jj >= 0 && ii < input.rows && jj < input.cols)
				output.data[i * output.cols + j] = input.data[ii * input.cols + jj];
			else
				output.data[i * output.cols + j] = 0;
		}

	return output;
}
Mat Rotation_8UC3(Mat input, double degree) {
	// ��꿡 �ʿ��� ���
	const double radian = degree * M_PI / 180.0;
	const double cc = cos(radian), ss = sin(-radian);
	const double cenY = input.rows / 2.0, cenX = input.cols / 2.0;

	// ��� �̹��� �ʱ�ȭ
	Mat output(input.rows, input.cols, CV_8UC3);

	// ��� - ���������� �ݴ�� ȸ������ ���� ����������
	for (int i = 0; i < output.rows; i++)
		for (int j = 0; j < output.cols; j++) {
			int ii = (int)(cenY + ((double)i - cenY) * cc - ((double)j - cenX) * ss);
			int jj = (int)(cenX + ((double)i - cenY) * ss + ((double)j - cenX) * cc);
			
			int inIdx = (ii * input.cols + jj) * 3;
			int outIdx = (i * output.cols + j) * 3;

			if (ii >= 0 && jj >= 0 && ii < input.rows && jj < input.cols)
				for (int col = 0; col < 3; col++)
					output.data[outIdx + col] = input.data[inIdx + col];
			else
				for (int col = 0; col < 3; col++)
					output.data[outIdx + col] = 0;
		}

	return output;
}
Mat FullRotation_8UC3(Mat input, double degree) {
	// ��꿡 �ʿ��� ���
	const double radian = degree * M_PI / 180.0;
	const double cc = cos(radian), ss = sin(radian);
	const double inCenY = input.rows / 2.0, inCenX = input.cols / 2.0;

	// ©�� �κ��� ���� 4���� �𼭸� ��ǥ �ִ� �ּҰ� ã��
	int y1 = (int)abs(ceil((inCenX) * ss + (inCenY) * cc));
	int x1 = (int)abs(ceil((inCenX) * cc - (inCenY) * ss));
	int y2 = (int)abs(ceil((inCenX) * ss - (inCenY) * cc));
	int x2 = (int)abs(ceil((inCenX) * cc + (inCenY) * ss));
	const int outCenY = max(y1, y2), outCenX = max(x1, x2);

	// ��� �̹��� �ʱ�ȭ
	Mat output(outCenY * 2, outCenX * 2, CV_8UC3);

	// ��� - ���������� �ݴ�� ȸ������ ���� ����������
	for (int i = 0; i < output.rows; i++)
		for (int j = 0; j < output.cols; j++) {
			int ii = (int)(inCenY + ((double)j - outCenX) * ss + ((double)i - outCenY) * cc);
			int jj = (int)(inCenX + ((double)j - outCenX) * cc - ((double)i - outCenY) * ss);

			int inIdx = (ii * input.cols + jj) * 3;
			int outIdx = (i * output.cols + j) * 3;

			if (ii >= 0 && jj >= 0 && ii < input.rows && jj < input.cols)
				for (int col = 0; col < 3; col++)
					output.data[outIdx + col] = input.data[inIdx + col];
			else
				for (int col = 0; col < 3; col++)
					output.data[outIdx + col] = 0;
		}

	return output;
}

int main()
{
	Mat img_in = imread("Lena_256x256.png");

	imshow("Input", img_in);
	/*imshow("Resize1 436x436", BilinearInterpolation_8UC1(img_in, 436, 436));
	imshow("Resize1 512x512", BilinearInterpolation_8UC1(img_in, 512, 512));*/

	/*imshow("Resize2 436x436", BilinearInterpolation_8UC3(img_in, 436, 436));
	imshow("Resize2 512x512", BilinearInterpolation_8UC3(img_in, 512, 512));*/

	/*imshow("Rotate1 30", Rotation_8UC1(img_in, 30));
	imshow("Rotate1 45", Rotation_8UC1(img_in, 45));
	imshow("Rotate1 60", Rotation_8UC1(img_in, 60));*/

	/*imshow("Rotate2 30", Rotation_8UC3(img_in, 30));
	imshow("Rotate2 45", Rotation_8UC3(img_in, 45));
	imshow("Rotate2 60", Rotation_8UC3(img_in, 60));*/

	/* More Testcase */

	imshow("Resize 1", BilinearInterpolation_8UC3(img_in, 1024, 128));
	imshow("Resize 2", BilinearInterpolation_8UC3(img_in, 128, 1024));

	imshow("Rotate 1", FullRotation_8UC3(img_in, 115));
	imshow("Rotate 2", FullRotation_8UC3(img_in, 275));
	imshow("Rotate 3", FullRotation_8UC3(img_in, 415));
	imshow("Rotate 4", FullRotation_8UC3(img_in, 415));

	waitKey(0);
	return 0;
}