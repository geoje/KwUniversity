#include <stdio.h>

int main()
{
	double arr[5] = {1.1, 2.2, 3.3, 4.4, 5.5 };
	double* parr = arr;
	for (int i = 0; i < 5; i++)
	{
		*(parr + i) *= 2;
		printf("%lf\n", *(parr + i));
	}
}