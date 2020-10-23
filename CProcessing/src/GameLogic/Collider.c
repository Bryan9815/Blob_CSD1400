#include <stdbool.h>
#include <cprocessing.h>
#include "Collider.h"


float COL_Dist(Collider hitBox1, Collider hitBox2) //wtf
{
	return CP_Math_Distance(hitBox1.position.x, hitBox1.position.y, hitBox2.position.x, hitBox2.position.y);
	
}

bool COL_IsColliding (Collider hitBox1, Collider hitBox2) //wtf
{
	bool col = false;

	if (hitBox1.shapeType == COL_CIRCLE) 
	{
		if (hitBox2.shapeType == COL_CIRCLE) //Both Circle
		{
			col = (COL_Dist(hitBox1, hitBox2) < hitBox1.radius + hitBox2.radius) ? true : false;
		}
		else if (hitBox2.shapeType == COL_RECT)	//Collider 1 Circle & Collider 2 Rect
		{

		}
	}
	else if (hitBox1.shapeType == COL_RECT)
	{
		if (hitBox2.shapeType == COL_CIRCLE) //Collider 1 Rect & Collider 2 Circle
		{


		}
		else if (hitBox2.shapeType == COL_RECT) //Both Rect
		{

		}
	}

	return col;

}