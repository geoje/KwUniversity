#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int xpos;
	int ypos;
}Point;

int main()
{
	Point* p = (Point*)malloc(sizeof(Point));

	scanf_s("%d %d", &p->xpos, &p->ypos);
	printf("%d %d\n", p->xpos, p->ypos);
	free(p);

	return 0;
}