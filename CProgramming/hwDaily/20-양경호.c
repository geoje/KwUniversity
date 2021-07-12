#include <stdio.h>
#include <string.h>

void main()
{
	char str1[20], str2[20], str3[20];
	scanf("%s %s", str1, str2);
	printf("str1: %s\n", str1);
	printf("str2: %s\n", str2);
	printf("length of str1: %d\n", strlen(str1));
	printf("length of str2: %d\n", strlen(str2));
	strcpy(str3, str1);
	strcat(str1, str2);
	printf("str1+str2: %s\n", str1);
	printf("%ssame\n", strcmp(str3, str2) == 0 ? "" : "not ");
}