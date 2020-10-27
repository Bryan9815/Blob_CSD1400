#include <stdio.h>
#include <cprocessing.h>
#include "player.h"
#include "../GameLogic/BlobInput.h"
#include "../GameLogic/Collision.h"
#include "../GameLogic/grid.h"



CP_Color backgroundColour;
//Player newPlayer;
void CreatePlayer(Player* player) //Default Variables
{
	//Set player state
	playerState = STILL;
	playerArrowState = WITHPLAYER;

	playerColor = CP_Color_Create(255, 255, 255, 255);
	//sprite = CP_Image_Load(".dioface.png");

	//Player Stats and Position
	player->health = 1;
	player->radius = CP_System_GetWindowWidth() / 40.0f;
	player->rotation = 0.0f;
	player->position = CP_Vector_Set(CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 2.0f);
	player->vel = CP_Vector_Set(0, -1);
#if 0
	player->hitBox.shapeType = COL_RECT; //RECT COLLIDER
	player->hitBox.position = CP_Vector_Set(CP_System_GetWindowWidth() / 2.0f - player->width / 2, CP_System_GetWindowHeight() / 2.0f - player->width / 2); //Align Hitbox to Corner
	player->hitBox.width = CP_System_GetWindowWidth() / 15.0f;
	player->hitBox.height = CP_System_GetWindowWidth() / 15.0f;
#endif
#if 1
	player->hitBox.shapeType = COL_CIRCLE; //CIRCLE COLLIDER
	player->hitBox.position = player->position;
	player->hitBox.radius = player->radius;
#endif

	//Player dodge
	dodgeDistance = CP_System_GetWindowWidth() / 60.0f;
	dodgeTimer = 0.0f;
	dodgeBlur = 3;
	player->numDodge = 2;

	//Player Arrow
	CreateArrow(&(player->arrow));

}

void PlayerDraw(Player* player)
{
	CP_Settings_EllipseMode(CP_POSITION_CENTER);
	CP_Settings_RectMode(CP_POSITION_CENTER);
	MouseTracking(player);
	if (playerState == DODGING)
	{
		//Draw player
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 100));
		CP_Graphics_DrawEllipseAdvanced(player->position.x, player->position.y, player->radius * 2, player->radius * 2, player->rotation);

		//Draw arrow
		CP_Settings_Fill(CP_Color_Create(255, 0, 0, 100));
		CP_Graphics_DrawRectAdvanced(player->arrow.currentPosition.x, player->arrow.currentPosition.y, player->arrow.width, player->arrow.width, player->rotation + 45.0f, 1);
	}
	else
	{
		//Draw player
		CP_Settings_Fill(playerColor);
		CP_Graphics_DrawEllipseAdvanced(player->position.x, player->position.y, player->radius * 2, player->radius * 2, player->rotation);

		//Draw arrow
		CP_Settings_Fill(arrowColor);
		CP_Graphics_DrawRectAdvanced(player->arrow.currentPosition.x, player->arrow.currentPosition.y, player->arrow.width, player->arrow.width, player->rotation + 45.0f, 1);
	}

	
	//HitBox
	
	CP_Settings_Fill(CP_Color_Create(255, 0, 0, 200));	
#if 1
	CP_Settings_EllipseMode(CP_POSITION_CENTER);
	CP_Graphics_DrawCircle(					//CIRCLE COLLIDER
		player->hitBox.position.x,
		player->hitBox.position.y,
		player->hitBox.radius * 2);
#endif
#if 0
	CP_Settings_RectMode(CP_POSITION_CORNER);
	CP_Graphics_DrawRect(					//RECT COLLIDER
		player->hitBox.position.x,
		player->hitBox.position.y,
		player->hitBox.width,
		player->hitBox.height
	);
#endif
	//Draw Dio
	//CP_Image_DrawAdvanced(sprite, player->position.x, player->position.y, dioWidth, dioHeight, 255, player->rotation);
}

