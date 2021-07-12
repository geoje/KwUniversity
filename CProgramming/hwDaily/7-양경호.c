#include<stdio.h>

int main() {
	int n;
	scanf("%d", &n);
	if (n < -10)
		printf("n < -10\n");
	else if (-10 <= n && n < 0)
			printf("-10 <= n < 0\n");
	else if (0 <= n && n < 10)
		printf("0 <= n < 10\n");
	else
		printf("n >= 10\n");

	return 0;
}