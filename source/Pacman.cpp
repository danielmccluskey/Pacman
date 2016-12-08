#include "Pacman.h"
#include "UGFW.h"
#include "stdlib.h"
#include "CustomEnum.h"
#include "windows.h"
#include <iostream>

int pacmanMap[1008] =
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

void PacmanProperties::SetLives()
{
	--lives;
	PlaySound(TEXT("./sounds/death.wav"), NULL, SND_FILENAME | SND_SYNC);//Plays Death sound and Hangs program until finished
}

//Creating Sprite
void PacmanProperties::CreatePacman()
{
	SpriteID = UG::CreateSprite("./images/pacman/pacman.png", SpriteWidth, SpriteWidth, true);
	UG::DrawSprite(SpriteID);	
	initialise(); //Sets the variables for pacman. (Will move to class)
	UG::MoveSprite(SpriteID, 32, 64); //Moves Pacman to starting Position
	UG::SetSpriteUVCoordinates(SpriteID, 1, .5f, .5f, 1);
	playerDirection[east] = true;
}



int PacmanProperties::GetTile(int x, int y)
{
	return pacmanMap[(y * 28) + x];
}
void PacmanProperties::GetTiles()
{
	mapXPos = (fX) / tileWidths;
	mapYPos = (fY) / tileWidths;
	tileTop = GetTile(mapXPos - 1, (mapYPos));
	tileLeft = GetTile((mapXPos - 2), mapYPos - 1);
	tileRight = GetTile((mapXPos), mapYPos - 1);
	tileBottom = GetTile(mapXPos - 1, (mapYPos - 2));
	tileCurrent = GetTile((mapXPos - 1), mapYPos - 1);
}

void PacmanProperties::SetPlayerDirection(PacmanProperties& pacSprite, float movementspeed, short a_upKey, short a_downKey, short a_leftKey, short a_rightKey)
{
	GetTiles();
	if (tileRight == 8)
	{
		fX = 432;
		fY = 304;
		initialise();
		playerDirection[west] = true;
	}
	if (tileLeft == 6)
	{
		fX = 32;
		fY = 304;
		initialise();
		playerDirection[east] = true;
	}
	if (moving == false)
	{

		if (UG::IsKeyDown(a_upKey) && tileTop != 0)
		{
			initialise();
			playerDirection[north] = true;
			std::cout << "UPP" << std::endl;
		}
		if (UG::IsKeyDown(a_downKey) && tileBottom != 0)
		{
			initialise();
			playerDirection[south] = true;
			std::cout << "DOWN" << std::endl;
		}
		if (UG::IsKeyDown(a_leftKey) && tileLeft != 0)
		{
			initialise();
			playerDirection[west] = true;
			std::cout << "LEFT" << std::endl;
		}
		if (UG::IsKeyDown(a_rightKey) && tileRight != 0)
		{
			initialise();
			playerDirection[east] = true;
			std::cout << "RIGHT" << std::endl;
		}


		if (playerDirection[north] == true && tileTop != 0)
		{
			nextTile = fY + tileWidths;
			moving = true;
			UG::SetSpriteUVCoordinates(SpriteID, 0, 0, .5f, .5f);
		}
		else if (playerDirection[south] == true && tileBottom != 0)
		{
			nextTile = fY - tileWidths;
			moving = true;
			UG::SetSpriteUVCoordinates(SpriteID, 0, .5f, .5f, 1);
		}
		else if (playerDirection[west] == true && tileLeft != 0)
		{
			nextTile = fX - tileWidths;
			moving = true;
			UG::SetSpriteUVCoordinates(SpriteID, .5f, .5f, 1, 1);
		}
		else if (playerDirection[east] == true && tileRight != 0)
		{
			nextTile = fX + tileWidths;
			moving = true;
			UG::SetSpriteUVCoordinates(SpriteID, 1, .5f, .5f, 1);

		}
	}
}
void PacmanProperties::MovePlayer(PacmanProperties& pacSprite, float movementspeed)
{
	if (moving == true)
	{
		if (playerDirection[north] == true)
		{
			fY += movementspeed;
			if (fY >= nextTile)
			{
				fY = nextTile;
				moving = false;
				PlaySound(TEXT("./sounds/siren.wav"), NULL, SND_NOSTOP | SND_ASYNC);
				
			}
		}
		else if (playerDirection[south] == true)
		{
			fY -= movementspeed;
			if (fY <= nextTile)
			{
				fY = nextTile;
				moving = false;
				PlaySound(TEXT("./sounds/siren.wav"), NULL, SND_NOSTOP | SND_ASYNC);

			}
		}
		else if (playerDirection[east] == true)
		{
			fX += movementspeed;
			if (fX >= nextTile)
			{
				fX = nextTile;
				moving = false;
				PlaySound(TEXT("./sounds/siren.wav"), NULL, SND_NOSTOP | SND_ASYNC);
			}
		}
		else if (playerDirection[west] == true)
		{
			fX -= movementspeed;
			if (fX <= nextTile)
			{
				fX = nextTile;
				moving = false;		
				PlaySound(TEXT("./sounds/siren.wav"), NULL, SND_NOSTOP | SND_ASYNC);

			}
		}
		
	}
	UG::MoveSprite(SpriteID, fX, fY);
}










