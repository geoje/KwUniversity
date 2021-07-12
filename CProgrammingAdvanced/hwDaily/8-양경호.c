#include<stdio.h>

typedef struct {
	char name[20];
	int age;
}Person;

void main() {
	Person p[3];
	Person *pptr = p;

	for(int i = 0; i < 3; i++)
		scanf("%s %d", &p[i].name, &p[i].age);

	for (int i = 0; i < 3; i++)
		printf("Name:%s, Age:%d\n", (pptr + i)->name, (pptr +i)->age);
}