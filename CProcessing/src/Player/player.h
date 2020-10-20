typedef struct
{
	float speed;

	int velX, 
		velY;

} Player;

Player CreatePlayer();

void PlayerUpdate(Player player);
