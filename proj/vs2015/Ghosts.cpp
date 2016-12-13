//==============================================================================================================================
// Project: Pacman
// File: Ghosts.cpp
// Author: Daniel McCluskey
// Date Created: 17/10/16
// Brief: This is the header file that contains the code that controls the behaviour and mechanics of the ghosts during Gameplay.
// Last Edited by: (See BitBucket Commits: https://bitbucket.org/Danielmclovin/ct4019-pacman)
//==============================================================================================================================
#include "UGFW.h"
#include "Ghosts.h"
#include "MapCreation.h"
#include "stdlib.h"
#include <iostream>
#include "CustomEnum.h"
#include "windows.h"
#include "time.h"
int ghostMap[1008] =
{
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,2,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,2,0,
	0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,
	0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,
	0,2,1,2,1,1,2,0,0,2,1,1,2,0,0,2,1,1,2,0,0,2,1,1,2,1,2,0,
	0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0,
	0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0,
	0,2,1,2,0,0,2,1,1,2,1,1,2,1,1,2,1,1,2,1,1,2,0,0,2,1,2,0,
	0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0,
	0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0,
	0,2,1,1,1,1,2,1,1,2,1,1,2,0,0,2,1,1,2,1,1,2,1,1,1,1,2,0,
	0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,
	1,1,1,1,1,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,1,1,1,1,1,
	1,1,1,1,1,0,1,0,0,2,1,1,1,1,1,1,1,1,2,0,0,1,0,1,1,1,1,1,
	1,1,1,1,1,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,1,1,1,1,1,
	0,0,0,0,0,0,1,0,0,1,0,1,1,1,1,1,1,0,1,0,0,1,0,0,0,0,0,0,
	0,1,1,1,0,0,2,1,1,2,0,1,1,1,1,1,1,0,2,1,1,2,0,0,1,1,1,0,
	0,0,0,0,0,0,1,0,0,1,0,1,1,1,1,1,1,0,1,0,0,1,0,0,0,0,0,0,
	1,1,1,1,1,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,1,1,1,1,1,
	1,1,1,1,1,0,1,0,0,2,1,1,2,1,2,2,1,1,2,0,0,1,0,1,1,1,1,1,
	1,1,1,1,1,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,1,1,1,1,1,
	0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,
	0,2,1,1,1,1,2,0,0,2,1,1,2,0,0,2,1,1,2,0,0,2,1,1,1,1,2,0,
	0,1,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,1,0,
	0,1,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,1,0,
	0,2,1,1,1,1,2,1,1,2,1,1,2,1,1,2,1,1,2,1,1,2,1,1,1,1,2,0,
	0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0,
	0,1,0,1,1,0,1,0,1,1,1,0,1,0,0,1,0,1,1,1,0,1,0,1,1,0,1,0,
	0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0,
	0,2,1,1,1,1,2,1,1,1,1,1,2,0,0,2,1,1,1,1,1,2,1,1,1,1,2,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
};

void GhostProperties::SetCageTime()
{
	--iCageTime;
	if (iCageTime > 0)
	{
		fX = iCageX;
		fY = iCageY;
	}
	if (iCageTime < 0 && iCageTime > -10)
	{
		initialise();
		fX = 240;
		fY = 352;
	}
}
int GhostProperties::GetTile(int a_iX, int a_iY)
{
	return ghostMap[(a_iY *28) + a_iX];
}
void GhostProperties::GetTiles()
{
	
	int iMapXPos = (fX) / iTileWidths;
	int iMapYPos = (fY) / iTileWidths;
	iTileTop = GetTile(iMapXPos - 1, (iMapYPos));
	iTileLeft = GetTile((iMapXPos - 2), iMapYPos - 1);
	iTileRight = GetTile((iMapXPos), iMapYPos - 1);
	iTileBottom = GetTile(iMapXPos - 1, (iMapYPos - 2));
	iTileCurrent = GetTile((iMapXPos)-1, iMapYPos - 1);
	
}

