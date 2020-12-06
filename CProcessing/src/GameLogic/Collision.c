#include "Collision.h"
#include "../Audio/AudioManager.h"
#include <math.h>
#include <stdio.h>
bool Col_PointRect(float x, float y, Collider rect) 
{
	return 
		(x >= rect.position.x - rect.width / 2 &&           // right of the left edge AND
		x <= rect.position.x + rect.width / 2 &&			// left of the right edge AND
		y >= rect.position.y - rect.height / 2 &&           // below the top AND
		y <= rect.position.y + rect.height / 2)				// above the bottom
		? true : false;
}

float Min(float f1, float f2) 
{
	return (f1 > f2) ? f2 : f1;
}

float Max(float f1, float f2) 
{
	return (f1 > f2) ? f1 : f2;
}

bool GridCollisionCheck(Body* entity)
{
	
	bool Colliding = false;
	for (int i = 0; i < GetLevelWidth(); i++)
	{
		for (int j = 0; j < GetLevelHeight(); j++)
		{
			Collider wallCol = level[i][j].collider;
			Collider entityCol = entity->hitbox;

			entityCol.shapeType = COL_RECT;					//Im not gonna do math now so just casting entity hitbox to rects for collision
			entityCol.width = entity->hitbox.radius * 2;
			entityCol.height = entity->hitbox.radius * 2;
			entityCol.position.x += entity->velocity.x;
			
			//Player can be replaced with any reference a struct with a collider and stores its position there instead, pass entity refer to INTOBJ.AS


			//@REDO
			//TOUCH FLOOR
			if (	(level[i][j].isCollidable)																																&&
					(Col_PointRect(entity->hitbox.position.x, entity->hitbox.position.y + entity->hitbox.radius + entity->velocity.y, wallCol)								||
					Col_PointRect(entity->hitbox.position.x + entity->hitbox.radius - 1 , entity->hitbox.position.y + entity->hitbox.radius + entity->velocity.y, wallCol)	||		//Point Collision
					Col_PointRect(entity->hitbox.position.x - entity->hitbox.radius + 1 , entity->hitbox.position.y + entity->hitbox.radius + entity->velocity.y, wallCol))	&&
					(entity->hitbox.position.y + entity->hitbox.radius) <= wallCol.position.y + wallCol.height / 2															&&		//Constrain
					entity->velocity.y > 0)																																			//Player is moving down
			{
				entity->velocity.y = (wallCol.position.y - wallCol.height / 2) - (entity->hitbox.position.y + entity->hitbox.radius);

				Colliding = true;
			}

			//TOUCH WALL			 @TODO ADD MORE MATHS SO BAD RIGHT NOW
			if (	(level[i][j].isCollidable)																		&&
					COL_IsColliding(entityCol, wallCol)																&&		//Shape Collision
					wallCol.position.x + wallCol.width / 2 >= entity->hitbox.position.x + entity->hitbox.radius		&&		//Constrain
					entity->velocity.x > 0)																					//Player is moving left
			{
				entity->velocity.x = (wallCol.position.x - wallCol.width / 2) - (entity->hitbox.position.x + entity->hitbox.radius);
				Colliding = true;
			}

			if (	(level[i][j].isCollidable)																		&&
					COL_IsColliding(entityCol, wallCol)																&&		//Shape Collision
					wallCol.position.x - wallCol.width / 2 <= entity->hitbox.position.x - entity->hitbox.radius		&&		//Constrain
					entity->velocity.x < 0)																					//Player is moving right
			{
				entity->velocity.x = (wallCol.position.x + wallCol.width / 2) - (entity->hitbox.position.x - entity->hitbox.radius);
				Colliding = true;
			}

			//TOUCH CEILING
			if (	(level[i][j].isCollidable)																																&&
					(Col_PointRect(entity->hitbox.position.x, entity->hitbox.position.y - entity->hitbox.radius + entity->velocity.y, wallCol)								||
					Col_PointRect(entity->hitbox.position.x + entity->hitbox.radius - 1, entity->hitbox.position.y - entity->hitbox.radius + entity->velocity.y, wallCol)	||		//Point Collision
					Col_PointRect(entity->hitbox.position.x - entity->hitbox.radius + 1, entity->hitbox.position.y - entity->hitbox.radius + entity->velocity.y, wallCol))	&&
					(entity->hitbox.position.y - entity->hitbox.radius) >= wallCol.position.y - wallCol.height / 2																&&		//Constrain
					entity->velocity.y < 0)																																			//Player is moving up
			{
				entity->velocity.y = (wallCol.position.y + wallCol.height / 2) - (entity->hitbox.position.y - entity->hitbox.radius);
				Colliding = true;
			}

		}

	}
	return Colliding;
}

