﻿//---------------------------------------------------------
// file:	player.c
// author:	[Lim Zi Qing]
// email:	[ziqing.l@digipen.edu]
//
// brief:	Player object. Contains main player code, collision, and functions.
//
// Copyright � 2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#include <stdio.h>
#include <cprocessing.h>
#include "player.h"
#include "../GameLogic/BlobInput.h"
#include "../Bosses/Boss.h"
#include "../Screen/scr_level_1.h"
#include "../GameLogic//ScreenManager.h"
#include "../Audio/AudioManager.h"


CP_Color backgroundColour;
float pickuptimer = 0;
float chargetimer = 0;
int pulse = 0;

void PlayerInit(Player* player) //Initialize player
{
	//Set Player and Arrow state
	playerState = STILL;
	player->arrow.arrowState = WITHENTITY;
	player->arrow.arrowSprite = CP_Image_Load("././Assets/arrow.png");

	playerColor = CP_Color_Create(255, 255, 255, 255);
	sprite = CP_Image_Load("././Assets/slime.png"); // NO MORE KONO DIO DA!


	//Player Stats and Position
	player->health = 1;
	player->pBody.rotation = 0.0f;

#if 0
	player->hitBox.shapeType = COL_RECT; //RECT COLLIDER
	player->hitBox.position = CP_Vector_Set(CP_System_GetWindowWidth() / 2.0f - player->width / 2, CP_System_GetWindowHeight() / 2.0f - player->width / 2); //Align Hitbox to Corner
	player->hitBox.width = CP_System_GetWindowWidth() / 15.0f;
	player->hitBox.height = CP_System_GetWindowWidth() / 15.0f;
#endif
#if 1
	player->pBody.hitbox.shapeType = COL_CIRCLE; //CIRCLE COLLIDER
	player->pBody.hitbox.position = CP_Vector_Set(CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 2.0f);
	player->pBody.hitbox.radius = 40.0f;
	player->arrow.aBody.hitbox.position = player->pBody.hitbox.position;
	player->arrow.aBody.hitbox.radius = 25.0f;
#endif

	//Player dodge
	dodgeDistance = 55.0f;
	dodgeTimer = 0.0f;
	dodgeBlur = 20;
	player->numDodge = 2;

	//Player Arrow
	CreateArrow(&(player->arrow));

}

void ChargeSFX(Player* player) //Player arrow charge effect
{
	int r, g, b;
	r = 255;
	g = 255;
	b = 255;
	
	if (player->arrow.charge < (MAX_FORCE - DEFAULT_FORCE))
	{
		g = 255;
		b = 0;
		if (chargetimer == 0)
		{
			chargetimer = 255;
		}
		chargetimer -= CP_System_GetDt() * 255;
		if (chargetimer < 1)
		{
			chargetimer = 1;
		}
		b = (int)chargetimer;
		printf("%f\n", 255.0f/chargetimer);
		CP_Settings_Fill(CP_Color_Create(r, g, b, 70));
		CP_Graphics_DrawCircle(player->pBody.hitbox.position.x, player->pBody.hitbox.position.y, player->pBody.hitbox.radius * 2.5f);
	}
	else
	{
		
		if (pulse == 0)
		{
			chargetimer += CP_System_GetDt() * 170;
			printf("charge timer: %f\n", chargetimer);
			if (chargetimer > 70)
			{
				pulse = 1;
			}
		}
		else if (pulse == 1)
		{
			chargetimer -= CP_System_GetDt() * 170;
			printf("charge timer: %f\n", chargetimer);
			if (chargetimer <= 0)
			{
				pulse = 0;
			}
		}
		b = (int)chargetimer;
		CP_Settings_Fill(CP_Color_Create(r, g, b, (int)chargetimer));
		CP_Graphics_DrawCircle(player->pBody.hitbox.position.x, player->pBody.hitbox.position.y, player->pBody.hitbox.radius * 2.5f);
		CP_Image_DrawAdvanced(player->arrow.arrowSprite, player->arrow.aBody.hitbox.position.x, player->arrow.aBody.hitbox.position.y, player->arrow.aBody.hitbox.radius * 3.0f, player->arrow.aBody.hitbox.radius * 3.0f, (int)chargetimer, player->arrow.aBody.rotation);
	}

}

