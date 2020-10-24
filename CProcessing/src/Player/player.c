#include <stdio.h>
#include <cprocessing.h>
#include "player.h"
#include "../GameLogic/BlobInput.h"



CP_Color backgroundColour;
//Player newPlayer;
void CreatePlayer(Player* player) //Default Variables
{
	//Set player state
	playerState = STILL;

	playerColor = CP_Color_Create(255, 255, 255, 255);
	//sprite = CP_Image_Load(".dioface.png");

	//Player Stats and Position
	player->health = 1;
	player->radius = CP_System_GetWindowWidth() / 20.0f;
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
	dodgeDistance = CP_System_GetWindowWidth() / 100.0f;
	dodgeTimer = 0.0f;
	dodgeBlur = 3;
	player->numDodge = 2;

	//Player Arrow
	player->playerHasArrow = 1;
	CreateArrow(&(player->arrow));

}

void PlayerDraw(Player* player)
{
	CP_Settings_EllipseMode(CP_POSITION_CENTER);
	CP_Settings_RectMode(CP_POSITION_CENTER);
	MouseTracking(player);
	//Draw player
	CP_Settings_Fill(playerColor);
	CP_Graphics_DrawEllipseAdvanced(player->position.x, player->position.y, player->radius *2, player->radius * 2, player->rotation);
	CP_Graphics_DrawRectAdvanced(player->position.x, player->position.y, player->radius, player->radius, player->rotation, 1);

	//Draw arrow
	CP_Settings_Fill(arrowColor);
	CP_Graphics_DrawRectAdvanced(player->arrow.position.x, player->arrow.position.y, player->arrow.width, player->arrow.width, player->rotation+45.0f, 1);
	
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
		if (CP_Input_KeyTriggered(KEY_SPACE) && (player->numDodge > 0))
		{
			playerState = DODGING;

			player->numDodge -= 1;

		}
		//else if (CP_Input_KeyDown(KEY_W) && CP_Input_KeyDown(KEY_A))
		else if (GetBlobInputDown(BLOB_UP) && GetBlobInputDown(BLOB_LEFT))
		{
			playerState = MOVING;
			player->vel = CP_Vector_Set(-1, -1);
			player->position.x += (player->vel.x * PLAYER_SPEED);
			player->position.y += (player->vel.y * PLAYER_SPEED);
			//player->rotation = -45.0f;
		}
		//else if ((CP_Input_KeyDown(KEY_W) && CP_Input_KeyDown(KEY_D)))
		else if (GetBlobInputDown(BLOB_UP) && GetBlobInputDown(BLOB_RIGHT))
		{
			playerState = MOVING;
			player->vel = CP_Vector_Set(1, -1);
			player->position.x += (player->vel.x * PLAYER_SPEED);
			player->position.y += (player->vel.y * PLAYER_SPEED);
			//player->rotation = 45.0f;
		}
		//else if (CP_Input_KeyDown(KEY_W))
		else if (GetBlobInputDown(BLOB_UP))
		{
			playerState = MOVING;
			player->vel = CP_Vector_Set(0, -1);
			player->position.x += (player->vel.x * PLAYER_SPEED);
			player->position.y += (player->vel.y * PLAYER_SPEED);
			//player->rotation = 0.0f;
		}
		//else if (CP_Input_KeyDown(KEY_S) && CP_Input_KeyDown(KEY_D))
		else if (GetBlobInputDown(BLOB_DOWN) && GetBlobInputDown(BLOB_RIGHT))
		{
			playerState = MOVING;
			player->vel = CP_Vector_Set(1, 1);
			player->position.x += (player->vel.x * PLAYER_SPEED);
			player->position.y += (player->vel.y * PLAYER_SPEED);
			//player->rotation = 135.0f;
		}
		//else if (CP_Input_KeyDown(KEY_S) && CP_Input_KeyDown(KEY_A))
		else if (GetBlobInputDown(BLOB_DOWN) && GetBlobInputDown(BLOB_LEFT))
		{
			playerState = MOVING;
			player->vel = CP_Vector_Set(-1, 1);
			player->position.x += (player->vel.x * PLAYER_SPEED);
			player->position.y += (player->vel.y * PLAYER_SPEED);
			//player->rotation = 225.0f;
		}
		//else if (CP_Input_KeyDown(KEY_S))
		else if (GetBlobInputDown(BLOB_DOWN))
		{
			playerState = MOVING;
			player->vel = CP_Vector_Set(0, 1);
			player->position.x += (player->vel.x * PLAYER_SPEED);
			player->position.y += (player->vel.y * PLAYER_SPEED);
			//player->rotation = 180.0f;
		}

		//else if (CP_Input_KeyDown(KEY_A))
		else if (GetBlobInputDown(BLOB_LEFT))
		{
			playerState = MOVING;
			player->vel = CP_Vector_Set(-1, 0);
			player->position.x += (player->vel.x * PLAYER_SPEED);
			player->position.y += (player->vel.y * PLAYER_SPEED);
			//player->rotation = -90.0f;
		}

		//else if (CP_Input_KeyDown(KEY_D))
		else if (GetBlobInputDown(BLOB_RIGHT))
		{
			playerState = MOVING;
			player->vel = CP_Vector_Set(1, 0);
			player->position.x += (player->vel.x * PLAYER_SPEED);
			player->position.y += (player->vel.y * PLAYER_SPEED);
			//player->rotation = 90.0f;
		}
		
	}
	//HitBox
