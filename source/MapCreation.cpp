#include "UGFW.h"
#include "MapCreation.h"

int map[mapWidth * mapHeight] = {

	8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
	8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
	6,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,5,
	2,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,1,
	2,8,12,0,0,0,0,0,0,0,0,9,8,12,9,8,12,0,0,0,0,0,0,0,0,9,8,1,
	2,8,11,3,3,3,3,5,6,3,3,10,8,1,2,8,11,3,3,5,6,3,3,3,3,10,8,1,
	2,8,8,8,8,8,8,1,2,8,8,8,8,1,2,8,8,8,8,1,2,8,8,8,8,8,8,1,
	7,0,9,8,12,9,8,1,2,8,12,0,0,4,7,0,0,9,8,1,2,8,12,9,8,12,0,4,
	6,3,10,8,1,2,8,11,10,8,11,3,3,3,3,3,3,10,8,11,10,8,1,2,8,11,3,5,
	2,8,8,8,1,2,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,1,2,8,8,8,1,
	2,8,12,0,4,2,8,12,0,0,0,9,8,12,9,8,12,0,0,0,9,8,1,7,0,9,8,1,
	2,8,11,3,3,10,8,11,3,3,3,10,8,1,2,8,11,3,3,3,10,8,11,3,3,10,8,1,
	2,8,8,8,8,8,8,8,8,8,8,8,8,1,2,8,8,8,8,8,8,8,8,8,8,8,8,1,
	7,0,0,0,0,9,8,12,9,8,12,0,0,4,7,0,0,9,8,12,9,8,12,0,0,0,0,4,
	8,8,8,8,8,2,8,1,2,8,11,3,3,3,3,3,3,10,8,1,2,8,1,8,8,8,8,8,
	8,8,8,8,8,2,8,1,2,8,8,8,8,8,8,8,8,8,8,1,2,8,1,8,8,8,8,8,
	8,8,8,8,8,2,8,1,2,8,12,0,0,0,0,0,0,9,8,1,2,8,1,8,8,8,8,8,
	6,3,3,3,3,10,8,11,10,8,1,8,8,8,8,8,8,2,8,11,10,8,11,3,3,3,3,5,
	2,8,8,8,8,0,8,8,8,8,1,8,8,8,8,8,8,2,8,8,8,8,8,0,8,8,8,1,
	7,0,0,0,0,9,8,12,9,8,1,8,8,8,8,8,8,2,8,12,9,8,12,0,0,0,0,4,
	8,8,8,8,8,2,8,1,2,8,11,3,3,3,3,3,3,10,8,1,2,8,1,8,8,8,8,8,
	8,8,8,8,8,2,8,1,2,8,8,8,8,8,8,8,8,8,8,1,2,8,1,8,8,8,8,8,
	8,8,8,8,8,2,8,1,7,0,0,9,8,12,9,8,12,0,0,4,2,8,1,8,8,8,8,8,
	6,3,3,3,3,10,8,1,6,3,3,10,8,1,2,8,11,3,3,5,2,8,11,3,3,3,3,5,
	2,8,8,8,8,8,8,1,2,8,8,8,8,1,2,8,8,8,8,1,2,8,8,8,8,8,8,1,
	2,8,12,0,0,9,8,1,2,8,12,0,0,4,7,0,0,9,8,1,2,8,12,0,0,9,8,1,
	2,8,11,3,3,10,8,11,10,8,11,3,3,3,3,3,3,10,8,11,10,8,11,3,3,10,8,1,
	2,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,1,
	2,8,12,0,0,9,8,12,0,0,0,9,8,12,9,8,12,0,0,0,9,8,12,0,0,9,8,1,
	2,8,1,8,8,2,8,1,8,8,8,2,8,1,2,8,1,8,8,8,2,8,1,8,8,2,8,1,
	2,8,11,3,3,10,8,11,3,3,3,10,8,1,2,8,11,3,3,3,10,8,11,3,3,10,8,1,
	2,8,8,8,8,8,8,8,8,8,8,8,8,1,2,8,8,8,8,8,8,8,8,8,8,8,8,1,
	7,0,0,0,0,0,0,0,0,0,0,0,0,4,7,0,0,0,0,0,0,0,0,0,0,0,0,4,
	8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
	8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
	8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8
};


void TileProperties::SetTile(char* imagePath, int iTileX, int iTileY)
{
	int tileX = (iTileX * 16) + 15;
	int tileY = (iTileY * 16) + 15;
	int SpriteID = UG::CreateSprite(imagePath, 16, 16, true);
	UG::MoveSprite(SpriteID, tileX, tileY);
	UG::DrawSprite(SpriteID);
}


int TileProperties::GetTile(int x, int y)
{
	return map[(y*mapWidth) + x];
}

