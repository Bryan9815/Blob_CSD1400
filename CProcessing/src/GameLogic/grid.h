
/*-------------------------
This is for casting a grid
--------------------------*/

#define GRID_WIDTH 40							//Set the horizontal length
#define GRID_HEIGHT 40							//Set the vertical length

#define GRID_UNIT_WIDTH 50	
#define GRID_UNIT_HEIGHT 50	

#define GRID_SIZE GRID_WIDTH*GRID_HEIGHT		//Total size

//Grid that stores the GRID_ELEMENTS type
typedef enum 
{
	GE_VOID,		
	GE_WALL,	

}GRID_ELEMENTS;

void GridInit(GRID_ELEMENTS* grid, int w, int h);
void GridUpdate(GRID_ELEMENTS* grid, int w, int h);