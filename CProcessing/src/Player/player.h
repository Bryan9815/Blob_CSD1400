#pragma once
#include <cprocessing.h>
#include "Arrow.h"
#include "../GameLogic/Collider.h"

#define PLAYER_SPEED	7.0f
#define DODGE_COOLDOWN	4	//Seconds
#define MAX_DODGE		2

typedef struct
{
	int			health;
	float		radius,
				rotation;
	CP_Vector	position;	//Position of player
	CP_Vector   vel;		//direction/velocity

	int			numDodge;	// number of dodges
	Collider	hitBox;

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

void PlayerInit(void);

void CreatePlayer(Player* player);
void PlayerDraw(Player* player);
void MouseTracking(Player* player);

void PlayerUpdate(Player* player);
void PlayerMovement(Player* player);
void Dodge(Player* player);
void DodgeRecharge(Player* player);

void ArrowTrigger(Player* player);
void ArrowStateChange(Player* player, Arrow* arrow);
