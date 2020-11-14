#pragma once
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
	SCR_CREDITS,

}GameState;

typedef enum PlayState
{
	GAME_PLAY,
	GAME_PAUSE,
	GAME_OVER,
}PlayState;

PlayState currPlayState;

void GameInit(void);
void GameUpdate(void);
void GameExit(void);
void SetGameState(GameState nextGameState);

void ScreenStartFade(FadeType fadeType);
void DrawOverlay(void);
void SetPlayState(PlayState nextPlayState);
void SetGameOver(bool win);
Fader* GetFader();