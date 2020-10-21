#include <cprocessing.h>
#include "Boss.h"

void BossPositioning(Boss currentboss) //function to set position of boss(es)
{
	//temporary
	currentboss.Position = CP_Vector_Set((float)CP_System_GetWindowWidth() / 2, (float)CP_System_GetWindowHeight() / 2);
}

void BossDraw(Boss currentboss) //function to draw boss(es)
{
	CP_Color BossColor = CP_Color_Create(0, 0, 255, 255);
	CP_Settings_Fill(BossColor);
	CP_Graphics_DrawCircle(currentboss.Position.x, currentboss.Position.y, currentboss.Size);
}