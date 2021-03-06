﻿//---------------------------------------------------------
// file:	Camera.h
// author:	[Teh Kai Hong Bryan]
// email:	[t.kaihongbryan@digipen.edu]
//
// brief:	Header file for Camera.c
//
//
// Copyright � 2020 DigiPen, All rights reserved.
//---------------------------------------------------------
#pragma once
#include <cprocessing.h>
#include "../Screen/fader.h"

typedef enum CameraMode
{
	LOCK_PLAYER,
	PAN_PLAYER,
}CameraMode;

void CameraInit(CP_Vector* charPos, CameraMode cameraMode);
void ScreenShake(float timer, float shakeVal);
void CameraUpdate(CP_Vector* charPos, Fader* fader);
void CameraExit(void);

CP_Vector GetCameraPos();
CameraMode GetCameraMode(void);
void SetCameraMode(CameraMode cameraMode);