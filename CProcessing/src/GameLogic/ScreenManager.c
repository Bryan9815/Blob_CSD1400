#pragma once
#include "ScreenManager.h"
#include "../Screen/scr_intro.h"
#include "../Screen/scr_mainmenu.h"
#include "../Screen/scr_options.h"
#include "../Screen/scr_level_1.h"

#include "../Bosses/Boss.h"
#include "../Bosses/Shield.h"

GameState currGameState = SCR_INTRO;
Fader fader;
CP_Image shield;

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
	case SCR_INTRO:
		fader = CreateFader();
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
		break;
	case SCR_GAMEPLAY:
		Level1Init();
		CreatePlayer(&newPlayer);
		break;
	default:
		break;
	}
	ScreenStartFade(FADE_OUT);
	Level1Init();
	CreateBoss(&ArmorSlime, 1, 100.f);
	shield = CP_Image_Load("././Assets/Shield1.png"); //the shield for boss 1 because the back has to be exposed
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
		break;
	case SCR_GAMEPLAY:
		Level1Update(&newPlayer);
		PlayerUpdate(&newPlayer);
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
		break;
	default:
		break;
	}
	CP_Image_Free(&shield);
}
