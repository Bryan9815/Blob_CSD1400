#include <cprocessing.h>
#include "../GameLogic/Button.h"
#include "../GameLogic/ScreenManager.h"
#include "src_options.h"
#define OPTIONS_BUTTONS 3

typedef enum {
	SOUND,
	CONTROLS,
	EXIT,
}ButtonList;

CP_Color bgColor, GREEN, WHITE;
Button optionList[OPTIONS_BUTTONS];
int selectButton, overlayNum;
int customInputX, customInputY;
int changingInput;
Button customInputMenu[BLOB_PAUSE+2][4];

void OptionsInit(void)
{
	selectButton = 0;
	overlayNum = OPTIONS_BUTTONS;
	customInputX = 1;
	customInputY = 0;
	changingInput = 0;

	bgColor = CP_Color_Create(0, 0, 0, 255);
	GREEN = CP_Color_Create(0, 255, 0, 255);
	WHITE = CP_Color_Create(255, 255, 255, 255);
	float buttonBufferY = 125.f;

	optionList[SOUND] = CreateButton((float)CP_System_GetWindowWidth() / 2, (float)CP_System_GetWindowHeight() / 2, 250.f, 100.f, "Sound");
	optionList[CONTROLS] = CreateButton((float)CP_System_GetWindowWidth() / 2, (float)CP_System_GetWindowHeight() / 2 + buttonBufferY, 250.f, 100.f, "Controls");
	optionList[EXIT] = CreateButton((float)CP_System_GetWindowWidth() / 2, (float)CP_System_GetWindowHeight() / 2 + buttonBufferY * 3, 500.f, 50.f, "Return to Main Menu");

	for (int i = 0; i < BLOB_PAUSE+1; i++)
	{
		customInputMenu[i][0] = CreateButton((float)CP_System_GetWindowWidth()/6, (float)CP_System_GetWindowHeight()/8 + 75.f * i, 250.f, 50.f, GetBlobInputName(i));
		customInputMenu[i][0].objColor = WHITE;
		for (int j = 1; j < 4; j++)
		{
			customInputMenu[i][j] = CreateButton((float)CP_System_GetWindowWidth() / 6 + 350.f * j, (float)CP_System_GetWindowHeight() / 8 + 75.f * i, 250.f, 50.f, GetBlobKeyName(i, j - 1));
			customInputMenu[i][j].isSelected = 0;
			customInputMenu[i][j].objColor = WHITE;
		}
	}
	customInputMenu[6][0] = CreateButton((float)CP_System_GetWindowWidth() / 2, (float)CP_System_GetWindowHeight() / 8 + 75 * 8, 250.f, 100.f, "Exit");
	customInputMenu[6][0].objColor = WHITE;
}

void OptionsDraw(void)
{
	CP_Settings_Background(bgColor);

	// Draw Buttons
	for (int i = 0; i < OPTIONS_BUTTONS; i++)
	{
		if (selectButton == i)
			DrawButton(optionList[i], 48.f, 1.f, GREEN);
		else
			DrawButton(optionList[i], 48.f, 1.f, WHITE);
	}

	switch (overlayNum)
	{
	case SOUND:
		// SFX and Music slider options
		break;
	case CONTROLS:
		// Draw Overlay
		CP_Settings_Fill(CP_Color_Create(50, 50, 50, 155));
		CP_Graphics_DrawRect((float)CP_System_GetWindowWidth() / 2, (float)CP_System_GetWindowHeight() / 2, (float)CP_System_GetWindowWidth()/8*7, (float)CP_System_GetWindowHeight()/8*7);
		// Draw custom inputs
		for (int i = 0; i < BLOB_PAUSE + 2; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (i != BLOB_PAUSE + 1)
				{
					if (customInputY == i && customInputX == j && customInputMenu[i][j].isSelected == 0)
						DrawButton(customInputMenu[i][j], 48.f, 1.f, GREEN);
					else
						DrawButton(customInputMenu[i][j], 48.f, 1.f, customInputMenu[i][j].objColor);
				}
				else
				{
					if (customInputY == i)
						DrawButton(customInputMenu[i][0], 48.f, 1.f, GREEN);
					else
						DrawButton(customInputMenu[i][0], 48.f, 1.f, customInputMenu[i][j].objColor);
				}
			}
		}
		break;
	default:
		break;
	}
}

