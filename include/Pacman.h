#ifndef _PACMAN_H_
#define _PACMAN_H_

class PacmanProperties
{
public:
	
	void initialise()
	{
		for (int i = 0; i < 4; ++i)
		{
			playerDirection[i] = false;
		}
		moving = false;
	}

	int lives;
	float fX = 32;
	float fY = 64;
	int SpriteID;
	int SpriteWidth = 16;
	float fTimer = 0;

	bool moving;
	bool playerDirection[4];
	int nextTile;
	int tileWidths = 16;
	int mapXPos;
	int mapYPos;

	//Tiles
	int tileTop;
	int tileLeft;
	int tileRight;
	int tileBottom;
	int tileCurrent;

	void CreatePacman();
	int GetTile(int x, int y);
	void GetTiles();
	void SetPlayerDirection(PacmanProperties& pacSprite, float movementspeed, short a_upKey, short a_downKey, short a_leftKey, short a_rightKey);
	void MovePlayer(PacmanProperties& pacSprite, float movementspeed);
	void SetLives();
	void SetSpriteFrame();

private:
	
};

#endif