//==============================================================================================================================
// Project: Pacman
// File: Ghosts.h
// Author: Daniel McCluskey
// Date Created: 17/10/16
// Brief: This is the header file that contains the code that controls the behaviour and mechanics of the ghosts during Gameplay.
// Last Edited by: (See BitBucket Commits: https://bitbucket.org/Danielmclovin/ct4019-pacman)
//==============================================================================================================================
#ifndef _GHOSTS_H_
#define _GHOSTS_H_


class GhostProperties
{
public:
	void initialise()
	{
		for (int i = 0; i < 4; ++i)
		{
			bGhostDirection[i] = false;
		}
		bMoving = false;
	}

	
	float fX = 128;
	float fY = 64;
	int iSpriteID;
	int iGhostWidth = 16;
	int iLastDirection;
	int iRandomDirection;

	int iCageTime;
	int iCageX;
	int iCageY;
	bool bMoving;
	bool bGhostDirection[4];
	int iNextTile;
	int iTileWidths = 16;

	void CreateGhost(int a_iGhostType);
	int GetTile(int a_iX, int a_iY);
	void GetTiles();
	int GetDirection();
	void SetGhostDirection(GhostProperties& a_ghostSprite, float a_fMovementspeed);
	void MoveGhost(GhostProperties& a_ghostSprite, float a_fMovementspeed);
	bool Pacmancollide(GhostProperties& a_ghostSprite,int a_iX, int a_iY);
	void SetCageTime();
	void SetEdibleGhostsPos(GhostProperties& a_ghost);
	

private:
	//Tiles
	int iTileTop;
	int iTileLeft;
	int iTileRight;
	int iTileBottom;
	int iTileCurrent = 2;
};

#endif //_GHOSTS_H_