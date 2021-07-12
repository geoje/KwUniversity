#include <stdio.h>

int sum(int n)
{
	return n <= 1 ? 1 : n + sum(n - 1);
}

int power(int n)
{
	return n <= 1 ? 2 : 2 * power(n - 1);
}

void main()
{
	int num;
	scanf("%d", &num);
	printf("sum %d\n", sum(num));
	printf("power %d\n", power(num));
}