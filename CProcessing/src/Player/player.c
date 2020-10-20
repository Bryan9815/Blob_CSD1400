#include <stdio.h>
#include <cprocessing.h>
#include "player.h"


Player CreatePlayer() //Default Variables
{
	Player newPlayer;

	newPlayer.speed = 10.0f;

	newPlayer.velX = 0;
	newPlayer.velY = 0;

	return newPlayer;
}

/*Physics*/
void PlayerUpdate(Player player)
{

}