void PlayerDraw(Player* player) //Draw player
{
	CP_Settings_EllipseMode(CP_POSITION_CENTER);
	CP_Settings_RectMode(CP_POSITION_CENTER);
	CP_Settings_NoStroke();
	if (playerState == DODGING)
	{
		int transparency = 50;
		
		//Draw player
		CP_Image_DrawAdvanced(sprite, player->pBody.hitbox.position.x, player->pBody.hitbox.position.y, player->pBody.hitbox.radius * 2, player->pBody.hitbox.radius * 2, transparency, player->pBody.rotation);

		//Draw arrow
		CP_Image_DrawAdvanced(player->arrow.arrowSprite, player->arrow.aBody.hitbox.position.x, player->arrow.aBody.hitbox.position.y, player->arrow.aBody.hitbox.radius, player->arrow.aBody.hitbox.radius, transparency, player->arrow.aBody.rotation);

	}
	else
	{
		//Draw player

		CP_Image_DrawAdvanced(sprite, player->pBody.hitbox.position.x, player->pBody.hitbox.position.y, player->pBody.hitbox.radius * 2, player->pBody.hitbox.radius * 2, 255, player->pBody.rotation);

	}

	//Draw Dodge Bar
	if (dodgeTimer > 0)
	{
		char numDodgeText[2] = { (char)(player->numDodge + '0'), '\0' };
		CP_Settings_Fill(CP_Color_Create(255, 255, 100, 100));
		CP_Graphics_DrawRect(player->pBody.hitbox.position.x, player->pBody.hitbox.position.y - player->pBody.hitbox.radius - 10.0f, player->pBody.hitbox.radius, player->pBody.hitbox.radius / 5);
		CP_Settings_Fill(CP_Color_Create(255, 255, 100, 255));
		CP_Graphics_DrawRect(player->pBody.hitbox.position.x, player->pBody.hitbox.position.y - player->pBody.hitbox.radius - 10.0f, player->pBody.hitbox.radius * (dodgeTimer / DODGE_COOLDOWN), player->pBody.hitbox.radius / 5);
		CP_Settings_TextSize(15);
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		CP_Font_DrawText(numDodgeText, player->pBody.hitbox.position.x + player->pBody.hitbox.radius, player->pBody.hitbox.position.y - player->pBody.hitbox.radius - 10.0f);
	}

	if (player->arrow.charging == 1)
	{
		ChargeSFX(player);
		
	}
	else
	{
		chargetimer = 0;
	}

	//HitBox
	//CP_Settings_Fill(CP_Color_Create(255, 0, 0, 200));	
}

