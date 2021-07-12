#include "main.h"

SDL_Texture* TextTexture(char *text, TTF_Font *ttf, SDL_Color *color) {
	SDL_Surface *surface = TTF_RenderText_Blended(ttf, text, *color);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	return texture;
}
void DrawText(SDL_Texture *texture, SDL_Rect rect, int align, double size) {
	if (size != 1) {
		rect.w *= size;
		rect.h *= size;
	}
	switch (align & 7) {
	case MIDDLE:
		rect.y -= rect.h / 2;
		break;
	case BOTTOM:
		rect.y -= rect.h;
		break;
	}
	switch (align & 56) {
	case CENTER:
		rect.x -= rect.w / 2;
		break;
	case RIGHT:
		rect.x -= rect.w;
		break;
	}

	SDL_RenderCopy(renderer, texture, NULL, &rect);
}