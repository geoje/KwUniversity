#include <stdio.h>
#include <string.h>

void compareStrings(const char* str1, const char* str2) {
	printf("str1: %s\n", str1);
	printf("str2: %s\n", str2);
	printf("length of str1: %d\n", strlen(str1));
	printf("length of str2: %d\n", strlen(str2));
	printf("%ssame\n", strcmp(str1, str2) == 0 ? "" : "not ");
}

int main()
{
	char str1[10], str2[10];
	scanf("%s %s", str1, str2);
	compareStrings(str1, str2);
}