void PlayerMovement(Player* player)
{
	CP_Settings_Background(backgroundColour);

	if (playerState != DODGING)
	{
		playerState = STILL;
		player->vel = CP_Vector_Set(0, 0);
		//else if (CP_Input_KeyDown(KEY_W) && CP_Input_KeyDown(KEY_A))
		if (GetBlobInputDown(BLOB_UP) && GetBlobInputDown(BLOB_LEFT))
		{
			playerState = MOVING;
			player->vel = CP_Vector_Set(-1, -1);
			//player->position.x += (player->vel.x * PLAYER_SPEED);
			//player->position.y += (player->vel.y * PLAYER_SPEED);
			//player->rotation = -45.0f;
		}
		//else if ((CP_Input_KeyDown(KEY_W) && CP_Input_KeyDown(KEY_D)))
		else if (GetBlobInputDown(BLOB_UP) && GetBlobInputDown(BLOB_RIGHT))
		{
			playerState = MOVING;
			player->vel = CP_Vector_Set(1, -1);
			//player->position.x += (player->vel.x * PLAYER_SPEED);
			//player->position.y += (player->vel.y * PLAYER_SPEED);
			//player->rotation = 45.0f;
		}
		//else if (CP_Input_KeyDown(KEY_W))
		else if (GetBlobInputDown(BLOB_UP))
		{
			playerState = MOVING;
			player->vel = CP_Vector_Set(0, -1);
			//player->position.x += (player->vel.x * PLAYER_SPEED);
			//player->position.y += (player->vel.y * PLAYER_SPEED);
			//player->rotation = 0.0f;
		}
		//else if (CP_Input_KeyDown(KEY_S) && CP_Input_KeyDown(KEY_D))
		else if (GetBlobInputDown(BLOB_DOWN) && GetBlobInputDown(BLOB_RIGHT))
		{
			playerState = MOVING;
			player->vel = CP_Vector_Set(1, 1);
			//player->position.x += (player->vel.x * PLAYER_SPEED);
			//player->position.y += (player->vel.y * PLAYER_SPEED);
			//player->rotation = 135.0f;
		}
		//else if (CP_Input_KeyDown(KEY_S) && CP_Input_KeyDown(KEY_A))
		else if (GetBlobInputDown(BLOB_DOWN) && GetBlobInputDown(BLOB_LEFT))
		{
			playerState = MOVING;
			player->vel = CP_Vector_Set(-1, 1);
			//player->position.x += (player->vel.x * PLAYER_SPEED);
			//player->position.y += (player->vel.y * PLAYER_SPEED);
			//player->rotation = 225.0f;
		}
		//else if (CP_Input_KeyDown(KEY_S))
		else if (GetBlobInputDown(BLOB_DOWN))
		{
			playerState = MOVING;
			player->vel = CP_Vector_Set(0, 1);
			//player->position.x += (player->vel.x * PLAYER_SPEED);
			//player->position.y += (player->vel.y * PLAYER_SPEED);
			//player->rotation = 180.0f;
		}

		//else if (CP_Input_KeyDown(KEY_A))
		else if (GetBlobInputDown(BLOB_LEFT))
		{
			playerState = MOVING;
			player->vel = CP_Vector_Set(-1, 0);
			//player->position.x += (player->vel.x * PLAYER_SPEED);
			//player->position.y += (player->vel.y * PLAYER_SPEED);
			//player->rotation = -90.0f;
		}

		//else if (CP_Input_KeyDown(KEY_D))
		else if (GetBlobInputDown(BLOB_RIGHT))
		{
			playerState = MOVING;
			player->vel = CP_Vector_Set(1, 0);
			//player->position.x += (player->vel.x * PLAYER_SPEED);
			//player->position.y += (player->vel.y * PLAYER_SPEED);
			//player->rotation = 90.0f;
		}

		if (CP_Input_KeyTriggered(KEY_SPACE) && playerState != STILL && (player->numDodge > 0))
		{
			playerState = DODGING;

			player->numDodge -= 1;

		}
		
	}
	player->vel.x = (player->vel.x * PLAYER_SPEED);
	player->vel.y = (player->vel.y * PLAYER_SPEED);

	CollisionCheck(&newPlayer, level[0]);
	
	player->position.x += player->vel.x;
	player->position.y += player->vel.y;
	player->hitBox.position = player->position;		//Circle
#if 0
	player->hitBox.position = CP_Vector_Set(player->position.x - player->width / 2, player->position.y - player->width / 2);	//RECT
#endif
#if 1
	
#endif
	player->arrow.currentPosition = player->position;
	
}

void MouseTracking(Player* player)
{
	mousePositionVector = CP_Vector_Subtract(CP_Vector_Set(CP_Input_GetMouseWorldX(), CP_Input_GetMouseWorldY()), player->position);
	if (mousePositionVector.x < 0)
	{
		player->rotation = CP_Vector_Angle(mousePositionVector, CP_Vector_Set(0.0f, 1.0f)) + 180.0f;
	}
	else
	{
		player->rotation = CP_Vector_Angle(mousePositionVector, CP_Vector_Set(0.0f, -1.0f));
	}

}

void Dodge(Player* player)
{
	DodgeRecharge(player);
	if (playerState == DODGING)
	{

		if (dodgeBlur != 0)
		{
			dodgeBlur -= 1;
		}
		else
		{
			dodgeBlur = 3;
			playerState = STILL;
		}
		player->vel.x = player->vel.x * (PLAYER_SPEED * (dodgeDistance / 4));
		player->vel.y = player->vel.y * (PLAYER_SPEED * (dodgeDistance / 4));

		CollisionCheck(&newPlayer, level[0]);

		player->position.x += player->vel.x;
		player->position.y += player->vel.y;
		player->hitBox.position = player->position;

		//HitBox
#if 0
		player->hitBox.position = CP_Vector_Set(player->position.x - player->width / 2, player->position.y - player->width / 2);	//RECT
#endif
#if 1
		player->hitBox.position = player->position;		//Circle
#endif
		player->arrow.currentPosition = player->position;
	}
}

void DodgeRecharge(Player* player) //Recharge Dodge
{
	if (player->numDodge < 2)
	{
		dodgeTimer += CP_System_GetDt();
		if (dodgeTimer > DODGE_COOLDOWN)
		{
			player->numDodge += 1;
			dodgeTimer = 0.0f;
		}
	}
}

void ArrowTrigger(Player* player)
{
	if (playerArrowState == WITHPLAYER)
	{
		if (CP_Input_MouseDown(MOUSE_BUTTON_LEFT))
		{
			if (playerState == STILL)
			{
				CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
				CP_Graphics_DrawRectAdvanced(player->arrow.currentPosition.x, player->arrow.currentPosition.y, player->arrow.width, player->arrow.width, player->rotation + 45.0f, 1);
				if (player->arrow.forceTimer <= 30)
				{
					player->arrow.forceTimer += CP_System_GetDt() * 10;
				}
			}
			else if (playerState == MOVING || playerState == DODGING)
			{
				player->arrow.forceTimer = 0.0f;
			}
		}
		else if (CP_Input_MouseReleased(MOUSE_BUTTON_LEFT))
		{
			playerState = SHOOTING;
			if (playerState == SHOOTING)
			{
				ArrowRelease(&(player->arrow));
			}
		}
	}
}

void PlayerInit(void)
{
	CreatePlayer(&newPlayer);
}

/*Update Player*/
void PlayerUpdate(Player* player)
{
	PlayerMovement(player);
	Dodge(player);
	ArrowTrigger(player);
	ArrowPhysics(&(player->arrow));
}