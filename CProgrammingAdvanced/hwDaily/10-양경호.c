#include<stdio.h>

#define PI 3.141592

void main() {
	double r;
	scanf_s("%lf", &r);

	printf("���� �ѷ�: %lf\n", 2 * PI * r);
	printf("���� ����: %lf\n", PI * r * r);
}