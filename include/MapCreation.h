#ifndef _PADDLE_H_
#define _PADDLE_H_
const int mapWidth = 28;
const int mapHeight = 36;

class TileProperties
{
public:

	bool bWall;
	int	iTileX;
	int iTileY;
	
	int GetTile(int x, int y);
	void SetTile(char* imagePath, int tileX, int tileY);

private:
	int SpriteID = 0;
	
};

#endif