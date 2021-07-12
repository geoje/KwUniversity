#include <stdio.h>

int main(void)
{
	int num1, num2, temp;
	printf("두 개의 0이 아닌 양의 정수: ");
	scanf("%d %d", &num1, &num2);
	if (num1 > num2)
	{
		temp = num1;
		num1 = num2;
		num2 = temp;
	}
	for (; num1 <= num2; num1++)
	{
		for (int i = 1; i <= 9; i++)
			printf("%d * %d = %d\n", num1, i, num1 * i);
		printf("\n");
	}

	return 0;
}