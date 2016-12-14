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
	//Reset directional and movement values
	void initialise()
	{
		for (int i = 0; i < 4; ++i)
		{
			bGhostDirection[i] = false;
		}
		bMoving = false;
	}

	
	
	int iSpriteID;//SpriteID
	int iLastDirection;//Stores the last direction the ghost was travelling
	int iRandomDirection;//Stores the random direction of the ghost

	int iCageTime;//Stores the remaining time left in the cage of the ghost
	int iCageX;//Stores the XPos of the ghost when in the cage
	int iCageY;//Stores the YPos of the ghost when in the cage
	bool bMoving;//Controls whether the ghost can move
	bool bGhostDirection[4];//Variable to sotre the current direction
	int iNextTile;//Stores the next tile the ghost should move to
	int iTileWidths = 16;//Stores the width of the tiles

	//Positional values
	float fX = 128;
	float fY = 64;

	void CreateGhost(int a_iGhostType);//Function to create the Ghosts
	int GetTile(int a_iX, int a_iY);//Function to get the tile from the collision map at given X,Y Pos
	void GetTiles();//Gets all the tiles around the ghost
	int GetDirection();//Gets the current direction of the ghost as an integer value
	void SetGhostDirection(GhostProperties& a_ghostSprite, float a_fMovementspeed);//Sets the direction of the ghost based off of a randomly chosen direction
	void MoveGhost(GhostProperties& a_ghostSprite, float a_fMovementspeed);//Moves the ghost in the randomly chosen direction
	bool Pacmancollide(GhostProperties& a_ghostSprite, float a_fX, float a_fY);//Checks to see if the ghost has collided with pacman
	void SetCageTime();//Controls the ghost in the cage and releases it
	void SetEdibleGhostsPos(GhostProperties& a_ghost);//Moves edible ghosts to their relative ghost
	

private:
	//Variables to store the tiles currently around the pacman sprite
	int iTileTop;
	int iTileLeft;
	int iTileRight;
	int iTileBottom;
	int iTileCurrent = 2;

	int iGhostWidth = 16;//Width of the sprite
};

#endif //_GHOSTS_H_