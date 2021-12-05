#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

// src			: 원본 이미지
// k			: k-means의 k 값
// considerPos	: (x, y) 좌표 값 또한 고려할 것인지 여부
Mat KMeansClustering(Mat src, int k, bool considerPos = false) {
	// 1. 선언
	Mat points;			// 입력 데이터
	Mat labels;			// 라벨링 값
	Mat centers;		// k-means 결과값
	Mat dst;			// 결과 영상

	// 2. 초기화
	points.create(src.rows * src.cols, considerPos ? 5 : 3, CV_32F);
	centers.create(k, 1, points.type());
	dst.create(src.size(), src.type());

	// 3. 입력 데이터 생성
	if (considerPos)	// b, g, r 색상에 x, y 좌표까지 고려
		for (int i = 0, n = 0; i < src.rows; i++)
			for (int j = 0; j < src.cols; j++, n++) {
				for (int k = 0; k < 3; k++)
					points.at<float>(n, k) = src.at<Vec3b>(i, j)[k];
				points.at<float>(n, 3) = i;
				points.at<float>(n, 4) = k;
			}
	else	// b, g, r 색상만 고려
		for (int i = 0, n = 0; i < src.rows; i++)
			for (int j = 0; j < src.cols; j++, n++)
				for (int k = 0; k < 3; k++)
					points.at<float>(n, k) = src.at<Vec3b>(i, j)[k];

	// 4. k-means 알고리즘 실행
	kmeans(
		points,						// 입력 데이터
		k,							// 클러스터의 수
		labels,						// 라벨링 값
		TermCriteria(
			TermCriteria::MAX_ITER |	// 10번 반복 하거나
			TermCriteria::EPS,			// 1픽셀 이하로 움직이면 멈춤
			10,							// 반복 횟수
			1.0),						// 정확도
		3,							// 다른 초기 라벨 사용하는 알고리즘 실행 횟수
		KMEANS_PP_CENTERS,			// 초기 중심값 정하는 플래그
		centers						// k-means 결과값
	);

	// 5. 클러스터링 결과 영상 변환
	for (int i = 0, n = 0; i < src.rows; i++)
		for (int j = 0; j < src.cols; j++, n++)
			for (int k = 0, cIdx = labels.at<int>(n); k < 3; k++)
				dst.at<Vec3b>(i, j)[k] =	// k-means 결과값에서 데이터 추출
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