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

//Map of the Ghosts collision map
// 0 == Wall
// 1 == Moveable space
// 2 == Change direction spot
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
	--iCageTime;//Subtract from the cage time
	if (iCageTime > 0)//If the cage time runs out
	{
		//Move relative ghost to its specific cage spot
		fX = iCageX;
		fY = iCageY;
	}
	if (iCageTime < 0 && iCageTime > -10)
	{
		initialise();//Reset directional and movement values

		//Move out of cage
		fX = 240;
		fY = 352;
	}
}
int GhostProperties::GetTile(int a_iX, int a_iY)
{
	return ghostMap[(a_iY *28) + a_iX];//Finds and returns what pellet is at X,Y
}
void GhostProperties::GetTiles()
{
	//Converts the Ghosts actual position in the window to a position in the collision map
	int iMapXPos = (fX) / iTileWidths;
	int iMapYPos = (fY) / iTileWidths;

	//Finds what tile is at the appropriate value e.g. iTileTop will get the tile above pacman
	//GetTile(x,y) will get the tile top right of pacman so adjustments are made within with integers.
	iTileTop = GetTile(iMapXPos - 1, (iMapYPos));
	iTileLeft = GetTile((iMapXPos - 2), iMapYPos - 1);
	iTileRight = GetTile((iMapXPos), iMapYPos - 1);
	iTileBottom = GetTile(iMapXPos - 1, (iMapYPos - 2));
	iTileCurrent = GetTile((iMapXPos)-1, iMapYPos - 1);
	
}

void GhostProperties::CreateGhost(int a_iGhostType)
{
	//Creates the appropriate ghost, sets its starting cage time and cage position and then dfraws the sprite.
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
	initialise();//Reset directional and movement values
	iCageY = 320;
	
	
}

int GhostProperties::GetDirection()
{
	//Gets the current direction of a ghost as an integer value
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
	if (bMoving == false )//If ghost is not moving
	{		
		if (iTileCurrent == 2)//If current tile is a change direction tile
		{			
			int openDirections[4] = { -1, -1 ,-1 ,-1 }; //Array to check which directions are open
			int i = 0;

			//If block to check if the relative direction is open and that they did not just come from that direction
			if (iTileTop != 0 && iLastDirection != 2)
			{
				openDirections[i] = 0;//Add current direction to the array
				++i;
			}
			if (iTileBottom != 0 && iLastDirection != 0)
			{
				openDirections[i] = 2;//Add current direction to the array
				++i;
			}
			if (iTileRight != 0 && iLastDirection != 3)
			{
				openDirections[i] = 1;//Add current direction to the array
				++i;
			}			
			if (iTileLeft != 0 && iLastDirection != 1)
			{
				openDirections[i] = 3;//Add current direction to the array
				++i;
			}
			
			srand(time(NULL));//Resets the seed of the random generator to produce more random ghost movement
			iRandomDirection = openDirections[(rand() % i)];//Sets the random direction to a random member of the array

			//While loop just incase the random number chooses -1
			do
			{
				iRandomDirection = openDirections[(rand() % i)];
			} while (iRandomDirection == -1);			
		}


		//If block to set the direction based off of the direction chosen at the previous change direction tile
		if (iRandomDirection == 0)
		{
			iNextTile = fY + iTileWidths;//Sets the next tile the ghost should go to
			bGhostDirection[north] = true;//Sets the direction
			bMoving = true;//Allows the ghost to start moving again
			iLastDirection = 0;//Sets the last direction to the current direction
		}		
		else if (iRandomDirection == 3)
		{
			iNextTile = fX - iTileWidths;//Sets the next tile the ghost should go to
			bGhostDirection[west] = true;//Sets the direction
			bMoving = true;//Allows the ghost to start moving again
			iLastDirection = 3;//Sets the last direction to the current direction
		}
		else if (iRandomDirection == 1)
		{
			iNextTile = fX + iTileWidths;//Sets the next tile the ghost should go to
			bGhostDirection[east] = true;//Sets the direction
			bMoving = true;//Allows the ghost to start moving again
			iLastDirection = 1;//Sets the last direction to the current direction
		}
		else if (iRandomDirection == 2)
		{
			iNextTile = fY - iTileWidths;//Sets the next tile the ghost should go to
			bGhostDirection[south] = true;//Sets the direction
			bMoving = true;//Allows the ghost to start moving again
			iLastDirection = 2;//Sets the last direction to the current direction
		}		
	}
}
void GhostProperties::MoveGhost(GhostProperties& a_ghostSprite, float a_fMovementspeed)
{
	if (bMoving == true)//If the ghost is allowed to move
	{
		//If block to move the ghost in the randomly chosen direction
		if (bGhostDirection[north] == true)
		{
			fY += a_fMovementspeed;//Adds the movement speed to the position to move the ghost
			if (fY >= iNextTile)//If the position is past the next tile
			{
				fY = iNextTile;//Sets the position to the next tile to keep grid alignment
				bMoving = false;//Sets movement to false to allow direction change again
				initialise();//Reset directional and movement values
			}
		}
		else if (bGhostDirection[south] == true)
		{
			fY -= a_fMovementspeed;//Adds the movement speed to the position to move the ghost
			if (fY <= iNextTile)//If the position is past the next tile
			{
				fY = iNextTile;//Sets the position to the next tile to keep grid alignment
				bMoving = false;//Sets movement to false to allow direction change again
				initialise();//Reset directional and movement values
			}
		}
		else if (bGhostDirection[east] == true )
		{
			fX += a_fMovementspeed;//Adds the movement speed to the position to move the ghost
			if (fX >= iNextTile)//If the position is past the next tile
			{
				fX = iNextTile;//Sets the position to the next tile to keep grid alignment
				bMoving = false;//Sets movement to false to allow direction change again
				initialise();//Reset directional and movement values
			}
		}
		else if (bGhostDirection[west] == true)
		{
			fX -= a_fMovementspeed;//Adds the movement speed to the position to move the ghost
			if (fX <= iNextTile)//If the position is past the next tile
			{
				fX = iNextTile;//Sets the position to the next tile to keep grid alignment
				bMoving = false;//Sets movement to false to allow direction change again
				initialise();//Reset directional and movement values
			}
		}
	}
	UG::MoveSprite(iSpriteID, fX, fY);//Moves Ghost
}
bool GhostProperties::Pacmancollide(GhostProperties& a_ghostSprite, int a_iX, int a_iY)
{
	//Function to check whether the ghost is within the boundaries of the pacman sprite
	//IF it is colliding return TRUE, else FALSE
	
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
	//Moves the Edible ghost to the same position as the ghost it follows
	fX = a_ghost.fX;
	fY = a_ghost.fY;
	UG::MoveSprite(iSpriteID, fX, fY);
}