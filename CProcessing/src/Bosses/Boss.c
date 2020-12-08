//---------------------------------------------------------
// file:	Boss.c
// author:	[Koh Le An Leonard]
// email:	[l.koh@digipen.edu]
//
// brief:	Functions that are used for all bosses in the game
//
// Copyright ? 2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#include <cprocessing.h>
#include "Boss.h"
#include "../Player/player.h"
#include "../GameLogic/Collision.h"
#include "../GameLogic/grid.h"
#include "../Screen/scr_level_1.h"
#include "../Audio/AudioManager.h"

float NoDamageTimer = 0.f;

void BossInit(Boss *currentboss, int health, float size, CP_Vector startPos) //function to set variables of boss(es)
{
	currentboss->BossBody.hitbox.shapeType = COL_CIRCLE;
	currentboss->BossBody.hitbox.position = startPos; //temp(?)
	currentboss->Health = health;
	currentboss->maxHealth = health;
	currentboss->BossBody.hitbox.radius = size;
	currentboss->BossBody.velocity = CP_Vector_Set(0.f,0.f); //to be balanced
	currentboss->BossBody.rotation = 0.0f;
	currentboss->State = IDLE;
	currentboss->bossAlpha = 255;
	NoDamageTimer = 0.f;
}
void BossDraw(Boss currentboss) //function to draw boss(es)
{
	CP_Image_DrawAdvanced(currentboss.bosssprite, 
						  currentboss.BossBody.hitbox.position.x, currentboss.BossBody.hitbox.position.y, 
						 (currentboss.BossBody.hitbox.radius * 2), (currentboss.BossBody.hitbox.radius * 2),
						  currentboss.bossAlpha, currentboss.BossBody.rotation);
}

void BossHealthDraw(Boss boss) //function to draw boss health bar
{
	CP_Settings_Fill(CP_Color_Create(50, 50, 50, 150));
	CP_Settings_RectMode(CP_POSITION_CORNER);
	CP_Graphics_DrawRect((boss.BossBody.hitbox.position.x - boss.BossBody.hitbox.radius), 
						 (boss.BossBody.hitbox.position.y - boss.BossBody.hitbox.radius - 10.f),
						 (boss.BossBody.hitbox.radius * 2), 10.f);
	CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
	CP_Graphics_DrawRect((boss.BossBody.hitbox.position.x - boss.BossBody.hitbox.radius + 1.f),
						 (boss.BossBody.hitbox.position.y - boss.BossBody.hitbox.radius - 9.f), 
						 (float)(boss.BossBody.hitbox.radius * 2 * boss.Health/boss.maxHealth), 8.f);
}

void BossMovement(Boss* currentboss, Player player, GridUnit* grid) //function for boss  to slowly moves toward player
{
	float distance;
	CP_Vector MoveDir = CP_Vector_Subtract(player.pBody.hitbox.position, currentboss->BossBody.hitbox.position);
	CP_Vector DirVector = CP_Vector_Normalize(MoveDir); //normalise for direction vector
	if ((int)CP_System_GetMillis() % 1000 <= 700) //boss moves for 0.3s every 1s (to be balanced)
		distance = 300.f * CP_System_GetDt();
	else
		distance = 600.f * CP_System_GetDt();
		
	if (COL_Dist(currentboss->BossBody.hitbox, player.pBody.hitbox) >= 
		(currentboss->BossBody.hitbox.radius + player.pBody.hitbox.radius + distance)) //boss destination does not overlap with player
	{
		currentboss->BossBody.velocity = CP_Vector_Scale(DirVector, distance); //scale direction vector with speed over dt
		GridCollisionCheck(&(currentboss->BossBody));
	}
	else
	{
		distance = COL_Dist(currentboss->BossBody.hitbox, player.pBody.hitbox) 
				- (currentboss->BossBody.hitbox.radius + player.pBody.hitbox.radius); //find distance from player
		currentboss->BossBody.velocity = CP_Vector_Scale(DirVector, distance); //scale direction vector with remaining distance
		GridCollisionCheck(&(currentboss->BossBody));
	}
	
	currentboss->BossBody.hitbox.position =  CP_Vector_Add(currentboss->BossBody.velocity, currentboss->BossBody.hitbox.position); //update position	
}

void BossRotation(Boss* currentboss, CP_Vector position) //function for boss to always face player
{
	//For rotation
	CP_Vector UpDir = CP_Vector_Set(0.f, 1.f);
	CP_Vector MoveDir = CP_Vector_Subtract(position, currentboss->BossBody.hitbox.position);

	if (position.x < currentboss->BossBody.hitbox.position.x)
		currentboss->BossBody.rotation = CP_Vector_Angle(UpDir, MoveDir); //clockwise rotation of boss from upward dir
	else
		currentboss->BossBody.rotation = 360.f - CP_Vector_Angle(UpDir, MoveDir); //find the larger angle if > 180 degrees
}


void BossDamage(bool* hit, Boss* boss) //function for boss invincibility between hits
{
	if (NoDamageTimer == 0.f)
	{
		if (*hit == true)
		{
			boss->Health--;
			*hit = false;
			CP_Sound_Play(damageSFX);
			NoDamageTimer += CP_System_GetDt();
			boss->bossAlpha = 100;
		}
	}
	else if (NoDamageTimer > 0.f && NoDamageTimer < 3.f)
	{
		//boss flicker every 0.25s to show invincibility
		if ((NoDamageTimer - (int)(NoDamageTimer)) < 0.25f || 
			((NoDamageTimer - (int)(NoDamageTimer)) < 0.75f) && (NoDamageTimer - (int)(NoDamageTimer)) > 0.5f)
			boss->bossAlpha = 100;
		else
			boss->bossAlpha = 255;

		NoDamageTimer += CP_System_GetDt();
	}
	else if (NoDamageTimer >= 3.f) //invincibilty over, reset
	{
		NoDamageTimer = 0.f;
		boss->bossAlpha = 255;
	}
}