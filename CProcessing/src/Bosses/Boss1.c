#include <cprocessing.h>
#include "Boss.h"
//#include "../Player/player.h"
#include "Boss1.h"
//#include "../GameLogic/grid.h"
//#include "../Screen/scr_level_1.h"
#include "../GameLogic/Collider.h"
//#include "../GameLogic/Collision.h"

float BossRange = 200.f;

void Shield1Draw(Boss armorboss) //draws shield for boss 1
{
	CP_Settings_ImageMode(CP_POSITION_CENTER); //draw from center of boss
	CP_Image_DrawAdvanced(shield, armorboss.BossBody.hitbox.position.x, armorboss.BossBody.hitbox.position.y, 200.f, 200.f, 30, armorboss.BossBody.rotation);
}

void AttackNear(Boss* armorboss, Player* player) //attacks a radius around boss
{
	static float AttackTimer = 0;
	//set hitbox for boss attack
	Attack.shapeType = COL_CIRCLE;
	Attack.position = armorboss->BossBody.hitbox.position;
	Attack.radius = BossRange;
	
	if (AttackTimer <= 0.5) //warning for 2 sec before attack
	{
		NearAttack = WARNING;
		AttackTimer += CP_System_GetDt();
	}
	else if (AttackTimer >= 0.5 && AttackTimer <= 1.5) // attack after 2 sec, animation 1 sec
	{
		NearAttack = ATTACK;
		if (COL_IsColliding(Attack, player->pBody.hitbox)) //check if player is hit by attack
			player->health--;
		AttackTimer += CP_System_GetDt();
	}
	else //attack finished
	{
		NearAttack = NOT_ATTACK;
		AttackTimer = 0; //reset timer after attack
		armorboss->State = IDLE; //change back to idle state
	}
}

void AttackNearDraw(Boss armorboss)
{
	if (NearAttack == WARNING)
	{
		CP_Color WarningColor = CP_Color_Create(255, 0, 0, 125);
		CP_Settings_Fill(WarningColor);
		CP_Graphics_DrawCircle(armorboss.BossBody.hitbox.position.x, armorboss.BossBody.hitbox.position.y, (BossRange*2));
	}
	else if (NearAttack == ATTACK)
	{
		CP_Color AttackColor = CP_Color_Create(0, 0, 0, 255);
		CP_Settings_Fill(AttackColor);
		CP_Graphics_DrawCircle(armorboss.BossBody.hitbox.position.x, armorboss.BossBody.hitbox.position.y, (BossRange * 2));
	}
}

void AttackCharge(Player *player, Boss* armorboss, GridUnit *grid) //boss charges at player
{
	//timing and balance later
	static float AttackTimer = 0;
	if (AttackTimer <= 0.5) //warning for 2 sec
	{
		FarAttack = WARNING;
		AttackTimer += CP_System_GetDt();
	}
	else if (AttackTimer > 0.5 && AttackTimer <= 2.5) //charging for 2 sec
	{
		FarAttack = ATTACK;
		CP_Vector DirVector = CP_Vector_Normalize(ChargeDir); //normalise for direction vector
		armorboss->BossBody.velocity = CP_Vector_Scale(DirVector, (CP_System_GetDt() * 600.f)); //boss moves at 2.0x(?) speed to that point
		armorboss->BossBody.hitbox.position = CP_Vector_Add(armorboss->BossBody.hitbox.position, armorboss->BossBody.velocity); //update boss position

		if (COL_IsColliding(armorboss->BossBody.hitbox, player->pBody.hitbox)) //if boss runs into player
			player->health--;
		if (CollisionCheck(&(armorboss->BossBody), grid))
		{
			armorboss->State = STUNNED;
			AttackTimer = 0;
		}
	}
	else
	{
		FarAttack = NOT_ATTACK;
		armorboss->State = IDLE;
		AttackTimer = 0; //after 4 sec, not hit wall stop attack
	}
}

