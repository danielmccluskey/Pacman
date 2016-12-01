#include "UGFW.h"
#include "MapCreation.h"
#include "Enumerations.h"
#include "Ghosts.h"
#include "Pacman.h"
#include "CustomEnum.h"
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

//Positions
float xPos, yPos = 0;
float tileWidth = 16;

//Movement Speed for the player, Divided by tileWidth to keep it Grid aligned
float movementSpeed = 25/tileWidth;

//Tiles for collision
int tileTop, tileBottom, tileRight, tileLeft;
int mapXPos, mapYPos;
//Structure for the Pacman



void GetTiles(TileProperties& tileQuery, int spriteID);

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


		do
		{
			 //Gets position of the Pacman in the level.
			TileProperties tileQuery;//Defines a new class thing, this was the only way I could figure out how to use classes, will fix in future
			

			//Movement for Pacman
			GetTiles(tileQuery, pacSprite.SpriteID); //Gets the tiles around the Pacman for collision detection
			pacSprite.SetPlayerDirection(pacSprite, movementSpeed, UG::KEY_W, UG::KEY_S, UG::KEY_A, UG::KEY_D, tileTop, tileRight, tileLeft, tileBottom); //Sets direction on keypress
			pacSprite.MovePlayer(pacSprite, movementSpeed, tileTop, tileRight, tileLeft, tileBottom);//Decides whether to move Pacman depending on direction and collision
			UG::MoveSprite(pacSprite.SpriteID, pacSprite.pacXPos, pacSprite.pacYPos);//Moves pacman

			//Movement for Blinky (Red)
			GetTiles(tileQuery,blinky.SpriteID);//Gets surrounding tiles for collision detection
			blinky.SetGhostDirection(blinky, movementSpeed, UG::KEY_UP, UG::KEY_S, UG::KEY_A, UG::KEY_D, tileTop, tileRight, tileLeft, tileBottom);//Sets direction Randomly
			blinky.MoveGhost(blinky, movementSpeed, tileTop, tileRight, tileLeft, tileBottom);//Decides whether to move ghost depending on direction and collision
			UG::MoveSprite(blinky.SpriteID, blinky.ghostXPos, blinky.ghostYPos);//Moves Ghost



			//Movement for Pinky (Red)
			GetTiles(tileQuery, pinky.SpriteID);//Gets surrounding tiles for collision detection
			pinky.SetGhostDirection(pinky, movementSpeed, UG::KEY_UP, UG::KEY_S, UG::KEY_A, UG::KEY_D, tileTop, tileRight, tileLeft, tileBottom);//Sets direction Randomly
			pinky.MoveGhost(pinky, movementSpeed, tileTop, tileRight, tileLeft, tileBottom);//Decides whether to move ghost depending on direction and collision
			UG::MoveSprite(pinky.SpriteID, pinky.ghostXPos, pinky.ghostYPos);//Moves Ghost


			//Movement for Inky (Red)
			GetTiles(tileQuery, inky.SpriteID);//Gets surrounding tiles for collision detection
			inky.SetGhostDirection(inky, movementSpeed, UG::KEY_UP, UG::KEY_S, UG::KEY_A, UG::KEY_D, tileTop, tileRight, tileLeft, tileBottom);//Sets direction Randomly
			inky.MoveGhost(inky, movementSpeed, tileTop, tileRight, tileLeft, tileBottom);//Decides whether to move ghost depending on direction and collision
			UG::MoveSprite(inky.SpriteID, inky.ghostXPos, inky.ghostYPos);//Moves Ghost


			//Movement for Clyde (Red)
			GetTiles(tileQuery, clyde.SpriteID);//Gets surrounding tiles for collision detection
			clyde.SetGhostDirection(clyde, movementSpeed, UG::KEY_UP, UG::KEY_S, UG::KEY_A, UG::KEY_D, tileTop, tileRight, tileLeft, tileBottom);//Sets direction Randomly
			clyde.MoveGhost(clyde, movementSpeed, tileTop, tileRight, tileLeft, tileBottom);//Decides whether to move ghost depending on direction and collision
			UG::MoveSprite(clyde.SpriteID, clyde.ghostXPos, clyde.ghostYPos);//Moves Ghost

			//pinky.SetGhostDirection;
			//inky.SetGhostDirection;
			//clyde.SetGhostDirection;

			
			//pinky.MoveGhost;
			//inky.MoveGhost;
			//clyde.MoveGhost;
			

			std::cout << "Tile Top: " << tileTop << std::endl;
			std::cout << "Tile Bottom: " << tileBottom << std::endl;
			std::cout << "Tile Left: " << tileLeft << std::endl;
			std::cout << "Tile Right: " << tileRight << std::endl;

			std::cout << "\nxPos: " << pacSprite.pacXPos << std::endl;
			std::cout << "yPos: " << pacSprite.pacYPos << "\n\n\n" << std::endl;

			std::cout << "\nMoving: " << pacSprite.moving << std::endl;
			std::cout << "Next Pos: " << pacSprite.nextTile << "\n\n\n" << std::endl;
			std::cout << "Dir: " << pacSprite.playerDirection[0] << std::endl;
			std::cout << "Dir: " << pacSprite.playerDirection[1] << std::endl;
			std::cout << "Dir: " << pacSprite.playerDirection[2] << std::endl;
			std::cout << "Dir: " << pacSprite.playerDirection[3] << std::endl;


			UG::ClearScreen();
		} while (UG::Process());

		/*UG::StopDrawingSprite(pacSprite.SpriteID);
		UG::DestroySprite(pacSprite.SpriteID);
		UG::Dispose();*/


	}
	return 0;
}

void GetTiles(TileProperties& tileQuery, int spriteID)
{
	UG::GetSpritePosition(spriteID, xPos, yPos);
	mapXPos = (xPos) / tileWidth;
	mapYPos = (yPos) / tileWidth;
	tileTop = tileQuery.GetTile(mapXPos - 1, (mapYPos));
	tileLeft = tileQuery.GetTile((mapXPos - 2), mapYPos - 1);
	tileRight = tileQuery.GetTile((mapXPos), mapYPos - 1);
	tileBottom = tileQuery.GetTile(mapXPos - 1, (mapYPos - 2));
}


