//==============================================================================================================================
// Project: Pacman
// File: MapCreation.h
// Author: Daniel McCluskey
// Date Created: 17/10/16
// Brief: This is the header file that contains the code that draws the "Maze" of the Pacman game.
// Last Edited by: (See BitBucket Commits: https://bitbucket.org/Danielmclovin/ct4019-pacman)
//==============================================================================================================================
#ifndef _PADDLE_H_
#define _PADDLE_H_
const int iMapWidth = 28;
const int iMapHeight = 36;

class TileProperties
{
public:

	bool bWall;
	int	iTileX;
	int iTileY;
	
	int GetTile(int a_iX, int a_iY);
	void SetTile(char* a_cImagePath, int a_iTileX, int a_iTileY);
	void DrawMap();

private:
	int iSpriteID = 0;
	
};

#endif //_PADDLE_H_