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
	printf("��� �Ϸ�\n");
}
int main(void)
{
	int n1, n2;
	scanf("%d %d", &n1, &n2);
	printf("��: %d\n", add(n1, n2));
	printf("��: %d\n", sub(n1, n2));
	printf("��: %d\n", mul(n1, n2));
	printMsg();

	return 0;
}