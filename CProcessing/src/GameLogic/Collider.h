#pragma once
#include <cprocessing.h>
#include <stdbool.h>

typedef enum COL_SHAPE
{
	COL_CIRCLE,			//CIRCLE
	COL_RECT			//RECT

}COL_SHAPE;

typedef struct 
{
	CP_Vector position;

	float width,			//USE FOR RECT COLLIDER
		  height,			//USE FOR RECT COLLIDER

		  radius;			//USE FOR CIRCLE COLLIDER

	COL_SHAPE shapeType;	//COLLIDER SHAPE

}Collider;
float COL_Dist(Collider hitBox1, Collider hitBox2);
bool COL_IsColliding(Collider hitBox1, Collider hitBox2);
