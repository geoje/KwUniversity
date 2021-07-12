#include<stdio.h>

#define PI 3.141592

void main() {
	double r;
	scanf_s("%lf", &r);

	printf("원의 둘레: %lf\n", 2 * PI * r);
	printf("원의 넓이: %lf\n", PI * r * r);
}