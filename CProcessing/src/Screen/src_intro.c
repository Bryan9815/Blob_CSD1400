#include <cprocessing.h>
#include "ScreenManager.h"
#include "src_intro.h"

float splashTimer, logoWidth, logoHeight, logoPosX, logoPosY;
float logoAlpha;
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

	// Draw Logo
	if (logoAlpha < 255.f)
		logoAlpha += CP_System_GetDt() * 150;

	CP_Image_Draw(splashLogo, logoPosX, logoPosY, logoWidth, logoHeight, (int)logoAlpha);

	// Handle timer
	splashTimer -= CP_System_GetDt();
	if (splashTimer <= 0)
		SetGameState(SRC_MAIN_MENU);
}

void IntroExit(void)
{

}