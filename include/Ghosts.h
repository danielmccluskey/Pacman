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


	float ghostXPos = 128;
	float ghostYPos = 64;
	int SpriteID;
	int iGhostWidth = 16;

	bool moving;
	bool ghostDirection[4];
	int nextTile;
	int tileWidths;

	void CreateGhost(int ghostType);
	int GetTile(int x, int y);
	void SetGhostDirection(GhostProperties& ghostSprite, float movementspeed, short a_upKey, short a_downKey, short a_leftKey, short a_rightKey, int tileTop, int tileRight, int tileLeft, int tileBottom);
	void MoveGhost(GhostProperties& ghostSprite, float movementspeed, int tileTop, int tileRight, int tileLeft, int tileBottom);

private:

};

#endif