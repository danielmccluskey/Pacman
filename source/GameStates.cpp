//==============================================================================================================================
// Project: Pacman
// File: GameStates.cpp
// Author: Daniel McCluskey
// Date Created: 17/10/16
// Brief: This is the file that contains the code to control all of the Menu sprites.
// Last Edited by: (See BitBucket Commits: https://bitbucket.org/Danielmclovin/ct4019-pacman)
//==============================================================================================================================
#include "UGFW.h"
#include "Enumerations.h"
#include "CustomEnum.h"
#include "GameStates.h"

void GameStateProperties::CreateSprite(char* a_cImagePath, int a_iX, int a_iY, int iSizeX, int iSizeY)
{
	iSpriteID = UG::CreateSprite(a_cImagePath, iSizeX, iSizeY, true);
	UG::MoveSprite(iSpriteID, a_iX, a_iY);

}

void GameStateProperties::ShowSprite()
{
	UG::ClearScreen();
	UG::DrawSprite(iSpriteID);
}

void GameStateProperties::HideSprite()
{
	UG::StopDrawingSprite(iSpriteID);
	UG::ClearScreen();
}
