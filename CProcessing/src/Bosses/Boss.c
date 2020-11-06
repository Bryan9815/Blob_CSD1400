#include <cprocessing.h>
#include "Boss.h"
#include "../Player/player.h"
#include "../GameLogic/Collision.h"
#include "../GameLogic/grid.h"
#include "../Screen/scr_level_1.h"

CP_Image bosssprite;
void BossInit(Boss *currentboss, int health, float size) //function to set variables of boss(es)
{
	bosssprite = CP_Image_Load("././Assets/Boss1.png");
	currentboss->BossBody.hitbox.shapeType = COL_CIRCLE;
	currentboss->BossBody.hitbox.position = CP_Vector_Set(200.f,200.f); //temp(?)
	currentboss->Health = health;
	currentboss->BossBody.hitbox.radius = size;
	currentboss->BossBody.velocity = CP_Vector_Set(0.f,0.f); //to be balanced
	currentboss->BossBody.rotation = 0.0f;
	currentboss->State = IDLE;
}

void BossDraw(Boss currentboss) //function to draw boss(es)
{

	//CP_Color BossColor = CP_Color_Create(0, 255, 255, 60);
	//CP_Settings_Fill(BossColor);
	CP_Image_DrawAdvanced(bosssprite, currentboss.BossBody.hitbox.position.x, currentboss.BossBody.hitbox.position.y, (currentboss.BossBody.hitbox.radius * 2), (currentboss.BossBody.hitbox.radius * 2), 255, currentboss.BossBody.rotation);
	//CP_Graphics_DrawCircle(currentboss.BossBody.hitbox.position.x, currentboss.BossBody.hitbox.position.y, (currentboss.BossBody.hitbox.radius*2)); //replace with image once finalised
}

void BossMovement(Boss* currentboss, Player player, GridUnit* grid) //boss slowly moves toward player
{
	float distance;
	CP_Vector MoveDir = CP_Vector_Subtract(player.pBody.hitbox.position, currentboss->BossBody.hitbox.position);
	CP_Vector DirVector = CP_Vector_Normalize(MoveDir); //normalise for direction vector
	if ((int)CP_System_GetMillis() % 1000 <= 700) //boss moves for 0.3s every 1s (to be balanced)
		distance = 300.f * CP_System_GetDt();
	else
		distance = 600.f * CP_System_GetDt();
		
	if (COL_Dist(currentboss->BossBody.hitbox, player.pBody.hitbox) >= (currentboss->BossBody.hitbox.radius + player.pBody.hitbox.radius + distance)) //boss destination does not overlap with player
	{
		currentboss->BossBody.velocity = CP_Vector_Scale(DirVector, distance); //scale direction vector with speed over dt
		CollisionCheck(&(currentboss->BossBody), grid);
	}
	else
	{
		distance = COL_Dist(currentboss->BossBody.hitbox, player.pBody.hitbox) - (currentboss->BossBody.hitbox.radius + player.pBody.hitbox.radius); //find distance from player
		currentboss->BossBody.velocity = CP_Vector_Scale(DirVector, distance); //scale direction vector with remaining distance
		CollisionCheck(&(currentboss->BossBody), grid);
	}

	currentboss->BossBody.hitbox.position =  CP_Vector_Add(currentboss->BossBody.velocity, currentboss->BossBody.hitbox.position); //update position	
}

void BossRotation(Boss* currentboss, CP_Vector position)
{
	//For rotation
	CP_Vector UpDir = CP_Vector_Set(0.f, 1.f);
	CP_Vector MoveDir = CP_Vector_Subtract(position, currentboss->BossBody.hitbox.position);

	//if (position.x < currentboss->BossBody.hitbox.position.x)
	//	currentboss->Rotation = CP_Vector_Angle(UpDir, MoveDir); //clockwise rotation of boss from upward dir
	//else
	//	currentboss->Rotation = 360.f - CP_Vector_Angle(UpDir,MoveDir); //find the larger angle if > 180 degrees
	if (position.x < currentboss->BossBody.hitbox.position.x)
		currentboss->BossBody.rotation = CP_Vector_Angle(UpDir, MoveDir); //clockwise rotation of boss from upward dir
	else
		currentboss->BossBody.rotation = 360.f - CP_Vector_Angle(UpDir, MoveDir); //find the larger angle if > 180 degrees
}