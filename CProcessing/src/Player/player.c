#include <stdio.h>
#include <cprocessing.h>
#include "player.h"


CP_Color backgroundColour;
//Player newPlayer;
void CreatePlayer(Player* newPlayer) //Default Variables
{
	//Set player state
	playerState = STILL;

	playerColor = CP_Color_Create(255, 255, 255, 255);
	//sprite = CP_Image_Load(".dioface.png");

	//Player Stats and Position
	newPlayer->health = 1;
	newPlayer->width = CP_System_GetWindowWidth() / 15.0f;
	newPlayer->rotation = 0.0f;
	newPlayer->position = CP_Vector_Set(CP_System_GetWindowWidth() / 2.0f,
						  (CP_System_GetWindowHeight() / 2.0f) + (CP_System_GetWindowHeight() / 4.0f));
	newPlayer->vel = CP_Vector_Set(0, -1);

	//Player dodge
	dodgeDistance = CP_System_GetWindowWidth() / 100.0f;
	dodgeTimer = 0.0f;
	dodgeBlur = 3;
	newPlayer->numDodge = 2;

	//Player Arrow
	newPlayer->playerHasArrow = 1;
	CreateArrow(&(newPlayer->arrow));

}

void PlayerDraw(Player* player)
{
	//Draw player
	CP_Settings_Fill(playerColor);
	CP_Graphics_DrawRectAdvanced(player->position.x, player->position.y, player->width, player->width, player->rotation, 1);

	//Draw arrow
	CP_Settings_Fill(arrowColor);
	CP_Graphics_DrawRectAdvanced(player->arrow.position.x, player->arrow.position.y, player->arrow.width, player->arrow.width, player->rotation + 45.0f, 1);

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
		else if (CP_Input_KeyDown(KEY_W) && CP_Input_KeyDown(KEY_A))
		{
			playerState = MOVING;
			player->vel = CP_Vector_Set(-1, -1);
			player->position.x += (player->vel.x * PLAYER_SPEED);
			player->position.y += (player->vel.y * PLAYER_SPEED);
			player->rotation = -45.0f;
		}
		else if ((CP_Input_KeyDown(KEY_W) && CP_Input_KeyDown(KEY_D)))
		{
			playerState = MOVING;
			player->vel = CP_Vector_Set(1, -1);
			player->position.x += (player->vel.x * PLAYER_SPEED);
			player->position.y += (player->vel.y * PLAYER_SPEED);
			player->rotation = 45.0f;
		}
		else if (CP_Input_KeyDown(KEY_W))
		{
			playerState = MOVING;
			player->vel = CP_Vector_Set(0, -1);
			player->position.x += (player->vel.x * PLAYER_SPEED);
			player->position.y += (player->vel.y * PLAYER_SPEED);
			player->rotation = 0.0f;
		}
		else if (CP_Input_KeyDown(KEY_S) && CP_Input_KeyDown(KEY_D))
		{
			playerState = MOVING;
			player->vel = CP_Vector_Set(1, 1);
			player->position.x += (player->vel.x * PLAYER_SPEED);
			player->position.y += (player->vel.y * PLAYER_SPEED);
			player->rotation = 135.0f;
		}
		else if (CP_Input_KeyDown(KEY_S) && CP_Input_KeyDown(KEY_A))
		{
			playerState = MOVING;
			player->vel = CP_Vector_Set(-1, 1);
			player->position.x += (player->vel.x * PLAYER_SPEED);
			player->position.y += (player->vel.y * PLAYER_SPEED);
			player->rotation = 225.0f;
		}
		else if (CP_Input_KeyDown(KEY_S))
		{
			playerState = MOVING;
			player->vel = CP_Vector_Set(0, 1);
			player->position.x += (player->vel.x * PLAYER_SPEED);
			player->position.y += (player->vel.y * PLAYER_SPEED);
			player->rotation = 180.0f;
		}

		else if (CP_Input_KeyDown(KEY_A))
		{
			playerState = MOVING;
			player->vel = CP_Vector_Set(-1, 0);
			player->position.x += (player->vel.x * PLAYER_SPEED);
			player->position.y += (player->vel.y * PLAYER_SPEED);
			player->rotation = -90.0f;
		}

		else if (CP_Input_KeyDown(KEY_D))
		{
			playerState = MOVING;
			player->vel = CP_Vector_Set(1, 0);
			player->position.x += (player->vel.x * PLAYER_SPEED);
			player->position.y += (player->vel.y * PLAYER_SPEED);
			player->rotation = 90.0f;
		}
	}

	player->arrow.position = player->position;
	PlayerDraw(player);
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

/*Update Player*/
void PlayerUpdate(Player* player)
{
	PlayerMovement(player);
	Dodge(player);
	ArrowTrigger(player);
	ArrowRelease(&(player)->arrow);
}