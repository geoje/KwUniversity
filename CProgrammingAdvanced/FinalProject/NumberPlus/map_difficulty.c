#include "main.h"

SDL_Texture *dif_texture_title, *dif_texture_dif[DIFFICULTY];
SDL_Rect dif_rect_title, dif_rect_dif[DIFFICULTY], dif_rect_dif_text[DIFFICULTY], *dif_rect_mini[DIFFICULTY];
TTF_Font *ttf_dif;
const char *dif_text_dif[] = { "Easy", "Normal", "Hard", "Hell" };
int dif_selected_index = 0, dif_selected_index_previous = 0;
Mix_Chunk *dif_chunk_choose, *dif_chunk_select, *dif_chunk_close;

void DifSelectedIndexChanged(int *now, int *previous);

void DifficultyInit() {
	//Title
	const char *title = "Select difficulty level";
	TTF_Font *ttf_title = TTF_OpenFont("timeburnerbold.ttf", 36);
	dif_rect_title.x = SCREEN_WIDTH / 2;
	dif_rect_title.y = 20;
	TTF_SizeText(ttf_title, title, &dif_rect_title.w, &dif_rect_title.h);
	dif_texture_title = TextTexture(title, ttf_title, &COLOR_WHITE);
	TTF_CloseFont(ttf_title);

	//Difficulty text and region
	SDL_Color color_dif = { 127, 127, 127 };
	ttf_dif = TTF_OpenFont("timeburnernormal.ttf", 24);
	for (int i = 0; i < DIFFICULTY; i++) {
		dif_rect_dif[i].x = i % 2 == 0 ? 0 : SCREEN_WIDTH / 2;
		dif_rect_dif[i].y = SCREEN_HEIGHT / 3 * (i < 2 ? 1 : 2) - 40;
		dif_rect_dif[i].w = SCREEN_WIDTH / 2;
		dif_rect_dif[i].h = SCREEN_HEIGHT / 3;

		char text[20];
		sprintf_s(text, sizeof(text), "%s-%d", dif_text_dif[i], gam_highscore[i]);
		dif_rect_dif_text[i].x = SCREEN_WIDTH / 4 * (i % 2 == 0 ? 1 : 3);
		dif_rect_dif_text[i].y = SCREEN_HEIGHT / 3 * (i < 2 ? 2 : 3) - 40;
		TTF_SizeText(ttf_dif, text, &dif_rect_dif_text[i].w, &dif_rect_dif_text[i].h);
		dif_texture_dif[i] = TextTexture(text, ttf_dif, &color_dif);
	}

	//Difficulty shape
	int size = 0;
	for (int i = 0; i < DIFFICULTY; i++) {
		int rect_line_count = i + 2;
		int size = rect_line_count * rect_line_count;
		dif_rect_mini[i] = (SDL_Rect*)calloc(size, sizeof(SDL_Rect));
		int offset = 4;
		int x = dif_rect_dif[i].x + (dif_rect_dif[i].w / 4);
		int start_x = x;
		int y = dif_rect_dif[i].y + (dif_rect_dif[i].h / 4) - 20;
		int w = (dif_rect_dif[i].w / 2 - (offset * (rect_line_count - 1))) / rect_line_count;
		int h = w;
		printf("[%d x %d]\n", rect_line_count, rect_line_count);
		for (int j = 0; j < size;) {
			dif_rect_mini[i][j].x = x;
			dif_rect_mini[i][j].y = y;
			dif_rect_mini[i][j].w = w;
			dif_rect_mini[i][j].h = h;
			printf("%d %d %d %d\n", x, y, w, h);
			x += w + offset;
			if (++j % rect_line_count == 0) {
				x = start_x;
				y += h + offset;
			}
		}
		printf("\n");
	}

	//Sound
	dif_chunk_choose = Mix_LoadWAV("choose.wav");
	dif_chunk_select = Mix_LoadWAV("select.wav");
	dif_chunk_close = Mix_LoadWAV("close.wav");
}
void DifficultyStep() {
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
			quit = 1;
		else if (e.type == SDL_KEYDOWN)
			switch (e.key.keysym.sym) {
			case SDLK_ESCAPE:
				Mix_PlayChannel(-1, dif_chunk_close, 0);
				ChangeMap(MAP_PRIMARY);
				return;
			case SDLK_UP:
			case SDLK_DOWN:
				dif_selected_index = (dif_selected_index + 2) % 4;
				break;
			case SDLK_LEFT:
				if (--dif_selected_index < 0)
					dif_selected_index += 4;
				break;
			case SDLK_RIGHT:
				dif_selected_index = ++dif_selected_index % 4;
				break;
			case SDLK_KP_ENTER:
				Mix_PlayChannel(-1, dif_chunk_select, 0);
				ChangeMap(MAP_GAME);
				return;
			}
		else if (e.type == SDL_MOUSEMOTION) {
			int mx, my;
			SDL_GetMouseState(&mx, &my);
			for (int i = 0; i < DIFFICULTY; i++)
				if (checkPointInRect(dif_rect_dif[i], mx, my)) {
					dif_selected_index = i;
					break;
				}
		}
		else if (e.type == SDL_MOUSEBUTTONDOWN) {
			int mx, my;
			SDL_GetMouseState(&mx, &my);
			for (int i = 0; i < DIFFICULTY; i++)
				if (checkPointInRect(dif_rect_dif[i], mx, my)) {
					Mix_PlayChannel(-1, dif_chunk_select, 0);
					ChangeMap(MAP_GAME);
					return;
				}
		}
	}
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	//Title
	DrawText(dif_texture_title, dif_rect_title, CENTER | TOP, 1);

	//Difficulty selection
	if (dif_selected_index != dif_selected_index_previous)
		DifSelectedIndexChanged(&dif_selected_index, &dif_selected_index_previous);
	SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);
	SDL_RenderFillRect(renderer, &dif_rect_dif[dif_selected_index]);
	//Diffiuclty shape and text
	for (int i = 0; i < DIFFICULTY; i++) {
		int color = dif_selected_index == i ? 255 : 127;
		SDL_SetRenderDrawColor(renderer, color, color, color, 255);
		SDL_RenderFillRects(renderer, dif_rect_mini[i], (i + 2) * (i + 2));
		//SDL_RenderFillRects(renderer, dif_rect_mini[0], 4);
		DrawText(dif_texture_dif[i], dif_rect_dif_text[i], CENTER | BOTTOM, 1);
	}

	SDL_RenderPresent(renderer);
}
int DifficultyQuit() {
	SDL_DestroyTexture(dif_texture_title);
	for (int i = 0; i < DIFFICULTY; i++) {
		SDL_DestroyTexture(dif_texture_dif[i]);
		free(dif_rect_mini[i]);
	}
	TTF_CloseFont(ttf_dif);

	return dif_selected_index;
}

void DifSelectedIndexChanged(int *now, int *previous) {
	SDL_Color color_dif = { 127, 127, 127 };
	if (*previous >= 0) {
		SDL_DestroyTexture(dif_texture_dif[*previous]);
		char text[20];
		sprintf_s(text, sizeof(text), "%s-%d", dif_text_dif[*previous], gam_highscore[*previous]);
		dif_texture_dif[*previous] = TextTexture(text, ttf_dif, &color_dif);
	}

	SDL_DestroyTexture(dif_texture_dif[*now]);
	char text[20];
	sprintf_s(text, sizeof(text), "%s-%d", dif_text_dif[*now], gam_highscore[*now]);
	dif_texture_dif[*now] = TextTexture(text, ttf_dif, &COLOR_WHITE);

	*previous = *now;
	Mix_PlayChannel(-1, dif_chunk_choose, 0);
}