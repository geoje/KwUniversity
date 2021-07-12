#include <stdio.h>

int add(int num1, int num2)
{
	return num1 + num2;
}
int sub(int num1, int num2)
{
	return num1 - num2;
}
int mul(int num1, int num2)
{
	return num1 * num2;
}
void printMsg()
{
	printf("계산 완료\n");
}
int main(void)
{
	int n1, n2;
	scanf("%d %d", &n1, &n2);
	printf("합: %d\n", add(n1, n2));
	printf("차: %d\n", sub(n1, n2));
	printf("곱: %d\n", mul(n1, n2));
	printMsg();

	return 0;
}