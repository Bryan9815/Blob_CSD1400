#pragma once
#include <cprocessing.h>
#include "Arrow.h"
#include "../GameLogic/Collision.h"
#include "../GameLogic/grid.h"

#define PLAYER_SPEED	320.0f
#define DODGE_COOLDOWN	3	//Seconds
#define MAX_DODGE		2

typedef struct
{
	//float		rotation;   //Necessary for sprite
	int			health;
	int			numDodge;	// number of dodges
	Body		pBody;		//Player position and velocity;
	Arrow		arrow;		//Player arrow

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

CP_Image	sprite;
CP_Color	playerColor;
CP_Color	backgroundColour;

float	dodgeTimer;		//Timer for dodging cooldown
float	dodgeDistance;	//distance travelled via dodge
int		dodgeBlur;			//Dodge blur effect
float	arrowCharge;		//Arrow Charge

void PlayerInit(Player* player);

void PlayerDraw(Player* player);

void PlayerUpdate(Player* player);
void PlayerMovement(Player* player);
void Dodge(Player* player);
void DodgeRecharge(Player* player);

bool ArrowStateCheck(Body* pBody, Body* bBody, Arrow* arrow);
bool ArrowTrigger(Player* player);
bool ArrowBoss1Collision(Arrow* arrow, Body* bBody);