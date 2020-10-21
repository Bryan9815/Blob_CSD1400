#include "../Screen/fader.h"

typedef enum GameState {
	SRC_INTRO,
	SRC_MAIN_MENU,
	SRC_OPTION,
	SRC_GAMEPLAY,
	SRC_CREDITS,
}GameState;

void GameInit(void);
void GameUpdate(void);
void GameExit(void);
void SetGameState(GameState nextState);

void ScreenStartFade(FadeType fadeType);
Fader GetFader();