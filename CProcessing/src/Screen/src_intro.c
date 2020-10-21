#include <cprocessing.h>
#include "ScreenManager.h"
#include "src_intro.h"

float splashTimer, logoWidth, logoHeight, logoPosX, logoPosY;
int logoAlpha;
CP_Image splashLogo;
CP_Color bgColor;

void IntroInit(void)
{
	splashTimer = 5.f;

	splashLogo = CP_Image_Load("././Assets/DigiPen_WHITE.png");
	logoWidth = (float)CP_Image_GetWidth(splashLogo);
	logoHeight = (float)CP_Image_GetHeight(splashLogo);
	logoPosX = (float)CP_System_GetWindowWidth() / 2;
	logoPosY = (float)CP_System_GetWindowHeight() / 2;
	logoAlpha = 0;

	bgColor = CP_Color_Create(0, 0, 0, 255);
}

void IntroUpdate(void)
{
	CP_Settings_Background(bgColor);

	CP_Image_Draw(splashLogo, logoPosX, logoPosY, logoWidth, logoHeight, logoAlpha);
	splashTimer -= CP_System_GetDt();
	if (splashTimer <= 0)
	{
		SetGameState(MAIN_MENU);
		CP_Engine_SetNextGameState(GameInit, GameUpdate, GameExit);
	}
}

void IntroExit(void)
{

}