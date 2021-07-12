#include <stdio.h>

void main()
{
	int a, b, result;
	scanf("%d %d", &a, &b);
	result = (~a + 1) << b;
	printf("-1 * %d * 2^%d = %d", a, b, result);
}