void PlayerMovement(Player* player) //Player movement
{
	CP_Settings_Background(backgroundColour);
	bool shooting = ArrowTrigger(player);
	if (shooting == false)
	{
		if (playerState != DODGING && player->arrow.charging == 0)
		{
			playerState = STILL;
			player->pBody.velocity = CP_Vector_Set(0, 0);
			if (GetBlobInputDown(BLOB_DOWN) && GetBlobInputDown(BLOB_UP))
			{
				playerState = MOVING;
				player->pBody.velocity = CP_Vector_Set(0, 0);
			}
			else if (GetBlobInputDown(BLOB_UP))
			{
				playerState = MOVING;
				player->pBody.velocity = CP_Vector_Set(0, -1);

				//player->rotation = 0.0f;
			}
			else if (GetBlobInputDown(BLOB_DOWN))
			{
				playerState = MOVING;
				player->pBody.velocity = CP_Vector_Set(0, 1);

				//player->rotation = 180.0f;
			}

			if (GetBlobInputDown(BLOB_LEFT) && GetBlobInputDown(BLOB_RIGHT))
			{
				playerState = MOVING;
				player->pBody.velocity = CP_Vector_Set(0, 0);
			}
			else if (GetBlobInputDown(BLOB_LEFT))
			{
				playerState = MOVING;
				player->pBody.velocity = CP_Vector_Set(-1, 0);

				//player->rotation = -90.0f;
			}
			else if (GetBlobInputDown(BLOB_RIGHT))
			{
				playerState = MOVING;
				player->pBody.velocity = CP_Vector_Set(1, 0);

				//player->rotation = 90.0f;
			}

			if (GetBlobInputDown(BLOB_UP) && GetBlobInputDown(BLOB_LEFT))
			{
				playerState = MOVING;
				//player->pBody.velocity = CP_Vector_Set(-1, -1);
				CP_Matrix rotatedir = CP_Matrix_Rotate(-45.0f);
				player->pBody.velocity = CP_Vector_MatrixMultiply(rotatedir, CP_Vector_Set(0.0f, -1.0f));

				//player->rotation = -45.0f;
			}
			if (GetBlobInputDown(BLOB_UP) && GetBlobInputDown(BLOB_RIGHT))
			{
				playerState = MOVING;
				//player->pBody.velocity = CP_Vector_Set(1, -1);
				CP_Matrix rotatedir = CP_Matrix_Rotate(45.0f);
				player->pBody.velocity = CP_Vector_MatrixMultiply(rotatedir, CP_Vector_Set(0.0f, -1.0f));

				//player->rotation = 45.0f;
			}

			if (GetBlobInputDown(BLOB_DOWN) && GetBlobInputDown(BLOB_RIGHT))
			{
				playerState = MOVING;
				//player->pBody.velocity = CP_Vector_Set(1, 1);
				CP_Matrix rotatedir = CP_Matrix_Rotate(-45.0f);
				player->pBody.velocity = CP_Vector_MatrixMultiply(rotatedir, CP_Vector_Set(0.0f, 1.0f));

				//player->rotation = 135.0f;
			}
			if (GetBlobInputDown(BLOB_DOWN) && GetBlobInputDown(BLOB_LEFT))
			{
				playerState = MOVING;
				//player->pBody.velocity = CP_Vector_Set(-1, 1);
				CP_Matrix rotatedir = CP_Matrix_Rotate(45.0f);
				player->pBody.velocity = CP_Vector_MatrixMultiply(rotatedir, CP_Vector_Set(0.0f, 1.0f));

				//player->rotation = 225.0f;
			}
			if (CP_Input_KeyTriggered(KEY_SPACE) && (player->numDodge > 0))
			{
				player->numDodge -= 1;
				if (playerState == STILL)
				{
					CP_Matrix rotatedir = CP_Matrix_Rotate(player->pBody.rotation); //rotation matrix
					CP_Vector dir = CP_Vector_MatrixMultiply(rotatedir, CP_Vector_Set(0.0f, -1.0f)); //rotate based off (0,1) to get direction vector
					player->pBody.velocity = dir;
				}

				player->pBody.velocity.x = player->pBody.velocity.x * (PLAYER_SPEED * CP_System_GetDt() * (dodgeDistance / 20));
				player->pBody.velocity.y = player->pBody.velocity.y * (PLAYER_SPEED * CP_System_GetDt() * (dodgeDistance / 20));
				playerState = DODGING;
			}
			if (playerState != DODGING)
			{
				player->pBody.velocity.x = (player->pBody.velocity.x * PLAYER_SPEED * CP_System_GetDt());
				player->pBody.velocity.y = (player->pBody.velocity.y * PLAYER_SPEED * CP_System_GetDt());
			}
		}
	}

	bool playerBossCol;
	switch (GetGameState())
	{
	case SCR_TUTORIAL:
		GridCollisionCheck(&(player->pBody));
		break;
	case SCR_LEVEL1:
		playerBossCol = PlayerEntityCollision(&player->pBody, &ArmorSlime.BossBody);
		GridCollisionCheck(&(player->pBody));
		if (playerBossCol == true && playerState == DODGING)
		{
			player->pBody.velocity = CP_Vector_Set(0.0f, 0.0f);
		}
		break;
	case SCR_LEVEL2:
		playerBossCol = PlayerEntityCollision(&player->pBody, &Boss2.BossBody);
		GridCollisionCheck(&(player->pBody));
		if (playerBossCol == true && playerState == DODGING)
		{
			player->pBody.velocity = CP_Vector_Set(0.0f, 0.0f);
		}
		break;
	default:
		break;
	}
	Dodge(player);

	player->pBody.hitbox.position.x += player->pBody.velocity.x;		//Circle
	player->pBody.hitbox.position.y += player->pBody.velocity.y;
}

void Dodge(Player* player) //Player dodge
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
			dodgeBlur = 20;
			playerState = STILL;
		}
		
		if (player->arrow.arrowState == WITHENTITY)
		{
			player->arrow.aBody.hitbox.position = player->pBody.hitbox.position;
		}
	}
		
}

void DodgeRecharge(Player* player) //Recharge Player Dodge
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

bool ArrowTrigger(Player* player) //Fucntion for arrow
{
	if (player->arrow.arrowState == WITHENTITY)
	{
		if (CP_Input_MouseDown(MOUSE_BUTTON_LEFT))
		{
			player->pBody.velocity.x = 0.0f;
			player->pBody.velocity.y = 0.0f;
			player->arrow.charging = 1;
			if (player->arrow.charge <= (MAX_FORCE - DEFAULT_FORCE))
			{
				player->arrow.charge += CP_System_GetDt() * 10;
				return true;
			}

		}
		else if (CP_Input_MouseReleased(MOUSE_BUTTON_LEFT))
		{
			if (player->arrow.charging == 1)
			{
				player->arrow.arrowState = RELEASE;
				CP_Vector target = CP_Vector_Set(CP_Input_GetMouseWorldX(), CP_Input_GetMouseWorldY());
				CalculateRelease(&player->arrow, &player->pBody, target);
				player->arrow.charging = 0;
				return false;
			}
		}
	}

	else if (playerState == MOVING || playerState == DODGING)
	{
		player->arrow.charge = 0.0f;
		player->arrow.charging = 0;
	}
	return false;
}

