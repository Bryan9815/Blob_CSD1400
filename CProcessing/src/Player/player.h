#include <cprocessing.h>
typedef struct
{
	float		speed,
				width,
				rotation;
	CP_Vector	position;
	int			velX,
				velY;
	//CP_Image sprite;

} Player;

void CreatePlayer(Player* player);
void PlayerUpdate(Player player);
void PlayerMovement(Player* player);
