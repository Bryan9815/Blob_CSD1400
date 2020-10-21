#include <cprocessing.h>
#include "ScreenManager.h"
#include "src_mainmenu.h"

CP_Color bgColor;

void MainMenuInit(void)
{
	bgColor = CP_Color_Create(0, 255, 0, 255);
}

void MainMenuUpdate(void)
{
	CP_Settings_Background(bgColor);
}

void MainMenuExit(void)
{

}