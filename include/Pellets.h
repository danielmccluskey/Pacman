//==============================================================================================================================
// Project: Pacman
// File: Pellets.h
// Author: Daniel McCluskey
// Date Created: 17/10/16
// Brief: This is the header file that contains the code that controls the mechanics of the pellets during Gameplay.
// Last Edited by: (See BitBucket Commits: https://bitbucket.org/Danielmclovin/ct4019-pacman)
//==============================================================================================================================
#ifndef _PELLETS_H_
#define _PELLETS_H_

class PelletProperties
{
public:
	float fX;//X position
	float fY;//Y Positon
	int iSpriteID = -1;//Sprite ID
	int iSpriteWidth = 16;//Width of the Sprite
	int iCurrentHighScore;//The current highscore read from a text file
	int iTotalScore = 0;//Holds the current score during gameplay
	int iTotalPellets = 0;//Holds the amount of pellets the player has eaten

	//Map Height and Width
	/*float fMapWidth = 28;
	float fMapHeight = 36;*/
	
	

	

	void CreatePellet(char* a_cImagePath, float a_fTileX, float a_fTileY);//Function to create the pellets from the pellet map
	void DrawPellets(PelletProperties *a_pellet);//Draws the pellets from the pellet map
	PelletProperties& GetPellet(PelletProperties *a_pellet, int a_iX, int a_iY);//Gets what pellet is currently being selected
	int GetTile(int a_iX, int a_iY);//Gets the tile from the pellet map
	bool DestroyPellets(PelletProperties *a_pellet, int a_iX, int a_iY);//Function to destroy and stop drawing pellets at given X,Y
	void FillPellets(PelletProperties *a_pellet);//Function to fill the empty pellet spaces in the map with pellets after the game has ended
	void SetHighScore();//Function that checks if the players score is higher than the highscore, if so, it replaces the highscore
	void GetHighScore();//Gets the highscore from a file
	void DrawHighScore();//Draws the highscore
	void ClearHighScore();//Clears the highscore from both the program and the file.

private:

};

#endif //_PELLETS_H_