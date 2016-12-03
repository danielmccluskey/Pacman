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


	float fX = 32;
	float fY = 64;
	int SpriteID;
	int SpriteWidth = 16;

	bool moving;
	bool playerDirection[4];
	int nextTile;
	int tileWidths;



	void CreatePacman();
	void SetPlayerDirection(PacmanProperties& pacSprite, float movementspeed, short a_upKey, short a_downKey, short a_leftKey, short a_rightKey, int tileTop, int tileRight, int tileLeft, int tileBottom);
	void MovePlayer(PacmanProperties& pacSprite, float movementspeed, int tileTop, int tileRight, int tileLeft, int tileBottom);


private:
	
};

#endif