#pragma once
#include <cprocessing.h>
#include <stdbool.h>

typedef enum COL_SHAPE
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

bool COL_IsColliding(Collider hitBox1, Collider hitBox2);
