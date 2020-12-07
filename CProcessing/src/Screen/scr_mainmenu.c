#include <cprocessing.h>
#include "../GameLogic/Button.h"
#include "../GameLogic/ScreenManager.h"
#include "scr_mainmenu.h"
#include "../Audio/AudioManager.h"
#define MAIN_MENU_BUTTONS 4

typedef enum {
	START,
	OPTION,
	CREDITS,
	EXIT,
}ButtonList;

CP_Color bgColor;
static Button menuList[MAIN_MENU_BUTTONS];
int selectButton;
bool mouseCheck;
CP_Vector mousePos;
CP_Image mainMenuImg;

void MainMenuInit(void)
{
	LoadGame();
	mainMenuImg = CP_Image_Load("././Assets/MainMenuScr.png");
	selectButton = 0;
	mouseCheck = false;
	bgColor = CP_Color_Create(0, 0, 0, 255);
	float buttonBufferY = 90.f;
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	menuList[START] = CreateButton((float)CP_System_GetWindowWidth() / 2, (float)CP_System_GetWindowHeight() / 2, 200.f, 75.f, "Start");
	menuList[OPTION] = CreateButton((float)CP_System_GetWindowWidth() / 2, (float)CP_System_GetWindowHeight() / 2 + buttonBufferY, 200.f, 75.f, "Options");
	menuList[CREDITS] = CreateButton((float)CP_System_GetWindowWidth() / 2, (float)CP_System_GetWindowHeight() / 2 + buttonBufferY * 2, 200.f, 75.f, "Credits");
	menuList[EXIT] = CreateButton((float)CP_System_GetWindowWidth() / 2, (float)CP_System_GetWindowHeight() / 2 + buttonBufferY * 3, 200.f, 75.f, "Quit");
	AudioMenuInit();
}



void MainMenuDraw(void)
{
	CP_Settings_Background(bgColor);
	CP_Settings_ImageMode(CP_POSITION_CENTER);
	CP_Image_Draw(mainMenuImg, (float)CP_System_GetWindowWidth() / 2, (float)CP_System_GetWindowHeight() / 2, (float)CP_System_GetWindowWidth(), (float)CP_System_GetWindowHeight(), 255);

	//Title
	//CP_Settings_TextSize(200.0f);
	
	//CP_Font_DrawText("BLOB", (float)CP_System_GetWindowWidth() / 2, (float)CP_System_GetWindowHeight() / 3);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	// Draw Buttons
	for (int i = 0; i < MAIN_MENU_BUTTONS; i++)
	{
		if(menuList[i].isSelected == 1)
			DrawButton(menuList[i], 48.f, 1.1f, CP_Color_Create(0, 255, 0, 255));
		else if (selectButton == i)
			DrawButton(menuList[i], 48.f, 1.f, CP_Color_Create(0, 255, 0, 255));
		else
			DrawButton(menuList[i], 48.f, 1.f, CP_Color_Create(255,255,255,255));
	}
}

void MenuButtonActivate()
{
	switch (selectButton)
	{
	case START:
		AudioMenuExit();
		SetGameState(SCR_TUTORIAL);
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

void MainMenuUpdate(void)
{
	CP_Vector oldMousePos = CP_Vector_Set(mousePos.x, mousePos.y);
	mousePos = CP_Vector_Set(CP_Input_GetMouseWorldX(), CP_Input_GetMouseWorldY());
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
	// Mouse Input
	if (!mouseCheck)
	{
		for (int i = 0; i < MAIN_MENU_BUTTONS; i++)
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
			MenuButtonActivate();
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
		MenuButtonActivate();

	MainMenuDraw();
}



void MainMenuExit(void)
{	
	CP_Image_Free(&mainMenuImg);
}