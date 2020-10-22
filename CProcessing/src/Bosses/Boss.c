#pragma once
#include <cprocessing.h>
#include "Boss.h"
#include "../Player/player.h"

void CreateBoss(Boss *currentboss, int health, float size) //function to set variables of boss(es)
{
	currentboss->Position = CP_Vector_Set((float)CP_System_GetWindowWidth() / 2, (float)CP_System_GetWindowHeight() / 2); //temp(?)
	currentboss->Health = health;
	currentboss->Size = size;
	currentboss->Speed = 100.0f; //to be balanced
}

void BossDraw(Boss currentboss) //function to draw boss(es)
{
	CP_Color BossColor = CP_Color_Create(0, 255, 255, 255);
	CP_Settings_Fill(BossColor);
	CP_Graphics_DrawCircle(currentboss.Position.x, currentboss.Position.y, currentboss.Size); //replace with image once finalised
}

void BossMovement(Boss* currentboss/*, Player* player*/) //boss slowly moves toward player
{
	if ((int)CP_System_GetMillis() % 1000 >= 700) //boss moves for 0.3s every 1s (to be balanced)
	{
		CP_Vector testvector = CP_Vector_Set(0.f, 0.f); //temporary, remove once player is added
		CP_Vector MoveDir = CP_Vector_Subtract(testvector, currentboss->Position);
		//CP_Vector_Subtract(player->position, currentboss->Position); replace above with this for direction of boss to player
		CP_Vector DirVector = CP_Vector_Normalize(MoveDir); //normalise for direction vector
		CP_Vector Movement = CP_Vector_Scale(DirVector, (currentboss->Speed * CP_System_GetDt())); //scale direction vector with speed over dt
		currentboss->Position = CP_Vector_Add(Movement, currentboss->Position); //update position
	}
}