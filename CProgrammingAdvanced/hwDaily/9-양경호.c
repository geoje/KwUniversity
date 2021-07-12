#include<stdio.h>

typedef struct
{
	int xpos;
	int ypos;
} Point;
void scale2x(Point* pp)
{
	pp->xpos *= 2;
	pp->ypos *= 2;
}

void main() {
	Point p[3];
	for (int i = 0; i < 3; i++) {
		scanf_s("%d %d", &p[i].xpos, &p[i].ypos);
		scale2x(p + i);
	}
	for (int i = 0; i < 3; i++) {
		printf("[%d] %d %d\n", i, (p + i)->xpos, (p + i)->ypos);
	}
}