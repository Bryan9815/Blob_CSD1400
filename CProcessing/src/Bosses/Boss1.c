#include <cprocessing.h>
#include "Boss.h"
#include "../Player/player.h"
#include "Boss1.h"

float BossRange = 350.f;

void Shield1Draw(Boss armorboss) //draws shield for boss 1
{
	CP_Settings_ImageMode(CP_POSITION_CENTER); //draw from center of boss
	CP_Image_DrawAdvanced(shield, armorboss.Position.x, armorboss.Position.y, 270.f, 270.f, 255, armorboss.Rotation);
}

void AttackNear(Boss* armorboss) //attacks a radius around boss
{
	static int AttackTimer = 0;
	if (AttackTimer <= (2 * CP_System_GetFrameRate())) //warning for 2 sec before attack
	{
		NearAttack = WARNING;
		AttackTimer++;
	}
	else if (AttackTimer >= (2 * CP_System_GetFrameRate()) && AttackTimer <= (3 * CP_System_GetFrameRate())) // attack after 2 sec, animation 1 sec
	{
		//hitbox code is here
		NearAttack = ATTACK;
		AttackTimer++;
	}
	else //attack finished
	{
		NearAttack = NOT_ATTACK;
		AttackTimer = 0; //reset timer after attack
		armorboss->State = IDLE; //change back to idle state
	}
}

void AttackNearDraw(Boss* armorboss)
{
	if (NearAttack == WARNING)
	{
		CP_Color WarningColor = CP_Color_Create(255, 0, 0, 125);
		CP_Settings_Fill(WarningColor);
		CP_Graphics_DrawCircle(armorboss->Position.x, armorboss->Position.y, BossRange);
	}
	else if (NearAttack == ATTACK)
	{
		CP_Color AttackColor = CP_Color_Create(0, 0, 0, 255);
		CP_Settings_Fill(AttackColor);
		CP_Graphics_DrawCircle(armorboss->Position.x, armorboss->Position.y, BossRange);
	}
}


void AttackCharge(Player player, Boss* armorboss) //boss charges at player
{
	//timing and balance later
	CP_Vector TargetPos = player.position; //get player's position (implement only getting it ONCE)
	CP_Vector ChargeDir = CP_Vector_Subtract(TargetPos, armorboss->Position); //vector to player
	static int AttackTimer = 0;
	if (AttackTimer <= (2 * CP_System_GetFrameRate()))
	{
		FarAttack = WARNING;
		AttackTimer++;
	}
	else
	{
		FarAttack = ATTACK;
		CP_Vector DirVector = CP_Vector_Normalize(ChargeDir); //normalise for direction vector
		CP_Vector ChargeAttack = CP_Vector_Scale(DirVector, (CP_System_GetDt() * 2.0f * armorboss->Speed)); //boss moves at 2.0x(?) speed to that point
		armorboss->Position = CP_Vector_Add(armorboss->Position, ChargeAttack); //update boss position

		CP_Vector UpDir = CP_Vector_Set(0.f, 1.f);
		if (player.position.x < armorboss->Position.x)
			armorboss->Rotation = CP_Vector_Angle(UpDir, DirVector); //clockwise rotation of boss from upward dir
		else
			armorboss->Rotation = 360.f - CP_Vector_Angle(UpDir, DirVector); //counterclockwise rotation
		//armorboss.State = STUNNED; //stunned if collide with wall
		//armorboss.State = IDLE; //revert to idle if not
	}
}

void AttackFarDraw(Boss* armorboss, Player player)
{
	if (FarAttack == WARNING)
	{
		CP_Vector RightDir = CP_Vector_Set(1.f, 0.f);
		CP_Vector ChargeDir = CP_Vector_Subtract(player.position, armorboss->Position); //vector to player
		float width = CP_Vector_Distance(player.position, armorboss->Position);
		float rotation;
		if (player.position.y > armorboss->Position.y)
			rotation = CP_Vector_Angle(RightDir, ChargeDir); //clockwise rotation of boss from rightward dir
		else
			rotation = 360.f - CP_Vector_Angle(RightDir, ChargeDir); //counterclockwise rotation
		CP_Color WarningColor = CP_Color_Create(255, 0, 0, 125);
		CP_Settings_Fill(WarningColor);
		CP_Settings_RectMode(CP_POSITION_CORNER);
		CP_Graphics_DrawRectAdvanced(armorboss->Position.x, (armorboss->Position.y - 50.f), width, 100.f, rotation, 0.f);
	}
}

void StunTimer(Boss currentboss)
{
	static float Stuntime = 0;
	Stuntime++;
	if (Stuntime >= (3 * CP_System_GetFrameRate())) //stunned for 3 sec
	{
		currentboss.State = IDLE; //revert to idle after
		Stuntime = 0;
	}
}

void B1_StateChange(Player player, Boss* currentboss) //this determines WHEN the boss does its actions
{
	static float StateTimer = 0;
	float PlayerDist = CP_Vector_Distance(player.position, currentboss->Position);

	//-Battle starts in idle -> After 6 sec attack once -> Go back to idle -> Stop once defeated
	if (currentboss->State == IDLE); //timer should only go up when in idle
		StateTimer++;
	if (currentboss->Health == 0) //defeat should come first to stop all other functions
	{
		currentboss->State = DEFEAT;
		StateTimer = 0;
	}
	else if (StateTimer >= (6 * CP_System_GetFrameRate()) && PlayerDist <= BossRange) //if player is within distance after 6 sec
	{
		currentboss->State = ATTACK_NEAR;
		StateTimer = 0;
	}
	else if (StateTimer >= (6 * CP_System_GetFrameRate()) && PlayerDist > BossRange) //if player is beyond distance after 6 sec
	{
		currentboss->State = ATTACK_FAR;
		StateTimer = 0;
	}
}

void BossAction(Player player) //determines the boss actions, only one should be active at any time
{
	CP_Color errortext = CP_Color_Create(255, 0, 0, 255); //only used for error/bug check, REMOVE BEFORE FINAL
	char errormessage[] = "ERROR"; //only used for error/bug check, REMOVE BEFORE FINAL
	switch (ArmorSlime.State) 
	{
	case IDLE:
		BossMovement(&ArmorSlime, player); //boss should only be walking in idle
		break;
	case ATTACK_NEAR:
		AttackNear(&ArmorSlime); //boss does close range attack
		break;
	case ATTACK_FAR:
		AttackCharge(player, &ArmorSlime); //boss charge
		break;
	case STUNNED:
		StunTimer(ArmorSlime);
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

void Boss1Battle(Player player)
{
	B1_StateChange(player, &ArmorSlime);
	BossAction(player);
}