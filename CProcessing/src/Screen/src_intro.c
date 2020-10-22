#include <cprocessing.h>
#include "../GameLogic/ScreenManager.h"
#include "src_intro.h"

float splashTimer, logoWidth, logoHeight, logoPosX, logoPosY;
float logoAlpha;
CP_Image splashLogo;
CP_Color bgColor;

void IntroInit(void)
{
	splashTimer = 3.f;	//Hold Timer

	splashLogo = CP_Image_Load("././Assets/DigiPen_WHITE.png");
	logoWidth = (float)CP_Image_GetWidth(splashLogo);
	logoHeight = (float)CP_Image_GetHeight(splashLogo);
	logoPosX = (float)CP_System_GetWindowWidth() / 2;
	logoPosY = (float)CP_System_GetWindowHeight() / 2;
	logoAlpha = 255;

	bgColor = CP_Color_Create(0, 0, 0, 255);
}

void IntroUpdate(void)
{
	CP_Settings_Background(bgColor);

	if (!GetFader().isFading)
	{
		if (GetFader().fadeAlpha == 0) 
		{
			splashTimer -= CP_System_GetDt();
			if (splashTimer <= 0) 
			{
				ScreenStartFade(FADE_IN);
			}
		}
		else if(GetFader().fadeAlpha == 255)
		{
			SetGameState(SRC_MAIN_MENU);
		}
	}

	CP_Image_Draw(splashLogo, logoPosX, logoPosY, logoWidth, logoHeight, (int)logoAlpha);
}

void IntroExit(void)
{

}