#pragma once
#include "ScreenManager.h"
#include "../Screen/scr_intro.h"
#include "../Screen/scr_mainmenu.h"
#include "../Screen/scr_options.h"
#include "../Screen/scr_credits.h"
#include "../Screen/scr_level_1.h"
#include "../Screen/scr_gameover.h"


GameState preGameState = SCR_INTRO; //For Unloading
GameState currGameState = SCR_INTRO;
Fader fader;

void ScreenStartFade(FadeType fadeType) 
{
	StartFade(&fader, fadeType);
}

Fader* GetFader()
{
	return &fader;
}

void GameInit(void)
{
	switch (currGameState)
	{
	case SCR_INTRO:
		CreateFader(&fader);
		BlobInputInit();
		IntroInit();
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
	case SCR_GAMEPLAY:
		Level1Init();
		break;
	case SCR_GAME_OVER:
		GameOverInit();
		break;
	default:
		break;
	}
	ScreenStartFade(FADE_OUT);
	//Level1Init();
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
	case SCR_GAMEPLAY:
		Level1Update(&newPlayer);
		break;
	case SCR_GAME_OVER:
		GameOverUpdate();
	default:
		break;
	}
	UpdateFade(&fader);
}



void GameExit(void)
{
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
	case SCR_GAMEPLAY:
		Level1Exit();
	case SCR_GAME_OVER:
		GameOverExit();
		break;
	default:
		break;
	}
	CP_Image_Free(&shield);
	preGameState = currGameState;
}