CP_Vector ArrowReflection(Body* entity, CP_Vector n)
{
	float dotproduct = CP_Vector_DotProduct(entity->velocity, n);
	//printf("%f\n",dotproduct);
	CP_Vector r = CP_Vector_Subtract(entity->velocity, CP_Vector_Scale(n, 2 * dotproduct));
	/*printf("Velocity: (%.2f, %.2f)\n", entity->velocity.x, entity->velocity.y);
	printf("Reflection: (%.2f, %.2f)\n", r.x, r.y);*/
	return r;
}

//bool checkSide(CP_Vector c1, CP_Vector c2, CP_Vector center)
//{
//	return ((c2.x - c1.x) * (center.y - c1.y) - (c2.y - c1.y) * (center.x - c1.x)) >= 0;
//}
//
////Buggy with corners
//CP_Vector Circle_Intersect_Rect(Collider circle, Collider rect)
//{
//	CP_Vector v1, v2, v3, v4; //rect vertices
//	v1 = CP_Vector_Set(rect.position.x - rect.width / 2 + 1, rect.position.y - rect.height / 2 + 1); //Top left
//	v2 = CP_Vector_Set(rect.position.x + rect.width / 2 + 1, rect.position.y - rect.height / 2 + 1); //Top Right
//	v3 = CP_Vector_Set(rect.position.x + rect.width / 2 + 1, rect.position.y + rect.height / 2 + 1);  //Bottom Right
//	v4 = CP_Vector_Set(rect.position.x - rect.width / 2 + 1, rect.position.y + rect.height / 2 + 1);  //Bottom left
//
//	CP_Vector n = CP_Vector_Set(0.0f, 0.0f);
//
//	bool isAboveV1V3 = checkSide(v3, v1, circle.position);
//	bool isAboveV2V4 = checkSide(v2, v4, circle.position);
//
//
//
//	if (isAboveV1V3)
//	{
//		if (isAboveV2V4)
//		{
//			//Top Edge Intersect
//			printf("Top Edge\n");
//			n = CP_Vector_Set(0.0f, -1.0f);
//			
//		}
//		else
//		{
//			printf("Right Edge\n");
//			n = CP_Vector_Set(1.0f, 0.0f);
//		}
//	}
//	else
//	{
//		if (isAboveV2V4)
//		{
//			//Left Edge Intersect
//			printf("Left Edge\n");
//			n = CP_Vector_Set(-1.0f, 0.0f);
//		}
//		else
//		{
//			printf("Bottom Edge\n");
//			n = CP_Vector_Set(0.0f, 1.0f);
//		}
//	}
//	return n;
//}

