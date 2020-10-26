#include <cprocessing.h>

#define DEFAULT_FORCE 50.0f

CP_Color		arrowColor;

typedef struct
{
	CP_Vector	oldPosition,
				currentPosition,
				newPosition,
				dir;

	float		width,
				chargeTimer,
				chargeScale;

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

void CreateArrow(Arrow* arrow);
void CalculateNewPosition(Arrow* arrow);
void ArrowInMotion(Arrow* arrow);
void ArrowRecall(Arrow* arrow, CP_Vector playerPos);