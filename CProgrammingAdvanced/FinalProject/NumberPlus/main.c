#include "main.h"

int quit = 0;
const int SCREEN_WIDTH = 360;
const int SCREEN_HEIGHT = 480;
SDL_Renderer* renderer;

int main()
{
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return 1;
	}

	//Initialize TTF
	if (TTF_Init() < 0) {
		printf("TTF could not initialize! TTF_Error: %s\n", TTF_GetError());
		SDL_Quit();
		return 1;
	}

	//Initialize Mixer
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096) == -1) {
		printf("Mixer could not initialize! Mix_Error: %s\n", Mix_GetError());
		SDL_Quit();
		return 1;
	}

	//Create window
	SDL_Window* window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		Mix_CloseAudio();
		SDL_Quit();
		return 1;
	}

	//Create renderer for window
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL)
	{
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		Mix_CloseAudio();
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	//Load highscore
	FILE *f = NULL;
	fopen_s(&f, "Highscore.txt", "r");
	if (f != NULL) {
		fscanf_s(f, "Easy=%d\nNormal=%d\nHard=%d\nHell=%d",
			&gam_highscore[0], &gam_highscore[1], &gam_highscore[2], &gam_highscore[3]);
		fclose(f);
	}

	PrimaryInit();
	while (!quit)
		switch (map_now) {
		case MAP_PRIMARY:
			PrimaryStep();
			break;
		case MAP_DIFFICULTY:
			DifficultyStep();
			break;
		case MAP_GAME:
			GameStep();
			break;
		case MAP_FINISH:
			FinishStep();
			break;
		}

	fopen_s(&f, "Highscore.txt", "w");
	if (f != NULL) {
		fprintf_s(f, "Easy=%d\nNormal=%d\nHard=%d\nHell=%d",
			gam_highscore[0], gam_highscore[1], gam_highscore[2], gam_highscore[3]);
		fclose(f);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	Mix_CloseAudio();
	TTF_Quit();
	SDL_Quit();

	return 0;
}