//end me now
//Collision with Boss 1
bool ArrowBoss1Collision(Arrow* arrow, Body* bBody)
{
	bool dealdamage = false;
	if (COL_IsColliding(arrow->aBody.hitbox, bBody->hitbox))
	{
		
		float offset = (arrow->aBody.hitbox.radius + bBody->hitbox.radius) - CP_Vector_Distance(arrow->aBody.hitbox.position, bBody->hitbox.position);
		CP_Vector offsetv = CP_Vector_Negate(CP_Vector_Scale(arrow->aBody.velocity, offset / CP_Vector_Length(arrow->aBody.velocity)));
		arrow->aBody.hitbox.position = CP_Vector_Add(arrow->aBody.hitbox.position, offsetv);

		CP_Vector differences = CP_Vector_Subtract(arrow->aBody.hitbox.position, bBody->hitbox.position); //Vector from arrow position to boss position
		CP_Matrix rotatedir = CP_Matrix_Rotate(bBody->rotation); //rotation matrix
		CP_Vector dir = CP_Vector_MatrixMultiply(rotatedir, CP_Vector_Set(0.0f, 1.0f)); //rotate based off (0,1) to get direction vector 
		float theta = CP_Vector_Angle(differences, dir); //angle between dir vector and arrow vector
		//r = d-2(d.n)n
		//CP_Sound_Play(ReflectSFX);
		CP_Vector normal = CP_Vector_Normalize(differences);
		//CP_Vector resultantVector = ArrowReflection(&arrow->aBody, normal);
		float dotproduct = CP_Vector_DotProduct(arrow->aBody.velocity, normal);
		CP_Vector resultantVector = CP_Vector_Subtract(arrow->aBody.velocity, CP_Vector_Scale(normal, 2 * dotproduct));
		arrow->aBody.velocity = resultantVector;
		//Adjust arrow rotation Here
		CalculateRotation(&arrow->aBody, arrow->aBody.velocity);
		//arrow->aBody.hitbox.position = CP_Vector_Add(CP_Vector_Add(arrow->aBody.hitbox.position, CP_Vector_Scale(resultantVector, 10)), bBody->velocity);

		if (theta >= 150.0f) //Assumes gap is 60 degress wide, May need adjusting
		{
			dealdamage = true;
			return dealdamage;
		}

	}
	return dealdamage;
}

//Check Arrow State and adjust position
bool ArrowStateCheck(Body* pBody, Body* bBody, Arrow* arrow)
{
	bool arrowBossCol = false;
	switch (arrow->arrowState)
	{
	case RELEASE:
		arrow->arrowState = MOTION;

		break;
	case MOTIONLESS:
		ArrowPickup(arrow, pBody); //pickup arrow
		IdleArrowCollision_Circle(&arrow->aBody, bBody);
		if (CP_Input_MouseTriggered(MOUSE_BUTTON_RIGHT)) // && !COL_IsColliding(arrow->aBody.hitbox, bBody->hitbox)
		{
			printf("\n");
			CalculateRecall(arrow, pBody);
			arrow->arrowState = RECALL;
		}
		break;
	case WITHENTITY:
		pickuptimer = 0;
		arrow->aBody.hitbox.position = pBody->hitbox.position;
		MouseTracking(&arrow->aBody);
		break;
	default:
		break;
	}

	if (arrow->arrowState == MOTION || arrow->arrowState == RECALL)
	{
		pickuptimer += CP_System_GetDt();
		if (pickuptimer > 0.5f)
		{
			ArrowPickup(arrow, pBody); //pickup arrow
		}
		arrowBossCol = ArrowBoss1Collision(arrow, bBody);
		ArrowInMotion(arrow);
	}
	return arrowBossCol;
}

/*Update Player*/
void PlayerUpdate(Player* player)
{
	MouseTracking(&player->pBody);
	if (player->health == 1)
	{
		PlayerMovement(player);
		ArrowTrigger(player);
	}
	else //Player death
	{
		SetGameOver(false);
		PlayerMovement(player);
		ArrowTrigger(player);
	}
}

void PlayerExit()
{
	CP_Image_Free(&sprite);
}