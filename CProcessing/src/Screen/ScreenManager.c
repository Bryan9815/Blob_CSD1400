#include <cprocessing.h>
#include <stdio.h>

static const float WINDOW_SCALE = 0.8f;
static const int WINDOW_WIDTH = 1600, WINDOW_HEIGHT = 900;

CP_Color bgColor;

void GameInit(void)
{
	/*Window Settings*/
	CP_System_SetWindowTitle("Blob");
	CP_System_SetWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	CP_System_SetFrameRate(60.0f);

	/*Debug Console*/
	CP_System_ShowConsole();
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);

	bgColor = CP_Color_Create(0, 0, 0, 255);
	CP_Settings_Background(bgColor);
}


void GameUpdate(void)
{
	// check input, update simulation, render etc.
}


void GameExit(void)
{
	
}
