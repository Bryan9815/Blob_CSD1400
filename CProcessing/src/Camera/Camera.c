#include <cprocessing.h>
#include "../GameLogic/BlobInput.h"
#include "Camera.h"

static CP_Vector currentPosition, centerOffset;
float centerX;
float centerY;

static CP_Matrix scaleMatrix, rotationMatrix, translationMatrix;
float shakeTimer, shakeValue;

void CameraInit(CP_Vector *charPos)
{
	centerX = CP_System_GetWindowWidth() / 2.0f;
	centerY = CP_System_GetWindowHeight() / 2.0f;
	centerOffset = CP_Vector_Set(centerX, centerY);
	currentPosition = CP_Vector_Set(charPos->x - centerX, charPos->y - centerY);
	translationMatrix = CP_Matrix_Translate(currentPosition);
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
		translationMatrix = CP_Matrix_Translate(currentPosition);
		/*if (CP_Input_KeyTriggered(KEY_R)) // Screen Shake test
			ScreenShake(0.5f, 15.0f);*/
	}
	else
	{
		currentPosition = CP_Vector_Set(-(charPos->x - centerX + (CP_Random_RangeFloat(-shakeValue, shakeValue))), -(charPos->y - centerY + (CP_Random_RangeFloat(-shakeValue, shakeValue))));
		translationMatrix = CP_Matrix_Translate(currentPosition);
		shakeTimer -= dt;
	}

	fader->fadePosX = -currentPosition.x;
	fader->fadePosY = -currentPosition.y;
	CP_Settings_ApplyMatrix(translationMatrix);
}

void CameraExit(void)
{

}