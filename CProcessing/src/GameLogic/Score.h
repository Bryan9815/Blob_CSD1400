#pragma once
#include <cprocessing.h>
#include "../Bosses/Boss.h"
#include "../Player/player.h"
#define BUFFERSIZE 15

float Score;
float Boss1Timer;

void StageTime(float *timer);
float CalculateScore(float time, bool win);
void DisplayScore(float scorePosX, float scorePosY, float time, float score);