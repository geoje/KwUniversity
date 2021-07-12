#include <stdio.h>

void main() {
	int i;
	double d;
	char c;
	scanf("%d %lf %c", &i, &d, &c);
	printf("i: %d, %d\n", i, &i);
	printf("d: %lf, %d\n", d, &d);
	printf("c: %c, %d\n\n", c, &c);
	
	int *pi = &i;
	double *pd = &d;
	char *pc = &c;
	*pi += 1;
	*pd += 1;
	*pc += 1;
	printf("i+1: %d\n", i);
	printf("d+1: %lf\n", d);
	printf("c+1: %c\n\n", c);

	printf("size of pi: %d\n", sizeof(pi));
	printf("size of pd: %d\n", sizeof(pd));
	printf("size of pc: %d\n", sizeof(pc));
}
