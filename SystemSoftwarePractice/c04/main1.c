#include <stdio.h>
#include <stdlib.h>

int main() {
	int size, i;

	scanf("%d", &size);
	int* buffer = (int*)malloc(size * sizeof(int));

	buffer[0] = buffer[1] = 1;
	for(i = 0; i < size; i++) {
		buffer[i + 2] = buffer[i + 1] + buffer[i]; //violation
		printf("%d ", buffer[i]);
	}
	printf("\n");
	return 0;
}
