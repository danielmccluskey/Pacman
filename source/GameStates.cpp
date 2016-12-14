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

void GameStateProperties::CreateSprite(char* a_cImagePath, float a_fX, float a_fY, float a_fSizeX, float a_fSizeY)
{
	//Create the sprite and move it to the specified position
	iSpriteID = UG::CreateSprite(a_cImagePath, a_fSizeX, a_fSizeY, true);
	UG::MoveSprite(iSpriteID, a_fX, a_fY);

}

void GameStateProperties::ShowSprite()
{
	//Draws the sprite
	UG::ClearScreen();
	UG::DrawSprite(iSpriteID);
}

void GameStateProperties::HideSprite()
{
	//Hides the sprite
	UG::StopDrawingSprite(iSpriteID);
	UG::ClearScreen();
}
