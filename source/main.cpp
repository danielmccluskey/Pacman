#include "UGFW.h"
#include "MapCreation.h"
#include "Enumerations.h"
#include "Ghosts.h"
#include "Pacman.h"
#include "CustomEnum.h"
#include "Pellets.h"
#include "GameStates.h"

#include "stdlib.h"
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

//Sets the random clock to produce more random patterns for the ghosts.


//Positions (Will convert to Vector 2 class later)
float xPos, yPos = 0;

//Width of the tiles
float tileWidth = 16;

//Timer for the Splash screen
float ftime = 0;

//Decides the position for the selection box for the main menu
int menuState = 0;

//Co-ords of the Center of the screen
int iCenterX = (mapWidth*tileWidth)*0.5f;
int iCenterY = (mapHeight*tileWidth)*0.5f;

//Holds the amount of pellets on the map to make initialising the Array easier.
int pelletCount = mapWidth*mapHeight;

//Movement Speed for the player, Divided by tileWidth to keep it Grid aligned
float movementSpeed = 19/tileWidth;

//Variable to keep track of when the game is being started for the first time
bool gameStart = true;


int main(int argv, char* argc[])
{	
	
	//Creation of the PacMan Window, Width and height is the size of the Map array multiplied by the tile images resolution.
	if (UG::Create((mapWidth*tileWidth), (mapHeight*tileWidth), false, "Pacman", 100, 100))
	{		
		//Adds the font for the text displayed on Screen.
	//	UG::AddFont("./fonts/invaders.fnt");
		std::cout << "hey";
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


		GameStateProperties difficultySprite;
		difficultySprite.CreateSprite("./images/backgrounds/difficulty.png", iCenterX, iCenterY, (mapWidth*tileWidth), (mapHeight*tileWidth));
		GameStateProperties menuSprite;
		menuSprite.CreateSprite("./images/backgrounds/menu.png", iCenterX, iCenterY, (mapWidth*tileWidth), (mapHeight*tileWidth));
		GameStateProperties selectSprite;
		selectSprite.CreateSprite("./images/backgrounds/selection.png", iCenterX, iCenterY, 234, 49);
		GameStateProperties splashSprite;
		splashSprite.CreateSprite("./images/backgrounds/splash.png", iCenterX, iCenterY, (mapWidth*tileWidth), (mapHeight*tileWidth));
		GameStateProperties slidingSprite;
		slidingSprite.CreateSprite("./images/backgrounds/slide.png", ((mapWidth*tileWidth) + (156 / 2)), ((mapHeight*tileWidth)*0.55f), 156, 26);
		int currentState = SPLASH;
		do
		{
			switch (currentState)
			{
			case SPLASH:
			{
				UG::ClearScreen();				
				if (ftime == 0)
				{
					PlaySound(TEXT("./sounds/intro.wav"), NULL, SND_ASYNC);
				}//Plays Sound
				if (ftime >= 50) //Exits the Splash screen and goes to menu
				{
					ftime = 0;
					UG::MoveSprite(slidingSprite.SpriteID, ((mapWidth*tileWidth) + (156 / 2)), ((mapHeight*tileWidth)*0.55f));
					splashSprite.HideSprite();
					slidingSprite.HideSprite();					
					currentState = MENU;
					break;
				}
				UG::GetSpritePosition(slidingSprite.SpriteID, xPos, yPos);
				UG::MoveSprite(slidingSprite.SpriteID, xPos - 2.5f, yPos);
				ftime += 0.2f;
				break;
			}
			case MENU:
			{
				if (UG::IsKeyDown(UG::KEY_S))
				{
					++menuState;
					PlaySound(TEXT("./sounds/chomp1.wav"), NULL, SND_FILENAME | SND_SYNC);
				}
				if (UG::IsKeyDown(UG::KEY_W))
				{
					--menuState;
					PlaySound(TEXT("./sounds/chomp1.wav"), NULL, SND_FILENAME | SND_SYNC);
				}
				if (menuState >= 3)
				{
					menuState = 0;
				}
				if (menuState <= -1)
				{
					menuState = 2;
				}
				switch (menuState)
				{
				case PLAY:
				{
					UG::MoveSprite(selectSprite.SpriteID, iCenterX, iCenterY);
					if (UG::IsKeyDown(UG::KEY_ENTER))
					{
						menuState = 0;
						PlaySound(TEXT("./sounds/chomp1.wav"), NULL, SND_FILENAME | SND_SYNC);
						menuSprite.HideSprite();
						//difficultySprite.ShowSprite();
						currentState = DIFFICULTY;
					}
					break;
				}
				case HIGHSCORES:
				{
					UG::MoveSprite(selectSprite.SpriteID, iCenterX, ((mapHeight*tileWidth)*0.35f));
					break;
				}
				case QUIT:
				{
					UG::MoveSprite(selectSprite.SpriteID, iCenterX, ((mapHeight*tileWidth)*0.19f));
					if (UG::IsKeyDown(UG::KEY_ENTER))
					{
						PlaySound(TEXT("./sounds/death.wav"), NULL, SND_FILENAME | SND_SYNC);
						UG::Close();
					}
				}
				}
				break;
			}

			case DIFFICULTY:
			{

				if (UG::IsKeyDown(UG::KEY_S))
				{
					++menuState;
					PlaySound(TEXT("./sounds/chomp1.wav"), NULL, SND_FILENAME | SND_SYNC);
				}
				if (UG::IsKeyDown(UG::KEY_W))
				{
					--menuState;
					PlaySound(TEXT("./sounds/chomp1.wav"), NULL, SND_FILENAME | SND_SYNC);
				}
				if (menuState >= 3)
				{
					menuState = 0;
				}
				if (menuState <= -1)
				{
					menuState = 2;
				}
				switch (menuState)
				{
				case EASY:
				{
					UG::MoveSprite(selectSprite.SpriteID, iCenterX, iCenterY);
					if (UG::IsKeyDown(UG::KEY_ENTER))
					{
						menuState = 0;
						PlaySound(TEXT("./sounds/chomp1.wav"), NULL, SND_FILENAME | SND_SYNC);
						movementSpeed = 10 / tileWidth;
						pacSprite.lives = 2;
						difficultySprite.HideSprite();
						selectSprite.HideSprite();
						currentState = GAMEPLAY;
					}
				}


					break;
				case MEDIUM:
				{
					UG::MoveSprite(selectSprite.SpriteID, iCenterX, ((mapHeight*tileWidth)*0.35f));
					if (UG::IsKeyDown(UG::KEY_ENTER))
					{
						menuState = 0;
						movementSpeed = 15 / tileWidth;
						pacSprite.lives = 1;
						difficultySprite.HideSprite();
						selectSprite.HideSprite();
						currentState = GAMEPLAY;
					}
					break;
				}
				case HARD:
				{
					UG::MoveSprite(selectSprite.SpriteID, iCenterX, ((mapHeight*tileWidth)*0.19f));
					if (UG::IsKeyDown(UG::KEY_ENTER))
					{
						movementSpeed = 20 / tileWidth;
						menuState = 0;
						pacSprite.lives = 0;
						difficultySprite.HideSprite();
						selectSprite.HideSprite();
						currentState = GAMEPLAY;
					}
					break;
				}

				}
				break;
			}
			case GAMEPLAY:
			{
				if (gameStart == true)
				{
					PlaySound(TEXT("./sounds/intro.wav"), NULL, SND_FILENAME);
					
					gameStart = false;
				}

				//Handling Pacmans movement
				pacSprite.SetPlayerDirection(pacSprite, movementSpeed, UG::KEY_W, UG::KEY_S, UG::KEY_A, UG::KEY_D); //Sets direction on keypress
				pacSprite.MovePlayer(pacSprite, movementSpeed);//Decides whether to move Pacman depending on direction and collision

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
				pellet[0].DestroyPellets(pellet, pacSprite.mapXPos - 1, pacSprite.mapYPos - 1); //Function to destroy pellets on the same tile as Pacman

				blinky.SetCageTime();
				pinky.SetCageTime();
				inky.SetCageTime();
				clyde.SetCageTime();

				//Test Collison with Ghosts
				bool collide[4] = { false, false, false, false }; //Array to see if any of the Ghosts are colliding with Pacman
				collide[0] = blinky.Pacmancollide(blinky, pacSprite.fX, pacSprite.fY,100);//Checks if Pacman is colliding with Blinky
				collide[1] = pinky.Pacmancollide(pinky, pacSprite.fX, pacSprite.fY,300);//Checks if Pacman is colliding with Pinky
				collide[2] = inky.Pacmancollide(inky, pacSprite.fX, pacSprite.fY,400);//Checks if Pacman is colliding with Inky
				collide[3] = clyde.Pacmancollide(clyde, pacSprite.fX, pacSprite.fY,600);//Checks if Pacman is colliding with Clyde

				//For Loop to loop through the array to see if any of the ghosts collided with Pacman
				for (int i = 0; i < 4; i++)
				{
					if (collide[i] == true)
					{
						pacSprite.SetLives();
						if (pacSprite.lives < 0)
						{

							menuSprite.ShowSprite();//Shows the Menu sprite
							selectSprite.ShowSprite();//Shows the Selection box						
							currentState = MENU;//Sets GameState to the Menu
						}
						
					}
				}


				std::ostringstream ssConverter;
				//ssConverter << "Pellets Collected: " << pellet[0].pelletsCollected << "Lives: " << pacSprite.lives;
				//ssConverter << "test";
			//	UG::SetFont("./fonts/invaders.fnt");
				//UG::DrawString(ssConverter.str().c_str(), (int)(mapWidth * 0.19f), mapHeight - 2, 1.f);
				//UG::ClearScreen();
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