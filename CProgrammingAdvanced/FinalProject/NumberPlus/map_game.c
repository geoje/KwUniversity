#include <stdlib.h>
#include <time.h>
#include "main.h"
#define GAME_TIME 30

SDL_Texture *gam_texture_title, *gam_texutre_num_tiles[25], *gam_texture_highscore[2], *gam_texture_score[2], *gam_texture_num_time;
SDL_Rect gam_rect_title, *gam_rect_tiles, *gam_rect_num_tiles, gam_rect_highscore[2], gam_rect_score[2], gam_rect_time, gam_rect_num_time;
TTF_Font *ttf_num;
int gam_difficulty, gam_selected_index = -1, *gam_num_tiles, gam_highscore[DIFFICULTY] = { 0, }, gam_score;
double gam_time_start, gam_time_now;
float gam_score_size = 1, gam_highscore_size = 1;

void GamSetNewNumber(int *arr, int size, int index);
double GamTimeChanged(double *now);

Mix_Chunk *gam_chunk_up, *gam_chunk_down, *gam_chunk_close;

void GameInit(int difficulty) {
	//Set difficulty
	gam_difficulty = difficulty;

	//Title
	const char *gam_text_dif[] = { "Easy", "Normal", "Hard", "Hell" };
	const char *title = gam_text_dif[gam_difficulty];
	TTF_Font *ttf_title = TTF_OpenFont("timeburnerbold.ttf", 48);
	gam_rect_title.x = SCREEN_WIDTH / 2;
	gam_rect_title.y = 44;
	TTF_SizeText(ttf_title, title, &gam_rect_title.w, &gam_rect_title.h);
	gam_texture_title = TextTexture(title, ttf_title, &COLOR_WHITE);
	TTF_CloseFont(ttf_title);

	//Tiles and Numbers
	int rect_line_count = gam_difficulty + 2;
	int size = rect_line_count * rect_line_count;
	gam_num_tiles = (int*)calloc(size, sizeof(int));
	gam_rect_tiles = (SDL_Rect*)calloc(size, sizeof(SDL_Rect));
	gam_rect_num_tiles = (SDL_Rect*)calloc(size, sizeof(SDL_Rect));

	int offset = 4;
	int x = 20;
	int start_x = x;
	int y = SCREEN_HEIGHT - SCREEN_WIDTH - start_x - offset;
	int w = (SCREEN_WIDTH - (start_x * 2) - (offset * (rect_line_count - 1))) / rect_line_count;
	int h = w;

	ttf_num = TTF_OpenFont("timeburnerbold.ttf", 24);
	srand(time(NULL));

	printf("[%s]\n", title);
	for (int i = 0; i < size;) {
		//Tiles
		gam_rect_tiles[i].x = x;
		gam_rect_tiles[i].y = y;
		gam_rect_tiles[i].w = w;
		gam_rect_tiles[i].h = h;
		printf("%d %d %d %d\n", x, y, w, h);

		//Numbers
		GamSetNewNumber(gam_num_tiles, size, i);

		//Numbers Texture
		char str_num[4];
		gam_rect_num_tiles[i].x = x + w / 2;
		gam_rect_num_tiles[i].y = y + h / 2;
		sprintf_s(str_num, sizeof(str_num), "%d", gam_num_tiles[i]);
		TTF_SizeText(ttf_num, str_num, &gam_rect_num_tiles[i].w, &gam_rect_num_tiles[i].h);
		gam_texutre_num_tiles[i] = TextTexture(str_num, ttf_num, &COLOR_BLACK);

		//Refesh Rectangle
		x += w + offset;
		if (++i % rect_line_count == 0) {
			x = start_x;
			y += h + offset;
		}
	}

	//Highscore
	TTF_Font *ttf_score = TTF_OpenFont("timeburnernormal.ttf", 18);
	char str_highscore[10] = "Highscore";
	gam_rect_highscore[0].x = 60;
	gam_rect_highscore[0].y = 44;
	TTF_SizeText(ttf_score, str_highscore, &gam_rect_highscore[0].w, &gam_rect_highscore[0].h);
	gam_texture_highscore[0] = TextTexture(str_highscore, ttf_score, &COLOR_WHITE);

	gam_rect_highscore[1].x = 60;
	gam_rect_highscore[1].y = 44;
	sprintf_s(str_highscore, sizeof(str_highscore), "%d", gam_highscore[gam_difficulty]);
	TTF_SizeText(ttf_num, str_highscore, &gam_rect_highscore[1].w, &gam_rect_highscore[1].h);
	gam_texture_highscore[1] = TextTexture(str_highscore, ttf_num, &COLOR_WHITE);

	//Score
	gam_score = 0;

	char *str_score = "Score";
	gam_rect_score[0].x = SCREEN_WIDTH - 60;
	gam_rect_score[0].y = 44;
	TTF_SizeText(ttf_score, str_score, &gam_rect_score[0].w, &gam_rect_score[0].h);
	gam_texture_score[0] = TextTexture(str_score, ttf_score, &COLOR_WHITE);

	gam_rect_score[1].x = SCREEN_WIDTH - 60;
	gam_rect_score[1].y = 44;
	TTF_SizeText(ttf_num, "0", &gam_rect_score[1].w, &gam_rect_score[1].h);
	gam_texture_score[1] = TextTexture("0", ttf_num, &COLOR_WHITE);

	//Time
	gam_time_start = (double)clock() / 1000;
	gam_rect_time.x = 0;
	gam_rect_time.y = SCREEN_HEIGHT -  10;
	gam_rect_time.w = SCREEN_WIDTH;
	gam_rect_time.h = 10;

	char str_time[4];
	sprintf_s(str_time, sizeof(str_time), "%d", GAME_TIME);
	gam_rect_num_time.x = SCREEN_WIDTH / 2;
	gam_rect_num_time.y = SCREEN_HEIGHT - 10;
	TTF_SizeText(ttf_num, str_time, &gam_rect_num_time.w, &gam_rect_num_time.h);
	gam_texture_num_time = TextTexture(str_time, ttf_num, &COLOR_WHITE);

	//Sound
	gam_chunk_up = Mix_LoadWAV("curious_up.wav");
	gam_chunk_down = Mix_LoadWAV("curious_down.wav");
	gam_chunk_close = Mix_LoadWAV("close.wav");
}
void GameStep() {
	SDL_Event e;
	int rect_line_count = gam_difficulty + 2;
	int size = rect_line_count * rect_line_count;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
			quit = 1;
		else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
			Mix_PlayChannel(-1, gam_chunk_close, 0);
			ChangeMap(MAP_DIFFICULTY);
			return;
		}
		else if (e.type == SDL_MOUSEMOTION) {
			int mx, my;
			SDL_GetMouseState(&mx, &my);
			gam_selected_index = -1;
			for (int i = 0; i < size; i++)
				if (checkPointInRect(gam_rect_tiles[i], mx, my)) {
					gam_selected_index = i;
					break;
				}
		}
		else if (e.type == SDL_MOUSEBUTTONDOWN) {
			int mx, my;
			SDL_GetMouseState(&mx, &my);
			if (gam_selected_index >= 0) {
				if (gam_num_tiles[gam_selected_index] == gam_score + 1) {
					Mix_PlayChannel(-1, gam_chunk_up, 0);
					GamSetNewNumber(gam_num_tiles, size, gam_selected_index);

					char str_num[4];
					sprintf_s(str_num, sizeof(str_num), "%d", ++gam_score);
					SDL_DestroyTexture(gam_texture_score[1]);
					TTF_SizeText(ttf_num, str_num, &gam_rect_score[1].w, &gam_rect_score[1].h);
					gam_texture_score[1] = TextTexture(str_num, ttf_num, &COLOR_WHITE);
					gam_score_size = 2;
					if (gam_score > gam_highscore[gam_difficulty]) {
						SDL_DestroyTexture(gam_texture_highscore[1]);
						TTF_SizeText(ttf_num, str_num, &gam_rect_highscore[1].w, &gam_rect_highscore[1].h);
						gam_texture_highscore[1] = TextTexture(str_num, ttf_num, &COLOR_WHITE);

						gam_score_size = 3;
						gam_highscore_size = 3;
					}
				}
				else {
					Mix_PlayChannel(-1, gam_chunk_down, 0);
					gam_time_start--;
					if (GamTimeChanged(&gam_time_now) <= 0)
						return;
				}
			}
		}
	}
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	//Title
	DrawText(gam_texture_title, gam_rect_title, CENTER | MIDDLE, 1);

	//Tiles
	SDL_SetRenderDrawColor(renderer, 196, 196, 196, 255);
	SDL_RenderFillRects(renderer, gam_rect_tiles, size);
	if (gam_selected_index >= 0) {
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderFillRect(renderer, &gam_rect_tiles[gam_selected_index]);
	}

	//Numbers
	for (int i = 0; i < size; i++) {
		DrawText(gam_texutre_num_tiles[i], gam_rect_num_tiles[i], CENTER | MIDDLE, 1);
	}

	//Highscore
	if (gam_highscore_size > 1)
		gam_highscore_size -= 0.1;
	else
		gam_highscore_size = 1;
	DrawText(gam_texture_highscore[0], gam_rect_highscore[0], CENTER | BOTTOM, 1);
	DrawText(gam_texture_highscore[1], gam_rect_highscore[1], CENTER | TOP, gam_highscore_size);

	//Score
	if (gam_score_size > 1)
		gam_score_size -= 0.1;
	else
		gam_score_size = 1;
	DrawText(gam_texture_score[0], gam_rect_score[0], CENTER | BOTTOM, 1);
	DrawText(gam_texture_score[1], gam_rect_score[1], CENTER | TOP, gam_score_size);

	//Time
	gam_time_now = (double)clock() / 1000;
	if (GamTimeChanged(&gam_time_now) <= 0)
		return;
	gam_rect_time.w = SCREEN_WIDTH * (1 - (gam_time_now - gam_time_start) / GAME_TIME);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &gam_rect_time);
	DrawText(gam_texture_num_time, gam_rect_num_time, CENTER | BOTTOM, 1);

	SDL_RenderPresent(renderer);
}
GameResult GameQuit() {
	TTF_CloseFont(ttf_num);

	SDL_DestroyTexture(gam_texture_title);
	int rect_line_count = gam_difficulty + 2;
	int size = rect_line_count * rect_line_count;
	for (int i = 0; i < size; i++)
		SDL_DestroyTexture(gam_texutre_num_tiles[i]);
	SDL_DestroyTexture(gam_texture_highscore[0]);
	SDL_DestroyTexture(gam_texture_highscore[1]);
	SDL_DestroyTexture(gam_texture_score[0]);
	SDL_DestroyTexture(gam_texture_score[1]);
	SDL_DestroyTexture(gam_texture_num_time);

	free(gam_num_tiles);
	free(gam_rect_tiles);
	free(gam_rect_num_tiles);

	GameResult result = { gam_difficulty, gam_score };
	return result;
}

