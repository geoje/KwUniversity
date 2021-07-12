#include <stdio.h>

void main()
{
	for (int i = 1; i <= 100; i++)
	{
		printf("%-7d", i);
		if (i % 5 == 0)
			printf("\n");
	}
}