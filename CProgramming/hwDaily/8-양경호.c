#include <stdio.h>

int main() {
	int num, sum = 0;
	while (1)
	{
		scanf("%d", &num);
		if (num == 0)
			break;
		sum += num;
	}
	printf("sum: %d\n", sum);

	printf("choose potion: ");
	scanf("%d", &num);
	switch (num)
	{
	case 1:
		printf("2*sum = %d\n", 2 * sum);
		break;
	case 2:
		printf("sum*sum = %d\n", sum * sum);
		break;
	default:
		printf("sum = %d\n", sum);
		break;
	}

	return 0;
}