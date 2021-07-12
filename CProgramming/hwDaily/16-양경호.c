#include <stdio.h>

int main()
{
	int num[5], min, max, sum;
	for (int i = 0; i < 5; i++)
	{
		scanf("%d", &num[i]);
		if (i == 0)
		{
			min = num[i];
			max = num[i];
			sum = num[i];
		}
		else
		{
			min = min > num[i] ? num[i] : min;
			max = max < num[i] ? num[i] : max;
			sum += num[i];
		}
	}
	printf("min: %d\n", min);
	printf("max: %d\n", max);
	printf("sum: %d\n", sum);
}