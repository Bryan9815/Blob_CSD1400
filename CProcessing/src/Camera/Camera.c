#include <cprocessing.h>
#include "../GameLogic/BlobInput.h"
#include "Camera.h"
#include <stdio.h>

static CP_Vector currentPosition, cameraPos, cameraOffset, cameraVelocity;
float centerX;
float centerY;
float cameraOffsetDist;

static CP_Matrix scaleMatrix, rotationMatrix, translationMatrix;
float shakeTimer, shakeValue;

void CameraInit(CP_Vector *charPos)
{
	centerX = CP_System_GetWindowWidth() / 2.0f;
	centerY = CP_System_GetWindowHeight() / 2.0f;
	currentPosition = CP_Vector_Set(charPos->x - centerX, charPos->y - centerY);
	cameraPos = CP_Vector_Set(charPos->x - centerX, charPos->y - centerY);
	translationMatrix = CP_Matrix_Translate(currentPosition);
	cameraVelocity = CP_Vector_Set(1, 1);
	shakeTimer = 0;
	shakeValue = 15;
}

void ScreenShake(float timer, float shakeVal)
{
	shakeTimer = timer;
	shakeValue = shakeVal;
}

void CameraUpdate(CP_Vector* charPos, Fader* fader)
{
	float dt = CP_System_GetDt();
	if (shakeTimer <= 0)
	{
		currentPosition = CP_Vector_Set(-(charPos->x - centerX), -(charPos->y - centerY));
		cameraOffset = CP_Vector_Subtract(currentPosition, cameraPos);
		cameraOffsetDist = CP_Vector_Distance(currentPosition, cameraPos);
		
		cameraPos.x += cameraOffset.x * dt * 2;
		cameraPos.y += cameraOffset.y * dt * 2.5f;
		translationMatrix = CP_Matrix_Translate(cameraPos);
		//if (CP_Input_KeyTriggered(KEY_R)) // Screen Shake test
		//	ScreenShake(0.5f, 150.0f);
	}
	else
	{
		currentPosition = CP_Vector_Set(-(charPos->x - centerX + (CP_Random_RangeFloat(-shakeValue, shakeValue))), -(charPos->y - centerY + (CP_Random_RangeFloat(-shakeValue, shakeValue))));
		cameraOffset = CP_Vector_Subtract(currentPosition, cameraPos);
		cameraOffsetDist = CP_Vector_Distance(currentPosition, cameraPos);

		cameraPos.x += cameraOffset.x * dt * 2;
		cameraPos.y += cameraOffset.y * dt * 2.5f;
		translationMatrix = CP_Matrix_Translate(cameraPos);
		shakeTimer -= dt;
	}

	fader->fadePosX = -cameraPos.x;
	fader->fadePosY = -cameraPos.y;
	CP_Settings_ApplyMatrix(translationMatrix);
}

void CameraExit(void)
{

}