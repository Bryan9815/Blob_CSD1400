//---------------------------------------------------------
// file:	Boss1.c
// author:	[Koh Le An Leonard]
// email:	[l.koh@digipen.edu]
//
// brief:	Functions for the first boss in the game
//
// Copyright � 2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#include <cprocessing.h>
#include <stdio.h>
#include "Boss.h"
#include "../Audio/AudioManager.h"
#include "Boss1.h"
#include "../GameLogic/Collider.h"
#include "../GameLogic/ScreenManager.h"

float BossRange = 200.f;
float NearAttackTimer;
float FarAttackTimer = 0.f;
float NearTimer = 0.f;
float FarTimer = 0.f;
float ChargeTimer = 0.f;
float AttackCount = 0.f;
float Stuntime = 0.f;

void Boss1Init(void) //initialises the first boss
{
	BossInit(&ArmorSlime, 3, 80.f, CP_Vector_Set(200.f,200.f));
	ArmorSlime.bosssprite = CP_Image_Load("././Assets/Boss1.png");
	NearAttack = FarAttack = NOT_ATTACK; //reset attack states
	FarAttackTimer = NearAttackTimer = NearTimer = FarTimer = ChargeTimer = AttackCount = Stuntime = 0.f; //reset timers
}

void AttackNear(Boss* armorboss, Player* player) //attacks a radius around boss
{
	//set hitbox for boss attack
	Attack.shapeType = COL_CIRCLE;
	Attack.position = armorboss->BossBody.hitbox.position;
	Attack.radius = BossRange;
	
	if (NearAttackTimer <= 0.5) //warning for 2 sec before attack
	{
		NearAttack = WARNING;
		if (SFXPlaying == false)
		{
			//CP_Sound_Play(warningSFX);
			SFXPlaying = true;
		}
		NearAttackTimer += CP_System_GetDt();
	}
	else if (NearAttackTimer >= 0.5 && NearAttackTimer <= 1.5) // attack after 2 sec, animation 1 sec
	{
		NearAttack = ATTACK;
		if (SFXPlaying == true)
		{
			//CP_Sound_Play(attackSFX);
			SFXPlaying = false;
		}
		if (COL_IsColliding(Attack, player->pBody.hitbox)) //check if player is hit by attack
		{
			player->health = 0;
		}
		NearAttackTimer += CP_System_GetDt();
	}
	else //attack finished
	{
		SFXPlaying = false;
		NearAttack = NOT_ATTACK;
		NearAttackTimer = 0; //reset timer after attack
		armorboss->State = IDLE; //change back to idle state
	}
}

void AttackNearDraw(Boss armorboss) //draws warning area for near attack
{
	if (NearAttack == WARNING)
	{
		CP_Color WarningColor = CP_Color_Create(255, 0, 0, 125);
		CP_Settings_Fill(WarningColor);
		CP_Graphics_DrawCircle(armorboss.BossBody.hitbox.position.x, armorboss.BossBody.hitbox.position.y, (BossRange*2));
		CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
		CP_Graphics_DrawCircle(armorboss.BossBody.hitbox.position.x, armorboss.BossBody.hitbox.position.y, (NearAttackTimer * BossRange * 4));
	}
	else if (NearAttack == ATTACK)
	{
		CP_Color AttackColor = CP_Color_Create(0, 0, 0, 125);
		CP_Settings_Fill(AttackColor);
		CP_Graphics_DrawCircle(armorboss.BossBody.hitbox.position.x, armorboss.BossBody.hitbox.position.y, (BossRange * 2));
	}
}

void AttackCharge(Player *player, Boss* armorboss, GridUnit *grid) //boss charges at player
{
	//timing and balance later
	Attack.shapeType = COL_CIRCLE;
	Attack.position = armorboss->BossBody.hitbox.position;
	Attack.radius = armorboss->BossBody.hitbox.radius;

	if (FarAttackTimer <= 0.5) //warning for 2 sec
	{
		FarAttack = WARNING;
		if (SFXPlaying == false)
		{
			//CP_Sound_Play(warningSFX);
			SFXPlaying = true;
		}
		FarAttackTimer += CP_System_GetDt();
	}
	else if (FarAttackTimer > 0.5 && FarAttackTimer <= 1.5) //charging for 2 sec
	{
		FarAttack = ATTACK;
		CP_Vector DirVector = CP_Vector_Normalize(ChargeDir); //normalise for direction vector
		armorboss->BossBody.velocity = CP_Vector_Scale(DirVector, (CP_System_GetDt() * 600.f)); //boss moves at 2.0x(?) speed to that point
		armorboss->BossBody.hitbox.position = CP_Vector_Add(armorboss->BossBody.hitbox.position, armorboss->BossBody.velocity); //update boss position
		FarAttackTimer += CP_System_GetDt();

		if (COL_IsColliding(Attack, player->pBody.hitbox)) //if boss runs into player
		{
			player->health = 0;
		}
		if (GridCollisionCheck(&(armorboss->BossBody)))
		{
			ScreenShake(0.5f, 500);
			//CP_Sound_Play(SlamSFX);
			armorboss->State = STUNNED;
			FarAttackTimer = 0;
		}
	}
	else
	{
		SFXPlaying = false;
		FarAttack = NOT_ATTACK;
		armorboss->State = IDLE;
		FarAttackTimer = 0; //after 4 sec, not hit wall stop attack
	}
}

