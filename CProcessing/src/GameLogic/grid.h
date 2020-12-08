//---------------------------------------------------------
// file:	grid.h
// author:	[Phang Jia Rong]
// email:	[jiarong.phang@digipen.edu]
//
// brief:	Header file for grid.c
//
//
// Copyright � 2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#pragma once
#include "Collider.h"
#include <stdbool.h>

/*-------------------------
This is for casting a grid
--------------------------*/
//DEFAULT VARIABLES

#define GRID_UNIT_WIDTH 50		//Unit width of one unit of the grid
#define GRID_UNIT_HEIGHT 50		//Unit height of one unit of the grid

#define GRID_SIZE GRID_WIDTH*GRID_HEIGHT	//Total size of grid	

//ENUMS that stores the GRID type
typedef enum 
{
	GE_VOID,
	GE_FLOOR,
	GE_WALL,
	GE_DAMAGE,
	GE_PIT,
	GE_SWITCH,
	GE_DOOR,
	GE_PORTAL,	
	GE_PILLAR,
}GRID_ELEMENTS;

//ENUMS that stores the GRID ASSET
typedef enum
{
	GA_VOID,
	GA_FLOOR,
	GA_WALL1,
	GA_WALL2,
	GA_WALL3,
	GA_DAMAGE1,
	GA_PIT,
	GA_SWITCH,
	GA_DOOR,
	GA_PORTAL,
	GA_PILLAR,
}GRID_ASSET;

//ENUM FOR LEVEL DATA
typedef enum
{
	Level0,
	Level1,
	Level2,

}MAP;

//STRUCT for individual GridUnit
typedef struct 
{
	bool isActive;
	bool isCollidable;
	int hp;
	Collider collider;

	GRID_ELEMENTS gridType;

	GRID_ASSET gridAsset;

}GridUnit;

//DATA FOR MAP
char* levelData;

//The pointer for the level, USE THIS TO REFERENCE THE LEVEL
GridUnit** level;

//NOTE: NOT THIS SIZE IS NOT BY PIXEL SIZE BUT BY NUMBER OF ELEMENTS, THIS IS THE LEVEL AS A FULL RECTANGLE, INCLUDING EMPTY ELEMENTS. 

int GetLevelWidth();	//RETURN LEVEL WIDTH
int GetLevelHeight();	//RETURN LEVEL HEIGHT

//NOTE: CALL THIS FUNCTION BEFORE GRIDINIT, THIS LOADS THE MAP for Initializing
void LoadMapFile(MAP level);

//GRID FUNCTION CALLS
void GridInit();
void GridDraw(Collider playerHitBox);
void GridUpdate(Collider playerHitBox, Collider arrowHitBox);
void GridExit();

GridUnit * GetGridUnit(int x, int y);