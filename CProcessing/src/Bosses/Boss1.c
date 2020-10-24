#include <cprocessing.h>
#include "Boss.h"
#include "../Player/player.h"
#include "Boss1.h"

void Shield1Draw(Boss armorboss, CP_Image shield) //draws shield for boss 1
{
	CP_Settings_ImageMode(CP_POSITION_CENTER); //draw from center of boss
	CP_Image_DrawAdvanced(shield, armorboss.Position.x, armorboss.Position.y, 120.f, 120.f, 255, armorboss.Rotation);
}

/*!UNTESTED!*/
void AttackNear(Player player, Boss* armorboss) //attacks a radius around boss
{
	static int timer = 0;
	CP_Graphics_DrawCircle(armorboss->Position.x, armorboss->Position.y, 200.f); //warning before attack
	timer++;
	if ((timer / (2 * CP_System_GetFrameRate())) == 1) // after 2 sec, attack
	{
		//hitbox code is here
		timer = 0;
	}
}

void AttackCharge(Player player, Boss* armorboss) //boss charges at player
{
	//timing and balance later
	CP_Vector TargetPos;
	TargetPos = player.position; //get player's position (implement only getting it ONCE)
	CP_Vector ChargeDir = CP_Vector_Subtract(TargetPos, armorboss->Position); //vector to player
	CP_Vector DirVector = CP_Vector_Normalize(ChargeDir); //normalise for direction vector
	CP_Vector ChargeAttack = CP_Vector_Scale(DirVector, (CP_System_GetDt() * 2.5f * armorboss->Speed)); //boss moves at 2.5x(?) speed to that point
	armorboss->Position = CP_Vector_Add(armorboss->Position, ChargeAttack); //update boss position

	CP_Vector UpDir = CP_Vector_Set(0.f, 1.f);
	armorboss->Rotation = CP_Vector_Angle(UpDir, DirVector); //rotation of boss from upward dir
}

void BossStateChanger(enum BossState Boss1) //this determines WHEN the boss does its actions
{
	//if statements to be here
}

void Boss1Battle(Player player, CP_Image shield)
{
	CP_Color errortext = CP_Color_Create(255, 0, 0, 255); //only used for error/bug check, REMOVE BEFORE FINAL
	char errormessage[] = "ERROR"; //only used for error/bug check, REMOVE BEFORE FINAL
	Shield1Draw(ArmorSlime, shield);
	BossDraw(ArmorSlime); //note that boss is drawn after to be on top of shield
	//BossStateChanger(); remove comment when finished
	switch (Boss1_State) //determines the boss actions, only one should be active at any time
	{
		case IDLE:
			BossMovement(&ArmorSlime); //boss should only be walking in idle
			break;
		case ATTACK_NEAR:
			AttackNear(player, &ArmorSlime); //boss does close range attack
			break;
		case ATTACK_FAR:
			AttackCharge(player, &ArmorSlime); //boss charge
			break;
		case STUNNED:
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