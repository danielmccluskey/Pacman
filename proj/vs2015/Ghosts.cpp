#include "UGFW.h"
#include "Ghosts.h"
#include "MapCreation.h"
#include "stdlib.h"
#include <iostream>
#include "CustomEnum.h"
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
	0,2,1,1,1,1,2,1,1,2,1,1,2,0,0,2,1,1,1,1,1,2,1,1,1,1,2,0,
	0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,
	1,1,1,1,1,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,1,1,1,1,1,
	1,1,1,1,1,0,1,0,0,2,1,1,1,1,1,1,1,1,2,0,0,1,0,1,1,1,1,1,
	1,1,1,1,1,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,1,1,1,1,1,
	0,0,0,0,0,0,1,0,0,1,0,1,1,1,1,1,1,0,1,0,0,1,0,0,0,0,0,0,
	0,1,1,1,0,0,2,1,1,2,0,1,1,1,1,1,1,0,2,1,1,2,0,0,1,1,1,0,
	0,0,0,0,0,0,1,0,0,1,0,1,1,1,1,1,1,0,1,0,0,1,0,0,0,0,0,0,
	1,1,1,1,1,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,1,1,1,1,1,
	1,1,1,1,1,0,1,0,0,2,1,1,2,1,1,2,1,1,2,0,0,1,0,1,1,1,1,1,
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

int GhostProperties::GetTile(int x, int y)
{
	return ghostMap[(y*28) + x];
}
void GhostProperties::GetTiles()
{
	
	int mapXPos = (fX) / tileWidths;
	int mapYPos = (fY) / tileWidths;
	tileTop = GetTile(mapXPos - 1, (mapYPos));
	tileLeft = GetTile((mapXPos - 2), mapYPos - 1);
	tileRight = GetTile((mapXPos), mapYPos - 1);
	tileBottom = GetTile(mapXPos - 1, (mapYPos - 2));
	tileCurrent = GetTile((mapXPos)-1, mapYPos - 1);
	std::cout << tileCurrent << std::endl;
}

void GhostProperties::CreateGhost(int ghostType)
{
	switch (ghostType)
	{
	case blinky:
		SpriteID = UG::CreateSprite("./images/ghosts/red.png", iGhostWidth, iGhostWidth, true);
		UG::MoveSprite(SpriteID, 112, 416);
		fX = 112;
		fY = 448;
		break;                                                                        
	case pinky:
		SpriteID = UG::CreateSprite("./images/ghosts/pink.png", iGhostWidth, iGhostWidth, true);
		UG::MoveSprite(SpriteID, 352, 416);
		fX = 352;
		fY = 448;
		break;
	case inky:
		SpriteID = UG::CreateSprite("./images/ghosts/blue.png", iGhostWidth, iGhostWidth, true);
		UG::MoveSprite(SpriteID, 352, 128);
		fX = 352;
		fY = 160;
		break;
	case clyde:
		SpriteID = UG::CreateSprite("./images/ghosts/orange.png", iGhostWidth, iGhostWidth, true);
		UG::MoveSprite(SpriteID, 112, 128);
		fX = 112;
		fY = 160;
		break;
	}
	
	UG::DrawSprite(SpriteID);
	
}

int GhostProperties::GetDirection()
{
	for (int i = 0; i < 3; ++i)
	{
		if (ghostDirection[i] == true)
		{
			return i;
		}
	}
}



void GhostProperties::ChangeDirection(int currentDirection, int currentTile)
{
	if (currentTile == 2)
	{
		
		


	}
}
void GhostProperties::SetGhostDirection(GhostProperties& ghostSprite, float movementspeed)
{
	GetTiles();

	if (moving == false )
	{
		
		if (tileCurrent == 2)
		{
			
			int openDirections[4] = { -1, -1 ,-1 ,-1 };
			int i = 0;
			if (tileTop != 0 && lastDirection != 2)
			{
				openDirections[i] = 0;
				++i;
			}
			if (tileBottom != 0 && lastDirection != 0)
			{
				openDirections[i] = 2;
				++i;
			}
			if (tileRight != 0 && lastDirection != 3)
			{
				openDirections[i] = 1;
				++i;
			}
			
			if (tileLeft != 0 && lastDirection != 1)
			{
				openDirections[i] = 3;
				++i;
			}
			randomDirection = openDirections[(rand() % i)];
			do
			{
				randomDirection = openDirections[(rand() % i)];
			} while (randomDirection == -1);
			
			
		}
		if (randomDirection == 0)
		{
			ghostSprite.nextTile = ghostSprite.fY + tileWidths;
			ghostSprite.ghostDirection[north] = true;
			ghostSprite.moving = true;
			lastDirection = 0;
		}
		
		else if (randomDirection == 3)
		{
			ghostSprite.nextTile = ghostSprite.fX - tileWidths;
			ghostSprite.ghostDirection[west] = true;
			ghostSprite.moving = true;
			lastDirection = 3;
		}
		else if (randomDirection == 1)
		{
			ghostSprite.nextTile = ghostSprite.fX + tileWidths;
			ghostSprite.ghostDirection[east] = true;
			ghostSprite.moving = true;
			lastDirection = 1;


		}
		else if (randomDirection == 2)
		{

			ghostSprite.nextTile = ghostSprite.fY - tileWidths;
			ghostSprite.ghostDirection[south] = true;
			ghostSprite.moving = true;
			lastDirection = 2;


		}
		
				
		
	}
}
void GhostProperties::MoveGhost(GhostProperties& ghostSprite, float movementspeed)
{
	if (ghostSprite.moving == true)
	{
		if (ghostSprite.ghostDirection[north] == true)
		{
			ghostSprite.fY += movementspeed;
			if (ghostSprite.fY >= ghostSprite.nextTile)
			{
				ghostSprite.fY = ghostSprite.nextTile;
				ghostSprite.moving = false;
				ghostSprite.initialise();
				
				

			}
		}
		else if (ghostSprite.ghostDirection[south] == true)
		{
			ghostSprite.fY -= movementspeed;
			if (ghostSprite.fY <= ghostSprite.nextTile)
			{
				ghostSprite.fY = ghostSprite.nextTile;
				ghostSprite.moving = false;
				ghostSprite.initialise();
				


			}
		}
		else if (ghostSprite.ghostDirection[east] == true )
		{
			ghostSprite.fX += movementspeed;
			if (ghostSprite.fX >= ghostSprite.nextTile)
			{
				ghostSprite.fX = ghostSprite.nextTile;
				ghostSprite.moving = false;
				ghostSprite.initialise();
				

			}
		}
		else if (ghostSprite.ghostDirection[west] == true)
		{
			ghostSprite.fX -= movementspeed;
			if (ghostSprite.fX <= ghostSprite.nextTile)
			{
				ghostSprite.fX = ghostSprite.nextTile;
				ghostSprite.moving = false;
				ghostSprite.initialise();
				



			}
		}
		


	}
}