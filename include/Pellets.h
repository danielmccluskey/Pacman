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

	


	float fX;
	float fY;
	int iSpriteID = -1;
	int iSpriteWidth = 16;
	int iCurrentHighScore;
	int iMapWidth = 28;
	int iMapHeight = 36;
	
	int iNextTile;

	int iTotalScore = 0;
	int iTotalPellets = 0;

	void CreatePellet(char* a_cImagePath, int a_iTileX, int a_iTileY);
	void DrawPellets(PelletProperties *a_pellet);
	PelletProperties& GetPellet(PelletProperties *a_pellet, int a_iX, int a_iY);
	int GetTile(int a_iX, int a_iY);
	bool DestroyPellets(PelletProperties *a_pellet, int a_iX, int a_iY);
	void FillPellets(PelletProperties *a_pellet);
	void SetHighScore();
	void GetHighScore();
	void DrawHighScore();
	void ClearHighScore();

private:

};

#endif //_PELLETS_H_