#include <cprocessing.h>
#include <stdio.h>
#include "../Audio/AudioManager.h"
#include "Boss2.h"
#include "Projectile.h"
#include "../GameLogic/Collider.h"
#include "../GameLogic/ScreenManager.h"
#include <math.h>

static float BossRange = 500.f;
static float NearAttackTimer;
static float FarAttackTimer = 0.f;
static float NearTimer = 0.f;
static float FarTimer = 0.f;
static float ChargeTimer = 0.f;
static float AttackCount = 0.f;
static float Stuntime = 0.f;
int counter = 0;
static BossState2 bossState;
AttackState shootState;
Projectile projectileList[50];
CP_Color WarningColor;

void Boss2Init(void)
{
	BossInit(&Boss2, 5, 60.0f, CP_Vector_Set(200.f,200.f));
	Boss2.bosssprite = CP_Image_Load("././Assets/Boss1.png");
	bossState = IDLE_B2;
	FarAttackTimer = NearAttackTimer = NearTimer = FarTimer = ChargeTimer = AttackCount = Stuntime = 0.f; //reset timers
	shootState = NOT_ATTACK;
	WarningColor = CP_Color_Create(0, 0, 0, 175);
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
		if (FarAttackTimer >= 2.f)
		{
			bossState = SHOOT_1;
			shootState = WARNING;
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

	for (int i = 0; i < 50; i++)
	{
		if(projectileList[i].active)
			DrawProjectile(&projectileList[i]);
	}

	CP_Settings_Fill(WarningColor);
	CP_Graphics_DrawCircle(Boss2.BossBody.hitbox.position.x, Boss2.BossBody.hitbox.position.y, (Boss2.BossBody.hitbox.radius/4));

	BossHealthDraw(Boss2);
}

void NewProjectile(CP_Vector pos, CP_Vector dir, float vel)
{
	for (int i = 0; i < 50; i++)
	{
		if (projectileList[i].active == false)
		{
			projectileList[i] = CreateProjectile(pos, dir, vel);
			break;
		}
	}
}

void Boss2Rotation(Boss* currentboss, CP_Vector position, float dt)
{
	//For rotation
	CP_Vector UpDir = CP_Vector_Set(0.f, 1.f);
	CP_Vector MoveDir = CP_Vector_Subtract(position, currentboss->BossBody.hitbox.position);

	float targetRotation, rotationOffset;

	if (position.x < currentboss->BossBody.hitbox.position.x)
		targetRotation = CP_Vector_Angle(UpDir, MoveDir); //clockwise rotation of boss from upward dir
	else
	{
		targetRotation = 360.f - CP_Vector_Angle(UpDir, MoveDir); //find the larger angle if > 180 degrees
		//currentboss->BossBody.rotation += 360;
	}

	rotationOffset = roundf(targetRotation - currentboss->BossBody.rotation);
	if (currentboss->BossBody.rotation != targetRotation)
	{
		if (currentboss->BossBody.rotation < 90 && targetRotation > 180)
			currentboss->BossBody.rotation -= (rotationOffset * dt);
		else if(currentboss->BossBody.rotation > 270 && targetRotation < 180)
			currentboss->BossBody.rotation -= (rotationOffset * dt);
		else
			currentboss->BossBody.rotation += (rotationOffset * dt);
	}
	if (currentboss->BossBody.rotation < 0)
		currentboss->BossBody.rotation += 360;
	if (currentboss->BossBody.rotation > 360)
		currentboss->BossBody.rotation -= 360;
}

void Boss2Action(void) //determines the boss actions, only one should be active at any time
{
	float dt = CP_System_GetDt();
	switch (bossState)
	{
	case IDLE_B2:
		Boss2Rotation(&Boss2, newPlayer.pBody.hitbox.position, dt); //rotation of boss
		break;
	case SHOOT_1:
		switch (shootState)
		{
		case NOT_ATTACK:
			break;
		case WARNING:
			FarTimer += dt;
			WarningColor = CP_Color_Create((int)(170 * FarTimer), 0, 0, (int)(170 * FarTimer));
			if (FarTimer > 1.5f)
			{
				FarTimer = 0;
				shootState = ATTACK;
			}
			break;
		case ATTACK:
			FarTimer += dt;
			if (FarTimer >= 0.25f)
			{
				for (int i = 0; i < 3; i++)
				{
					CP_Vector dirVec = CP_Vector_Set(0, 1);
					CP_Matrix rotationProj = CP_Matrix_Rotate(Boss2.BossBody.rotation - 10 + (i * 10));
					dirVec = CP_Vector_MatrixMultiply(rotationProj, dirVec);
					NewProjectile(Boss2.BossBody.hitbox.position, dirVec, 7.5f);
				}
				counter++;
				FarTimer = 0.0f;
			}
			if (counter == 3)
			{
				bossState = IDLE_B2;
				counter = 0;
				shootState = NOT_ATTACK;
				WarningColor = CP_Color_Create(0, 0, 0, 175);
			}
			break;
		default:
			break;
		}
		break;
	case SHOOT_2:
		switch (shootState)
		{
		case NOT_ATTACK:
			break;
		case WARNING:
			BossRotation(&Boss2, newPlayer.pBody.hitbox.position);
			FarTimer += dt;
			WarningColor = CP_Color_Create((int)(170 * FarTimer), 0, 0, (int)(170 * FarTimer));
			if (FarTimer > 1.5f)
			{
				FarTimer = 0;
				shootState = ATTACK;
			}
			break;
		case ATTACK:
			BossRotation(&Boss2, newPlayer.pBody.hitbox.position);
			FarTimer += dt;
			if (FarTimer >= 0.25f)
			{
				for (int i = 0; i < 10; i++)
				{
					CP_Vector dirVec = CP_Vector_Set(0, 1);
					CP_Matrix rotationProj = CP_Matrix_Rotate(Boss2.BossBody.rotation + (i * 36));
					dirVec = CP_Vector_MatrixMultiply(rotationProj, dirVec);
					NewProjectile(Boss2.BossBody.hitbox.position, dirVec, 7.5f);
				}
				counter++;
				FarTimer = 0.0f;
			}
			if (counter == 5)
			{
				bossState = IDLE_B2;
				counter = 0;
				shootState = NOT_ATTACK;
				WarningColor = CP_Color_Create(0, 0, 0, 175);
				// Set stun timer
			}
			break;
		default:
			BossRotation(&Boss2, newPlayer.pBody.hitbox.position);
			break;
		}
		break;
	case SHOOT_3:
		switch (shootState)
		{
		case NOT_ATTACK:
			break;
		case WARNING:
			BossRotation(&Boss2, newPlayer.pBody.hitbox.position);
			FarTimer += dt;
			WarningColor = CP_Color_Create((int)(170 * FarTimer), 0, 0, (int)(170 * FarTimer));
			if (FarTimer > 1.5f)
			{
				FarTimer = 0;
				shootState = ATTACK;
			}
			break;
		case ATTACK:
			BossRotation(&Boss2, newPlayer.pBody.hitbox.position);
			FarTimer += dt;
			if (FarTimer >= 0.25f)
			{
				for (int i = 0; i < 50; i++)
				{
					CP_Vector dirVec = CP_Vector_Set(0, 1);
					CP_Matrix rotationProj = CP_Matrix_Rotate(Boss2.BossBody.rotation + 45 + (i * (360 / 50)));
					dirVec = CP_Vector_MatrixMultiply(rotationProj, dirVec);
					NewProjectile(Boss2.BossBody.hitbox.position, dirVec, 7.5f);
				}
				counter++;
				FarTimer = 0.0f;
			}
			if (counter == 1)
			{
				bossState = IDLE_B2;
				counter = 0;
				shootState = NOT_ATTACK;
				WarningColor = CP_Color_Create(0, 0, 0, 175);
				// Set stun timer
			}
			break;
		default:
			BossRotation(&Boss2, newPlayer.pBody.hitbox.position);
			break;
		}
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
	B2_StateChange(newPlayer); //determines boss state (other than defeat)
	Boss2Action(); //determine boss action
	for (int i = 0; i < 50; i++)
	{
		if(projectileList[i].active == true)
			UpdateProjectile(&projectileList[i]);
	}
}

void Boss2Exit(void)
{
	for (int i = 0; i < 50; i++)
	{
		projectileList[i].active = false;
	}
	CP_Image_Free(&(ArmorSlime.bosssprite));
}