#if 0
	player->hitBox.position = CP_Vector_Set(player->position.x - player->width / 2, player->position.y - player->width / 2);	//RECT
#endif
#if 1
	player->hitBox.position = player->position;		//Circle
#endif
	player->arrow.position = player->position;
	PlayerDraw(player);
}

void MouseTracking(Player* player)
{
	mousePositionVector = CP_Vector_Subtract(CP_Vector_Set(CP_Input_GetMouseX(), CP_Input_GetMouseY()), player->position);
	if (mousePositionVector.x < 0)
	{
		player->rotation = CP_Vector_Angle(mousePositionVector, CP_Vector_Set(0.0f, 1.0f)) + 190.0f;
	}
	else
	{
		player->rotation = CP_Vector_Angle(mousePositionVector, CP_Vector_Set(0.0f, -1.0f));
	}
	
	//if (CP_Vector_DotProduct(mousePositionVector, CP_Vector_Set(0.0f, -1.0f)) < 0)
	//{
	//	player->rotation += 90.0f;
	//}

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
		player->position.x += player->vel.x * (PLAYER_SPEED * (dodgeDistance / 4));
		player->position.y += player->vel.y * (PLAYER_SPEED * (dodgeDistance / 4));
		//HitBox
#if 0
		player->hitBox.position = CP_Vector_Set(player->position.x - player->width / 2, player->position.y - player->width / 2);	//RECT
#endif
#if 1
		player->hitBox.position = player->position;		//Circle
#endif
		player->arrow.position = player->position;
		PlayerDraw(player);
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
	if (player->playerHasArrow == 1)
	{
		if (CP_Input_MouseDown(MOUSE_BUTTON_LEFT))
		{
			if (playerState == STILL)
			{
				CP_Settings_Fill(CP_Color_Create(0, 0, 255, 100));
				CP_Graphics_DrawRectAdvanced(player->arrow.position.x, player->arrow.position.y, player->arrow.width, player->arrow.width, player->rotation + 45.0f, 1);
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
				PlayerDraw(player);
				player->arrow.dir.x = CP_Input_GetMouseX() - player->position.x;
				player->arrow.dir.y = CP_Input_GetMouseY() - player->position.y;
				player->arrow.force = DEFAULT_FORCE + player->arrow.forceTimer;
				player->arrow.forceTimer = 0.0f;

				//player->playerHasArrow = 0;

			}
		}
	}
}

void DisplayScore(float score) //function to display the score on screen
{
	char scoreBuffer[15]; //buffer for value of score
	sprintf_s(scoreBuffer, 15, "rotate: %d", (int)score); // print score into buffer

	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_LEFT, CP_TEXT_ALIGN_V_BASELINE);
	CP_Color textColor = CP_Color_Create(255, 255, 255, 255); //set text to white, size to 20
	CP_Settings_Fill(textColor);
	CP_Settings_TextSize(20);
	CP_Font_DrawText(scoreBuffer, 30.f, 40.f); //display score at top left corner
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
	ArrowRelease(&(player)->arrow);
	DisplayScore(player->rotation);
}