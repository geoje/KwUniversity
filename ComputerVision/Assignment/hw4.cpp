#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

// src			: ���� �̹���
// k			: k-means�� k ��
// considerPos	: (x, y) ��ǥ �� ���� ����� ������ ����
Mat KMeansClustering(Mat src, int k, bool considerPos = false) {
	// 1. ����
	Mat points;			// �Է� ������
	Mat labels;			// �󺧸� ��
	Mat centers;		// k-means �����
	Mat dst;			// ��� ����

	// 2. �ʱ�ȭ
	points.create(src.rows * src.cols, considerPos ? 5 : 3, CV_32F);
	centers.create(k, 1, points.type());
	dst.create(src.size(), src.type());

	// 3. �Է� ������ ����
	if (considerPos)	// b, g, r ���� x, y ��ǥ���� ���
		for (int i = 0, n = 0; i < src.rows; i++)
			for (int j = 0; j < src.cols; j++, n++) {
				for (int k = 0; k < 3; k++)
					points.at<float>(n, k) = src.at<Vec3b>(i, j)[k];
				points.at<float>(n, 3) = i;
				points.at<float>(n, 4) = k;
			}
	else	// b, g, r ���� ���
		for (int i = 0, n = 0; i < src.rows; i++)
			for (int j = 0; j < src.cols; j++, n++)
				for (int k = 0; k < 3; k++)
					points.at<float>(n, k) = src.at<Vec3b>(i, j)[k];

	// 4. k-means �˰��� ����
	kmeans(
		points,						// �Է� ������
		k,							// Ŭ�������� ��
		labels,						// �󺧸� ��
		TermCriteria(
			TermCriteria::MAX_ITER |	// 10�� �ݺ� �ϰų�
			TermCriteria::EPS,			// 1�ȼ� ���Ϸ� �����̸� ����
			10,							// �ݺ� Ƚ��
			1.0),						// ��Ȯ��
		3,							// �ٸ� �ʱ� �� ����ϴ� �˰��� ���� Ƚ��
		KMEANS_PP_CENTERS,			// �ʱ� �߽ɰ� ���ϴ� �÷���
		centers						// k-means �����
	);

	// 5. Ŭ�����͸� ��� ���� ��ȯ
	for (int i = 0, n = 0; i < src.rows; i++)
		for (int j = 0; j < src.cols; j++, n++)
			for (int k = 0, cIdx = labels.at<int>(n); k < 3; k++)
				dst.at<Vec3b>(i, j)[k] =	// k-means ��������� ������ ����
				(uchar)centers.at<Vec3f>(cIdx, 0)[k];

	return dst;
}

int main() {
	Mat src = imread("fruits.jpg");

	imshow("Source", src);
	imshow("KMeansClustering (k=5, considerPos=false)", KMeansClustering(src, 5));
	imshow("KMeansClustering (k=10, considerPos=false)", KMeansClustering(src, 10));
	imshow("KMeansClustering (k=20, considerPos=false)", KMeansClustering(src, 20));

	imshow("KMeansClustering (k=5, considerPos=true)", KMeansClustering(src, 5, true));
	imshow("KMeansClustering (k=10, considerPos=true)", KMeansClustering(src, 10, true));
	imshow("KMeansClustering (k=20, considerPos=true)", KMeansClustering(src, 20, true));

	waitKey(0);
	return 0;
}