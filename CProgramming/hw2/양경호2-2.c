#include <stdio.h>

void main()
{
	int num1;
	double num2;
	scanf("%d %lf", &num1, &num2);
	printf("%10d%10d%10d\n", num1 * 2, num1 * 4, num1 * 8);
	printf("%10.2lf%10.2lf%10.2lf\n", num2 * 2, num2 * 4, num2 * 8);
}