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
				forceTimer,
				forceScale;

} Arrow;

typedef enum
{
	WITHPLAYER,
	MOTION,
	MOTIONLESS
} ArrowState;

ArrowState  playerArrowState;

void ArrowRelease(Arrow* arrow);
void CreateArrow(Arrow* arrow);
void ArrowPhysics(Arrow* arrow);