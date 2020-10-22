#pragma once
#include <cprocessing.h>
typedef struct
{
	float		speed,
				width,
				rotation;
	CP_Vector	position;		//Position of player
	int			velX,			//direction/velocity along x-axis
				velY;			//direction/velocity along y axis
				
	int			numDodge,		//Number of Dodges
				isDodging,
				dodgeBlur,		//Afterimage
				dodgeCooldown;	//Cooldown of dodge
	float		dodgeFactor,	//Distance travelled via dodge
				dodgeTimer;		//Timer for dodging cooldown
	//CP_Image	  sprite;

} Player;

Player newPlayer;

void SetPlayer(Player* player);
void PlayerUpdate(Player player);
void PlayerMovement(Player* player);
