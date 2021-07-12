#include <stdio.h>
void swap(char** arr) {	char* temp = arr[0];
	arr[0] = arr[1];
	arr[1] = temp;}
void printArray(char** arr, int len)
{
	int i;
	printf("Array ");
	for (i = 0; i<len; i++)
		printf("[%d]:%s, ", i, arr[i]);
	printf("\n");
}
void main()
{
	char* strArr[] = { "aaa", "bbb" };
	printArray(strArr, sizeof(strArr) / sizeof(char*));
	swap(strArr);
	printArray(strArr, sizeof(strArr) / sizeof(char*));
}