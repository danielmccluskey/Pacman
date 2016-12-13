//==============================================================================================================================
// Project: Pacman
// File: GameStates.h
// Author: Daniel McCluskey
// Date Created: 17/10/16
// Brief: This is the header file that contains the code to control all of the Menu sprites.
// Last Edited by: (See BitBucket Commits: https://bitbucket.org/Danielmclovin/ct4019-pacman)
//==============================================================================================================================
#ifndef _GAMESTATES_H_
#define _GAMESTATES_H_


class GameStateProperties
{
public:
	void CreateSprite(char* a_cImagePath, int a_iX, int a_iY, int iSizeX, int iSizeY);
	void ShowSprite();
	void HideSprite();
	int iSpriteID = 0;
private:
	

};

#endif //_GAMESTATES_H_