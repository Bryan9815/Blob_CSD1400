#include <cprocessing.h>
#include "ScreenManager.h"
#include "src_mainmenu.h"
#define BUTTON_NUM 4

CP_Color bgColor;
Button startGame, options, credits, exit;
Button *menuList[BUTTON_NUM] = { &startGame, &options, &credits, &exit };
int selectButton;

void MainMenuInit(void)
{
	selectButton = 0;
	bgColor = CP_Color_Create(0, 0, 0, 255);

	startGame.posX = (float)CP_System_GetWindowWidth() / 2;
	startGame.posY = (float)CP_System_GetWindowHeight() / 2;
	startGame.width = 250.f;
	startGame.height = 100.f;
	startGame.text = "Start";

	options.posX = (float)CP_System_GetWindowWidth() / 2;
	options.posY = (float)CP_System_GetWindowHeight() / 2 + 125.f;
	options.width = 250.f;
	options.height = 100.f;
	options.text = "Options";

	credits.posX = (float)CP_System_GetWindowWidth() / 2;
	credits.posY = (float)CP_System_GetWindowHeight() / 2 + 250.f;
	credits.width = 250.f;
	credits.height = 100.f;
	credits.text = "Credits";

	exit.posX = (float)CP_System_GetWindowWidth() / 2;
	exit.posY = (float)CP_System_GetWindowHeight() / 2 + 375.f;
	exit.width = 250.f;
	exit.height = 100.f;
	exit.text = "Quit";

	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	CP_Settings_RectMode(CP_POSITION_CENTER);
}

void DrawButton(Button button, float scale, CP_Color buttonColor)
{	
	CP_Settings_Fill(buttonColor);
	CP_Graphics_DrawRect(button.posX, button.posY, button.width * scale, button.height * scale);
	CP_Settings_Fill(CP_Color_Create(0,0,0,255));
	CP_Settings_TextSize(48 * scale);
	CP_Font_DrawText(button.text, button.posX, button.posY);
}

void MainMenuUpdate(void)
{
	CP_Settings_Background(bgColor);

	// Draw Buttons
	for (int i = 0; i < BUTTON_NUM; i++)
	{
		if(selectButton == i)
			DrawButton(*menuList[i], 1.25f, CP_Color_Create(255, 255, 255, 255));
		else
			DrawButton(*menuList[i], 1.f, CP_Color_Create(255,255,255,255));
	}

	// Input
	if (CP_Input_KeyTriggered(KEY_UP))
	{
		if (selectButton == 0)
			selectButton = 3;
		else
			selectButton--;
	}
	else if (CP_Input_KeyTriggered(KEY_DOWN))
	{
		if (selectButton == 3)
			selectButton = 0;
		else
			selectButton++;
	}
	if (CP_Input_KeyTriggered(KEY_SPACE) || CP_Input_KeyTriggered(KEY_ENTER))
	{
		switch (selectButton)
		{
		case 0: // Start
			SetGameState(SRC_GAMEPLAY);
			break;
		case 1: // Options
			SetGameState(SRC_OPTION);
			break;
		case 2: // Credits
			SetGameState(SRC_CREDITS);
			break;
		case 3: // Exit
			MainMenuExit();
			break;
		default:
			break;
		}
	}
}

void MainMenuExit(void)
{
	CP_Engine_Terminate();
}