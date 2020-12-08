//---------------------------------------------------------
// file:	scr_intro.c
// author:	[Teh Kai Hong Bryan]
// email:	[t.kaihongbryan@digipen.edu]
//
// brief:	Header file for scr_intro.c
//
//
// Copyright � 2020 DigiPen, All rights reserved.
//---------------------------------------------------------
#include <cprocessing.h>
#include "../GameLogic/ScreenManager.h"
#include "SCR_intro.h"

float splashTimer, logoWidth, logoHeight, logoPosX, logoPosY;
float logoAlpha;
CP_Image splashLogo;
CP_Color bgColor;

// Initializes Intro
void IntroInit(void)
{
	splashTimer = 2.0f;	//Hold Timer

	splashLogo = CP_Image_Load("././Assets/DigiPen_WHITE.png");
	logoWidth = (float)CP_Image_GetWidth(splashLogo);
	logoHeight = (float)CP_Image_GetHeight(splashLogo);
	logoPosX = (float)CP_System_GetWindowWidth() / 2;
	logoPosY = (float)CP_System_GetWindowHeight() / 2;
	logoAlpha = 255;

	bgColor = CP_Color_Create(0, 0, 0, 255);
}

// Updates Intro
void IntroUpdate(void)
{
	CP_Settings_Background(bgColor);

	if (!GetFader()->isFading)
	{
		if (GetFader()->fadeAlpha == 0)
		{
			splashTimer -= CP_System_GetDt();
			if (splashTimer <= 0) 
			{
				ScreenStartFade(FADE_IN);
			}
		}
		else if(GetFader()->fadeAlpha == 255)
		{
			SetGameState(SCR_MAIN_MENU);
		}
	}
	if (GetBlobInputTriggered(BLOB_INTERACT))
	{
		SetGameState(SCR_MAIN_MENU);
	}

	CP_Image_Draw(splashLogo, logoPosX, logoPosY, logoWidth, logoHeight, (int)logoAlpha);
}

// Exits Intro
void IntroExit(void)
{
	CP_Image_Free(&splashLogo);
}