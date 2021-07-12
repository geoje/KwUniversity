#pragma once
#include <SDL.h>
#include <SDL_ttf.h>

//text
typedef enum {
	TOP = 1,
	MIDDLE = 2,
	BOTTOM = 4,
	LEFT = 8,
	CENTER = 16,
	RIGHT = 32
} TextAlignFlags;
SDL_Texture* TextTexture(char *text, TTF_Font *ttf, SDL_Color *color);
void DrawText(SDL_Texture *texture, SDL_Rect rect, int align, double size);

//math
double radians(double angle);

//check
int checkPointInRect(SDL_Rect rect, int x, int y);

//color
extern const SDL_Color COLOR_BLACK;
extern const SDL_Color COLOR_WHITE;
void HSVtoRGB(float fH, float fS, float fV, float *fR, float *fG, float *fB);