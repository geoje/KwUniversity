#include "main.h"
#include <math.h>

SDL_Texture *pri_texture_title1, *pri_texture_title2, *pri_texture_start;
SDL_Rect pri_rect_title1, pri_rect_title2, pri_rect_start;
int pri_title_size_angle = 0;
Mix_Chunk *pri_chunk_select;

void PrimaryInit() {
	//Title 'NUMBER'
	const char *title1 = "NUMBER";
	TTF_Font *ttf_title = TTF_OpenFont("timeburnerbold.ttf", 80);
	pri_rect_title1.x = SCREEN_WIDTH / 2;
	pri_rect_title1.y = 160;
	TTF_SizeText(ttf_title, title1, &pri_rect_title1.w, &pri_rect_title1.h);
	pri_texture_title1 = TextTexture(title1, ttf_title, &COLOR_WHITE);

	//Title 'PLUS+'
	const char *title2 = "PLUS";
	pri_rect_title2.x = 260;
	pri_rect_title2.y = 220;
	TTF_SizeText(ttf_title, title2, &pri_rect_title2.w, &pri_rect_title2.h);
	pri_texture_title2 = TextTexture(title2, ttf_title, &COLOR_WHITE);
	TTF_CloseFont(ttf_title);

	//Start
	const char *start = "Start to press enter or click";
	pri_rect_start.x = SCREEN_WIDTH / 2;
	pri_rect_start.y = 360;
	TTF_Font *ttf_start = TTF_OpenFont("timeburnernormal.ttf", 24);
	TTF_SizeText(ttf_start, start, &pri_rect_start.w, &pri_rect_start.h);
	SDL_Color color_start = { 200, 200, 200 };
	pri_texture_start = TextTexture(start, ttf_start, &color_start);
	TTF_CloseFont(ttf_start);

	//Sound
	pri_chunk_select = Mix_LoadWAV("select.wav");
}
void PrimaryStep() {
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT) {
			quit = 1;
			return;
		}
		else if (e.type == SDL_KEYDOWN)
			switch (e.key.keysym.sym) {
			case SDLK_ESCAPE:
				quit = 1;
				return;
			case SDLK_RETURN:
				Mix_PlayChannel(-1, pri_chunk_select, 0);
				ChangeMap(MAP_DIFFICULTY);
				return;
			}
		else if (e.type == SDL_MOUSEBUTTONDOWN) {
			Mix_PlayChannel(-1, pri_chunk_select, 0);
			ChangeMap(MAP_DIFFICULTY);
			return;
		}
	}
	float r, g, b;
	//HSVtoRGB(pri_title_size_angle, 80, 80, &r, &g, &b);
	//SDL_SetRenderDrawColor(ren, r, g, b, 255);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	//Title
	pri_title_size_angle += pri_title_size_angle < 360 ? 1 : -360;
	DrawText(pri_texture_title1, pri_rect_title1, CENTER | MIDDLE, 0.9 + sin(radians(pri_title_size_angle)) / 10);
	DrawText(pri_texture_title2, pri_rect_title2, CENTER | MIDDLE, 0.6 + sin(radians(pri_title_size_angle)) / 10);
	
	//Start
	pri_rect_start.y = 360 + sin(radians(pri_title_size_angle * 2)) * 10;
	DrawText(pri_texture_start, pri_rect_start, CENTER | MIDDLE, 1);

	SDL_RenderPresent(renderer);
}
void PrimaryQuit() {
	SDL_DestroyTexture(pri_texture_title1);
	SDL_DestroyTexture(pri_texture_title2);
	SDL_DestroyTexture(pri_texture_start);
}