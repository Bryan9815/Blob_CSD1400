#include <cprocessing.h>
#include <stdio.h>
#include "../Audio/AudioManager.h"
#include "Boss2.h"
#include "../GameLogic/Collider.h"
#include "../GameLogic/ScreenManager.h"

static float BossRange = 200.f;
static float NearAttackTimer;
static float FarAttackTimer = 0.f;
static float NearTimer = 0.f;
static float FarTimer = 0.f;
static float ChargeTimer = 0.f;
static float AttackCount = 0.f;
static float Stuntime = 0.f;

void Boss2Init(void)
{
	BossInit(&Boss2, 5, 150.f, CP_Vector_Set(200.f,200.f));
	Boss2.bosssprite = CP_Image_Load("././Assets/Boss1.png");
	FarAttackTimer = NearAttackTimer = NearTimer = FarTimer = ChargeTimer = AttackCount = Stuntime = 0.f; //reset timers
}

void B2_StateChange(Player player, Boss* currentboss) //this determines WHEN the boss does its actions
{
	//float PlayerDist = CP_Vector_Distance(player.pBody.hitbox.position, currentboss->BossBody.hitbox.position);

	////-Battle starts in idle -> if near for 2 sec do near attack -> if near 3x or far for 2 sec do charge
	//if (currentboss->State == IDLE)
	//{
	//	if (PlayerDist <= BossRange && AttackCount < 3)
	//		NearTimer += CP_System_GetDt();
	//	else if (PlayerDist > BossRange && AttackCount < 3) //if player is beyond distance after 6 sec
	//		FarTimer += CP_System_GetDt();
	//	
	//	if (FarTimer >= 2 || AttackCount >= 3)
	//		ChargeTimer += CP_System_GetDt();
	//}
	//
	//if (ChargeTimer >= 0.5)
	//{
	//	ChargeTarget = player.pBody.hitbox.position; //gets player position once
	//	ChargeDir = CP_Vector_Subtract(ChargeTarget, currentboss->BossBody.hitbox.position); //vector to destination
	//	currentboss->State = ATTACK_FAR; //change to charge attack state
	//	ChargeTimer = FarTimer = AttackCount = 0;
	//}
	//if (NearTimer > 0.5)
	//{
	//	currentboss->State = ATTACK_NEAR; //change to close range attack state
	//	FarTimer = NearTimer = 0;
	//	AttackCount++;
	//}
}

void Boss2Draw(Boss boss)
{
	BossDraw(boss);
	BossHealthDraw(boss);
}

void Boss2Action(void) //determines the boss actions, only one should be active at any time
{
	switch (Boss2.State)
	{
	//case IDLE:
	//	BossMovement(&ArmorSlime, newPlayer, level[0]); //boss should only be walking in idle
	//	BossRotation(&ArmorSlime, newPlayer.pBody.hitbox.position); //rotation of boss
	//	break;
	//case ATTACK_NEAR:
	//	//BossMovement(&ArmorSlime, player, grid); //boss should only be walking in idle
	//	AttackNear(&ArmorSlime, &newPlayer); //boss does close range attack
	//	BossRotation(&ArmorSlime, newPlayer.pBody.hitbox.position);
	//	break;
	//case ATTACK_FAR:
	//	AttackCharge(&newPlayer, &ArmorSlime, level[0]); //boss charge attack
	//	break;
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

void Boss2Battle(void)
{
	if (Boss2.Health == 0) //defeat should come first to stop all other functions
	{
		Boss2.State = DEFEAT;
	}

	//B2_StateChange(newPlayer, &ArmorSlime); //determines boss state (other than defeat)
	Boss2Action(); //determine boss action
}

void Boss2Exit(void)
{
	CP_Image_Free(&(ArmorSlime.bosssprite));
}