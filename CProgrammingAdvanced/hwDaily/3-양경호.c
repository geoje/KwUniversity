#include <stdio.h>

int isPrime(int num) {
	for (int i = 2; i < num; i++)
		if (num % i == 0)
			return 0;
	return 1;
}

void print99Dan(int num) {
	for (int i = 1; i <= 9; i++)
		printf("%d * %d = %d\n", num, i, num * i);
}

void main() {
	int n;
	scanf("%d", &n);

	if (n % 2 == 0)
		print99Dan(n);
	else if (n % 3 == 0)
		for (int i = 2; i <= n; i++)
		{
			if (isPrime(i))
				printf("%d ", i);
		}
	else
		for (int i = 2; i <= n; i++)
			if (isPrime(i))
			{
				print99Dan(i);
				printf("\n");
			}
	printf("\n");
}