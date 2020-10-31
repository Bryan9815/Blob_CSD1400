#include <cprocessing.h>
#include "../GameLogic/Collision.h"

#define DEFAULT_FORCE 50.0f

CP_Color		arrowColor;

typedef struct
{
	CP_Vector	oldPosition,
				newPosition;

	float		chargeTimer,
				chargeScale;

	int			charging;
	Body		aBody;

} Arrow;

typedef enum
{
	RELEASE,
	RECALL,
	WITHPLAYER,
	MOTION,
	MOTIONLESS
} ArrowState;

ArrowState  playerArrowState;
float 	travelTimer, travelDistance, currentDistance; 

void CreateArrow(Arrow* arrow);
void CalculateNewPosition(Arrow* arrow, Body pbody);
void ArrowInMotion(Arrow* arrow);
void ArrowPlayerCollision(Arrow* arrow, Body pbody);