#include "main.h"

int checkPointInRect(SDL_Rect rect, int x, int y)
{
	if (x < rect.x)
		return 0;
	else if (x > rect.x + rect.w)
		return 0;
	else if (y < rect.y)
		return 0;
	else if (y > rect.y + rect.h)
		return 0;

	return 1;
}