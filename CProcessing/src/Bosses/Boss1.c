#include <cprocessing.h>
#include "Boss.h"
#include "../Player/player.h"

void Shield1Draw(Boss armorboss, CP_Image shield) //draws shield for boss 1
{
	CP_Settings_ImageMode(CP_POSITION_CENTER); //draw from center of boss
	CP_Image_DrawAdvanced(shield, armorboss.Position.x, armorboss.Position.y, 120.f, 120.f, 255, armorboss.Rotation);
}
																/*!UNTESTED!*/
void AttackNear(void)
{
	
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
}