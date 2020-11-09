#include "Collision.h"
#include <math.h>
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

bool CollisionCheck(Body* entity, GridUnit* _level)
{
	
	bool Colliding = false;
	for (int i = 0; i < GetLevelWidth(); i++)
	{
		for (int j = 0; j < GetLevelHeight(); j++)
		{
			Collider wallCol = _level[i * GetLevelHeight() + j].collider;
			Collider entityCol = entity->hitbox;

			entityCol.shapeType = COL_RECT;					//Im not gonna do math now so just casting entity hitbox to rects for collision
			entityCol.width = entity->hitbox.radius * 2;
			entityCol.height = entity->hitbox.radius * 2;
			entityCol.position.x += entity->velocity.x;
			
			//Player can be replaced with any reference a struct with a collider and stores its position there instead, pass entity refer to INTOBJ.AS


			//@REDO
			//TOUCH FLOOR
			if (	_level[i * GetLevelHeight() + j].gridType == GE_WALL &&
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
			if (	_level[i * GetLevelHeight() + j].gridType == GE_WALL											&&
					COL_IsColliding(entityCol, wallCol)																&&		//Shape Collision
					wallCol.position.x + wallCol.width / 2 >= entity->hitbox.position.x + entity->hitbox.radius		&&		//Constrain
					entity->velocity.x > 0)																						//Player is moving left
			{
				entity->velocity.x = (wallCol.position.x - wallCol.width / 2) - (entity->hitbox.position.x + entity->hitbox.radius);
				Colliding = true;
			}

			if (	_level[i * GetLevelHeight() + j].gridType == GE_WALL											&&
					COL_IsColliding(entityCol, wallCol)																&&		//Shape Collision
					wallCol.position.x - wallCol.width / 2 <= entity->hitbox.position.x - entity->hitbox.radius &&		//Constrain
					entity->velocity.x < 0)																						//Player is moving right
			{
				entity->velocity.x = (wallCol.position.x + wallCol.width / 2) - (entity->hitbox.position.x - entity->hitbox.radius);
				Colliding = true;
			}

			//TOUCH CEILING
			if (	_level[i * GetLevelHeight() + j].gridType == GE_WALL																								&&
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

//Shamelessly stolen from Jia Rong, thanks btw
bool ArrowCollision(Body* entity, GridUnit* _level)
{
	bool Colliding = false;
	for (int i = 0; i < GetLevelWidth(); i++)
	{
		for (int j = 0; j < GetLevelHeight(); j++)
		{
			Collider wallCol = _level[i * GetLevelHeight() + j].collider;
			Collider entityCol = entity->hitbox;

			//entityCol.position.x += entity->velocity.x * 10;
			//entityCol.position.y += entity->velocity.y * 10;

			//Fuck my life
			if (COL_IsColliding(entityCol, wallCol) && _level[i * GetLevelHeight() + j].gridType == GE_WALL)
			{
				float nearestX = Max(wallCol.position.x - wallCol.width / 2, Min(entityCol.position.x , wallCol.position.x + wallCol.width / 2));	//Get Nearest Point X
				float nearestY = Max(wallCol.position.y - wallCol.height / 2, Min(entityCol.position.y , wallCol.position.y + wallCol.height / 2)); //Get Nearest Point Y

				CP_Vector dist = CP_Vector_Set(entityCol.position.x - nearestX, entityCol.position.y - nearestY);
				CP_Vector dnormal = CP_Vector_Set(-dist.y, dist.x);
				
				double nAngle = atan2(dnormal.y, dnormal.x);
				double incAngle = atan2(entity->velocity.y, entity->velocity.x);
				double theta = 2 * (nAngle - incAngle);

				
				CP_Matrix rotation = CP_Matrix_Rotate(CP_Math_Degrees((float)theta));
				entity->velocity = CP_Vector_MatrixMultiply(rotation, entity->velocity);
				entity->hitbox.position = CP_Vector_Add(entity->hitbox.position, CP_Vector_Scale(entity->velocity, 10));
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