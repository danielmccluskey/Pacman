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
	
	//Reset directional and movement values
	void initialise()
	{
		for (int i = 0; i < 4; ++i)
		{
			bPlayerDirection[i] = false;
		}
		bMoving = false;
	}

	bool bCanEatGhosts = false;//Controls whether the pacman dies or eats when colliding with ghosts
	int iLives;//Stores the amount of lives the player has	
	int iSpriteID;//SpriteID
	bool bMoving;//Controls the player movement
	bool bPlayerDirection[4];//Controls the players direction
	int iNextTile;//Stores the next tile the player moves to
	int iTileWidths = 16;//Stores the width of a tile
	float fEatGhostsTimer = 0;//Stores the time left that pacman can eat ghosts

	//Positional values relative to the collision map
	int iMapXPos;
	int iMapYPos;
	
	//Positional values
	float fX = 32;
	float fY = 64;
	

	void CreatePacman();//Function to create the pacman
	int GetTile(int a_iX, int a_iY);//Function to get the tile from the Pacman collision map from given X,Y Pos
	void GetTiles();//Gets the tiles surrounding the pacman sprite
	void SetPlayerDirection(PacmanProperties& a_pacSprite, float a_fMovementSpeed, short a_upKey, short a_downKey, short a_leftKey, short a_rightKey);//Function to set the direction of the pacman sprite depending on keypress
	void MovePlayer(PacmanProperties& a_pacSprite, float a_fMovementSpeed);//Moves pacman sprite
	void SetLives(PacmanProperties& a_pacSprite);//Function to handle death of pacman
	void SetSpriteFrame();//Function to handle animated frames of pacman
	void SetEatGhostsTimer(int a_iA, int a_iB, int a_iC, int a_iD);//Function to handle the edible ghosts rendering

private:
	//Variables to store the tiles currently around the pacman sprite
	int iTileTop;
	int iTileLeft;
	int iTileRight;
	int iTileBottom;
	int iTileCurrent;

	float fTimer = 0;//Timer for the animated frames
	int iSpriteWidth = 16;//Width of the sprite
};

#endif //_PACMAN_H_