#include <stdio.h>
#include <stdlib.h>

void main() {
	int* num = (int*)malloc(sizeof(int) * 10);
	for(int i = 0; i < 10; i++)
		num[i] = i;

	for(int i = 0; i < 10; i++)
		printf("%d ", num[i]);
	printf("\n");

	num = (int*)realloc(num, 20 * sizeof(int));
	for(int i = 0; i < 20; i++)
		num[i] = i;
	for(int i = 0; i < 20; i++)
		printf("%d ", num[i]);
	printf("\n");

	free(num);
}
