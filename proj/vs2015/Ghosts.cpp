#include "UGFW.h"
#include "Ghosts.h"
#include "stdlib.h"
#include "CustomEnum.h"

int ghostMap[1008] =
{
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,2,1,1,1,1,2,1,1,1,1,1,2,0,0,2,1,1,1,1,1,2,1,1,1,1,2,0,
	0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0,
	0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0,
	0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0,
	0,2,1,1,1,1,2,1,1,1,1,1,2,1,1,2,1,1,2,1,1,2,1,1,1,1,2,0,
	0,1,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,1,0,
	0,1,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,1,0,
	0,2,1,1,1,1,2,0,0,2,1,1,2,0,0,2,1,1,2,0,0,2,1,1,1,1,2,0,
	0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,
	0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,
	0,0,0,0,0,0,1,0,0,2,1,1,2,1,1,2,1,1,2,0,0,1,0,0,0,0,0,0,
	0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,
	0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,
	0,2,1,1,1,1,2,1,1,2,0,0,0,0,0,0,0,0,2,1,1,2,1,1,1,1,2,0,
	0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,
	0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,
	0,0,0,0,0,0,1,0,0,2,1,1,1,1,1,1,1,1,2,0,0,1,0,0,0,0,0,0,
	0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,
	0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,
	0,2,1,1,1,1,2,1,1,2,1,1,2,0,0,2,1,1,2,1,1,2,1,1,1,1,2,0,
	0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0,
	0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0,
	0,2,1,2,0,0,2,1,1,2,1,1,2,1,1,2,1,1,2,1,1,2,0,0,2,1,2,0,
	0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0,
	0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0,
	0,2,1,2,1,1,2,0,0,2,1,1,2,0,0,2,1,1,2,0,0,2,1,1,2,1,2,0,
	0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,
	0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,
	0,2,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,2,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};
int GhostProperties::GetTile(int x, int y)
{
	return ghostMap[(y*28) + x];
}

void GhostProperties::CreateGhost(int ghostType)
{
	switch (ghostType)
	{
	case blinky:
		SpriteID = UG::CreateSprite("./images/ghosts/red.png", iGhostWidth, iGhostWidth, true);
		UG::MoveSprite(SpriteID, 112, 448);
		ghostXPos = 112;
		ghostYPos = 448;
		break;                                                                        
	case pinky:
		SpriteID = UG::CreateSprite("./images/ghosts/pink.png", iGhostWidth, iGhostWidth, true);
		UG::MoveSprite(SpriteID, 352, 448);
		ghostXPos = 352;
		ghostYPos = 448;
		break;
	case inky:
		SpriteID = UG::CreateSprite("./images/ghosts/blue.png", iGhostWidth, iGhostWidth, true);
		UG::MoveSprite(SpriteID, 352, 160);
		ghostXPos = 352;
		ghostYPos = 160;
		break;
	case clyde:
		SpriteID = UG::CreateSprite("./images/ghosts/orange.png", iGhostWidth, iGhostWidth, true);
		UG::MoveSprite(SpriteID, 112, 160);
		ghostXPos = 112;
		ghostYPos = 160;
		break;
	}
	
	UG::DrawSprite(SpriteID);
	
}
void GhostProperties::SetGhostDirection(GhostProperties& ghostSprite, float movementspeed, short a_upKey, short a_downKey, short a_leftKey, short a_rightKey, int tileTop, int tileRight, int tileLeft, int tileBottom)
{
	if (moving == false)
	{
		int randomNumber = rand() % 4;
		if (randomNumber == 0 && tileTop == 8)
		{
			ghostSprite.nextTile = ghostSprite.ghostYPos + tileWidths;
			ghostSprite.ghostDirection[north] = true;
			ghostSprite.moving = true;
		}
		else if (randomNumber == 1 && tileBottom == 8)
		{

			ghostSprite.nextTile = ghostSprite.ghostYPos - tileWidths;
			ghostSprite.ghostDirection[south] = true;
			ghostSprite.moving = true;


		}
		else if (randomNumber == 2 && tileLeft == 8)
		{
			ghostSprite.nextTile = ghostSprite.ghostXPos - tileWidths;
			ghostSprite.ghostDirection[west] = true;
			ghostSprite.moving = true;
		}
		else if (randomNumber == 3 && tileRight == 8)
		{
			ghostSprite.nextTile = ghostSprite.ghostXPos + tileWidths;
			ghostSprite.ghostDirection[east] = true;
			ghostSprite.moving = true;


		}
	}
}
void GhostProperties::MoveGhost(GhostProperties& ghostSprite, float movementspeed, int tileTop, int tileRight, int tileLeft, int tileBottom)
{
	if (ghostSprite.moving == true)
	{
		if (ghostSprite.ghostDirection[north] == true)
		{
			ghostSprite.ghostYPos += movementspeed;
			if (ghostSprite.ghostYPos >= ghostSprite.nextTile)
			{
				ghostSprite.ghostYPos = ghostSprite.nextTile;
				ghostSprite.moving = false;
				ghostSprite.initialise();
				

			}
		}
		else if (ghostSprite.ghostDirection[south] == true)
		{
			ghostSprite.ghostYPos -= movementspeed;
			if (ghostSprite.ghostYPos <= ghostSprite.nextTile)
			{
				ghostSprite.ghostYPos = ghostSprite.nextTile;
				ghostSprite.moving = false;
				ghostSprite.initialise();
				


			}
		}
		else if (ghostSprite.ghostDirection[east] == true)
		{
			ghostSprite.ghostXPos += movementspeed;
			if (ghostSprite.ghostXPos >= ghostSprite.nextTile)
			{
				ghostSprite.ghostXPos = ghostSprite.nextTile;
				ghostSprite.moving = false;
				ghostSprite.initialise();
				

			}
		}
		else if (ghostSprite.ghostDirection[west] == true)
		{
			ghostSprite.ghostXPos -= movementspeed;
			if (ghostSprite.ghostXPos <= ghostSprite.nextTile)
			{
				ghostSprite.ghostXPos = ghostSprite.nextTile;
				ghostSprite.moving = false;
				ghostSprite.initialise();
				



			}
		}

	}
}