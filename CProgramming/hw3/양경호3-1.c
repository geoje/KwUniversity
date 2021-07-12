#include <stdio.h>

void main()
{
	int num[5];
	for (int i = 0; i < 5; i++)
		scanf_s("%d", &num[i]);
	for (int i = 4; i >= 0; i--)
		printf("%d ", num[i]);
	printf("\n");
}