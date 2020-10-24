#pragma once
#include <cprocessing.h>
#include "Boss.h"

//functions specifically for boss 1 here
enum BossState Boss1_State;

void Shield1Draw(Boss armorboss, CP_Image shield);
void AttackNear(Player player, Boss* armorboss);
void AttackCharge(Player player, Boss* armorboss);