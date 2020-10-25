#pragma once
#include <cprocessing.h>
#include "Boss.h"

//functions specifically for boss 1 here
CP_Image shield;

void Shield1Draw(Boss armorboss);
void AttackNear(Boss* armorboss);
void AttackCharge(Player player, Boss* armorboss);
void StunTimer(Boss currentboss);
void B1_StateChange(Player player, Boss* currentboss);
void Boss1Battle(Player player);