#include <cprocessing.h>
#include "Boss.h"
#include "../Player/player.h"
#include "../GameLogic/Collider.h"

void BossInit(Boss *currentboss, int health, float size) //function to set variables of boss(es)
{
	currentboss->Hitbox.shapeType = COL_CIRCLE;
	currentboss->Hitbox.position = currentboss->Position = CP_Vector_Set(100.f,100.f); //temp(?)
	currentboss->Health = health;
	currentboss->Hitbox.radius = currentboss->Radius = size;
	currentboss->Speed = 300.0f; //to be balanced
	currentboss->State = IDLE;
}

void BossDraw(Boss currentboss) //function to draw boss(es)
{
	CP_Color BossColor = CP_Color_Create(0, 255, 255, 255);
	CP_Settings_Fill(BossColor);
	CP_Graphics_DrawCircle(currentboss.Position.x, currentboss.Position.y, (currentboss.Radius*2)); //replace with image once finalised
}

void BossMovement(Boss* currentboss, Player player) //boss slowly moves toward player
{
	if ((int)CP_System_GetMillis() % 1000 >= 700) //boss moves for 0.3s every 1s (to be balanced)
	{
		CP_Vector MoveDir = CP_Vector_Subtract(player.position, currentboss->Position);
		CP_Vector DirVector = CP_Vector_Normalize(MoveDir); //normalise for direction vector
		float distance = currentboss->Speed * CP_System_GetDt();
		if (COL_Dist(currentboss->Hitbox, player.hitBox) >= (currentboss->Radius + player.radius + distance)) //boss destination does not overlap with player
		{
			CP_Vector Movement = CP_Vector_Scale(DirVector, distance); //scale direction vector with speed over dt
			currentboss->Hitbox.position = currentboss->Position = CP_Vector_Add(Movement, currentboss->Position); //update position
		}
		else
		{
			distance = COL_Dist(currentboss->Hitbox, player.hitBox) - (currentboss->Radius + player.radius); //find distance from player
			CP_Vector Movement = CP_Vector_Scale(DirVector, distance); //scale direction vector with remaining distance
			currentboss->Hitbox.position = currentboss->Position = CP_Vector_Add(Movement, currentboss->Position); //update position
		}
		CP_Vector UpDir = CP_Vector_Set(0.f, 1.f);
		
		if (player.position.x < currentboss->Position.x)
			currentboss->Rotation = CP_Vector_Angle(UpDir, DirVector); //clockwise rotation of boss from upward dir
		else
			currentboss->Rotation = 360.f - CP_Vector_Angle(UpDir, DirVector); //counterclockwise rotation
	}
}