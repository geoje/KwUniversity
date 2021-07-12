#include <stdio.h>

void swap(int *num1, int *num2, int *num3, int *num4)
{
	int temp = *num4;
	*num4 = *num3;
	*num3 = *num2;
	*num2 = *num1;
	*num1 = temp;
}

void main()
{
	int i1, i2, i3, i4;
	scanf("%d %d %d %d", &i1, &i2, &i3, &i4);
	swap(&i1, &i2, &i3, &i4);
	printf("%d %d %d %d\n", i1, i2, i3, i4);
}