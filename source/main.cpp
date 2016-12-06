#include "UGFW.h"
#include "MapCreation.h"
#include "Enumerations.h"
#include "Ghosts.h"
#include "Pacman.h"
#include "CustomEnum.h"
#include "Pellets.h"


#include "windows.h"
#include <iostream>
#include <string>
#include <sstream>
#pragma comment(lib, "winmm.lib")

//==============================================================================================================================
// File: Pong
// Author: Daniel McCluskey
// Date Created: 17/10/16
// Brief: This is a small recreation of the game Pacman using the UOG Framework.
// Last Edited by: (See BitBucket Commits: https://bitbucket.org/Danielmclovin/ct4019-pacman)
//==============================================================================================================================


//Definition of the Gamestates enumeration
typedef enum GameStates
{
	SPLASH,
	MENU,
	GAMEPLAY,
	GAMEOVER
}GameState;


//Positions (Will convert to Vector 2 class later)
float xPos, yPos = 0;

//Width of the tiles
float tileWidth = 16;

//Holds the amount of pellets on the map to make initialising the Array easier.
int pelletCount = mapWidth*mapHeight;

int splashSprite;

//Movement Speed for the player, Divided by tileWidth to keep it Grid aligned
float movementSpeed = 19/tileWidth;
void playSound(char* filePath);
int main(int argv, char* argc[])
{
	
	//Creation of the PacMan Window, Width and height is the size of the Map array multiplied by the tile images resolution.
	if (UG::Create((mapWidth*tileWidth), (mapHeight*tileWidth), false, "Pacman", 100, 100))
	{
		
		//Adds the font for the text displayed on Screen.
		UG::AddFont("./fonts/invaders.fnt");

		//Draws the background map with individual tiled images
		TileProperties newTile;
		newTile.DrawMap();

		//Drawing Pellets (Method used and modified from the Enemy Movement example on Bitbucket by Jstewart2: (https://bitbucket.org/GlosGP/enemymovementsimple/src/9c2c9d6d828c20d1e69586ddd92ad9b4dca0ebc0/source/main.cpp?at=default&fileviewer=file-view-default)
		PelletProperties *pellet = new PelletProperties[pelletCount]; //Creates new class member using array
		pellet[0].DrawPellets(pellet); //Draws the pellets on to the screen
		
		//Creating Pacman Sprite
		PacmanProperties pacSprite; //Creates new class member.
		pacSprite.CreatePacman(); //Creates the sprite and draws it.
		
		
		//Creating Ghosts
		GhostProperties blinky; //Creates a new class member for the ghost Blinky
		GhostProperties pinky;//Creates a new class member for the ghost Pinky
		GhostProperties inky;//Creates a new class member for the ghost Inky
		GhostProperties clyde;//Creates a new class member for the ghost Clyde

		
		blinky.CreateGhost(0);//Creates the Sprite and moves Blinky to their starting position
		pinky.CreateGhost(1);//Creates the Sprite and moves Pinky to their starting position
		inky.CreateGhost(2);//Creates the Sprite and moves Inky to their starting position
		clyde.CreateGhost(3);//Creates the Sprite and moves Clyde ghost to their starting position
		float ftime = 0;

		int currentState = SPLASH;
		bool start = false;
		splashSprite = UG::CreateSprite("./images/backgrounds/splash.png", 448, 576, true);
		UG::DrawSprite(splashSprite);
		UG::MoveSprite(splashSprite, ((mapWidth*tileWidth)*0.5f), ((mapHeight*tileWidth)*0.5f));
		do
		{
			switch (currentState)
			{
			case SPLASH:
				
				UG::ClearScreen();
				
				
				if (ftime >= 2)
				{
					ftime = 0;
					
					UG::ClearScreen();

					PlaySound(TEXT("./sounds/intro.wav"), NULL, SND_FILENAME);//Plays sound without lag but doesn't return until sound has finished.
					//Plays sound and returns instantly but is extremely laggy.
					UG::MoveSprite(splashSprite, (mapWidth*tileWidth)+(448/2),0);
					currentState = GAMEPLAY;
					
					
					
				}
				
				ftime += 0.2f;
				break;

			case MENU:
			

			case GAMEPLAY:
			{
				
				//Handling Pacmans movement
				pacSprite.SetPlayerDirection(pacSprite, movementSpeed, UG::KEY_W, UG::KEY_S, UG::KEY_A, UG::KEY_D); //Sets direction on keypress
				pacSprite.MovePlayer(pacSprite, movementSpeed);//Decides whether to move Pacman depending on direction and collision
				if (start == false)
				{
					
					start = true;
				}

															   //Movement for Blinky (Red)
				blinky.SetGhostDirection(blinky, movementSpeed);//Sets direction Randomly
				blinky.MoveGhost(blinky, movementSpeed);//Decides whether to move ghost depending on direction and collision

														//Movement for Pinky (Red)
				pinky.SetGhostDirection(pinky, movementSpeed);//Sets direction Randomly
				pinky.MoveGhost(pinky, movementSpeed);//Decides whether to move ghost depending on direction and collision

													  //Movement for Inky (Red)
				inky.SetGhostDirection(inky, movementSpeed);//Sets direction Randomly
				inky.MoveGhost(inky, movementSpeed);//Decides whether to move ghost depending on direction and collision

													//Movement for Clyde (Red)
				clyde.SetGhostDirection(clyde, movementSpeed);//Sets direction Randomly
				clyde.MoveGhost(clyde, movementSpeed);//Decides whether to move ghost depending on direction and collision

													  //Pellets
				pellet[0].DestroyPellets(pellet, pacSprite.mapXPos - 1, pacSprite.mapYPos - 1);

				//Test Collison with Ghosts
				bool collide[4] = { false, false, false, false };
				collide[0] = blinky.Pacmancollide(blinky, pacSprite.fX, pacSprite.fY);
				collide[1] = pinky.Pacmancollide(pinky, pacSprite.fX, pacSprite.fY);
				collide[2] = inky.Pacmancollide(inky, pacSprite.fX, pacSprite.fY);
				collide[3] = clyde.Pacmancollide(clyde, pacSprite.fX, pacSprite.fY);

				for (int i = 0; i < 4; i++)
				{
					if (collide[i] == true)
					{
						std::cout << "COLLIDE" << std::endl;
						PlaySound(TEXT("./sounds/death.wav"), NULL, SND_FILENAME);
						UG::MoveSprite(splashSprite, ((mapWidth*tileWidth)*0.5f), ((mapHeight*tileWidth)*0.5f));
						currentState = SPLASH;
					}
				}
				std::ostringstream ssConverter;

				ssConverter << "Pellets Collected: " << pellet[0].pelletsCollected;

				UG::SetFont("./fonts/invaders.fnt");
				UG::DrawString(ssConverter.str().c_str(), (int)(mapWidth * 0.19f), mapHeight - 2, 1.f);

				UG::ClearScreen();
				break;
			}
				break;
			case GAMEOVER:
				break;
			}
			
			
			
		} while (UG::Process());

		
		delete[] pellet;
		UG::StopDrawingSprite(pacSprite.SpriteID);
		UG::DestroySprite(pacSprite.SpriteID);
		UG::Dispose();


	}
	return 0;
}
void playSound(char* filePath)
{
	PlaySound(TEXT(filePath), NULL, SND_ASYNC);

}