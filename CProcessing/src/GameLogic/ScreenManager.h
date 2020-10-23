#include <cprocessing.h>
#include <stdio.h>
#include <stdbool.h>
#include "../Screen/fader.h"
#include "BlobInput.h"
#include "grid.h"

typedef enum GameState 
{
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