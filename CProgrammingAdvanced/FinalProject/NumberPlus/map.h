#pragma once
#include <SDL.h>
#define DIFFICULTY 4

//map
extern int map_now;
typedef enum {
	MAP_PRIMARY,
	MAP_DIFFICULTY,
	MAP_GAME,
	MAP_FINISH
} MapNumber;
void ChangeMap(int map_number);

//map_primary
void PrimaryInit();
void PrimaryStep();
void PrimaryQuit();

//map_difficulty
void DifficultyInit();
void DifficultyStep();
int DifficultyQuit();

//map_game
typedef struct {
	int difficulty, score;
}GameResult;
extern int gam_highscore[DIFFICULTY];
void GameInit(int difficulty);
void GameStep();
GameResult GameQuit();

//map_score
void FinishInit(GameResult score);
void FinishStep();
void FinishQuit();