CP_KEY getInput()
{
	if (CP_Input_KeyTriggered(KEY_SPACE))
		return KEY_SPACE;
	else if (CP_Input_KeyTriggered(KEY_APOSTROPHE))
		return KEY_APOSTROPHE;
	else if (CP_Input_KeyTriggered(KEY_COMMA))
		return KEY_COMMA;
	else if (CP_Input_KeyTriggered(KEY_MINUS))
		return KEY_MINUS;
	else if (CP_Input_KeyTriggered(KEY_PERIOD))
		return KEY_PERIOD;
	else if (CP_Input_KeyTriggered(KEY_SLASH))
		return KEY_SLASH;
	else if (CP_Input_KeyTriggered(KEY_0))
		return KEY_0;
	else if (CP_Input_KeyTriggered(KEY_1))
		return KEY_1;
	else if (CP_Input_KeyTriggered(KEY_2))
		return KEY_2;
	else if (CP_Input_KeyTriggered(KEY_3))
		return KEY_3;
	else if (CP_Input_KeyTriggered(KEY_4))
		return KEY_4;
	else if (CP_Input_KeyTriggered(KEY_5))
		return KEY_5;
	else if (CP_Input_KeyTriggered(KEY_6))
		return KEY_6;
	else if (CP_Input_KeyTriggered(KEY_7))
		return KEY_7;
	else if (CP_Input_KeyTriggered(KEY_8))
		return KEY_8;
	else if (CP_Input_KeyTriggered(KEY_9))
		return KEY_9;
	else if (CP_Input_KeyTriggered(KEY_SEMICOLON))
		return KEY_SEMICOLON;
	else if (CP_Input_KeyTriggered(KEY_EQUAL))
		return KEY_EQUAL;
	else if (CP_Input_KeyTriggered(KEY_A))
		return KEY_A;
	else if (CP_Input_KeyTriggered(KEY_B))
		return KEY_B;
	else if (CP_Input_KeyTriggered(KEY_C))
		return KEY_C;
	else if (CP_Input_KeyTriggered(KEY_D))
		return KEY_D;
	else if (CP_Input_KeyTriggered(KEY_E))
		return KEY_E;
	else if (CP_Input_KeyTriggered(KEY_F))
		return KEY_F;
	else if (CP_Input_KeyTriggered(KEY_G))
		return KEY_G;
	else if (CP_Input_KeyTriggered(KEY_H))
		return KEY_H;
	else if (CP_Input_KeyTriggered(KEY_I))
		return KEY_I;
	else if (CP_Input_KeyTriggered(KEY_J))
		return KEY_J;
	else if (CP_Input_KeyTriggered(KEY_K))
		return KEY_K;
	else if (CP_Input_KeyTriggered(KEY_L))
		return KEY_L;
	else if (CP_Input_KeyTriggered(KEY_M))
		return KEY_M;
	else if (CP_Input_KeyTriggered(KEY_N))
		return KEY_N;
	else if (CP_Input_KeyTriggered(KEY_O))
		return KEY_O;
	else if (CP_Input_KeyTriggered(KEY_P))
		return KEY_P;
	else if (CP_Input_KeyTriggered(KEY_Q))
		return KEY_Q;
	else if (CP_Input_KeyTriggered(KEY_R))
		return KEY_R;
	else if (CP_Input_KeyTriggered(KEY_S))
		return KEY_S;
	else if (CP_Input_KeyTriggered(KEY_T))
		return KEY_T;
	else if (CP_Input_KeyTriggered(KEY_U))
		return KEY_U;
	else if (CP_Input_KeyTriggered(KEY_V))
		return KEY_V;
	else if (CP_Input_KeyTriggered(KEY_W))
		return KEY_W;
	else if (CP_Input_KeyTriggered(KEY_X))
		return KEY_X;
	else if (CP_Input_KeyTriggered(KEY_Y))
		return KEY_Y;
	else if (CP_Input_KeyTriggered(KEY_Z))
		return KEY_Z;
	else if (CP_Input_KeyTriggered(KEY_LEFT_BRACKET))
		return KEY_LEFT_BRACKET;
	else if (CP_Input_KeyTriggered(KEY_BACKSLASH))
		return KEY_BACKSLASH;
	else if (CP_Input_KeyTriggered(KEY_RIGHT_BRACKET))
		return KEY_RIGHT_BRACKET;
	else if (CP_Input_KeyTriggered(KEY_GRAVE_ACCENT))
		return KEY_GRAVE_ACCENT;
	else if (CP_Input_KeyTriggered(KEY_WORLD_1))
		return KEY_WORLD_1;
	else if (CP_Input_KeyTriggered(KEY_WORLD_2))
		return KEY_WORLD_2;
	else if (CP_Input_KeyTriggered(KEY_ESCAPE))
		return KEY_ESCAPE;
	else if (CP_Input_KeyTriggered(KEY_ENTER))
		return KEY_ENTER;
	else if (CP_Input_KeyTriggered(KEY_TAB))
		return KEY_TAB;
	else if (CP_Input_KeyTriggered(KEY_BACKSPACE))
		return KEY_BACKSPACE;
	else if (CP_Input_KeyTriggered(KEY_INSERT))
		return KEY_INSERT;
	else if (CP_Input_KeyTriggered(KEY_DELETE))
		return KEY_DELETE;
	else if (CP_Input_KeyTriggered(KEY_RIGHT))
		return KEY_RIGHT;
	else if (CP_Input_KeyTriggered(KEY_LEFT))
		return KEY_LEFT;
	else if (CP_Input_KeyTriggered(KEY_DOWN))
		return KEY_DOWN;
	else if (CP_Input_KeyTriggered(KEY_UP))
		return KEY_UP;
	else if (CP_Input_KeyTriggered(KEY_PAGE_UP))
		return KEY_PAGE_UP;
	else if (CP_Input_KeyTriggered(KEY_PAGE_DOWN))
		return KEY_PAGE_DOWN;
	else if (CP_Input_KeyTriggered(KEY_HOME))
		return KEY_HOME;
	else if (CP_Input_KeyTriggered(KEY_END))
		return KEY_END;
	else if (CP_Input_KeyTriggered(KEY_CAPS_LOCK))
		return KEY_CAPS_LOCK;
	else if (CP_Input_KeyTriggered(KEY_SCROLL_LOCK))
		return KEY_SCROLL_LOCK;
	else if (CP_Input_KeyTriggered(KEY_NUM_LOCK))
		return KEY_NUM_LOCK;
	else if (CP_Input_KeyTriggered(KEY_PRINT_SCREEN))
		return KEY_PRINT_SCREEN;
	else if (CP_Input_KeyTriggered(KEY_PAUSE))
		return KEY_PAUSE;
	else if (CP_Input_KeyTriggered(KEY_F1))
		return KEY_F1;
	else if (CP_Input_KeyTriggered(KEY_COMMA))
		return KEY_F2;
	else if (CP_Input_KeyTriggered(KEY_COMMA))
		return KEY_F3;
	else if (CP_Input_KeyTriggered(KEY_COMMA))
		return KEY_F4;
	else if (CP_Input_KeyTriggered(KEY_F5))
		return KEY_F5;
	else if (CP_Input_KeyTriggered(KEY_F6))
		return KEY_F6;
	else if (CP_Input_KeyTriggered(KEY_F7))
		return KEY_F7;
	else if (CP_Input_KeyTriggered(KEY_F8))
		return KEY_F8;
	else if (CP_Input_KeyTriggered(KEY_F9))
		return KEY_F9;
	else if (CP_Input_KeyTriggered(KEY_F10))
		return KEY_F10;
	else if (CP_Input_KeyTriggered(KEY_F11))
		return KEY_F11;
	else if (CP_Input_KeyTriggered(KEY_F12))
		return KEY_F12;
	else if (CP_Input_KeyTriggered(KEY_F13))
		return KEY_F13;
	else if (CP_Input_KeyTriggered(KEY_F14))
		return KEY_F14;
	else if (CP_Input_KeyTriggered(KEY_F15))
		return KEY_F15;
	else if (CP_Input_KeyTriggered(KEY_F16))
		return KEY_F16;
	else if (CP_Input_KeyTriggered(KEY_F17))
		return KEY_F17;
	else if (CP_Input_KeyTriggered(KEY_F18))
		return KEY_F18;
	else if (CP_Input_KeyTriggered(KEY_F19))
		return KEY_F19;
	else if (CP_Input_KeyTriggered(KEY_F20))
		return KEY_F20;
	else if (CP_Input_KeyTriggered(KEY_F21))
		return KEY_F21;
	else if (CP_Input_KeyTriggered(KEY_F22))
		return KEY_F22;
	else if (CP_Input_KeyTriggered(KEY_F23))
		return KEY_F23;
	else if (CP_Input_KeyTriggered(KEY_F24))
		return KEY_F24;
	else if (CP_Input_KeyTriggered(KEY_F25))
		return KEY_F25;
	else if (CP_Input_KeyTriggered(KEY_KP_0))
		return KEY_KP_0;
	else if (CP_Input_KeyTriggered(KEY_KP_1))
		return KEY_KP_1;
	else if (CP_Input_KeyTriggered(KEY_KP_2))
		return KEY_KP_2;
	else if (CP_Input_KeyTriggered(KEY_KP_3))
		return KEY_KP_3;
	else if (CP_Input_KeyTriggered(KEY_KP_4))
		return KEY_KP_4;
	else if (CP_Input_KeyTriggered(KEY_KP_5))
		return KEY_KP_5;
	else if (CP_Input_KeyTriggered(KEY_KP_6))
		return KEY_KP_6;
	else if (CP_Input_KeyTriggered(KEY_KP_7))
		return KEY_KP_7;
	else if (CP_Input_KeyTriggered(KEY_KP_8))
		return KEY_KP_8;
	else if (CP_Input_KeyTriggered(KEY_KP_9))
		return KEY_KP_9;
	else if (CP_Input_KeyTriggered(KEY_KP_DECIMAL))
		return KEY_KP_DECIMAL;
	else if (CP_Input_KeyTriggered(KEY_KP_DIVIDE))
		return KEY_KP_DIVIDE;
	else if (CP_Input_KeyTriggered(KEY_KP_MULTIPLY))
		return KEY_KP_MULTIPLY;
	else if (CP_Input_KeyTriggered(KEY_KP_SUBTRACT))
		return KEY_KP_SUBTRACT;
	else if (CP_Input_KeyTriggered(KEY_KP_ADD))
		return KEY_KP_ADD;
	else if (CP_Input_KeyTriggered(KEY_KP_ENTER))
		return KEY_KP_ENTER;
	else if (CP_Input_KeyTriggered(KEY_KP_EQUAL))
		return KEY_KP_EQUAL;
	else if (CP_Input_KeyTriggered(KEY_LEFT_SHIFT))
		return KEY_LEFT_SHIFT;
	else if (CP_Input_KeyTriggered(KEY_LEFT_CONTROL))
		return KEY_LEFT_CONTROL;
	else if (CP_Input_KeyTriggered(KEY_LEFT_ALT))
		return KEY_LEFT_ALT;
	else if (CP_Input_KeyTriggered(KEY_LEFT_SUPER))
		return KEY_LEFT_SUPER;
	else if (CP_Input_KeyTriggered(KEY_RIGHT_SHIFT))
		return KEY_RIGHT_SHIFT;
	else if (CP_Input_KeyTriggered(KEY_RIGHT_CONTROL))
		return KEY_RIGHT_CONTROL;
	else if (CP_Input_KeyTriggered(KEY_RIGHT_ALT))
		return KEY_RIGHT_ALT;
	else if (CP_Input_KeyTriggered(KEY_RIGHT_SUPER))
		return KEY_RIGHT_SUPER;
	else if (CP_Input_KeyTriggered(KEY_MENU))
		return KEY_MENU;
	else
		return 0;
}

