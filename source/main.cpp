#include "UGFW.h"
#include "MapCreation.h"
#include "Enumerations.h"
#include "Ghosts.h"
#include "Pacman.h"
#include "CustomEnum.h"
#include "Pellets.h"
#include <iostream>
#include <string>
#include <sstream>

//==============================================================================================================================
// File: Pong
// Author: Daniel McCluskey
// Date Created: 17/10/16
// Brief: This is a small recreation of the game Pacman using the UOG Framework.
// Last Edited by: (See BitBucket Commits: )
//==============================================================================================================================

//Screen sizes
int iScreenWidth = 0;
int iScreenHeight = 0;

//Amount of Pellets on map

//Positions
float xPos, yPos = 0;
float tileWidth = 16;
int pelletCount = 300;
//Movement Speed for the player, Divided by tileWidth to keep it Grid aligned
float movementSpeed = 25/tileWidth;

struct PelletStruct
{
	int SpriteID = -1;
	int fX;
	int fY;
};
void DestroyPellets(PacmanProperties& pacSprite, PelletProperties *pellet);
int main(int argv, char* argc[])
{
	//Creation of the PacMan Window, Width and height is the size of the Map array multiplied by the tile images resolution.
	if (UG::Create((mapWidth*tileWidth), (mapHeight*tileWidth), false, "Pacman", 100, 100))
	{



		
		//The following is the code that draws out the tiles from the Array map
		for (int y = 0; y < mapHeight; ++y)  //Counts through the Y axis of the array each time the X axis completes a row
		{
			for (int x = 0; x < mapWidth; ++x) //Counts through the X axis
			{
				TileProperties newTile; //Defines a new class thing, this was the only way I could figure out how to use classes, will fix in future
				int tileType = newTile.GetTile(x, y); //Finds what type of tile needs to be placed at current place in map.

				switch (tileType) //Switch statement to actually create the tiles and draw them.
				{
				case bottom:
				{
					
					newTile.SetTile("./images/walls/bottom.png", x, y);

				}
				break;
				case left:
				{
					newTile.SetTile("./images/walls/left.png", x, y);

				}
				break;
				case right:
				{
					newTile.SetTile("./images/walls/right.png", x, y);
				}
				break;
				case top:
				{
					newTile.SetTile("./images/walls/top.png", x, y);
				}
				break;
				case blank:
				{
					newTile.SetTile("./images/blank.png", x, y);
				}
				break;
				case corner1:
				{
					newTile.SetTile("./images/corners/1.png", x, y);
				}
				break;
				case corner2:
				{
					newTile.SetTile("./images/corners/2.png", x, y);
				}
				break;
				case corner3:
				{
					newTile.SetTile("./images/corners/3.png", x, y);
				}
				break;
				case corner4:
				{
					newTile.SetTile("./images/corners/4.png", x, y);
				}
				break;
				case island1:
				{
					newTile.SetTile("./images/islands/1.png", x, y);
				}
				break;
				case island2:
				{
					newTile.SetTile("./images/islands/2.png", x, y);
				}
				break;
				case island3:
				{
					newTile.SetTile("./images/islands/3.png", x, y);
				}
				break;
				case island4:
				{
					newTile.SetTile("./images/islands/4.png", x, y);
				}
				break;
				}
			}
		}

		//Drawing Pellets (Taken and modified from the Enemy Movement example on Bitbucket (https://bitbucket.org/GlosGP/enemymovementsimple/src/9c2c9d6d828c20d1e69586ddd92ad9b4dca0ebc0/source/main.cpp?at=default&fileviewer=file-view-default)
		PelletProperties *pellet = new PelletProperties[pelletCount];
		PelletProperties test;
		test.DrawPellets(pellet);
		
	/*	tileType = pellet.GetTile(x, y);
		if (tileType != 0)
		{
			pellet.CreatePellet("./images/pacman/pellet.png", x, y);
		}
		Enemy &rcurrentEnemy = getEnemy(a_penemyArray, icol, irow);*/
		//Creating Pacman Sprite
		PacmanProperties pacSprite;
		pacSprite.CreatePacman();
		pacSprite.initialise();
		pacSprite.tileWidths = tileWidth;
		UG::MoveSprite(pacSprite.SpriteID, 32, 64);
		

		//Creating Ghosts
		GhostProperties blinky;
		GhostProperties pinky;
		GhostProperties inky;
		GhostProperties clyde;
		blinky.CreateGhost(0);
		pinky.CreateGhost(1);
		inky.CreateGhost(2);
		clyde.CreateGhost(3);

		blinky.initialise();
		blinky.tileWidths = tileWidth;

		pinky.initialise();
		pinky.tileWidths = tileWidth;

		inky.initialise();
		inky.tileWidths = tileWidth;

		clyde.initialise();
		clyde.tileWidths = tileWidth;

		blinky.moving = false;
		do
		{
			//Gets position of the Pacman in the level.
			
			

			//Movement for Pacman
			//GetTiles(tileQuery, pacSprite.SpriteID); //Gets the tiles around the Pacman for collision detection
			pacSprite.SetPlayerDirection(pacSprite, movementSpeed, UG::KEY_W, UG::KEY_S, UG::KEY_A, UG::KEY_D); //Sets direction on keypress
			pacSprite.MovePlayer(pacSprite, movementSpeed);//Decides whether to move Pacman depending on direction and collision
			UG::MoveSprite(pacSprite.SpriteID, pacSprite.fX, pacSprite.fY);//Moves pacman
			

			//Movement for Blinky (Red)
			//GetTiles(tileQuery,blinky.SpriteID);//Gets surrounding tiles for collision detection
			blinky.SetGhostDirection(blinky, movementSpeed);//Sets direction Randomly
			blinky.MoveGhost(blinky, movementSpeed);//Decides whether to move ghost depending on direction and collision
			UG::MoveSprite(blinky.SpriteID, blinky.fX, blinky.fY);//Moves Ghost



			//Movement for Pinky (Red)
			//GetTiles(tileQuery, pinky.SpriteID);//Gets surrounding tiles for collision detection
			pinky.SetGhostDirection(pinky, movementSpeed);//Sets direction Randomly
			pinky.MoveGhost(pinky, movementSpeed);//Decides whether to move ghost depending on direction and collision
			UG::MoveSprite(pinky.SpriteID, pinky.fX, pinky.fY);//Moves Ghost


			//Movement for Inky (Red)
			//GetTiles(tileQuery, inky.SpriteID);//Gets surrounding tiles for collision detection
			inky.SetGhostDirection(inky, movementSpeed);//Sets direction Randomly
			inky.MoveGhost(inky, movementSpeed);//Decides whether to move ghost depending on direction and collision
			UG::MoveSprite(inky.SpriteID, inky.fX, inky.fY);//Moves Ghost


			//Movement for Clyde (Red)
		//	GetTiles(tileQuery, clyde.SpriteID);//Gets surrounding tiles for collision detection
			clyde.SetGhostDirection(clyde, movementSpeed);//Sets direction Randomly
			clyde.MoveGhost(clyde, movementSpeed);//Decides whether to move ghost depending on direction and collision
			UG::MoveSprite(clyde.SpriteID, clyde.fX, clyde.fY);//Moves Ghost

			//Pellets

			test.DestroyPellets(pellet, pacSprite.mapXPos - 1, pacSprite.mapYPos - 1);








			//Debug
			
			/*std::cout << "Dir: " << blinky.ghostDirection[0] << std::endl;
			std::cout << "Dir: " << blinky.ghostDirection[1] << std::endl;
			std::cout << "Dir: " << blinky.ghostDirection[2] << std::endl;
			std::cout << "Dir: " << blinky.ghostDirection[3] << std::endl;
			std::cout << "random: " << blinky.randomNumber << std::endl;
			std::cout << "currentdir: " << blinky.GetDirection() << std::endl;
			std::cout << "moving: " << blinky.moving << std::endl;*/
			

			UG::ClearScreen();
		} while (UG::Process());

		
		delete[] pellet;
		UG::StopDrawingSprite(pacSprite.SpriteID);
		UG::DestroySprite(pacSprite.SpriteID);
		UG::Dispose();


	}
	return 0;
}

void DestroyPellets(PacmanProperties& pacSprite, PelletProperties *pellet)
{
	

	

}
