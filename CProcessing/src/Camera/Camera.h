#pragma once
#include <cprocessing.h>
#include "../Screen/fader.h"

typedef enum CameraMode
{
	LOCK_PLAYER,
	PAN_PLAYER,
}CameraMode;

void CameraInit(CP_Vector *charPos, CameraMode cameraMode);
void ScreenShake(float timer, float shakeVal);
void CameraUpdate(CP_Vector *charPos, Fader *fader);
void CameraExit(void);

CP_Vector GetCameraPos();
CameraMode GetCameraMode(void);
void SetCameraMode(CameraMode cameraMode);