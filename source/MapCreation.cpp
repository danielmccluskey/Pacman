#include "UGFW.h"
#include "MapCreation.h"
#include "CustomEnum.h"

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
	3,3,3,3,3,10,8,11,10,8,1,8,8,8,8,8,8,2,8,11,10,8,11,3,3,3,3,3,
	8,8,8,8,8,8,8,8,8,8,1,8,8,8,8,8,8,2,8,8,8,8,8,8,8,8,8,8,
	0,0,0,0,0,9,8,12,9,8,1,8,8,8,8,8,8,2,8,12,9,8,12,0,0,0,0,0,
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

void TileProperties::DrawMap()
{
	//The following is the code that draws out the tiles from the Array map
	for (int y = 0; y < mapHeight; ++y)  //Counts through the Y axis of the array each time the X axis completes a row
	{
		for (int x = 0; x < mapWidth; ++x) //Counts through the X axis
		{
			int tileType = GetTile(x, y); //Finds what type of tile needs to be placed at current place in map.

			switch (tileType) //Switch statement to actually create the tiles and draw them.
			{
			case bottom:
			{

				SetTile("./images/walls/bottom.png", x, y);

			}
			break;
			case left:
			{
				SetTile("./images/walls/left.png", x, y);

			}
			break;
			case right:
			{
				SetTile("./images/walls/right.png", x, y);
			}
			break;
			case top:
			{
				SetTile("./images/walls/top.png", x, y);
			}
			break;
			case blank:
			{
				SetTile("./images/blank.png", x, y);
			}
			break;
			case corner1:
			{
				SetTile("./images/corners/1.png", x, y);
			}
			break;
			case corner2:
			{
				SetTile("./images/corners/2.png", x, y);
			}
			break;
			case corner3:
			{
				SetTile("./images/corners/3.png", x, y);
			}
			break;
			case corner4:
			{
				SetTile("./images/corners/4.png", x, y);
			}
			break;
			case island1:
			{
				SetTile("./images/islands/1.png", x, y);
			}
			break;
			case island2:
			{
				SetTile("./images/islands/2.png", x, y);
			}
			break;
			case island3:
			{
				SetTile("./images/islands/3.png", x, y);
			}
			break;
			case island4:
			{
				SetTile("./images/islands/4.png", x, y);
			}
			break;
			}
		}
	}
}


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