void GamSetNewNumber(int *arr, int size, int index) {
	int i = 0;
	int randNum;
	int div = arr[index] == 0 ? 0 : (arr[index] - 1) / size + 1;
	while (i < size) {
		randNum = (size * div) + (rand() % size + 1);
		for (i = 0; i < size; i++)
			if (randNum == arr[i])
				break;
	}
	arr[index] = randNum;
	if (div > 0) {
		SDL_DestroyTexture(gam_texutre_num_tiles[index]);

		char str_num[4];
		sprintf_s(str_num, sizeof(str_num), "%d", gam_num_tiles[index]);
		TTF_SizeText(ttf_num, str_num, &gam_rect_num_tiles[index].w, &gam_rect_num_tiles[index].h);
		gam_texutre_num_tiles[index] = TextTexture(str_num, ttf_num, &COLOR_BLACK);
	}
}
double GamTimeChanged(double *now) {
	SDL_DestroyTexture(gam_texture_num_time);

	double remain_time = GAME_TIME - (*now - gam_time_start);
	if (remain_time <= 0) {
		ChangeMap(MAP_FINISH);
		return remain_time;
	}
	char str_num[10];
	sprintf_s(str_num, sizeof(str_num), "%.2lf", remain_time);
	TTF_SizeText(ttf_num, str_num, &gam_rect_num_time.w, &gam_rect_num_time.h);
	gam_texture_num_time = TextTexture(str_num, ttf_num, &COLOR_WHITE);
}