CP_Vector Get_CircleRectCOL_Side(Collider circle, Collider rect, CP_Vector v, CP_Vector startPos)
{
	CP_Vector v1, v2, v3, v4, n; //rect vertices
	n = CP_Vector_Set(0.0f, 0.0f);
	v1 = CP_Vector_Set(rect.position.x - rect.width / 2 + 1, rect.position.y - rect.height / 2 + 1); //Top left
	v2 = CP_Vector_Set(rect.position.x + rect.width / 2 + 1, rect.position.y - rect.height / 2 + 1); //Top Right
	v3 = CP_Vector_Set(rect.position.x + rect.width / 2 + 1, rect.position.y + rect.height / 2 + 1);  //Bottom Right
	v4 = CP_Vector_Set(rect.position.x - rect.width / 2 + 1, rect.position.y + rect.height / 2 + 1);  //Bottom left
	
	float topAngle = CP_Vector_Angle(CP_Vector_Subtract(v1, rect.position), CP_Vector_Set(0.0f, -1.0f));
	float rightAngle = CP_Vector_Angle(CP_Vector_Subtract(v2, rect.position), CP_Vector_Set(1.0f, 0.0f));
	float bottomAngle = CP_Vector_Angle(CP_Vector_Subtract(v3, rect.position), CP_Vector_Set(0.0f, 1.0f));
	float leftAngle = CP_Vector_Angle(CP_Vector_Subtract(v4, rect.position), CP_Vector_Set(-1.0f, 0.0f));

	//CP_Vector offset = CP_Vector_Subtract(circle.position, rect.position);
	CP_Vector offset = CP_Vector_Subtract(startPos, rect.position);
	float topAngleA = CP_Vector_Angle(offset, CP_Vector_Set(0.0f, -1.0f));
	float rightAngleA = CP_Vector_Angle(offset, CP_Vector_Set(1.0f, 0.0f));
	float bottomAngleA = CP_Vector_Angle(offset, CP_Vector_Set(0.0f, 1.0f));
	float leftAngleA = CP_Vector_Angle(offset, CP_Vector_Set(-1.0f, 0.0f));

	if (topAngleA < topAngle)
	{
		//Top Edge Intersect
		printf("Top Edge\n");
		n = CP_Vector_Set(0.0f, -1.0f);

		//if (v.y > 0)
		//{
		//	//Reflect off top
		//}
		//else if (v.y < 0)
		//{
		//	//Could be Left, Right, or Bottom
		//	
		//	//Reflect off Bottom
		//}
	}
	else if (rightAngleA < rightAngle)
	{
		//Closet to Right
		printf("Right Edge\n");
		n = CP_Vector_Set(1.0f, 0.0f);
	}
	else if (bottomAngleA < bottomAngle)
	{
		printf("Bottom Edge\n");
		n = CP_Vector_Set(0.0f, 1.0f);
		////Closet to Bottom
		//if (v.y < 0)
		//{
		//	//Reflect off Bottom
		//}
		//else if (v.y > 0)
		//{
		//	//Reflect off Bottom
		//}
	}
	else if (leftAngleA < leftAngle)
	{
		//Left Edge Intersect
		printf("Left Edge\n");
		n = CP_Vector_Set(-1.0f, 0.0f);
	}
	return n;
}

//Shamelessly stolen from Jia Rong, thanks btw
bool ArrowCollision(Body* entity, CP_Vector startPos)
{
	bool Colliding = false;
	for (int i = 0; i < GetLevelWidth(); i++)
	{
		for (int j = 0; j < GetLevelHeight(); j++)
		{
			Collider wallCol = level[i][j].collider;
			Collider entityCol = entity->hitbox;

			CP_Vector offset = CP_Vector_Negate(CP_Vector_Normalize(entity->velocity));

			//Fuck my life
			if (COL_IsColliding(entityCol, wallCol) && (level[i][j].gridType == GE_WALL || level[i][j].gridType == GE_SWITCH || level[i][j].gridType == GE_DOOR || level[i][j].gridType == GE_PILLAR))
			{
				while (COL_IsColliding(entity->hitbox, wallCol))
				{
					entity->hitbox.position = CP_Vector_Add(entity->hitbox.position, offset);
				}

				CP_Vector n = CP_Vector_Set(0.0f, 0.0f);
				CP_Vector r = entity->velocity;

				n = Get_CircleRectCOL_Side(entityCol, wallCol, entity->velocity, startPos);
				r = ArrowReflection(entity, n);
				while (COL_IsColliding(entity->hitbox, wallCol))
				{
					printf("Offset\n");
					entity->hitbox.position = CP_Vector_Add(entity->hitbox.position, offset);
				}

				entity->velocity = r;

				entity->hitbox.position = CP_Vector_Add(entity->hitbox.position, CP_Vector_Scale(entity->velocity, 20));
				Colliding = true;

				if (level[i][j].gridType == GE_PILLAR && level[i][j].isActive == false)
				{
					level[i][j].hp = 5;
					level[i][j].isActive = true;
				}
			}
		}
	}
	return Colliding;
}


bool PlayerEntityCollision(Body* player, Body* entity)
{
	bool colliding = false;

	if (COL_IsColliding(player->hitbox, entity->hitbox))
	{
		CP_Vector differences = CP_Vector_Subtract(player->hitbox.position, entity->hitbox.position);
		float mag = CP_Vector_Length(differences); //magnitude of diffvector
		float resMag = player->hitbox.radius + entity->hitbox.radius; //magnitude of resultant vector
		CP_Vector resultantVector = CP_Vector_Scale(differences, (resMag-mag)/mag );
		player->velocity = CP_Vector_Add(player->velocity, resultantVector);
		colliding = true;
	}

	return colliding;
}

//bool PlayerMultiCollision(Body *player, Body* entity, GridUnit* _level)