#pragma once
#include <cprocessing.h>
#include "../Screen/fader.h"

void CameraInit(CP_Vector *charPos);
void CameraUpdate(CP_Vector *charPos, Fader *fader);
void CameraExit(void);