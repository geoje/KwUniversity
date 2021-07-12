#include <stdio.h>

int main(void)
{
	int num;
	printf("2 이상의 정수: ");
	scanf("%d", &num);
	for (int i = 2, j; i <= num; i++)
	{
		for (j = 2; j < i; j++)
			if (i % j == 0)
				break;
		if (j == i)
			printf("%d ", i);
	}
	printf("\n");
	return 0;
}