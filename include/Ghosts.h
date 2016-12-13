#ifndef _GHOSTS_H_
#define _GHOSTS_H_


class GhostProperties
{
public:
	void initialise()
	{
		for (int i = 0; i < 4; ++i)
		{
			ghostDirection[i] = false;
		}
		moving = false;
	}

	
	float fX = 128;
	float fY = 64;
	int SpriteID;
	int iGhostWidth = 16;
	int lastDirection;
	int randomDirection;

	int cageTime;
	int cageX;
	int cageY;
	bool moving;
	bool ghostDirection[4];
	int nextTile;
	int tileWidths = 16;

	void CreateGhost(int ghostType);
	int GetTile(int x, int y);
	void GetTiles();
	int GetDirection();
	void SetGhostDirection(GhostProperties& ghostSprite, float movementspeed);
	void MoveGhost(GhostProperties& ghostSprite, float movementspeed);
	bool Pacmancollide(GhostProperties& ghostSprite,int x, int y);
	void SetCageTime();
	//Tiles
	int tileTop;
	int tileLeft;
	int tileRight;
	int tileBottom;
	int tileCurrent = 2;

private:

};

#endif