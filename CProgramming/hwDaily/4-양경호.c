#include <stdio.h>

int main(void)
{
	int numA = 9, numB = 2;
	printf("numA: %d, numB: %d\n", numA++, numB++);
	printf("numA: %d, numB: %d\n", numA, numB);
	printf("numA/numB: %d, numA%%numB: %d\n", numA / numB, numA % numB);
	printf("%d\n", (numA / numB) == (numA % numB));
}