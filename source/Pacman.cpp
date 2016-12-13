//==============================================================================================================================
// Project: Pacman
// File: Pacman.cpp
// Author: Daniel McCluskey
// Date Created: 17/10/16
// Brief: This is the header file that contains the code that controls the mechanics and behaviour of Pacman during Gameplay.
// Last Edited by: (See BitBucket Commits: https://bitbucket.org/Danielmclovin/ct4019-pacman)
//==============================================================================================================================
#include "Pacman.h"
#include "UGFW.h"
#include "stdlib.h"
#include "CustomEnum.h"
#include "windows.h"
#include <iostream>

int iPacmanMap[1008] =
{
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
	0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,
	0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,
	0,1,1,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,1,1,0,
	0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0,
	0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0,
	0,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,0,
	0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0,
	0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0,
	0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,
	0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,
	1,1,1,1,1,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,1,1,1,1,1,
	1,1,1,1,1,0,1,0,0,1,1,1,1,1,1,1,1,1,1,0,0,1,0,1,1,1,1,1,
	1,1,1,1,1,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,1,1,1,1,1,
	0,0,0,0,0,0,1,0,0,1,0,1,1,1,1,1,1,0,1,0,0,1,0,0,0,0,0,0,
	1,8,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,6,1,
	0,0,0,0,0,0,1,0,0,1,0,1,1,1,1,1,1,0,1,0,0,1,0,0,0,0,0,0,
	1,1,1,1,1,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,1,1,1,1,1,
	1,1,1,1,1,0,1,0,0,1,1,1,1,1,1,1,1,1,1,0,0,1,0,1,1,1,1,1,
	1,1,1,1,1,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,1,1,1,1,1,
	0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,
	0,1,1,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,1,1,0,
	0,1,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,1,0,
	0,1,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,1,0,
	0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
	0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0,
	0,1,0,1,1,0,1,0,1,1,1,0,1,0,0,1,0,1,1,1,0,1,0,1,1,0,1,0,
	0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0,
	0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
};
void PacmanProperties::SetSpriteFrame()
{
	fTimer += 0.2f;
	int iFirstFrame = 0;
	int iSecondFrame = 1;
	float iSpriteFrames[8][4] = 
	{
		{ 0.f,0.f,.5f,.25f}, //Up Open/
		{ 0.f,.5f,.5f,.75f },//Up Closed
		{ .5f,0.f,1.f,.25f },//East Open
		{ .5f,.5f,1.f,.75f },//East Closed
		{ 0.f,.25f,.5f,.5f },//South Open
		{ 0.f,.75f,.5f,1.f },//South Closed
		{ .5f,.25f,1.f,.5f },//West Open
		{ .5f,.75f,1.f,1.f }//West Closed
	};


	


	if (bPlayerDirection[north] == true)
	{
		iFirstFrame = 0;
		iSecondFrame = 1;		
	}
	else if (bPlayerDirection[south] == true)
	{
		iFirstFrame = 4;
		iSecondFrame = 5;
	}
	else if (bPlayerDirection[west] == true)
	{
		iFirstFrame = 6;
		iSecondFrame = 7;
	}
	else if (bPlayerDirection[east] == true)
	{
		iFirstFrame = 2;
		iSecondFrame = 3;
	}
	if (fTimer < 1)
	{
		UG::SetSpriteUVCoordinates(iSpriteID, iSpriteFrames[iFirstFrame]);
	}
	else
	{
		UG::SetSpriteUVCoordinates(iSpriteID, iSpriteFrames[iSecondFrame]);
	}
	if (fTimer > 2)
	{
		fTimer = 0;
	}
}

void PacmanProperties::SetEatGhostsTimer(int a_iA, int a_iB, int a_iC, int a_iD)
{
	if (fEatGhostsTimer > -1)
	{
		fEatGhostsTimer -= 0.1f;
	}
	
	if (fEatGhostsTimer < 0 && bCanEatGhosts == true)
	{
		bCanEatGhosts = false;
		UG::StopDrawingSprite(a_iA);
		UG::StopDrawingSprite(a_iB);
		UG::StopDrawingSprite(a_iC);
		UG::StopDrawingSprite(a_iD);
	}
}


void PacmanProperties::SetLives(PacmanProperties& a_pacSprite)
{
	--iLives;
	initialise();
	fX = 32;
	fY = 64;
	PlaySound(TEXT("./sounds/death.wav"), NULL, SND_FILENAME | SND_ASYNC);//Plays Death sound and Hangs program until finished
	bPlayerDirection[east] = true;
}

