#include <stdio.h>

typedef struct
{
	char name[10];
	int age;
}Person;

void main()
{
	Person person;
	scanf("%s %d", person.name, &person.age);
	printf("name: %s\n", person.name);
	printf("age: %d\n", person.age);
}