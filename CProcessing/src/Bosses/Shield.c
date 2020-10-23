#pragma once
#include <cprocessing.h>
#include "Boss.h"

void Shield1Draw(Boss armorboss, CP_Image shield) //draws shield for boss 1
{
	CP_Settings_ImageMode(CP_POSITION_CENTER); //draw from center of boss
	CP_Image_DrawAdvanced(shield,armorboss.Position.x, armorboss.Position.y, 120.f, 120.f, 255, armorboss.Rotation);
}

//function for draw shield for boss 3 here if implemented