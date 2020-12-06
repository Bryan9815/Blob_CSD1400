#include <cprocessing.h>
#include "../GameLogic/Button.h"
#include "../GameLogic/ScreenManager.h"
#include "scr_options.h"
#include "../Audio/AudioManager.h"
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
int soundInputX, soundInputY;
int changingInput;
bool mouseCheck;
Button customInputMenu[BLOB_PAUSE+2][3];
Button soundMenu[SFX + 2][3];
CP_Vector mousePos;

void CustomInputButtonsInit(void)
{
	mouseCheck = false;
	for (int i = 0; i <= BLOB_PAUSE; i++)
	{
		customInputMenu[i][0] = CreateButton((float)CP_System_GetWindowWidth() / 2 + ((float)CP_System_GetWindowWidth() / 3 * -1), (float)CP_System_GetWindowHeight() / 8 + 75.f * i, 250.f, 50.f, GetBlobInputName(i));
		customInputMenu[i][0].objColor = WHITE;
		for (int j = 1; j <= 2; j++)
		{
			/*switch (j)
			{
			case 1:
				customInputMenu[i][j] = CreateButton((float)CP_System_GetWindowWidth() / 2 - 450.f, (float)CP_System_GetWindowHeight() / 8 + 75.f * i, 250.f, 50.f, GetBlobKeyName(i, j - 1));
				break;
			case 2:
				customInputMenu[i][j] = CreateButton((float)CP_System_GetWindowWidth() / 2 + 450.f, (float)CP_System_GetWindowHeight() / 8 + 75.f * i, 250.f, 50.f, GetBlobKeyName(i, j - 1));
				break;
			}			*/
			customInputMenu[i][j] = CreateButton((float)CP_System_GetWindowWidth() / 2 + ((float)CP_System_GetWindowWidth() / 3 * (j-1)), (float)CP_System_GetWindowHeight() / 8 + 75.f * i, 250.f, 50.f, GetBlobKeyName(i, j - 1));
			customInputMenu[i][j].isSelected = 0;
			customInputMenu[i][j].objColor = WHITE;
		}
	}
}

void SoundMenuInit(void)
{
	mouseCheck = false;
	for (int i = 0; i <= SFX; i++)
	{
		soundMenu[i][0] = CreateButton((float)CP_System_GetWindowWidth() / 5, (float)CP_System_GetWindowHeight() / 4 + 150.f * i, 250.f, 50.f, GetSoundText(i));
		soundMenu[i][1] = CreateButton((float)CP_System_GetWindowWidth() / 5 + 600.f, (float)CP_System_GetWindowHeight() / 4 + 150.f * i, 50.f, 50.f, "-");
		soundMenu[i][2] = CreateButton((float)CP_System_GetWindowWidth() / 5 + 900.f, (float)CP_System_GetWindowHeight() / 4 + 150.f * i, 50.f, 50.f, "+");
		for (int j = 0; j <= 2; j++)
		{
			soundMenu[i][j].objColor = WHITE;
		}
	}
	soundMenu[2][0] = CreateButton((float)CP_System_GetWindowWidth() / 2, (float)CP_System_GetWindowHeight() / 8 + 75 * 8, 250.f, 100.f, "Exit");
	soundMenu[2][0].objColor = WHITE;
}

void OptionsInit(void)
{
	selectButton = 0;
	overlayNum = OPTIONS_BUTTONS;
	customInputX = 1;
	customInputY = 0;
	soundInputX = 1;
	soundInputY = 0;
	changingInput = 0;

	bgColor = CP_Color_Create(0, 0, 0, 255);
	GREEN = CP_Color_Create(0, 255, 0, 255);
	WHITE = CP_Color_Create(255, 255, 255, 255);
	float buttonBufferY = 125.f;

	optionList[SOUND] = CreateButton((float)CP_System_GetWindowWidth() / 2, (float)CP_System_GetWindowHeight() / 2, 250.f, 100.f, "Sound");
	optionList[CONTROLS] = CreateButton((float)CP_System_GetWindowWidth() / 2, (float)CP_System_GetWindowHeight() / 2 + buttonBufferY, 250.f, 100.f, "Controls");
	optionList[EXIT] = CreateButton((float)CP_System_GetWindowWidth() / 2, (float)CP_System_GetWindowHeight() / 2 + buttonBufferY * 3, 500.f, 50.f, "Return to Main Menu");

	CustomInputButtonsInit();
	customInputMenu[6][0] = CreateButton((float)CP_System_GetWindowWidth() / 2, (float)CP_System_GetWindowHeight() / 8 + 75 * 8, 250.f, 100.f, "Exit");
	customInputMenu[6][0].objColor = WHITE;

	SoundMenuInit();
}

