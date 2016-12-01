#include "Pacman.h"
#include "UGFW.h"
#include "CustomEnum.h"
//Creating Sprite
void PacmanProperties::CreatePacman()
{
	SpriteID = UG::CreateSprite("./images/pacman/pacman.png", iPacWidth, iPacWidth, true);
	UG::DrawSprite(SpriteID);

	
}

void PacmanProperties::SetPlayerDirection(PacmanProperties& pacSprite, float movementspeed, short a_upKey, short a_downKey, short a_leftKey, short a_rightKey, int tileTop, int tileRight, int tileLeft, int tileBottom)
{
	if (moving == false)
	{
		if (UG::IsKeyDown(a_upKey) && tileTop == 8)
		{
			initialise();
			playerDirection[north] = true;
		}
		if (UG::IsKeyDown(a_downKey) && tileBottom == 8)
		{
			initialise();
			playerDirection[south] = true;
		}
		if (UG::IsKeyDown(a_leftKey) && tileLeft == 8)
		{
			initialise();
			playerDirection[west] = true;
		}
		if (UG::IsKeyDown(a_rightKey) && tileRight == 8)
		{
			initialise();
			playerDirection[east] = true;
		}


		if (playerDirection[north] == true && tileTop == 8)
		{
			nextTile = pacSprite.pacYPos + tileWidths;
			moving = true;
			UG::SetSpriteUVCoordinates(SpriteID, 0, 0, .5f, .5f);
		}
		else if (playerDirection[south] == true && tileBottom == 8)
		{
			nextTile = pacSprite.pacYPos - tileWidths;
			moving = true;
			UG::SetSpriteUVCoordinates(SpriteID, 0, .5f, .5f, 1);
		}
		else if (playerDirection[west] == true && tileLeft == 8)
		{
			nextTile = pacXPos - tileWidths;
			moving = true;
			UG::SetSpriteUVCoordinates(SpriteID, .5f, .5f, 1, 1);
		}
		else if (playerDirection[east] == true && tileRight == 8)
		{
			nextTile = pacXPos + tileWidths;
			moving = true;
			UG::SetSpriteUVCoordinates(SpriteID, 1, .5f, .5f, 1);

		}
	}
}
void PacmanProperties::MovePlayer(PacmanProperties& pacSprite, float movementspeed, int tileTop, int tileRight, int tileLeft, int tileBottom)
{
	if (moving == true)
	{
		if (playerDirection[north] == true)
		{
			pacYPos += movementspeed;
			if (pacYPos >= nextTile)
			{
				pacYPos = nextTile;
				moving = false;
				
				
			}
		}
		else if (playerDirection[south] == true)
		{
			pacYPos -= movementspeed;
			if (pacYPos <= nextTile)
			{
				pacYPos = nextTile;
				moving = false;
				

			}
		}
		else if (playerDirection[east] == true)
		{
			pacXPos += movementspeed;
			if (pacXPos >= nextTile)
			{
				pacXPos = nextTile;
				moving = false;
			}
		}
		else if (playerDirection[west] == true)
		{
			pacXPos -= movementspeed;
			if (pacXPos <= nextTile)
			{
				pacXPos = nextTile;
				moving = false;			

			}
		}
		
	}
}










