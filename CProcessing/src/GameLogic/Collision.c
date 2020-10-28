#include "Collision.h"

bool Col_PointRect(float x, float y, Collider rect) 
{
	return 
		(x >= rect.position.x - rect.width / 2 &&           // right of the left edge AND
		x <= rect.position.x + rect.width / 2 &&			// left of the right edge AND
		y >= rect.position.y - rect.height / 2 &&           // below the top AND
		y <= rect.position.y + rect.height / 2)				// above the bottom
		? true : false;
}
void CollisionCheck(Player* player, GridUnit* _level)
{
	

	for (int i = 0; i < GetLevelWidth(); i++)
	{
		for (int j = 0; j < GetLevelHeight(); j++)
		{
			Collider wallCol = _level[i * GetLevelHeight() + j].collider;
			Collider playerCol = player->hitBox;

			playerCol.position.x += player->vel.x;
			
			//Player can be replaced with any reference a struct with a collider and stores its position there instead, pass entity refer to INTOBJ.AS

			//TOUCH FLOOR
			if (	_level[i * GetLevelHeight() + j].gridType == GE_WALL &&
					(Col_PointRect(player->hitBox.position.x, player->hitBox.position.y + player->hitBox.radius + player->vel.y, wallCol)								||
					Col_PointRect(player->hitBox.position.x + player->hitBox.radius - 1 , player->hitBox.position.y + player->hitBox.radius + player->vel.y, wallCol)	||		//Point Collision
					Col_PointRect(player->hitBox.position.x - player->hitBox.radius + 1, player->hitBox.position.y + player->hitBox.radius + player->vel.y, wallCol))	&&		
					(player->position.y + player->hitBox.radius) <= wallCol.position.y + wallCol.height / 2																&&		//Constrain
					player->vel.y > 0)																																			//Player is moving down
			{
				player->vel.y = (wallCol.position.y - wallCol.height / 2) - (player->hitBox.position.y + player->hitBox.radius);
			}

			//TOUCH WALL			 @TODO ADD MORE MATHS SO BAD RIGHT NOW
			if (	_level[i * GetLevelHeight() + j].gridType == GE_WALL											&&
					COL_IsColliding(playerCol, wallCol)																&&		//Shape Collision
					wallCol.position.x + wallCol.width / 2 >= player->hitBox.position.x +player->hitBox.radius		&&		//Constrain
					player->vel.x > 0)																						//Player is moving left
			{
				player->vel.x = (wallCol.position.x - wallCol.width / 2) - (player->position.x + player->hitBox.radius);
			}

			if (	_level[i * GetLevelHeight() + j].gridType == GE_WALL											&&
					COL_IsColliding(playerCol, wallCol)																&&		//Shape Collision
					wallCol.position.x - wallCol.width / 2 <= player->hitBox.position.x - player->hitBox.radius		&&		//Constrain
					player->vel.x < 0)																						//Player is moving right
			{
				player->vel.x = (wallCol.position.x + wallCol.width / 2) - (player->position.x - player->hitBox.radius);
			}

			//TOUCH CEILING
			if (	_level[i * GetLevelHeight() + j].gridType == GE_WALL																								&&
					(Col_PointRect(player->hitBox.position.x, player->hitBox.position.y - player->hitBox.radius + player->vel.y, wallCol)								|| 
					Col_PointRect(player->hitBox.position.x + player->hitBox.radius - 1, player->hitBox.position.y - player->hitBox.radius + player->vel.y, wallCol)	||		//Point Collision
					Col_PointRect(player->hitBox.position.x - player->hitBox.radius + 1, player->hitBox.position.y - player->hitBox.radius + player->vel.y, wallCol))	&& 
					(player->position.y - player->hitBox.radius) >= wallCol.position.y - wallCol.height / 2																&&		//Constrain
					player->vel.y < 0)																																			//Player is moving up
			{
				player->vel.y = (wallCol.position.y + wallCol.height / 2) - (player->hitBox.position.y - player->hitBox.radius);
			}

		}

	}

}