#include "main.h"

SDL_Texture *fin_texture_highscore[2], *fin_texture_score[2], *fin_texture_exit;
SDL_Rect fin_rect_highscore[2], fin_rect_score[2], fin_rect_exit;
int rect_line_count;
Mix_Chunk *fin_chunk_win, *fin_chunk_select, *fin_chunk_close;

void FinishInit(GameResult result) {
	char str_highscore[10] = "Highscore";
	char str_score[20] = "Score";
	//Set highscore
	int isHighscore = result.score > gam_highscore[result.difficulty] ? 1 : 0;
	if (isHighscore) {
		gam_highscore[result.difficulty] = result.score;
		sprintf_s(str_score, sizeof(str_score), "It's highscore!!!");
	}

	//Highscore
	TTF_Font *ttf_highscore = TTF_OpenFont("timeburnernormal.ttf", 24);
	fin_rect_highscore[0].x = SCREEN_WIDTH / 2;
	fin_rect_highscore[0].y = 100;
	TTF_SizeText(ttf_highscore, str_highscore, &fin_rect_highscore[0].w, &fin_rect_highscore[0].h);
	fin_texture_highscore[0] = TextTexture(str_highscore, ttf_highscore, &COLOR_WHITE);
	TTF_CloseFont(ttf_highscore);

	TTF_Font *ttf_highscore_num = TTF_OpenFont("timeburnerbold.ttf", 36);
	fin_rect_highscore[1].x = SCREEN_WIDTH / 2;
	fin_rect_highscore[1].y = 100;
	sprintf_s(str_highscore, sizeof(str_highscore), "%d", gam_highscore[result.difficulty]);
	TTF_SizeText(ttf_highscore_num, str_highscore, &fin_rect_highscore[1].w, &fin_rect_highscore[1].h);
	fin_texture_highscore[1] = TextTexture(str_highscore, ttf_highscore_num, &COLOR_WHITE);
	TTF_CloseFont(ttf_highscore_num);

	//Score
	TTF_Font *ttf_score = TTF_OpenFont("timeburnernormal.ttf", isHighscore ? 60 : 48);
	fin_rect_score[0].x = SCREEN_WIDTH / 2;
	fin_rect_score[0].y = SCREEN_HEIGHT / 2;
	TTF_SizeText(ttf_score, str_score, &fin_rect_score[0].w, &fin_rect_score[0].h);
	fin_texture_score[0] = TextTexture(str_score, ttf_score, &COLOR_WHITE);
	TTF_CloseFont(ttf_score);

	TTF_Font *ttf_score_num = TTF_OpenFont("timeburnerbold.ttf", isHighscore ? 72 : 60);
	fin_rect_score[1].x = SCREEN_WIDTH / 2;
	fin_rect_score[1].y = SCREEN_HEIGHT / 2;
	sprintf_s(str_score, sizeof(str_score), "%d", result.score);
	TTF_SizeText(ttf_score_num, str_score, &fin_rect_score[1].w, &fin_rect_score[1].h);
	fin_texture_score[1] = TextTexture(str_score, ttf_score_num, &COLOR_WHITE);
	TTF_CloseFont(ttf_score_num);

	//Exit
	const char *str_exit = "Exit to press Enter";
	TTF_Font *ttf_exit = TTF_OpenFont("timeburnernormal.ttf", 24);
	fin_rect_exit.x = SCREEN_WIDTH / 2;
	fin_rect_exit.y = SCREEN_HEIGHT - 60;
	TTF_SizeText(ttf_exit, str_exit, &fin_rect_exit.w, &fin_rect_exit.h);
	fin_texture_exit = TextTexture(str_exit, ttf_exit, &COLOR_WHITE);
	TTF_CloseFont(ttf_exit);

	int rect_line_count = result.difficulty + 2;

	//Sound
	fin_chunk_win = Mix_LoadWAV("win.wav");
	fin_chunk_select = Mix_LoadWAV("select.wav");
	fin_chunk_close = Mix_LoadWAV("close.wav");

	Mix_PlayChannel(-1, fin_chunk_win, 0);
}
void FinishStep() {
	SDL_Event e;
	int size = rect_line_count * rect_line_count;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
			quit = 1;
		else if (e.type == SDL_KEYDOWN) {
			if (e.key.keysym.sym == SDLK_ESCAPE) {
				Mix_PlayChannel(-1, fin_chunk_close, 0);
				ChangeMap(MAP_DIFFICULTY);
				return;
			}
			else if (e.key.keysym.sym == SDLK_RETURN) {
				Mix_PlayChannel(-1, fin_chunk_select, 0);
				ChangeMap(MAP_DIFFICULTY);
				return;
			}
		}
	}
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	//Highscore
	DrawText(fin_texture_highscore[0], fin_rect_highscore[0], CENTER | BOTTOM, 1);
	DrawText(fin_texture_highscore[1], fin_rect_highscore[1], CENTER | TOP, 1);

	//Score
	DrawText(fin_texture_score[0], fin_rect_score[0], CENTER | BOTTOM, 1);
	DrawText(fin_texture_score[1], fin_rect_score[1], CENTER | TOP, 1);

	//Exit
	DrawText(fin_texture_exit, fin_rect_exit, CENTER | CENTER, 1);

	SDL_RenderPresent(renderer);
}
void FinishQuit() {
	SDL_DestroyTexture(fin_texture_highscore[0]);
	SDL_DestroyTexture(fin_texture_highscore[1]);
	SDL_DestroyTexture(fin_texture_score[0]);
	SDL_DestroyTexture(fin_texture_score[1]);
	SDL_DestroyTexture(fin_texture_exit);
}