#include <stdio.h>

int main()
{
	int num, count = 1, sum = 0;
	scanf("%d", &num);
	while (count <= num)
	{
		printf("%d ", count);
		sum += count++;
	}
	printf("\n%d\n", sum);

	return 0;
}