void AttackFarDraw(Boss armorboss) //draws warning area for boss charge attack
{
	if (FarAttack == WARNING)
	{
		CP_Vector RightDir = CP_Vector_Set(1.f, 0.f);
		CP_Color WarningColor = CP_Color_Create(255, 0, 0, 125);
		CP_Settings_Fill(WarningColor);
		CP_Settings_RectMode(CP_POSITION_CORNER);
		float width = 600.f * CP_Vector_Length(CP_Vector_Normalize(ChargeDir));
		float rotation;
		//find clockwise rotation
		if (ChargeTarget.y >= armorboss.BossBody.hitbox.position.y)
			rotation = CP_Vector_Angle(RightDir, ChargeDir); //clockwise rotation of boss from rightward dir
		else
			rotation = 360 - CP_Vector_Angle(RightDir, ChargeDir); //find the larger angle if > 180 degrees

		//draw rectangle, adjust so it draws from the centre of the short side
		
		if (rotation <= 120 && rotation >= 60)
		{
			CP_Graphics_DrawRectAdvanced((armorboss.BossBody.hitbox.position.x + armorboss.BossBody.hitbox.radius),
										  armorboss.BossBody.hitbox.position.y, width, 
										 (armorboss.BossBody.hitbox.radius * 2), rotation, 0.f);
			CP_Settings_Fill(CP_Color_Create(255,0,0,255));
			CP_Graphics_DrawRectAdvanced((armorboss.BossBody.hitbox.position.x + armorboss.BossBody.hitbox.radius),
										  armorboss.BossBody.hitbox.position.y, (width * FarAttackTimer * 2),
										 (armorboss.BossBody.hitbox.radius * 2), rotation, 0.f);
		}
		else if (rotation <= 300 && rotation >= 240)
		{
			CP_Graphics_DrawRectAdvanced((armorboss.BossBody.hitbox.position.x - armorboss.BossBody.hitbox.radius),
										  armorboss.BossBody.hitbox.position.y, width, 
										 (armorboss.BossBody.hitbox.radius * 2), rotation, 0.f);
			CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
			CP_Graphics_DrawRectAdvanced((armorboss.BossBody.hitbox.position.x - armorboss.BossBody.hitbox.radius),
										  armorboss.BossBody.hitbox.position.y, (width * FarAttackTimer * 2),
										 (armorboss.BossBody.hitbox.radius * 2), rotation, 0.f);
		}
		else if (ChargeTarget.x > armorboss.BossBody.hitbox.position.x)
		{
			CP_Graphics_DrawRectAdvanced(armorboss.BossBody.hitbox.position.x, (armorboss.BossBody.hitbox.position.y - armorboss.BossBody.hitbox.radius),
										 width, (armorboss.BossBody.hitbox.radius * 2), rotation, 0.f);
			CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
			CP_Graphics_DrawRectAdvanced(armorboss.BossBody.hitbox.position.x, (armorboss.BossBody.hitbox.position.y - armorboss.BossBody.hitbox.radius),
										(width * FarAttackTimer * 2), (armorboss.BossBody.hitbox.radius * 2), rotation, 0.f);
		}
		else
		{
			CP_Graphics_DrawRectAdvanced(armorboss.BossBody.hitbox.position.x, (armorboss.BossBody.hitbox.position.y + armorboss.BossBody.hitbox.radius),
										 width, (armorboss.BossBody.hitbox.radius * 2), rotation, 0.f);
			CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
			CP_Graphics_DrawRectAdvanced(armorboss.BossBody.hitbox.position.x, (armorboss.BossBody.hitbox.position.y + armorboss.BossBody.hitbox.radius),
										(width * FarAttackTimer * 2), (armorboss.BossBody.hitbox.radius * 2), rotation, 0.f);

		}
	}
}

void StunTimer(Boss* currentboss) //function for boss getting stunned after hitting wall
{
	
	Stuntime+= CP_System_GetDt();
	if (Stuntime >= 3) //stunned for 3 sec
	{
		currentboss->State = IDLE; //revert to idle after
		Stuntime = 0;
	}
}

void B1_StateChange(Player player, Boss* currentboss) //function determines when the boss does its actions
{
	
	float PlayerDist = CP_Vector_Distance(player.pBody.hitbox.position, currentboss->BossBody.hitbox.position);

	//-Battle starts in idle -> if near for 2 sec do near attack -> if near 3x or far for 2 sec do charge
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

void Boss1Action(void) //determines the boss actions, only one should be active at any time
{
	switch (ArmorSlime.State) 
	{
	case IDLE:
		BossMovement(&ArmorSlime, newPlayer, level[0]); //boss should only be walking in idle
		BossRotation(&ArmorSlime, newPlayer.pBody.hitbox.position); //rotation of boss
		break;
	case ATTACK_NEAR:
		AttackNear(&ArmorSlime, &newPlayer); //boss does close range attack
		BossRotation(&ArmorSlime, newPlayer.pBody.hitbox.position);
		break;
	case ATTACK_FAR:
		AttackCharge(&newPlayer, &ArmorSlime, level[0]); //boss charge attack
		break;
	case STUNNED: 
		StunTimer(&ArmorSlime); //boss should stop moving, allowing player to shoot
		break; 
	case DEFEAT:
		SetGameOver(true); //proceed to next stage
		break; 
	default: //In case it ends up being something else
		ArmorSlime.State = IDLE;
		break;
	}
}

void Boss1Battle(void) //function for the entire boss battle
{
	if (ArmorSlime.Health == 0) //defeat should come first to stop all other functions
	{
		ArmorSlime.State = DEFEAT;
	}

	B1_StateChange(newPlayer, &ArmorSlime); //determines boss state (other than defeat)
	Boss1Action(); //determine boss action
}

void Boss1Draw(Boss armorboss) //function to draw boss and attacks
{
	AttackFarDraw(armorboss);
	AttackNearDraw(armorboss);
	BossDraw(armorboss);
	BossHealthDraw(armorboss);
}

void Boss1Exit(void) ///function for freeing boss image
{
	CP_Image_Free(&(ArmorSlime.bosssprite));
}