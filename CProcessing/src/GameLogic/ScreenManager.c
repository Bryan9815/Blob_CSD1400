//---------------------------------------------------------
// file:	ScreenManager.c
// author:	[Teh Kai Hong Bryan]
// email:	[t.kaihongbryan@digipen.edu]
//
// brief:	Manages transition from screen to screen
//
//
// Copyright � 2020 DigiPen, All rights reserved.
//---------------------------------------------------------
#pragma once
#include "ScreenManager.h"
#include "../Screen/scr_intro.h"
#include "../Screen/scr_mainmenu.h"
#include "../Screen/scr_options.h"
#include "../Screen/scr_credits.h"
#include "../Screen/scr_level_1.h"
#include "../Screen/scr_level_2.h"
#include "../Screen/scr_gameover.h"
#include "../Screen/pause_overlay.h"
#include "../Screen/scr_tutorial.h"


GameState preGameState = SCR_INTRO; //For Unloading
GameState currGameState = SCR_INTRO;
PlayState currPlayState;
Fader fader;

// Fades screen to black
void ScreenStartFade(FadeType fadeType) 
{
	StartFade(&fader, fadeType);
}

// Getter function for fader
Fader* GetFader()
{
	return &fader;
}

// Initializes PlayState and calls Init functions of each screen
void GameInit(void)
{
	currPlayState = GAME_PLAY;
	switch (currGameState)
	{
	case SCR_INTRO:
		CreateFader(&fader);
		BlobInputInit();
		PauseInit();
		IntroInit();
		VolumeInit();
		break;
	case SCR_MAIN_MENU:
		MainMenuInit();
		break;
	case SCR_OPTION:
		OptionsInit();
		break;
	case SCR_CREDITS:
		CreditsInit();
		break;
	case SCR_TUTORIAL:
		TutorialInit();
		break;
	case SCR_LEVEL1:
		Level1Init();
		break;
	case SCR_LEVEL2:
		Level2Init();
		break;
	default:
		break;
	}
	ScreenStartFade(FADE_OUT);
}

// Getter function for GameState
GameState GetGameState(void)
{
	return currGameState;
}

// Setter function for GameState
void SetGameState(GameState nextGameState)
{
	currGameState = nextGameState;
	CP_Engine_SetNextGameStateForced(GameInit, GameUpdate, GameExit);
}

// Draws overlays above the current screen
void DrawOverlay(void)
{
	switch (currPlayState)
	{
	case GAME_PLAY:
		break;
	case GAME_PAUSE:
		PauseUpdate();
		break;
	case GAME_OVER:
		GameOverUpdate();
		break;
	default:
		break;
	}
}

// Calls update functions of other screens
void GameUpdate(void)
{
	switch (currGameState)
	{
	case SCR_INTRO:
		IntroUpdate();		
		break;
	case SCR_MAIN_MENU:
		MainMenuUpdate();
		break;
	case SCR_OPTION:
		OptionsUpdate();
		break;
	case SCR_CREDITS:
		CreditsUpdate();
		break;
	case SCR_TUTORIAL:
		TutorialUpdate(&newPlayer);
		break;
	case SCR_LEVEL1:
		Level1Update(&newPlayer);
		break;
	case SCR_LEVEL2:
		Level2Update(&newPlayer);
		break;
	default:
		break;
	}
	UpdateFade(&fader); 
}

// Getter function for PlayState
PlayState GetPlayState(void)
{
	return currPlayState;
}

// Setter function for PlayState
void SetPlayState(PlayState nextPlayState)
{
	currPlayState = nextPlayState;
}

// Ends the game in scr_tutorial, scr_level_1 and scr_level_2 as either a win or lost
void SetGameOver(bool win)
{
	GameOverInit(win);
	SetPlayState(GAME_OVER);
}

// Resets fader and GameState and calls exit function of each screen
void GameExit(void)
{
	ResetFader(GetFader());
	switch (preGameState)
	{
	case SCR_INTRO:
		IntroExit();
		break;
	case SCR_MAIN_MENU:
		MainMenuExit();
		break;
	case SCR_OPTION:
		OptionsExit();
		break;
	case SCR_CREDITS:
		break;
	case SCR_TUTORIAL:
		TutorialExit();
		break;
	case SCR_LEVEL1:
		Level1Exit();
		break;
	case SCR_LEVEL2:
		Level2Exit();
		break;
	default:
		break;
	}
	//CP_Image_Free(&shield);
	preGameState = currGameState;
}
