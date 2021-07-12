#include <stdio.h>

int main(void)
{
	for (int i = 9; i > 0; i--)
	{
		for (int j = 1; j <= 9; j++)
			printf("%d * %d = %d\n", i, j, i * j);
		printf("\n");
	}

	return 0;
}