#include <cprocessing.h>
#include <stdio.h>
#include "ScreenManager.h"
#include "src_intro.h"
#include "src_mainmenu.h"

GameState currGameState = SRC_INTRO;

void GameInit(void)
{
	
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
		CP_Engine_SetNextGameState(IntroInit, IntroUpdate, IntroExit);
		break;
	case SRC_MAIN_MENU:
		CP_Engine_SetNextGameState(MainMenuInit, MainMenuUpdate, MainMenuExit);
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


void GameExit(void)
{
	
}
