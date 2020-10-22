#include <cprocessing.h>
#include <stdio.h>
#include "../GameLogic/Button.h"
#include "../GameLogic/ScreenManager.h"
#include "src_mainmenu.h"
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
	MainMenuDraw();
	// Input
	if (GetBlobInput(BLOB_UP))
	{
		if (selectButton == 0)
			selectButton = MAIN_MENU_BUTTONS - 1;
		else
			selectButton--;
	}
	else if (GetBlobInput(BLOB_DOWN))
	{
		if (selectButton == MAIN_MENU_BUTTONS - 1)
			selectButton = 0;
		else
			selectButton++;
	}
	if (GetBlobInput(BLOB_INTERACT))
	{
		switch (selectButton)
		{
		case START:
			SetGameState(SRC_GAMEPLAY);
			break;
		case OPTION:
			SetGameState(SRC_OPTION);
			break;
		case CREDITS:
			SetGameState(SRC_CREDITS);
			break;
		case EXIT:
			CP_Engine_Terminate();
			break;
		default:
			break;
		}
	}
}



void MainMenuExit(void)
{	
	
}