#include <cprocessing.h>
#include <stdio.h>
#include "../Audio/AudioManager.h"
#include "Boss2.h"
#include "Projectile.h"
#include "../GameLogic/Collider.h"
#include "../GameLogic/ScreenManager.h"

static float BossRange = 500.f;
static float NearAttackTimer;
static float FarAttackTimer = 0.f;
static float NearTimer = 0.f;
static float FarTimer = 0.f;
static float ChargeTimer = 0.f;
static float AttackCount = 0.f;
static float Stuntime = 0.f;
static BossState2 bossState;
Projectile projectileList[3];

void Boss2Init(void)
{
	BossInit(&Boss2, 5, 60.0f, CP_Vector_Set(200.f,200.f));
	Boss2.bosssprite = CP_Image_Load("././Assets/Boss1.png");
	bossState = IDLE_B2;
	FarAttackTimer = NearAttackTimer = NearTimer = FarTimer = ChargeTimer = AttackCount = Stuntime = 0.f; //reset timers
}

void Boss2Movement(Player player, GridUnit* grid) //boss slowly moves toward player
{
	
}

void B2_StateChange(Player player) //this determines WHEN the boss does its actions
{
	float dt = CP_System_GetDt();
	//float PlayerDist = CP_Vector_Distance(player.pBody.hitbox.position, Boss2.BossBody.hitbox.position);
	switch (bossState)
	{

	case IDLE_B2:
		FarAttackTimer += dt;
		if (FarAttackTimer >= 5.f)
		{
			bossState = SHOOT_1;
			FarAttackTimer = 0.f;
		}
		break;
	default:
		break;
	}
}

void Boss2Draw()
{
	// Draw Boss
	CP_Image_DrawAdvanced(Boss2.bosssprite, Boss2.BossBody.hitbox.position.x, Boss2.BossBody.hitbox.position.y, (Boss2.BossBody.hitbox.radius * 2), (Boss2.BossBody.hitbox.radius * 2), Boss2.bossAlpha, Boss2.BossBody.rotation);

	for (int i = 0; i < 3; i++)
	{
		if(projectileList[i].active)
			DrawProjectile(&projectileList[i]);
	}

	BossHealthDraw(Boss2);
}

void Boss2Action(void) //determines the boss actions, only one should be active at any time
{
	switch (bossState)
	{
	case IDLE_B2:
		BossRotation(&Boss2, newPlayer.pBody.hitbox.position); //rotation of boss
		break;
	case SHOOT_1:
		for (int i = 0; i < 3; i++)
		{
			CP_Vector dirVec = CP_Vector_Set(0, 1);
			CP_Matrix rotation = CP_Matrix_Rotate(Boss2.BossBody.rotation - 10 + (i * 10));
			dirVec = CP_Vector_MatrixMultiply(rotation, dirVec);
			projectileList[i] = CreateProjectile(Boss2.BossBody.hitbox.position, dirVec, 5.f);
		}
		FarTimer = 5.0f;
		bossState = IDLE_B2;
		break;
	case DEFEAT_B2:
		SetGameOver(true); //proceed to next stage
		break;
	default: //In case it ends up being something else
		break;
	}
}

void Boss2Battle(void)
{
	if (Boss2.Health == 0) //defeat should come first to stop all other functions
	{
		bossState = DEFEAT_B2;
	}
	if (FarTimer > 0)
	{
		for (int i = 0; i < 3; i++)
		{
			UpdateProjectile(&projectileList[i]);
		}
	}
	B2_StateChange(newPlayer); //determines boss state (other than defeat)
	Boss2Action(); //determine boss action
}

void Boss2Exit(void)
{
	CP_Image_Free(&(ArmorSlime.bosssprite));
}