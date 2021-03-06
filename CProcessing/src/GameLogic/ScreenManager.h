﻿//---------------------------------------------------------
// file:	ScreenManager.h
// author:	[Teh Kai Hong Bryan]
// email:	[t.kaihongbryan@digipen.edu]
//
// brief:	Header file for ScreenManager.c
//
//
// Copyright � 2020 DigiPen, All rights reserved.
//---------------------------------------------------------
#pragma once
#include "../Camera/Camera.h"
#include <stdio.h>
#include <stdbool.h>
#include "BlobInput.h"
#include "grid.h"
#include "../Player/player.h"
#include "../Bosses/Boss.h"
#include "../Bosses/Boss1.h"
#include "../Bosses/Boss2.h"
#include "../Audio/AudioManager.h"
#include "SaveLoad.h"

typedef enum GameState 
{
	SCR_INTRO,
	SCR_MAIN_MENU,
	SCR_OPTION,
	SCR_TUTORIAL,
	SCR_LEVEL1,
	SCR_LEVEL2,
	SCR_CREDITS,

}GameState;

typedef enum PlayState
{
	GAME_PLAY,
	GAME_PAUSE,
	GAME_OVER,
	GAME_SWAP,

}PlayState;

void GameInit(void);
void GameUpdate(void);
void GameExit(void);
void SetGameState(GameState nextGameState);

void ScreenStartFade(FadeType fadeType);
void DrawOverlay(void);
GameState GetGameState(void);
PlayState GetPlayState(void);
void SetPlayState(PlayState nextPlayState);
void SetGameOver(bool win);
Fader* GetFader();