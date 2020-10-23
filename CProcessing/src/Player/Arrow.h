#include <cprocessing.h>

#define DEFAULT_FORCE 50.0f

CP_Color		arrowColor;

typedef struct
{
	CP_Vector	position,
				newPosition,
				dir;

	float		width,
				forceTimer,
				force;
	int			canShoot;
	int			hasArrow;

} Arrow;

void ArrowRelease(Arrow* arrow);
void CreateArrow(Arrow* arrow);