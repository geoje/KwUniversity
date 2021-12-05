#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main() {
	// 1. ����
	const int k = 10;	// k ��
	Mat src, dst;		// ���� �� ��� ����
	Mat points;			// �Է� ������
	Mat labels;	// �󺧸� ��
	Mat centers;		// k-means �����

	// 2. �ʱ�ȭ
	src = imread("fruits.jpg");
	points.create(src.rows * src.cols, 1, CV_32FC3);
	centers.create(k, 1, points.type());
	dst.create(src.size(), src.type());

	// 3. �Է� ������ ����
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

	// 6. ��� ���� ǥ��
	imshow("Source", src);
	imshow("Result", dst);
	waitKey(0);
	return 0;
}