void OptionsInput(void)
{
	if (overlayNum >= OPTIONS_BUTTONS)
	{
		if (GetBlobInput(BLOB_UP))
		{
			if (selectButton == 0)
				selectButton = OPTIONS_BUTTONS - 1;
			else
				selectButton--;
		}
		else if (GetBlobInput(BLOB_DOWN))
		{
			if (selectButton == OPTIONS_BUTTONS - 1)
				selectButton = 0;
			else
				selectButton++;
		}
		if (GetBlobInput(BLOB_INTERACT))
		{
			switch (selectButton)
			{
			case SOUND:
				break;
			case CONTROLS:
				overlayNum = CONTROLS;
				break;
			case EXIT:
				SetGameState(SRC_MAIN_MENU);
				break;
			default:
				break;
			}
		}
	}
	else
	{
		if (changingInput == 0)
		{
			switch (overlayNum)
			{
			case SOUND:
				// SFX and Music slider options
				break;
			case CONTROLS:
				if (GetBlobInput(BLOB_UP))
				{
					if (customInputY == 0)
						customInputY = BLOB_PAUSE + 1;
					else
						customInputY--;
				}
				else if (GetBlobInput(BLOB_DOWN))
				{
					if (customInputY == BLOB_PAUSE + 1)
						customInputY = 0;
					else
						customInputY++;
				}
				if (GetBlobInput(BLOB_LEFT))
				{
					if (customInputX == 1)
						customInputX = 3;
					else
						customInputX--;
				}
				else if (GetBlobInput(BLOB_RIGHT))
				{
					if (customInputX == 3)
						customInputX = 1;
					else
						customInputX++;
				}
				if (GetBlobInput(BLOB_INTERACT))
				{
					if (customInputY == BLOB_PAUSE + 1) // if at Exit button
						overlayNum = OPTIONS_BUTTONS;
					else
					{
						customInputMenu[customInputY][customInputX].isSelected = 1;
						customInputMenu[customInputY][customInputX].objColor = CP_Color_Create(255, 255, 0, 255);
						changingInput = 1;
					}
				}
				break;
			default:
				break;
			}
		}
		else if (changingInput == 1)
		{
			if (getInput() != 0)
			{
				EditBlobInput(customInputY, customInputX - 1, getInput());
				customInputMenu[customInputY][customInputX].text = GetBlobKeyName(customInputY, customInputX - 1);
				customInputMenu[customInputY][customInputX].isSelected = 0;
				customInputMenu[customInputY][customInputX].objColor = WHITE;
				changingInput = 0;
			}
		}
	}
}

void OptionsUpdate(void)
{
	OptionsDraw();
	OptionsInput();
}

void OptionsExit(void)
{
	
}