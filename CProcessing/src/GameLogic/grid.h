#pragma once
#include "Collider.h"
#include <stdbool.h>

/*-------------------------
This is for casting a grid
--------------------------*/
//DEFAULT VARIABLES

//#define GRID_MAXWIDTH 200							//Set the horizontal length
//#define GRID_MAXHEIGHT 200							//Set the vertical length

#define GRID_UNIT_WIDTH 50	
#define GRID_UNIT_HEIGHT 50	

#define GRID_SIZE GRID_WIDTH*GRID_HEIGHT		//Total size

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
	GA_PORTAL

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

	Collider collider;

	GRID_ELEMENTS gridType;

	GRID_ASSET gridAsset;

}GridUnit;

//DATA FOR MAP
char* levelData;

//THE ARRAY FOR THE LEVEL, USE THIS TO REFERENCE THE LEVEL
GridUnit** level;//[GRID_MAXWIDTH][GRID_MAXHEIGHT];

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