void OptionsDraw(void)
{
	CP_Settings_Background(bgColor);

	CP_Settings_TextSize(125.0f);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Font_DrawText("OPTIONS", (float)CP_System_GetWindowWidth() / 2, (float)CP_System_GetWindowHeight() / 3);
	


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
		// SFX and Music slider options (currently buttons)
		CP_Settings_Fill(CP_Color_Create(50, 50, 50, 255));
		CP_Graphics_DrawRect((float)CP_System_GetWindowWidth() / 2, (float)CP_System_GetWindowHeight() / 2, (float)CP_System_GetWindowWidth() / 8 * 7, (float)CP_System_GetWindowHeight() / 8 * 7 + 10.0f);
		for (int i = 0; i < (SFX + 2); i++)
		{
			if (i == (SFX + 1)) //for exit button
			{
				if (soundInputY == i)
					DrawButton(soundMenu[i][0], 48.f, 1.f, GREEN);
				else 
					DrawButton(soundMenu[i][0], 48.f, 1.f, soundMenu[i][0].objColor);
			}
			else
			{
				CP_Settings_Fill(WHITE);
				CP_Font_DrawText(soundMenu[i][0].text, soundMenu[i][0].posX, soundMenu[i][0].posY); //text for "Music" and "Sound"
				CP_Font_DrawText(GetVolumeText(i), ((soundMenu[i][1].posX + soundMenu[i][2].posX) / 2.f), soundMenu[i][0].posY); //text for vol lvl
				for (int j = 1; j <= 2; j++)
				{
						if (soundInputY == i && soundInputX == j && soundMenu[i][j].isSelected == 0)
							DrawButton(soundMenu[i][j], 48.f, 1.f, GREEN);
						else
							DrawButton(soundMenu[i][j], 48.f, 1.f, soundMenu[i][j].objColor);
				}
			}
		}
		break;
	case CONTROLS:
		// Draw Overlay
		CP_Settings_Fill(CP_Color_Create(50, 50, 50, 255));
		CP_Graphics_DrawRect((float)CP_System_GetWindowWidth() / 2, (float)CP_System_GetWindowHeight() / 2, (float)CP_System_GetWindowWidth() / 8 * 7, (float)CP_System_GetWindowHeight() / 8 * 7 + 10.0f);
		// Draw custom inputs
		for (int i = 0; i < BLOB_PAUSE + 2; i++)
		{
			if (i == BLOB_PAUSE + 1)
			{
				DrawButton(customInputMenu[i][0], 48.f, 1.f, WHITE);
			}
			else
			{
				CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
				CP_Font_DrawText(customInputMenu[i][0].text, customInputMenu[i][0].posX, customInputMenu[i][0].posY);
			}
			for (int j = 1; j < 3; j++)
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

void OptionsMenuActivate(void)
{
	switch (selectButton)
	{
	case SOUND:
		overlayNum = SOUND;
		break;
	case CONTROLS:
		overlayNum = CONTROLS;
		break;
	case EXIT:
		SaveGame();
		SetGameState(SCR_MAIN_MENU);
		break;
	default:
		break;
	}
}

void ControlMenuActivate(void)
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

void SoundMenuActiviate(void)
{
	if (soundInputY == 2)
		overlayNum = OPTIONS_BUTTONS;
	else
	{
		soundMenu[soundInputY][soundInputX].isSelected = 1;
	}

	if (soundMenu[SFX][1].isSelected == 1 && GetSFXVolume() > SOUND_MIN)
		SetSFXVolume(GetSFXVolume() - 1);
	else if (soundMenu[SFX][2].isSelected == 1 && GetSFXVolume() < SOUND_MAX)
		SetSFXVolume(GetSFXVolume() + 1);
	else if (soundMenu[MUSIC][1].isSelected == 1 && GetBGMVolume() > SOUND_MIN)
		SetBGMVolume(GetBGMVolume() - 1);
	else if (soundMenu[MUSIC][2].isSelected == 1 && GetBGMVolume() < SOUND_MAX)
		SetBGMVolume(GetBGMVolume() + 1);

	soundMenu[soundInputY][soundInputX].isSelected = 0;
}

void OptionsInput(void)
{
	CP_Vector oldMousePos = CP_Vector_Set(mousePos.x, mousePos.y);
	mousePos = CP_Vector_Set(CP_Input_GetMouseWorldX(), CP_Input_GetMouseWorldY());
	// Options Menu
	if (overlayNum >= OPTIONS_BUTTONS)
	{
		if (GetBlobInputTriggered(BLOB_UP))
		{
			if (selectButton == 0)
				selectButton = OPTIONS_BUTTONS - 1;
			else
				selectButton--;
		}
		else if (GetBlobInputTriggered(BLOB_DOWN))
		{
			if (selectButton == OPTIONS_BUTTONS - 1)
				selectButton = 0;
			else
				selectButton++;
		}
		if (!mouseCheck)
		{
			for (int i = 0; i < OPTIONS_BUTTONS; i++)
			{
				// Mouse x-pos collision check
				if (mousePos.x >= (optionList[i].posX - optionList[i].width / 2) && mousePos.x <= (optionList[i].posX + optionList[i].width / 2))
				{
					// Mouse y-pos collision check	
					if (mousePos.y >= (optionList[i].posY - optionList[i].height / 2) && mousePos.y <= (optionList[i].posY + optionList[i].height / 2))
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
				optionList[selectButton].isSelected = 1;
			else if (CP_Input_MouseReleased(MOUSE_BUTTON_1))
			{
				OptionsMenuActivate();
				optionList[selectButton].isSelected = 0;
				mouseCheck = false;
			}
			if ((int)mousePos.x != (int)oldMousePos.x || (int)mousePos.y != (int)oldMousePos.y)
			{
				if (mousePos.x < (optionList[selectButton].posX - optionList[selectButton].width / 2) || mousePos.x >(optionList[selectButton].posX + optionList[selectButton].width / 2))
					mouseCheck = false;
				if (mousePos.y < (optionList[selectButton].posY - optionList[selectButton].height / 2) || mousePos.y >(optionList[selectButton].posY + optionList[selectButton].height / 2))
					mouseCheck = false;
			}
		}
		if (GetBlobInputTriggered(BLOB_INTERACT))
		{
			OptionsMenuActivate();
		}
	}
	else // Overlays
	{
		if (changingInput == 0)
		{
			switch (overlayNum)
			{
			case SOUND:
				// SFX and Music slider options
				if (GetBlobInputTriggered(BLOB_UP))
				{
					if (soundInputY == 0)
						soundInputY = SFX + 1;
					else
						soundInputY--;
				}
				else if (GetBlobInputTriggered(BLOB_DOWN))
				{
					if (soundInputY == SFX + 1)
						soundInputY = 0;
					else
						soundInputY++;
				}
				if (GetBlobInputTriggered(BLOB_LEFT))
				{
					if (soundInputX == 1)
						soundInputX = 2;
					else
						soundInputX--;
				}
				else if (GetBlobInputTriggered(BLOB_RIGHT))
				{
					if (soundInputX == 2)
						soundInputX = 1;
					else
						soundInputX++;
				}

				if (!mouseCheck)
				{
					for (int i = 0; i < 3; i++)
					{
						for (int j = 0; j < 3; j++)
						{
							// Mouse x-pos collision check
							if (mousePos.x >= (soundMenu[i][j].posX - soundMenu[i][j].width / 2) && mousePos.x <= (soundMenu[i][j].posX + soundMenu[i][j].width / 2))
							{
								// Mouse y-pos collision check	
								if (mousePos.y >= (soundMenu[i][j].posY - soundMenu[i][j].height / 2) && mousePos.y <= (soundMenu[i][j].posY + soundMenu[i][j].height / 2))
								{
									soundInputX = j;
									soundInputY = i;
									mouseCheck = true;
								}
							}
						}
					}
				}
				else
				{
					if (CP_Input_MouseDown(MOUSE_BUTTON_1))
						soundMenu[soundInputY][soundInputX].isSelected = 1;
					else if (CP_Input_MouseReleased(MOUSE_BUTTON_1))
					{
						SoundMenuActiviate();
						soundMenu[soundInputY][soundInputX].isSelected = 0;
						mouseCheck = true;
					}
					if ((int)mousePos.x != (int)oldMousePos.x || (int)mousePos.y != (int)oldMousePos.y)
					{
						if (mousePos.x < (soundMenu[soundInputY][soundInputX].posX - soundMenu[soundInputY][soundInputX].width / 2) || mousePos.x >(soundMenu[soundInputY][soundInputX].posX + soundMenu[soundInputY][soundInputX].width / 2))
							mouseCheck = false;
						if (mousePos.y < (soundMenu[soundInputY][soundInputX].posY - soundMenu[soundInputY][soundInputX].height / 2) || mousePos.y >(soundMenu[soundInputY][soundInputX].posY + soundMenu[soundInputY][soundInputX].height / 2))
							mouseCheck = false;
					}
				}
				if (GetBlobInputTriggered(BLOB_INTERACT))
				{
					ControlMenuActivate();
				}
				break;
			case CONTROLS:
				if (GetBlobInputTriggered(BLOB_UP))
				{
					if (customInputY == 0)
						customInputY = BLOB_PAUSE + 1;
					else
						customInputY--;
				}
				else if (GetBlobInputTriggered(BLOB_DOWN))
				{
					if (customInputY == BLOB_PAUSE + 1)
						customInputY = 0;
					else
						customInputY++;
				}
				if (GetBlobInputTriggered(BLOB_LEFT))
				{
					if (customInputX == 1)
						customInputX = 2;
					else
						customInputX--;
				}
				else if (GetBlobInputTriggered(BLOB_RIGHT))
				{
					if (customInputX == 2)
						customInputX = 1;
					else
						customInputX++;
				}
				if(!mouseCheck)
				{
					for (int i = 0; i < BLOB_PAUSE + 2; i++)
					{
						for (int j = 0; j < 4; j++)
						{
							// Mouse x-pos collision check
							if (mousePos.x >= (customInputMenu[i][j].posX - customInputMenu[i][j].width / 2) && mousePos.x <= (customInputMenu[i][j].posX + customInputMenu[i][j].width / 2))
							{
								// Mouse y-pos collision check	
								if (mousePos.y >= (customInputMenu[i][j].posY - customInputMenu[i][j].height / 2) && mousePos.y <= (customInputMenu[i][j].posY + customInputMenu[i][j].height / 2))
								{
									customInputX = j;
									customInputY = i;
									mouseCheck = true;
								}
							}
						}
					}
				}
				else
				{
					if (CP_Input_MouseDown(MOUSE_BUTTON_1))
						customInputMenu[customInputY][customInputX].isSelected = 1;
					else if (CP_Input_MouseReleased(MOUSE_BUTTON_1))
					{
						ControlMenuActivate();
						customInputMenu[customInputY][customInputX].isSelected = 0;
						mouseCheck = true;
					}
					if ((int)mousePos.x != (int)oldMousePos.x || (int)mousePos.y != (int)oldMousePos.y)
					{
						if (mousePos.x < (customInputMenu[customInputY][customInputX].posX - customInputMenu[customInputY][customInputX].width / 2) || mousePos.x >(customInputMenu[customInputY][customInputX].posX + customInputMenu[customInputY][customInputX].width / 2))
							mouseCheck = false;
						if (mousePos.y < (customInputMenu[customInputY][customInputX].posY - customInputMenu[customInputY][customInputX].height / 2) || mousePos.y >(customInputMenu[customInputY][customInputX].posY + customInputMenu[customInputY][customInputX].height / 2))
							mouseCheck = false;
					}
				}
				if (GetBlobInputTriggered(BLOB_INTERACT))
				{
					ControlMenuActivate();
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
				CustomInputButtonsInit();
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