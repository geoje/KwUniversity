#include <stdio.h>

int main()
{
	while (1)
	{
		char c;
		scanf_s("%c", &c);
		if (c == 10)
			break;
		printf("%c %d\n", c, c);
	}
}