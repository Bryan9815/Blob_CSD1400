#pragma once
#include <cprocessing.h>
#include "Arrow.h"
#include "../GameLogic/Collision.h"
#include "../GameLogic/grid.h"

#define PLAYER_SPEED	5.0f
#define DODGE_COOLDOWN	4	//Seconds
#define MAX_DODGE		2

typedef struct
{
	int			health;
	Body		pBody;		//Player position and velocity;
	float		rotation;   //Necessary for sprite
	int			numDodge;	// number of dodges
	Arrow		arrow;

} Player;

typedef enum
{
	MOVING,
	DODGING,
	STILL,
	SHOOTING

} PlayerState;

Player newPlayer;
PlayerState playerState;
CP_Vector	mousePositionVector;

//CP_Image	sprite;
CP_Color	playerColor;
CP_Color	backgroundColour;



float dodgeTimer;		//Timer for dodging cooldown
float dodgeDistance;	//distance travelled via dodge
int dodgeBlur;			//Dodge blur effect

void PlayerInit(Player* player);

void PlayerDraw(Player* player);
void MouseTracking(Player* player);

void PlayerUpdate(Player* player);
void PlayerMovement(Player* player);
void Dodge(Player* player);
void DodgeRecharge(Player* player);

void ArrowTrigger(Player* player);
void ArrowStateChange(Player* player, Arrow* arrow);

void DisplayScore(float score);
