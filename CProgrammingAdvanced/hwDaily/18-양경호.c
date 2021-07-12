#include <stdio.h>

void printString(const char* str) {
	printf("%s\n", str);
}
int main()
{
	char* str[3] = { "One", "Two", "Three" };
	void(*print)(const char*) = printString;
	for (int i = 0; i < 3; i++)
		print(str[i]);
}