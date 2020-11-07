#pragma once
#include "Collider.h"
/*-------------------------
This is for casting a grid
--------------------------*/
//DEFAULT VARIABLES

#define GRID_WIDTH 200							//Set the horizontal length
#define GRID_HEIGHT 200							//Set the vertical length

#define GRID_UNIT_WIDTH 50	
#define GRID_UNIT_HEIGHT 50	

#define GRID_SIZE GRID_WIDTH*GRID_HEIGHT		//Total size

//Grid that stores the GRID_ELEMENTS type
typedef enum 
{
	GE_VOID,
	GE_FLOOR,
	GE_WALL,	

}GRID_ELEMENTS;

typedef enum
{
	GA_VOID,
	GA_FLOOR,
	GA_WALL1,
	GA_WALL2,
	GA_WALL3,

}GRID_ASSET;

typedef enum
{
	Level0,
	Level1,
	Level2,

}MAP;

typedef struct 
{
	Collider collider;

	GRID_ELEMENTS gridType;

	GRID_ASSET gridAsset;

}GridUnit;

GridUnit level[GRID_WIDTH][GRID_HEIGHT];

int GetLevelWidth();
int GetLevelHeight();
void LoadMapFile(MAP level);
void GridInit(GridUnit* grid);
void GridUpdate(GridUnit* grid, Collider playerHitBox);
void GridExit();