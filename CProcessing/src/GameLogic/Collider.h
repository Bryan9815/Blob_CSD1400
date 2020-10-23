#include <cprocessing.h>

typedef enum //wtf
{
	COL_CIRCLE,
	COL_RECT

}COL_SHAPE;

typedef struct //wtf
{
	CP_Vector position;

	float width,
		  height,
		  radius;

	COL_SHAPE shapeType;

}Collider;
