#include "../GameLogic/BlobInput.h"
#include "Camera.h"

static CP_Vector currentPosition, centerOffset;
float centerX;
float centerY;

static CP_Matrix scaleMatrix, rotationMatrix, translationMatrix;

void CameraInit(CP_Vector *charPos)
{
	centerX = CP_System_GetWindowWidth() / 2.0f;
	centerY = CP_System_GetWindowHeight() / 2.0f;
	centerOffset = CP_Vector_Set(centerX, centerY);
	currentPosition = CP_Vector_Set(charPos->x - centerX, charPos->y - centerY);
	translationMatrix = CP_Matrix_Translate(currentPosition);
}

void CameraUpdate(CP_Vector* charPos)
{
	if (GetBlobInputDown(BLOB_UP) || GetBlobInputDown(BLOB_DOWN) || GetBlobInputDown(BLOB_LEFT) || GetBlobInputDown(BLOB_RIGHT))
	{
		currentPosition = CP_Vector_Set(-(charPos->x - centerX), -(charPos->y - centerY));
		translationMatrix = CP_Matrix_Translate(currentPosition);
	}

	CP_Settings_ApplyMatrix(translationMatrix);
}

void CameraExit(void)
{

}