

typedef enum //wtf
{
	COL_RECT,
	COL_CIRCLE

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
