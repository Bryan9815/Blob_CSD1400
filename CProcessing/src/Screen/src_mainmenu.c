#include <cprocessing.h>
#include "ScreenManager.h"
#include "src_mainmenu.h"
#define BUTTON_NUM 4

typedef struct Button {
	float posX;
	float posY;
	float width;
	float height;
	float alpha;
	const char* text;
	int isSelected;
	CP_Color objColor;
}Button;

typedef enum {
	START,
	OPTION,
	CREDITS,
	EXIT,
}ButtonList;

CP_Color bgColor;
Button menuList[BUTTON_NUM];
int selectButton;

void MainMenuInit(void)
{
	selectButton = 0;
	bgColor = CP_Color_Create(0, 0, 0, 255);

	menuList[START].posX = (float)CP_System_GetWindowWidth() / 2;
	menuList[START].posY = (float)CP_System_GetWindowHeight() / 2;
	menuList[START].width = 250.f;
	menuList[START].height = 100.f;
	menuList[START].text = "Start";

	menuList[OPTION].posX = (float)CP_System_GetWindowWidth() / 2;
	menuList[OPTION].posY = (float)CP_System_GetWindowHeight() / 2 + 125.f;
	menuList[OPTION].width = 250.f;
	menuList[OPTION].height = 100.f;
	menuList[OPTION].text = "Options";

	menuList[CREDITS].posX = (float)CP_System_GetWindowWidth() / 2;
	menuList[CREDITS].posY = (float)CP_System_GetWindowHeight() / 2 + 250.f;
	menuList[CREDITS].width = 250.f;
	menuList[CREDITS].height = 100.f;
	menuList[CREDITS].text = "Credits";

	menuList[EXIT].posX = (float)CP_System_GetWindowWidth() / 2;
	menuList[EXIT].posY = (float)CP_System_GetWindowHeight() / 2 + 375.f;
	menuList[EXIT].width = 250.f;
	menuList[EXIT].height = 100.f;
	menuList[EXIT].text = "Quit";

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
			DrawButton(menuList[i], 1.25f, CP_Color_Create(255, 255, 255, 255));
		else
			DrawButton(menuList[i], 1.f, CP_Color_Create(255,255,255,255));
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