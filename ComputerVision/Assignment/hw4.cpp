#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main() {
	// 1. 선언
	const int k = 10;	// k 값
	Mat src, dst;		// 원본 및 결과 영상
	Mat points;			// 입력 데이터
	Mat labels;	// 라벨링 값
	Mat centers;		// k-means 결과값

	// 2. 초기화
	src = imread("fruits.jpg");
	points.create(src.rows * src.cols, 1, CV_32FC3);
	centers.create(k, 1, points.type());
	dst.create(src.size(), src.type());

	// 3. 입력 데이터 생성
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

	// 6. 결과 영상 표시
	imshow("Source", src);
	imshow("Result", dst);
	waitKey(0);
	return 0;
}