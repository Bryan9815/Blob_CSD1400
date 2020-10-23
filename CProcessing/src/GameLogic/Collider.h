

typedef enum //wtf
{
	COL_CIRCLE,
	COL_RECT

}COL_SHAPE;

typedef struct //wtf
{
	float posX,
		  posY;

	float width,
		  height,
		  radius;

	COL_SHAPE shapeType;

}Collider;
