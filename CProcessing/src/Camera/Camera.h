#pragma once
#include <cprocessing.h>
#include "../Screen/fader.h"

void CameraInit(CP_Vector *charPos);
void ScreenShake(float timer, float shakeVal);
void CameraUpdate(CP_Vector *charPos, Fader *fader);
void CameraExit(void);