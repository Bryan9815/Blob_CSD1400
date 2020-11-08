#include "../Camera/Camera.h"
#include <stdio.h>
#include <stdbool.h>
#include "BlobInput.h"
#include "grid.h"
#include "../Player/player.h"
#include "../Bosses/Boss.h"
#include "../Bosses/Boss1.h"

typedef enum GameState 
{
	SCR_INTRO,
	SCR_MAIN_MENU,
	SCR_OPTION,
	SCR_GAMEPLAY,
	SCR_GAME_OVER,
	SCR_CREDITS,

}GameState;

void GameInit(void);
void GameUpdate(void);
void GameExit(void);
void SetGameState(GameState nextState);

void ScreenStartFade(FadeType fadeType);
Fader* GetFader();