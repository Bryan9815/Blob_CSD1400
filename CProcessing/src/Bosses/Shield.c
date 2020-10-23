#pragma once
#include <cprocessing.h>
#include "Boss.h"

void Shield1Draw(Boss armorboss, CP_Image shield)
{
	CP_Settings_ImageMode(CP_POSITION_CENTER);
	CP_Image_Draw(shield,armorboss.Position.x, armorboss.Position.y, 120.f, 120.f, 255);
}