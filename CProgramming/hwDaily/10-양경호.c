#include <stdio.h>

int gMul;
int addTotal(int num)
{
	int sum;
	for (sum = 0; num > 0; num--)
		sum += num;

	return sum;
}
void mulTotal(int num)
{
	int mul;
	for (mul = 1; num > 0; num--)
		mul *= num;
	gMul = mul;
}

int main(void)
{
	int n;
	scanf("%d", &n);
	printf("addTotal(): %d\n", addTotal(n));
	mulTotal(n);
	printf("gMul: %d\n", gMul);

	return 0;
}