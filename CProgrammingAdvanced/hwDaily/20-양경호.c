#include <stdio.h>

typedef struct {
	int xpos;
	int ypos;
}Point;

int main()
{
	int n;
	scanf("%d", &n);

	Point *points = (Point*)calloc(n, sizeof(Point));

	for (int i = 0; i < n; i++) {
		points[i].xpos = i;
		points[i].ypos = i*2;
	}
	for (int i = 0; i < n; i++)
		printf("%d %d\n", points[i].xpos, points[i].ypos);
	free(points);
}