#include <stdio.h>

int max(int *arr, int length)
{
	int max = arr[0];
	for(int i = 1; i < length; i++)
			max = arr[i] > max ? arr[i] : max;
	return max;
}

void main()
{
	int num[5], length = sizeof(num) / sizeof(int);
	for (int i = 0; i < length; i++)
		scanf_s("%d", &num[i]);
	printf("max: %d\n", max(num, length));
}