#include <cprocessing.h>
#include "../GameLogic/Collider.h"

#define DEFAULT_FORCE 50.0f

CP_Color		arrowColor;

typedef struct
{
	CP_Vector	oldPosition,
				currentPosition,
				newPosition,
				dir,
				normalizedDir;

	float		radius,
				chargeTimer,
				chargeScale;

	Collider	hitBox;

	int			charging;

} Arrow;

typedef enum
{
	RELEASE,
	WITHPLAYER,
	MOTION,
	MOTIONLESS
} ArrowState;

ArrowState  playerArrowState;
float 	travelTimer, travelDistance;

void CreateArrow(Arrow* arrow);
void CalculateNewPosition(Arrow* arrow);
void ArrowInMotion(Arrow* arrow);
void ArrowRecall(Arrow* arrow, CP_Vector playerPos);