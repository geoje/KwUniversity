#include <stdio.h>

void main() {
	int num[2];
	scanf("%d %d", num, num + 1);

	FILE *f = fopen("data.txt", "wt");
	fprintf(f, "%d %d", num[0], num[1]);
	fclose(f);

	f = fopen("data.txt", "rt");
	fprintf(f, "%d %d", num, num + 1);
	fclose(f);

	printf("%d %d\n", num[0], num[1]);
}