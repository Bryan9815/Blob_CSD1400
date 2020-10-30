#include "Collider.h"


float COL_Dist(Collider hitBox1, Collider hitBox2) //Distance between two colliders
{
	return CP_Math_Distance(hitBox1.position.x, hitBox1.position.y, hitBox2.position.x, hitBox2.position.y);
	
}

bool Circle_RectCollision(Collider circle, Collider rect) //Check for collision Circle/Rect
{
	bool col = false;

	float	nearestX = circle.position.x,
			nearestY = circle.position.y;

	if (circle.position.x < rect.position.x - rect.width / 2)					nearestX = rect.position.x - rect.width / 2;							//Left Edge
	else if (circle.position.x > rect.position.x + rect.width / 2)  nearestX = rect.position.x + rect.width / 2;			//Right Edge
	if (circle.position.y < rect.position.y - rect.height / 2)					nearestY = rect.position.y - rect.height / 2;							//Top Edge
	else if (circle.position.y > rect.position.y + rect.height / 2) nearestY = rect.position.y + rect.height / 2;			//Bottom

	//Get Distance from closest Edge
	/*float distX = circle.position.x - nearestX,
		  distY = circle.position.y - nearestY;*/

	return col = (CP_Math_Distance(circle.position.x, circle.position.y, nearestX, nearestY) < circle.radius) ? true : false;	//Distance less than radii
}

bool COL_IsColliding (Collider hitBox1, Collider hitBox2) //Collsion checking between 2 Collider
{
	bool col = false;

	if (hitBox1.shapeType == COL_CIRCLE) 
	{
		if (hitBox2.shapeType == COL_CIRCLE) //Both Circle
		{
			col = (COL_Dist(hitBox1, hitBox2) < hitBox1.radius + hitBox2.radius) ? true : false;		//Distance of centre points less than combined radii of circles
		}
		else if (hitBox2.shapeType == COL_RECT)	//Collider 1 Circle & Collider 2 Rect
		{
			col = Circle_RectCollision(hitBox1, hitBox2);
		}
	}
	else if (hitBox1.shapeType == COL_RECT)
	{
		if (hitBox2.shapeType == COL_CIRCLE) //Collider 1 Rect & Collider 2 Circle
		{
			col = Circle_RectCollision(hitBox2, hitBox1);

		}
		else if (hitBox2.shapeType == COL_RECT) //Both Rect
		{
			col = (hitBox1.position.x - hitBox1.width / 2 < hitBox2.position.x + hitBox2.width / 2 &&
				hitBox1.position.x + hitBox1.width / 2 > hitBox2.position.x - hitBox2.width / 2 &&
				hitBox1.position.y - hitBox1.height / 2 < hitBox2.position.y + hitBox2.height / 2 &&
				hitBox1.position.y + hitBox1.height / 2 > hitBox2.position.y - hitBox2.height / 2)
				? true : false;
		}
	}

	return col;

}