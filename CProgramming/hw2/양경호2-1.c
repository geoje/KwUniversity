#include <stdio.h>

void main()
{
	int num;
	scanf("%d", &num);
	printf("%d\n", ~num + 1);
}