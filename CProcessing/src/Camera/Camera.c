//---------------------------------------------------------
// file:	Camera.c
// author:	[Teh Kai Hong Bryan]
// email:	[t.kaihongbryan@digipen.edu]
//
// brief:	Camera for moving the screen
//
// Copyright � 2020 DigiPen, All rights reserved.
//---------------------------------------------------------
#include <cprocessing.h>
#include "../GameLogic/BlobInput.h"
#include "Camera.h"
#include <stdio.h>
#include <math.h>

static CP_Vector currentPosition, cameraPos, cameraOffset, cameraVelocity;
float centerX;
float centerY;
float cameraOffsetDist;

static CP_Matrix scaleMatrix, rotationMatrix, translationMatrix;
float shakeTimer, shakeValue;
CameraMode camMode;

// Initializes Camera variables
void CameraInit(CP_Vector* targetPos, CameraMode cameraMode)
{
	centerX = CP_System_GetWindowWidth() / 2.0f;
	centerY = CP_System_GetWindowHeight() / 2.0f;
	currentPosition = CP_Vector_Set(-(targetPos->x - centerX), -(targetPos->y - centerY));
	cameraPos = currentPosition;
	cameraVelocity = CP_Vector_Set(1, 1);
	shakeTimer = 0;
	shakeValue = 15;
	camMode = cameraMode;
}

// Shakes the screen
void ScreenShake(float timer, float shakeVal)
{
	shakeTimer = timer;
	shakeValue = shakeVal;
}

// Update function
void CameraUpdate(CP_Vector* targetPos, Fader* fader)
{
	float dt = CP_System_GetDt();
	if (shakeTimer <= 0)
	{
		currentPosition = CP_Vector_Set(-(targetPos->x - centerX), -(targetPos->y - centerY));
		//if (CP_Input_KeyTriggered(KEY_R)) // Screen Shake test
		//	ScreenShake(0.5f, 150.0f);
	}
	else
	{
		currentPosition = CP_Vector_Set(-(targetPos->x - centerX + (CP_Random_RangeFloat(-shakeValue, shakeValue))), -(targetPos->y - centerY + (CP_Random_RangeFloat(-shakeValue, shakeValue))));
		shakeTimer -= dt;
	}

	switch (camMode)
	{
	case LOCK_PLAYER:
		translationMatrix = CP_Matrix_Translate(currentPosition);
		cameraPos = currentPosition;
		break;
	case PAN_PLAYER:
		cameraOffset = CP_Vector_Subtract(currentPosition, cameraPos);
		cameraOffsetDist = CP_Vector_Distance(currentPosition, cameraPos);

		cameraPos.x += roundf(cameraOffset.x * dt * 2);
		cameraPos.y += roundf(cameraOffset.y * dt * 2.5f);
		translationMatrix = CP_Matrix_Translate(cameraPos);
		break;
	default:
		break;
	}

	fader->fadePosX = -cameraPos.x;
	fader->fadePosY = -cameraPos.y;
	CP_Settings_ApplyMatrix(translationMatrix);
}

// Getter function that returns the camera's position
CP_Vector GetCameraPos()
{
	CP_Vector returnVec = CP_Vector_Set(roundf(-cameraPos.x), roundf(-cameraPos.y));
	return returnVec;
}

// Changes between Lock and Panning camera modes
void SetCameraMode(CameraMode cameraMode)
{
	camMode = cameraMode;
}

// Getter function that returns current camera mode
CameraMode GetCameraMode(void)
{
	return camMode;
}

// Exit function
void CameraExit(void)
{

}