//Creating Sprite
void PacmanProperties::CreatePacman()
{
	iSpriteID = UG::CreateSprite("./images/pacman/pacmanSheet.png", iSpriteWidth, iSpriteWidth, true);
	UG::DrawSprite(iSpriteID);	
	initialise(); //Sets the variables for pacman. (Will move to class)
	UG::MoveSprite(iSpriteID, 32, 64); //Moves Pacman to starting Position
	UG::SetSpriteUVCoordinates(iSpriteID, .5f, .5f, 1.f, .75f);
	bPlayerDirection[east] = true;
}



int PacmanProperties::GetTile(int a_iX, int a_iY)
{
	return iPacmanMap[(a_iY * 28) + a_iX];
}
void PacmanProperties::GetTiles()
{
	iMapXPos = (fX) / iTileWidths;
	iMapYPos = (fY) / iTileWidths;
	iTileTop = GetTile(iMapXPos - 1, (iMapYPos));
	iTileLeft = GetTile((iMapXPos - 2), iMapYPos - 1);
	iTileRight = GetTile((iMapXPos), iMapYPos - 1);
	iTileBottom = GetTile(iMapXPos - 1, (iMapYPos - 2));
	iTileCurrent = GetTile((iMapXPos - 1), iMapYPos - 1);
}

void PacmanProperties::SetPlayerDirection(PacmanProperties& a_pacSprite, float a_fMovementSpeed, short a_upKey, short a_downKey, short a_leftKey, short a_rightKey)
{
	GetTiles();
	if (iTileRight == 8)
	{
		fX = 432;
		fY = 304;
		initialise();
		bPlayerDirection[west] = true;
	}
	if (iTileLeft == 6)
	{
		fX = 32;
		fY = 304;
		initialise();
		bPlayerDirection[east] = true;
	}
	if (bMoving == false)
	{

		if (UG::IsKeyDown(a_upKey) && iTileTop != 0)
		{
			initialise();
			bPlayerDirection[north] = true;
			std::cout << "UPP" << std::endl;
		}
		if (UG::IsKeyDown(a_downKey) && iTileBottom != 0)
		{
			initialise();
			bPlayerDirection[south] = true;
			std::cout << "DOWN" << std::endl;
		}
		if (UG::IsKeyDown(a_leftKey) && iTileLeft != 0)
		{
			initialise();
			bPlayerDirection[west] = true;
			std::cout << "LEFT" << std::endl;
		}
		if (UG::IsKeyDown(a_rightKey) && iTileRight != 0)
		{
			initialise();
			bPlayerDirection[east] = true;
			std::cout << "RIGHT" << std::endl;
		}


		if (bPlayerDirection[north] == true && iTileTop != 0)
		{
			iNextTile = fY + iTileWidths;
			bMoving = true;
		}
		else if (bPlayerDirection[south] == true && iTileBottom != 0)
		{
			iNextTile = fY - iTileWidths;
			bMoving = true;
		}
		else if (bPlayerDirection[west] == true && iTileLeft != 0)
		{
			iNextTile = fX - iTileWidths;
			bMoving = true;
		}
		else if (bPlayerDirection[east] == true && iTileRight != 0)
		{
			iNextTile = fX + iTileWidths;
			bMoving = true;

		}
		
	}
}
void PacmanProperties::MovePlayer(PacmanProperties& a_pacSprite, float a_fMovementSpeed)
{
	if (bMoving == true)
	{
		char* cSoundPath;
		if (bCanEatGhosts == true)
		{
			cSoundPath = "./sounds/eatGhosts.wav";
		}
		else
		{
			cSoundPath = "./sounds/siren.wav";
		}

		SetSpriteFrame();
		if (bPlayerDirection[north] == true)
		{
			fY += a_fMovementSpeed;
			if (fY >= iNextTile)
			{
				fY = iNextTile;
				bMoving = false;
				PlaySound(TEXT(cSoundPath), NULL,SND_FILENAME | SND_ASYNC);
				
			}
		}
		else if (bPlayerDirection[south] == true)
		{
			fY -= a_fMovementSpeed;
			if (fY <= iNextTile)
			{
				fY = iNextTile;
				bMoving = false;
				PlaySound(TEXT(cSoundPath), NULL, SND_FILENAME | SND_ASYNC);

			}
		}
		else if (bPlayerDirection[east] == true)
		{
			fX += a_fMovementSpeed;
			if (fX >= iNextTile)
			{
				fX = iNextTile;
				bMoving = false;
				PlaySound(TEXT(cSoundPath), NULL, SND_FILENAME | SND_ASYNC);
			}
		}
		else if (bPlayerDirection[west] == true)
		{
			fX -= a_fMovementSpeed;
			if (fX <= iNextTile)
			{
				fX = iNextTile;
				bMoving = false;
				PlaySound(TEXT(cSoundPath), NULL, SND_FILENAME | SND_ASYNC);

			}
		}
		
	}
	UG::MoveSprite(iSpriteID, fX, fY);
}










