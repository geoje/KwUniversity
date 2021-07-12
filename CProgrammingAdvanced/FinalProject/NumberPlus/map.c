#include "main.h"

int map_now = 0;
int gam_difficulty = -1;

void ChangeMap(int map_number) {
	int score = 0;
	GameResult result;
	switch (map_now) {
	case MAP_PRIMARY:
		PrimaryQuit();
		break;
	case MAP_DIFFICULTY:
		score = DifficultyQuit();
		break;
	case MAP_GAME:
		result = GameQuit();
		break;
	case MAP_FINISH:
		FinishQuit();
		break;
	}
	switch (map_number) {
	case MAP_PRIMARY:
		PrimaryInit();
		break;
	case MAP_DIFFICULTY:
		DifficultyInit();
		break;
	case MAP_GAME:
		GameInit(score);
		break;
	case MAP_FINISH:
		FinishInit(result);
		break;
	}
	map_now = map_number;
}