void GhostProperties::CreateGhost(int a_iGhostType)
{
	switch (a_iGhostType)
	{
	case blinky:
		iSpriteID = UG::CreateSprite("./images/ghosts/red.png", iGhostWidth, iGhostWidth, true);
		iCageTime = 100;
		iCageX = 256;
		UG::DrawSprite(iSpriteID);
		break;                                                                        
	case pinky:
		iSpriteID = UG::CreateSprite("./images/ghosts/pink.png", iGhostWidth, iGhostWidth, true);
		iCageTime = 300;
		iCageX = 240;
		UG::DrawSprite(iSpriteID);
		break;
	case inky:
		iSpriteID = UG::CreateSprite("./images/ghosts/blue.png", iGhostWidth, iGhostWidth, true);
		iCageTime = 500;
		iCageX = 224;
		UG::DrawSprite(iSpriteID);
		break;
	case clyde:
		iSpriteID = UG::CreateSprite("./images/ghosts/orange.png", iGhostWidth, iGhostWidth, true);
		iCageTime = 600;
		iCageX = 208;
		UG::DrawSprite(iSpriteID);
		break;
	case edible:
		iSpriteID = UG::CreateSprite("./images/ghosts/edible.png", iGhostWidth, iGhostWidth, true);
		break;

	}
	initialise();
	iCageY = 320;
	UG::MoveSprite(iSpriteID, 232, 320);
	
	
}

int GhostProperties::GetDirection()
{
	for (int i = 0; i < 3; ++i)
	{
		if (bGhostDirection[i] == true)
		{
			return i;
		}
	}
}
void GhostProperties::SetGhostDirection(GhostProperties& a_ghostSprite, float a_fMovementspeed)
{
	GetTiles();
	if (bMoving == false )
	{		
		if (iTileCurrent == 2)
		{			
			int openDirections[4] = { -1, -1 ,-1 ,-1 };
			int i = 0;
			if (iTileTop != 0 && iLastDirection != 2)
			{
				openDirections[i] = 0;
				++i;
			}
			if (iTileBottom != 0 && iLastDirection != 0)
			{
				openDirections[i] = 2;
				++i;
			}
			if (iTileRight != 0 && iLastDirection != 3)
			{
				openDirections[i] = 1;
				++i;
			}			
			if (iTileLeft != 0 && iLastDirection != 1)
			{
				openDirections[i] = 3;
				++i;
			}
			srand(time(NULL));
			iRandomDirection = openDirections[(rand() % i)];
			do
			{
				iRandomDirection = openDirections[(rand() % i)];
			} while (iRandomDirection == -1);			
		}
		if (iRandomDirection == 0)
		{
			iNextTile = fY + iTileWidths;
			bGhostDirection[north] = true;
			bMoving = true;
			iLastDirection = 0;
		}		
		else if (iRandomDirection == 3)
		{
			iNextTile = fX - iTileWidths;
			bGhostDirection[west] = true;
			bMoving = true;
			iLastDirection = 3;
		}
		else if (iRandomDirection == 1)
		{
			iNextTile = fX + iTileWidths;
			bGhostDirection[east] = true;
			bMoving = true;
			iLastDirection = 1;
		}
		else if (iRandomDirection == 2)
		{
			iNextTile = fY - iTileWidths;
			bGhostDirection[south] = true;
			bMoving = true;
			iLastDirection = 2;
		}		
	}
}
void GhostProperties::MoveGhost(GhostProperties& a_ghostSprite, float a_fMovementspeed)
{
	if (bMoving == true)
	{
		if (bGhostDirection[north] == true)
		{
			fY += a_fMovementspeed;
			if (fY >= iNextTile)
			{
				fY = iNextTile;
				bMoving = false;
				initialise();
			}
		}
		else if (bGhostDirection[south] == true)
		{
			fY -= a_fMovementspeed;
			if (fY <= iNextTile)
			{
				fY = iNextTile;
				bMoving = false;
				initialise();
			}
		}
		else if (bGhostDirection[east] == true )
		{
			fX += a_fMovementspeed;
			if (fX >= iNextTile)
			{
				fX = iNextTile;
				bMoving = false;
				initialise();
			}
		}
		else if (bGhostDirection[west] == true)
		{
			fX -= a_fMovementspeed;
			if (fX <= iNextTile)
			{
				fX = iNextTile;
				bMoving = false;
				initialise();
			}
		}
	}
	UG::MoveSprite(iSpriteID, fX, fY);//Moves Ghost
}
bool GhostProperties::Pacmancollide(GhostProperties& a_ghostSprite, int a_iX, int a_iY)
{
	if (a_iX <= fX && (a_iX + iTileWidths) >= fX)
	{
		if (a_iY <= fY && (a_iY + iTileWidths) >= fY)
		{
			return true;
		}
	}
	else
	{
		return false;
	}

}

void GhostProperties::SetEdibleGhostsPos(GhostProperties& a_ghost)
{
	fX = a_ghost.fX;
	fY = a_ghost.fY;
	UG::MoveSprite(iSpriteID, fX, fY);
}