#include <cprocessing.h>
#include "../GameLogic/Button.h"
#include "../GameLogic/ScreenManager.h"
#include "src_options.h"
#define BUTTON_NUM 4

typedef enum {
	RESOLUTION,
	SOUND,
	CONTROLS,
	EXIT,
}ButtonList;

CP_Color bgColor;
Button optionList[BUTTON_NUM];
int selectButton;

void OptionsInit(void)
{
	selectButton = 0;
	bgColor = CP_Color_Create(0, 0, 0, 255);
	float buttonBufferY = 125.f;

	optionList[RESOLUTION] = CreateButton((float)CP_System_GetWindowWidth() / 2, (float)CP_System_GetWindowHeight() / 2, 250.f, 100.f, "Window Resolution");
	optionList[SOUND] = CreateButton((float)CP_System_GetWindowWidth() / 2, (float)CP_System_GetWindowHeight() / 2 + buttonBufferY, 250.f, 100.f, "Sound");
	optionList[CONTROLS] = CreateButton((float)CP_System_GetWindowWidth() / 2, (float)CP_System_GetWindowHeight() / 2 + buttonBufferY * 2, 250.f, 100.f, "Controls");
	optionList[EXIT] = CreateButton((float)CP_System_GetWindowWidth() / 2, (float)CP_System_GetWindowHeight() / 2 + buttonBufferY * 3, 250.f, 100.f, "Quit");
}

void OptionsDraw(void)
{
	CP_Settings_Background(bgColor);

	// Draw Buttons
	for (int i = 0; i < BUTTON_NUM; i++)
	{
		if (selectButton == i)
			DrawButton(optionList[i], 48.f, 1.25f, CP_Color_Create(255, 255, 255, 255));
		else
			DrawButton(optionList[i], 48.f, 1.f, CP_Color_Create(255, 255, 255, 255));
	}
}

void OptionsUpdate(void)
{
	OptionsDraw();
}

void OptionsExit(void)
{
	//SetGameState(SRC_MAIN_MENU);
}