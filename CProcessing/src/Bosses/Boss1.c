#include <cprocessing.h>
#include "Boss.h"
#include "../Player/player.h"

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