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
	printf("%f\n",dotproduct);
	CP_Vector r = CP_Vector_Subtract(entity->velocity, CP_Vector_Scale(n, 2 * dotproduct));
	printf("Velocity: (%.2f, %.2f)\n", entity->velocity.x, entity->velocity.y);
	printf("Reflection: (%.2f, %.2f)\n", r.x, r.y);
	return r;
}

bool checkSide(CP_Vector c1, CP_Vector c2, CP_Vector center)
{
	return ((c2.x - c1.x) * (center.y - c1.y) - (c2.y - c1.y) * (center.x - c1.x)) >= 0;
}

//Buggy with corners
CP_Vector Circle_Intersect_Rect(Collider circle, Collider rect)
{
	CP_Vector v1, v2, v3, v4; //rect vertices
	v1 = CP_Vector_Set(rect.position.x - rect.width / 2 + 1, rect.position.y - rect.height / 2 + 1); //Top left
	v2 = CP_Vector_Set(rect.position.x + rect.width / 2 + 1, rect.position.y - rect.height / 2 + 1); //Top Right
	v3 = CP_Vector_Set(rect.position.x + rect.width / 2 + 1, rect.position.y + rect.height / 2 + 1);  //Bottom Right
	v4 = CP_Vector_Set(rect.position.x - rect.width / 2 + 1, rect.position.y + rect.height / 2 + 1);  //Bottom left

	CP_Vector n = CP_Vector_Set(0.0f, 0.0f);

	bool isAboveV1V3 = checkSide(v3, v1, circle.position);
	bool isAboveV2V4 = checkSide(v2, v4, circle.position);



	if (isAboveV1V3)
	{
		if (isAboveV2V4)
		{
			//Top Edge Intersect
			printf("Top Edge\n");
			
		}
		else
		{
			printf("Right Edge\n");
			n = CP_Vector_Set(1.0f, 0.0f);
		}
	}
	else
	{
		if (isAboveV2V4)
		{
			//Left Edge Intersect
			printf("Left Edge\n");
			n = CP_Vector_Set(-1.0f, 0.0f);
		}
		else
		{
			printf("Bottom Edge\n");
			n = CP_Vector_Set(0.0f, 1.0f);
		}
	}
	return n;
}


