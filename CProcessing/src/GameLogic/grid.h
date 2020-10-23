
/*-------------------------
This is for casting a grid
--------------------------*/

#define GRID_WIDTH 200							//Set the horizontal length
#define GRID_HEIGHT 200							//Set the vertical length

#define GRID_UNIT_WIDTH 50	
#define GRID_UNIT_HEIGHT 50	

#define GRID_SIZE GRID_WIDTH*GRID_HEIGHT		//Total size

//Grid that stores the GRID_ELEMENTS type
typedef enum 
{
	GE_VOID,
	GE_FlOOR,
	GE_WALL,	

}GRID_ELEMENTS;


typedef enum
{
	Level0,
	Level1,
	Level2,

}MAP;

int GetLevelWidth();
int GetLevelHeight();
void LoadMapFile(MAP level);
void GridInit(GRID_ELEMENTS* grid);
void GridUpdate(GRID_ELEMENTS* grid);