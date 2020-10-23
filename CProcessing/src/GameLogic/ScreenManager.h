#include <cprocessing.h>
#include <stdio.h>
#include <stdbool.h>
#include "../Screen/fader.h"
#include "BlobInput.h"
#include "grid.h"

typedef enum GameState 
{
	SCR_INTRO,
	SCR_MAIN_MENU,
	SCR_OPTION,
	SCR_GAMEPLAY,
	SCR_CREDITS,

}GameState;

void GameInit(void);
void GameUpdate(void);
void GameExit(void);
void SetGameState(GameState nextState);

void ScreenStartFade(FadeType fadeType);
Fader GetFader();