//Shamelessly stolen from Jia Rong, thanks btw
bool ArrowCollision(Body* entity)
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
			if (COL_IsColliding(entityCol, wallCol) && (level[i][j].gridType == GE_WALL || level[i][j].gridType == GE_SWITCH || level[i][j].gridType == GE_DOOR))
			{
				while (COL_IsColliding(entity->hitbox, wallCol))
				{
					entity->hitbox.position = CP_Vector_Add(entity->hitbox.position, offset);
				}
				//entity->hitbox.position = CP_Vector_Subtract(entity->hitbox.position, offset);
				//CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
				//CP_Graphics_DrawCircle(wallCol.position.x, wallCol.position.y, entityCol.radius * 2);
				CP_Vector n = CP_Vector_Set(0.0f, 0.0f);
				CP_Vector r = entity->velocity;

				//TOUCH FLOOR
				if ((level[i][j].isCollidable) &&
					(Col_PointRect(entity->hitbox.position.x, entity->hitbox.position.y + entity->hitbox.radius + entity->velocity.y, wallCol) ||
						Col_PointRect(entity->hitbox.position.x + entity->hitbox.radius - 1, entity->hitbox.position.y + entity->hitbox.radius + entity->velocity.y, wallCol) ||		//Point Collision
						Col_PointRect(entity->hitbox.position.x - entity->hitbox.radius + 1, entity->hitbox.position.y + entity->hitbox.radius + entity->velocity.y, wallCol)) &&
					(entity->hitbox.position.y + entity->hitbox.radius) <= wallCol.position.y + wallCol.height / 2 &&		//Constrain
					entity->velocity.y > 0)																																			//Arrow is moving down
				{
					printf("Touch Floor\n");
					n = CP_Vector_Set(0.0f, -1.0f);
				}

				//TOUCH CEILING
				else if ((level[i][j].isCollidable) &&
					(Col_PointRect(entity->hitbox.position.x, entity->hitbox.position.y - entity->hitbox.radius + entity->velocity.y, wallCol) ||
						Col_PointRect(entity->hitbox.position.x + entity->hitbox.radius - 1, entity->hitbox.position.y - entity->hitbox.radius + entity->velocity.y, wallCol) ||		//Point Collision
						Col_PointRect(entity->hitbox.position.x - entity->hitbox.radius + 1, entity->hitbox.position.y - entity->hitbox.radius + entity->velocity.y, wallCol)) &&
					(entity->hitbox.position.y - entity->hitbox.radius) >= wallCol.position.y - wallCol.height / 2 &&		//Constrain
					entity->velocity.y < 0)																																			//Arrow is moving up
				{
					printf("Touch Ceiling\n");
					n = CP_Vector_Set(0.0f, 1.0f);
				}

				//TOUCH WALL			 @TODO ADD MORE MATHS SO BAD RIGHT NOW
				else if ((level[i][j].isCollidable) &&
					COL_IsColliding(entityCol, wallCol) &&		//Shape Collision
					wallCol.position.x + wallCol.width / 2 >= entity->hitbox.position.x + entity->hitbox.radius &&		//Constrain
					entity->velocity.x > 0)																					//Arrow is moving left
				{
					printf("Touch Wall\n");
					n = CP_Vector_Set(1.0f, 0.0f);
				}

				else if ((level[i][j].isCollidable) &&
					COL_IsColliding(entityCol, wallCol) &&		//Shape Collision
					wallCol.position.x - wallCol.width / 2 <= entity->hitbox.position.x - entity->hitbox.radius &&		//Constrain
					entity->velocity.x < 0)																					//Arrow is moving right
				{
					printf("Touch Wall\n");
					n = CP_Vector_Set(-1.0f, 0.0f);
				}


				//n = Circle_Intersect_Rect(entityCol, wallCol);
				r = ArrowReflection(entity, n);
				//CP_Vector insct = Circle_Intersect_Rect(entityCol, wallCol);
				//printf("Intersection: %f, %f\n", insct.x, insct.y);
				//CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
				//CP_Graphics_DrawCircle(insct.x, insct.y, entityCol.radius * 2);
				//if (entity->velocity.x < 
				//entity->hitbox.position.y = wallCol.

				//if ((level[i + 1][j].isCollidable && (level[i + 1][j].gridType != GE_PIT)) && (level[i - 1][j].isCollidable && (level[i + 1][j].gridType != GE_PIT))) //Top and Bottom
				//{
				//	if (entity->velocity.y > 0) //if arrow is travelling downwards
				//	{
				//		n = CP_Vector_Set(0.0f, -1.0f);
				//	}
				//	else if (entity->velocity.y < 0) //If arrow is travelling upwards
				//	{
				//		n = CP_Vector_Set(0.0f, 1.0f);
				//	}
				//	r = ArrowReflection(entity, n);
				//}
				////else if(((level[i + 1][j].gridType == GE_WALL) && (level[i - 1][j].gridType == GE_WALL))
				//else if ((level[i][j + 1].isCollidable && (level[i + 1][j].gridType != GE_PIT)) && (level[i][j - 1].isCollidable && (level[i + 1][j].gridType != GE_PIT))) //Left and Right
				//{
				//	if (entity->velocity.x > 0) //If arrow is travelling to the right
				//	{
				//		n = CP_Vector_Set(-1.0f, 0.0f);
				//	}
				//	else if (entity->velocity.x < 0) //If arrow is travelling to the left
				//	{
				//		n = CP_Vector_Set(1.0f, 0.0f);
				//	}
				//	r = ArrowReflection(entity, n);
				//}
				while (COL_IsColliding(entity->hitbox, wallCol))
				{
					printf("Offset\n");
					entity->hitbox.position = CP_Vector_Add(entity->hitbox.position, offset);
				}
				entity->hitbox.position = CP_Vector_Add(entity->hitbox.position, offset);
				entity->hitbox.position = CP_Vector_Add(entity->hitbox.position, offset);
				//printf("%f, %f\n", n.x, n.y);
				entity->velocity = r;

				//entity->hitbox.position = CP_Vector_Add(entity->hitbox.position, CP_Vector_Scale(entity->velocity, 20));
				
				//float nearestX = Max(wallCol.position.x - wallCol.width / 2, Min(entityCol.position.x , wallCol.position.x + wallCol.width / 2));	//Get Nearest Point X
				//float nearestY = Max(wallCol.position.y - wallCol.height / 2, Min(entityCol.position.y , wallCol.position.y + wallCol.height / 2)); //Get Nearest Point Y

				//CP_Vector dist = CP_Vector_Set(entityCol.position.x - nearestX, entityCol.position.y - nearestY);
				//CP_Vector dnormal = CP_Vector_Set(-dist.y, dist.x);
				//
				//double nAngle = atan2(dnormal.y, dnormal.x);
				//double incAngle = atan2(entity->velocity.y, entity->velocity.x);
				//double theta = 2 * (nAngle - incAngle);

				//
				//CP_Matrix rotation = CP_Matrix_Rotate(CP_Math_Degrees((float)theta));
				//entity->velocity = CP_Vector_MatrixMultiply(rotation, entity->velocity);
				//entity->hitbox.position = CP_Vector_Add(entity->hitbox.position, CP_Vector_Scale(entity->velocity, 10));
				Colliding = true;

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