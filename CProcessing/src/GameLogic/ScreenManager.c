#include <cprocessing.h>
#include <stdio.h>
#include <stdbool.h>
#include "ScreenManager.h"
#include "../Screen/src_intro.h"
#include "../Screen/src_mainmenu.h"

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
		IntroInit();
		break;
	case SRC_MAIN_MENU:
		MainMenuInit();
		break;
	case SRC_OPTION:
		break;
	case SRC_CREDITS:
		break;
	case SRC_GAMEPLAY:
		break;
	default:
		break;
	}
	ScreenStartFade(FADE_OUT);
}

void SetGameState(GameState nextState)
{
	currGameState = nextState;
	CP_Engine_SetNextGameState(GameInit, GameUpdate, GameExit);
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
		break;
	case SRC_CREDITS:
		break;
	case SRC_GAMEPLAY:
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
		break;
	case SRC_CREDITS:
		break;
	case SRC_GAMEPLAY:
		break;
	default:
		break;
	}
}
