#include <stdio.h>

char convertASCII(char c)
{
	if (c >= 48 && c <= 57)
		return c;
	else if (c >= 65 && c <= 90)
		return c + 32;
	else if (c >= 97 && c <= 122)
		return c - 32;
	else
		return 0;
}

void main()
{
	char c;
	while (1)
	{
		scanf("%c", &c);
		if (c == 10)
			continue;
		c = convertASCII(c);
		if (!c)
		{
			printf("종료\n");
			break;
		}
		printf("출력: %c\n", c);
	}
}