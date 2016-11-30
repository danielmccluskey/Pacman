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
			pacSprite.nextTile = pacSprite.pacYPos + tileWidths;
			pacSprite.playerDirection[north] = true;
			pacSprite.moving = true;
			UG::SetSpriteUVCoordinates(pacSprite.SpriteID, 0, 0, .5f, .5f);
		}
		else if (UG::IsKeyDown(a_downKey) && tileBottom == 8)
		{

			pacSprite.nextTile = pacSprite.pacYPos - tileWidths;
			pacSprite.playerDirection[south] = true;
			pacSprite.moving = true;
			UG::SetSpriteUVCoordinates(pacSprite.SpriteID, 0, .5f, .5f, 1);


		}
		else if (UG::IsKeyDown(a_leftKey) && tileLeft == 8)
		{
			pacSprite.nextTile = pacSprite.pacXPos - tileWidths;
			pacSprite.playerDirection[west] = true;
			pacSprite.moving = true;
			UG::SetSpriteUVCoordinates(pacSprite.SpriteID, .5f, .5f, 1, 1);
		}
		else if (UG::IsKeyDown(a_rightKey) && tileRight == 8)
		{
			pacSprite.nextTile = pacSprite.pacXPos + tileWidths;
			pacSprite.playerDirection[east] = true;
			pacSprite.moving = true;

			UG::SetSpriteUVCoordinates(pacSprite.SpriteID, 1, .5f, .5f, 1);

		}
	}
}
void PacmanProperties::MovePlayer(PacmanProperties& pacSprite, float movementspeed, int tileTop, int tileRight, int tileLeft, int tileBottom)
{
	if (pacSprite.moving == true)
	{
		if (pacSprite.playerDirection[north] == true)
		{
			pacSprite.pacYPos += movementspeed;
			if (pacSprite.pacYPos >= pacSprite.nextTile)
			{
				pacSprite.pacYPos = pacSprite.nextTile;
				pacSprite.moving = false;
				pacSprite.initialise();
				
			}
		}
		else if (pacSprite.playerDirection[south] == true)
		{
			pacSprite.pacYPos -= movementspeed;
			if (pacSprite.pacYPos <= pacSprite.nextTile)
			{
				pacSprite.pacYPos = pacSprite.nextTile;
				pacSprite.moving = false;
				pacSprite.initialise();
				

			}
		}
		else if (pacSprite.playerDirection[east] == true)
		{
			pacSprite.pacXPos += movementspeed;
			if (pacSprite.pacXPos >= pacSprite.nextTile)
			{
				pacSprite.pacXPos = pacSprite.nextTile;
				pacSprite.moving = false;
				pacSprite.initialise();

			}
		}
		else if (pacSprite.playerDirection[west] == true)
		{
			pacSprite.pacXPos -= movementspeed;
			if (pacSprite.pacXPos <= pacSprite.nextTile)
			{
				pacSprite.pacXPos = pacSprite.nextTile;
				pacSprite.moving = false;
				pacSprite.initialise();
				
				

			}
		}
		
	}
}










