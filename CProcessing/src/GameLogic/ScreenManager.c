#pragma once
#include "ScreenManager.h"
#include "../Screen/src_intro.h"
#include "../Screen/src_mainmenu.h"
#include "../Screen/src_options.h"
#include "../Screen/scr_level_1.h"
#include "../Bosses/Boss.h"

GameState currGameState = SRC_INTRO;
Fader fader;

void ScreenStartFade(FadeType fadeType) 
{
	fader = StartFade(fader, fadeType);
}

Fader GetFader()
{
	return fader;
}

void GameInit(void)
{
	switch (currGameState)
	{
	case SRC_INTRO:
		fader = CreateFader();
		BlobInputInit();
		IntroInit();
		break;
	case SRC_MAIN_MENU:
		MainMenuInit();
		break;
	case SRC_OPTION:
		OptionsInit();
		break;
	case SRC_CREDITS:
		break;
	case SRC_GAMEPLAY:
		Level1Init();
		break;
	default:
		break;
	}
	ScreenStartFade(FADE_OUT);
}

void SetGameState(GameState nextState)
{
	currGameState = nextState;
	CP_Engine_SetNextGameStateForced(GameInit, GameUpdate, GameExit);
}

void GameUpdate(void)
{
	switch (currGameState)
	{
	case SRC_INTRO:
		IntroUpdate();		
		break;
	case SRC_MAIN_MENU:
		MainMenuUpdate();
		break;
	case SRC_OPTION:
		OptionsUpdate();
		break;
	case SRC_CREDITS:
		break;
	case SRC_GAMEPLAY:
		Level1Update();
		break;
	default:
		break;
	}
	fader = UpdateFade(fader);
}



void GameExit(void)
{
	switch (currGameState)
	{
	case SRC_INTRO:
		IntroExit();
		break;
	case SRC_MAIN_MENU:
		MainMenuExit();
		break;
	case SRC_OPTION:
		OptionsExit();
		break;
	case SRC_CREDITS:
		break;
	case SRC_GAMEPLAY:
		break;
	default:
		break;
	}
}
