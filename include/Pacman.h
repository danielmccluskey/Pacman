//==============================================================================================================================
// Project: Pacman
// File: Pacman.h
// Author: Daniel McCluskey
// Date Created: 17/10/16
// Brief: This is the header file that contains the code that controls the mechanics and behaviour of Pacman during Gameplay.
// Last Edited by: (See BitBucket Commits: https://bitbucket.org/Danielmclovin/ct4019-pacman)
//==============================================================================================================================
#ifndef _PACMAN_H_
#define _PACMAN_H_

class PacmanProperties
{
public:
	
	void initialise()
	{
		for (int i = 0; i < 4; ++i)
		{
			bPlayerDirection[i] = false;
		}
		bMoving = false;
	}

	bool bCanEatGhosts = false;

	int iLives;
	float fX = 32;
	float fY = 64;
	int iSpriteID;

	bool bMoving;
	bool bPlayerDirection[4];
	int iNextTile;
	int iTileWidths = 16;
	int iMapXPos;
	int iMapYPos;
	float fEatGhostsTimer = 0;

	

	void CreatePacman();
	int GetTile(int a_iX, int a_iY);
	void GetTiles();
	void SetPlayerDirection(PacmanProperties& a_pacSprite, float a_fMovementSpeed, short a_upKey, short a_downKey, short a_leftKey, short a_rightKey);
	void MovePlayer(PacmanProperties& a_pacSprite, float a_fMovementSpeed);
	void SetLives(PacmanProperties& a_pacSprite);
	void SetSpriteFrame();
	void SetEatGhostsTimer(int a_iA, int a_iB, int a_iC, int a_iD);

private:
	//Tiles
	int iTileTop;
	int iTileLeft;
	int iTileRight;
	int iTileBottom;
	int iTileCurrent;

	float fTimer = 0;

	

	int iSpriteWidth = 16;
};

#endif //_PACMAN_H_