void AttackFarDraw(Boss armorboss)
{
	if (FarAttack == WARNING)
	{
		CP_Vector RightDir = CP_Vector_Set(1.f, 0.f);
		CP_Color WarningColor = CP_Color_Create(255, 0, 0, 125);
		CP_Settings_Fill(WarningColor);
		CP_Settings_RectMode(CP_POSITION_CORNER);
		float width = 1000.f * CP_Vector_Length(CP_Vector_Normalize(ChargeDir));
		float rotation;
		//find clockwise rotation
		if (ChargeTarget.y >= armorboss.BossBody.hitbox.position.y)
			rotation = CP_Vector_Angle(RightDir, ChargeDir); //clockwise rotation of boss from rightward dir
		else
			rotation = 360 - CP_Vector_Angle(RightDir, ChargeDir); //find the larger angle if > 180 degrees
		
		//draw rectangle, adjust so it draws from the centre of the short side
		if (ChargeTarget.x >= armorboss.BossBody.hitbox.position.x) 
			CP_Graphics_DrawRectAdvanced(armorboss.BossBody.hitbox.position.x, (armorboss.BossBody.hitbox.position.y - 50.f), width, 100.f, rotation, 0.f);
		else
			CP_Graphics_DrawRectAdvanced(armorboss.BossBody.hitbox.position.x, (armorboss.BossBody.hitbox.position.y + 50.f), width, 100.f, rotation, 0.f);
	}
}

void StunTimer(Boss* currentboss)
{
	static float Stuntime = 0;
	Stuntime+= CP_System_GetDt();
	if (Stuntime >= 3) //stunned for 3 sec
	{
		currentboss->State = IDLE; //revert to idle after
		Stuntime = 0;
	}
}

void B1_StateChange(Player player, Boss* currentboss) //this determines WHEN the boss does its actions
{
	static float NearTimer = 0;
	static float FarTimer = 0;
	static float ChargeTimer = 0;
	static float AttackCount = 0;
	float PlayerDist = CP_Vector_Distance(player.pBody.hitbox.position, currentboss->BossBody.hitbox.position);

	//-Battle starts in idle -> After 6 sec attack once -> Go back to idle -> Stop once defeated
	if (currentboss->State == IDLE)
	{
		if (PlayerDist <= BossRange && AttackCount < 3)
			NearTimer += CP_System_GetDt();
		else if (PlayerDist > BossRange && AttackCount < 3) //if player is beyond distance after 6 sec
			FarTimer += CP_System_GetDt();
		
		if (FarTimer >= 2 || AttackCount >= 3)
			ChargeTimer += CP_System_GetDt();
	}
	
	if (ChargeTimer >= 0.5)
	{
		ChargeTarget = player.pBody.hitbox.position; //gets player position once
		ChargeDir = CP_Vector_Subtract(ChargeTarget, currentboss->BossBody.hitbox.position); //vector to destination
		currentboss->State = ATTACK_FAR; //change to charge attack state
		ChargeTimer = FarTimer = AttackCount = 0;
	}
	if (NearTimer > 0.5)
	{
		currentboss->State = ATTACK_NEAR; //change to close range attack state
		FarTimer = NearTimer = 0;
		AttackCount++;
	}
	
}

void BossAction(Player player, GridUnit* grid) //determines the boss actions, only one should be active at any time
{
	CP_Color errortext = CP_Color_Create(255, 0, 0, 255); //only used for error/bug check, REMOVE BEFORE FINAL
	char errormessage[] = "ERROR"; //only used for error/bug check, REMOVE BEFORE FINAL
	switch (ArmorSlime.State) 
	{
	case IDLE:
		BossMovement(&ArmorSlime, player, grid); //boss should only be walking in idle
		BossRotation(&ArmorSlime, newPlayer.pBody.hitbox.position);
		break;
	case ATTACK_NEAR:
		//BossMovement(&ArmorSlime, player, grid); //boss should only be walking in idle
		AttackNear(&ArmorSlime, &newPlayer); //boss does close range attack
		BossRotation(&ArmorSlime, newPlayer.pBody.hitbox.position);
		break;
	case ATTACK_FAR:
		AttackCharge(&player, &ArmorSlime, level[0]); //boss charge
		break;
	case STUNNED:
		StunTimer(&ArmorSlime);
		break; //boss should stop moving, allowing player to shoot
	case DEFEAT:
		break; //should proceed to next stage (main menu/win screen for prototype)
	default: //this is mainly to check for bugs/errors
		CP_Settings_Fill(errortext);
		CP_Settings_TextSize(100.f);
		CP_Font_DrawText(errormessage, (float)(CP_System_GetWindowWidth() / 2), (float)(CP_System_GetDisplayHeight() / 2));
		break;
	}
}

void Boss1Battle(Player player, GridUnit* grid)
{
	if (ArmorSlime.Health == 0) //defeat should come first to stop all other functions
	{
		ArmorSlime.State = DEFEAT;
	}
	else
	{
		B1_StateChange(player, &ArmorSlime);
		BossAction(player, grid);
	}
}

void Boss1Draw(Boss armorboss, Player player)
{
	AttackFarDraw(armorboss);
	AttackNearDraw(armorboss);
	Shield1Draw(armorboss);
	BossDraw(armorboss);
}