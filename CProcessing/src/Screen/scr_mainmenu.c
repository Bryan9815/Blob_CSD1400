#include <cprocessing.h>
#include <stdio.h>
#include "../GameLogic/Button.h"
#include "../GameLogic/ScreenManager.h"
#include "scr_mainmenu.h"
#define MAIN_MENU_BUTTONS 4

typedef enum {
	START,
	OPTION,
	CREDITS,
	EXIT,
}ButtonList;

CP_Color bgColor;
Button menuList[MAIN_MENU_BUTTONS];
int selectButton;

void MainMenuInit(void)
{
	selectButton = 0;
	bgColor = CP_Color_Create(0, 0, 0, 255);
	float buttonBufferY = 125.f;

	menuList[START] = CreateButton((float)CP_System_GetWindowWidth() / 2, (float)CP_System_GetWindowHeight() / 2, 250.f, 100.f, "Start");
	menuList[OPTION] = CreateButton((float)CP_System_GetWindowWidth() / 2, (float)CP_System_GetWindowHeight() / 2 + buttonBufferY, 250.f, 100.f, "Options");
	menuList[CREDITS] = CreateButton((float)CP_System_GetWindowWidth() / 2, (float)CP_System_GetWindowHeight() / 2 + buttonBufferY * 2, 250.f, 100.f, "Credits");
	menuList[EXIT] = CreateButton((float)CP_System_GetWindowWidth() / 2, (float)CP_System_GetWindowHeight() / 2 + buttonBufferY * 3, 250.f, 100.f, "Quit");
}



void MainMenuDraw(void)
{
	CP_Settings_Background(bgColor);

	// Draw Buttons
	for (int i = 0; i < MAIN_MENU_BUTTONS; i++)
	{
		if (selectButton == i)
			DrawButton(menuList[i], 48.f, 1.f, CP_Color_Create(0, 255, 0, 255));
		else
			DrawButton(menuList[i], 48.f, 1.f, CP_Color_Create(255,255,255,255));
	}
}

void MainMenuUpdate(void)
{
	// Input
	if (GetBlobInputTriggered(BLOB_UP))
	{
		if (selectButton == 0)
			selectButton = MAIN_MENU_BUTTONS - 1;
		else
			selectButton--;
	}
	else if (GetBlobInputTriggered(BLOB_DOWN))
	{
		if (selectButton == MAIN_MENU_BUTTONS - 1)
			selectButton = 0;
		else
			selectButton++;
	}
	if (GetBlobInputTriggered(BLOB_INTERACT))
	{
		switch (selectButton)
		{
		case START:
			SetGameState(SCR_GAMEPLAY);
			break;
		case OPTION:
			SetGameState(SCR_OPTION);
			break;
		case CREDITS:
			SetGameState(SCR_CREDITS);
			break;
		case EXIT:
			CP_Engine_Terminate();
			break;
		default:
			break;
		}
	}
	MainMenuDraw();
}



void MainMenuExit(void)
{	
	
}