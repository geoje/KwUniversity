#include <stdio.h>

void square(double* num)
{
	*num *= *num;
}

void main()
{
	double dvar;
	scanf("%lf", &dvar);
	square(&dvar);
	printf("%lf\n", dvar);
}