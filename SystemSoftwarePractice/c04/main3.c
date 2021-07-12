#include <stdio.h>
#include <stdlib.h>

int main() {
	int i;
	char* buffer1 = (char*)malloc(50 * sizeof(char));
	for(i = 0; i < 80; i++)
		buffer1[i] = 3;

	char* buffer2 = (char*)calloc(50, sizeof(char));
	for(i = 0; i < 50; i++)
		printf("%d ", buffer2[i]);

	printf("\n");
	return 0;
}
