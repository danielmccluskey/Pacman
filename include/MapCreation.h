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
	//Variables to hold the current position in the map
	int	iTileX;
	int iTileY;
	
	int GetTile(int a_iX, int a_iY);//Function to get a tile from the tilemap at given X,Y Pos
	void SetTile(char* a_cImagePath, int a_iTileX, int a_iTileY);//Sets the tile at the given X,Y Pos to given image by creating a sprite
	void DrawMap();//Draws all the sprites

private:
	int iSpriteID = 0;//Sprite ID
	
};

#endif //_PADDLE_H_