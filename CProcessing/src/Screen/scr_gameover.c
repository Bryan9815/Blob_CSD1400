#include <cprocessing.h>
#include "../GameLogic/Button.h"
#include "../GameLogic/ScreenManager.h"
#include "scr_GameOver.h"
#include "../GameLogic/Score.h"
#define GAME_OVER_BUTTONS 3

typedef enum {
	RETRY,
	MAIN_MENU,
	EXIT,
}ButtonList;

CP_Color bgColor;
Button menuList[GAME_OVER_BUTTONS];
int selectButton;
float buttonBufferY = 125.f;
bool mouseCheck;
bool lose;
CP_Vector mousePos, overlayCenter;

void GameOverInit(bool win)
{
	selectButton = 0;
	mouseCheck = false;
	overlayCenter = CP_Vector_Set((float)CP_System_GetWindowWidth() / 2 + GetCameraPos().x, (float)CP_System_GetWindowHeight() / 2 + GetCameraPos().y);
	lose = !win;
	bgColor = CP_Color_Create(50, 50, 50, 150);
	Score = CalculateScore(Boss1Timer, lose);

	menuList[RETRY] = CreateButton(overlayCenter.x, overlayCenter.y, 250.f, 100.f, "Retry");
	menuList[MAIN_MENU] = CreateButton(overlayCenter.x, overlayCenter.y + buttonBufferY, 250.f, 100.f, "Main Menu");
	menuList[EXIT] = CreateButton(overlayCenter.x, overlayCenter.y + buttonBufferY * 2, 250.f, 100.f, "Quit");
}

void GameOverDraw(void)
{
	CP_Settings_Fill(bgColor);
	CP_Settings_RectMode(CP_POSITION_CENTER);
	CP_Graphics_DrawRect(overlayCenter.x, overlayCenter.y, (float)CP_System_GetWindowWidth(), (float)CP_System_GetWindowHeight());

	//Title
	CP_Settings_TextSize(200.0f);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	if (lose)
	{
		CP_Font_DrawText("GAME OVER", overlayCenter.x, overlayCenter.y - (float)CP_System_GetWindowHeight() / 4);
	}
	else
	{
		CP_Font_DrawText("YOU WIN!", overlayCenter.x, overlayCenter.y - (float)CP_System_GetWindowHeight() / 4);
	}
	DisplayScore(overlayCenter.x, overlayCenter.y - (float)CP_System_GetWindowHeight() / 8, Boss1Timer, Score);

	// Draw Buttons
	menuList[RETRY] = CreateButton(overlayCenter.x, overlayCenter.y, 250.f, 100.f, "Retry");
	menuList[MAIN_MENU] = CreateButton(overlayCenter.x, overlayCenter.y + buttonBufferY, 250.f, 100.f, "Main Menu");
	menuList[EXIT] = CreateButton(overlayCenter.x, overlayCenter.y + buttonBufferY * 2, 250.f, 100.f, "Quit");
	for (int i = 0; i < GAME_OVER_BUTTONS; i++)
	{
		if(menuList[i].isSelected == 1)
			DrawButton(menuList[i], 48.f, 1.1f, CP_Color_Create(0, 255, 0, 255));
		else if (selectButton == i)
			DrawButton(menuList[i], 48.f, 1.f, CP_Color_Create(0, 255, 0, 255));
		else
			DrawButton(menuList[i], 48.f, 1.f, CP_Color_Create(255,255,255,255));
	}
}

void GameOverButtonActivate()
{
	switch (selectButton)
	{
	case RETRY:
		SetGameState(SCR_LEVEL1);
		break;
	case MAIN_MENU:
		SetGameState(SCR_MAIN_MENU);
		break;
	case EXIT:
		CP_Engine_Terminate();
		break;
	default:
		break;
	}
}

void GameOverUpdate(void)
{
	CP_Vector oldMousePos = CP_Vector_Set(mousePos.x, mousePos.y);
	mousePos = CP_Vector_Set(CP_Input_GetMouseWorldX(), CP_Input_GetMouseWorldY());
	overlayCenter = CP_Vector_Set((float)CP_System_GetWindowWidth() / 2 + GetCameraPos().x, (float)CP_System_GetWindowHeight() / 2 + GetCameraPos().y);;

	// Input
	if (GetBlobInputTriggered(BLOB_UP))
	{
		if (selectButton == 0)
			selectButton = GAME_OVER_BUTTONS - 1;
		else
			selectButton--;
	}
	else if (GetBlobInputTriggered(BLOB_DOWN))
	{
		if (selectButton == GAME_OVER_BUTTONS - 1)
			selectButton = 0;
		else
			selectButton++;
	}
	// Mouse Input
	if (!mouseCheck)
	{
		for (int i = 0; i < GAME_OVER_BUTTONS; i++)
		{
			// Mouse x-pos collision check
			if (mousePos.x >= (menuList[i].posX - menuList[i].width / 2) && mousePos.x <= (menuList[i].posX + menuList[i].width / 2))
			{
				// Mouse y-pos collision check	
				if (mousePos.y >= (menuList[i].posY - menuList[i].height / 2) && mousePos.y <= (menuList[i].posY + menuList[i].height / 2))
				{
					selectButton = i;
					mouseCheck = true;
				}
			}
		}
	}
	else
	{
		if (CP_Input_MouseDown(MOUSE_BUTTON_1))
			menuList[selectButton].isSelected = 1;
		else if (CP_Input_MouseReleased(MOUSE_BUTTON_1))
		{
			GameOverButtonActivate();
			menuList[selectButton].isSelected = 0;
			mouseCheck = false;
		}
		if ((int)mousePos.x != (int)oldMousePos.x || (int)mousePos.y != (int)oldMousePos.y)
		{
			if (mousePos.x < (menuList[selectButton].posX - menuList[selectButton].width / 2) || mousePos.x >(menuList[selectButton].posX + menuList[selectButton].width / 2))
				mouseCheck = false;
			if (mousePos.y < (menuList[selectButton].posY - menuList[selectButton].height / 2) || mousePos.y >(menuList[selectButton].posY + menuList[selectButton].height / 2))
				mouseCheck = false;
		}
	}

	if (GetBlobInputTriggered(BLOB_INTERACT))
		GameOverButtonActivate();

	GameOverDraw();
}



void GameOverExit(void)
{	
	
}