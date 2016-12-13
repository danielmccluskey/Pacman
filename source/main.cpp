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

float deathFrames[16][4] =
{
	{ .75f,.0f,1.f,.25f },
	{ .5f,.0f,.75f,.25f },
	{ .25f,.0f,.5f,.25f },
	{ 0.f,.0f,.25f,.25f },
	{ .75f,.25f,1.f,.5f },
	{ .5f,.25f,.75f,.5f },
	{ .25f,.25f,.5f,.5f },
	{ 0.f,.25f,.25f,.5f },
	{ .75f,.5f,1.f,.75f },
	{ .5f,.5f,.75f,.75f },
	{ .25f,.5f,.5f,.75f },
	{ 0.f,.5f,.25f,.75f },
	{ .75f,.75f,1.f,1.f },
	{ .5f,.75f,.75f,1.f },
	{ .25f,.75f,.5f,1.f },
	{ 0.f,.75f,.25f,1.f }


};
//Sets the random clock to produce more random patterns for the ghosts.
//Sets the Variable for the death animation

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

//Screen width and height variables
int iScreenWidth, iScreenHeight;

//Holds the amount of pellets on the map to make initialising the Array easier.
int pelletCount = mapWidth*mapHeight;

//Movement Speed for the player, Divided by tileWidth to keep it Grid aligned
float movementSpeed = 19/tileWidth;

//Variable to keep track of when the game is being started for the first time
bool gameStart = true;

void Reset(PacmanProperties& pacSprite);

int main(int argv, char* argc[])
{	
	
	//Creation of the PacMan Window, Width and height is the size of the Map array multiplied by the tile images resolution.
	if (UG::Create((mapWidth*tileWidth), (mapHeight*tileWidth), false, "Pacman", 100, 100))
	{		
		//Adds the font for the text displayed on Screen.
		UG::AddFont("./fonts/font.fnt");
		UG::SetBackgroundColor(0x0f0f0f);
		//Gets screen size
		UG::GetScreenSize(iScreenWidth, iScreenHeight);
		//Draws the background map with individual tiled images
		TileProperties newTile;
		newTile.DrawMap();
		//Drawing Pellets (Method used and modified from the Enemy Movement example on Bitbucket by Jstewart2: (https://bitbucket.org/GlosGP/enemymovementsimple/src/9c2c9d6d828c20d1e69586ddd92ad9b4dca0ebc0/source/main.cpp?at=default&fileviewer=file-view-default)
		PelletProperties *pellet = new PelletProperties[pelletCount]; //Creates new class member using array
		pellet[0].DrawPellets(pellet); //Draws the pellets on to the screen	
		pellet[0].GetHighScore();//Gets the Highscore from a file.
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
		GameStateProperties highScoresSprite;
		highScoresSprite.CreateSprite("./images/backgrounds/highscores.png", iCenterX, iCenterY, (mapWidth*tileWidth), (mapHeight*tileWidth));
		GameStateProperties pauseSprite;
		pauseSprite.CreateSprite("./images/backgrounds/pause.png", iCenterX, iCenterY, 700, 230);
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

		splashSprite.ShowSprite();
		slidingSprite.ShowSprite();
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
				}//Plays Sounds
				if (ftime >= 50) //Exits the Splash screen and goes to menu
				{
					ftime = 0;
					UG::MoveSprite(slidingSprite.SpriteID, ((mapWidth*tileWidth) + (156 / 2)), ((mapHeight*tileWidth)*0.55f));
					splashSprite.HideSprite();
					slidingSprite.HideSprite();	
					menuSprite.ShowSprite();
					selectSprite.ShowSprite();

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
						menuState = 1;
						PlaySound(TEXT("./sounds/chomp1.wav"), NULL, SND_FILENAME | SND_SYNC);
						menuSprite.HideSprite();
						difficultySprite.ShowSprite();
						currentState = DIFFICULTY;
					}
					break;
				}
				case HIGHSCORES:
				{
					if (UG::IsKeyDown(UG::KEY_ENTER))
					{
						menuState = 1;
						PlaySound(TEXT("./sounds/chomp1.wav"), NULL, SND_FILENAME | SND_SYNC);
						menuSprite.HideSprite();
						highScoresSprite.ShowSprite();
						currentState = SCORES;
					}
					UG::MoveSprite(selectSprite.SpriteID, iCenterX, ((mapHeight*tileWidth)*0.35f));
					
				}
				break;
				case QUIT:
				{
					UG::MoveSprite(selectSprite.SpriteID, iCenterX, ((mapHeight*tileWidth)*0.19f));
					if (UG::IsKeyDown(UG::KEY_ENTER))
					{
						PlaySound(TEXT("./sounds/death.wav"), NULL, SND_FILENAME | SND_SYNC);
						UG::Close();
					}
				}
				break;
				}
				break;
			}

			case DIFFICULTY:
			{
				if (UG::IsKeyDown(UG::KEY_ESCAPE))
				{
					PlaySound(TEXT("./sounds/chomp1.wav"), NULL, SND_FILENAME | SND_SYNC);
					menuSprite.ShowSprite();
					difficultySprite.HideSprite();
					currentState = MENU;
				}
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

				}
					break;
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
					
				}
				break;
				}
				break;
			}
			break;
			case GAMEPLAY:
			{
				pellet[0].DrawHighScore();
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

				//Movement for Pinky (Pink)
				pinky.SetGhostDirection(pinky, movementSpeed);//Sets direction Randomly
				pinky.MoveGhost(pinky, movementSpeed);//Decides whether to move ghost depending on direction and collision

				//Movement for Inky (Blue)
				inky.SetGhostDirection(inky, movementSpeed);//Sets direction Randomly
				inky.MoveGhost(inky, movementSpeed);//Decides whether to move ghost depending on direction and collision

				//Movement for Clyde (Orange)
				clyde.SetGhostDirection(clyde, movementSpeed);//Sets direction Randomly
				clyde.MoveGhost(clyde, movementSpeed);//Decides whether to move ghost depending on direction and collision

				//Pellets
				pellet[0].DestroyPellets(pellet, pacSprite.mapXPos - 1, pacSprite.mapYPos - 1); //Function to destroy pellets on the same tile as Pacman

				

				//Test Collison with Ghosts
				bool collide[4] = { false, false, false, false }; //Array to see if any of the Ghosts are colliding with Pacman
				collide[0] = blinky.Pacmancollide(blinky, pacSprite.fX, pacSprite.fY);//Checks if Pacman is colliding with Blinky
				collide[1] = pinky.Pacmancollide(pinky, pacSprite.fX, pacSprite.fY);//Checks if Pacman is colliding with Pinky
				collide[2] = inky.Pacmancollide(inky, pacSprite.fX, pacSprite.fY);//Checks if Pacman is colliding with Inky
				collide[3] = clyde.Pacmancollide(clyde, pacSprite.fX, pacSprite.fY);//Checks if Pacman is colliding with Clyde

				//For Loop to loop through the array to see if any of the ghosts collided with Pacman
				
				for (int i = 0; i < 4; i++)
				{
					
					if (collide[i] == true)
					{
						
						pacSprite.SetLives(pacSprite);
						blinky.cageTime = 200;
						pinky.cageTime = 400;
						inky.cageTime = 600;
						clyde.cageTime = 700;

						if (pacSprite.lives < 0)
						{
							pellet[0].FillPellets(pellet);
							ftime = 15;
							UG::SetSpriteTexture(pacSprite.SpriteID, "./images/pacman/deathSheets.png");
							currentState = GAMEOVER;//Sets GameState to the Menu
						}
						
					}
				}
				if (UG::IsKeyDown(UG::KEY_ESCAPE))
				{
					PlaySound(TEXT("./sounds/chomp1.wav"), NULL, SND_FILENAME | SND_SYNC);
					pauseSprite.ShowSprite();
					selectSprite.ShowSprite();
					currentState = PAUSE;
				}
				
				blinky.SetCageTime();
				pinky.SetCageTime();
				inky.SetCageTime();
				clyde.SetCageTime();

				UG::ClearScreen();
				break;
			}
				break;
			case GAMEOVER:
			{
				ftime -= 0.1f;


				if (ftime < 0)
				{
					pellet[0].SetHighScore();
					pellet[0].pelletsCollected = 0;
					menuSprite.ShowSprite();//Shows the Menu sprite
					selectSprite.ShowSprite();//Shows the Selection box	
					gameStart = true;
					UG::SetSpriteTexture(pacSprite.SpriteID, "./images/pacman/pacmanSheet.png");
					currentState = MENU;
				}
				else
				{
					
					UG::SetSpriteUVCoordinates(pacSprite.SpriteID, deathFrames[(int(ftime))]);
				}

				
			}
			break;
			case PAUSE:
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
				if (menuState >= 2)
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
					UG::MoveSprite(selectSprite.SpriteID, iCenterX, ((mapHeight*tileWidth)*0.62f));
					if (UG::IsKeyDown(UG::KEY_ENTER))
					{
						menuState = 0;
						PlaySound(TEXT("./sounds/chomp1.wav"), NULL, SND_FILENAME | SND_SYNC);
						selectSprite.HideSprite();
						pauseSprite.HideSprite();
						currentState = GAMEPLAY;
					}
					break;
				}
				case MEDIUM:
				{
					UG::MoveSprite(selectSprite.SpriteID, iCenterX, ((mapHeight*tileWidth)*0.385f));
					if (UG::IsKeyDown(UG::KEY_ENTER))
					{
						menuState = 0;
						PlaySound(TEXT("./sounds/chomp1.wav"), NULL, SND_FILENAME | SND_SYNC);
						menuSprite.ShowSprite();
						pauseSprite.HideSprite();
						currentState = MENU;
					}
				}
				break;
				}
			}
			break;
			case SCORES:
			{

				std::ostringstream HIGHSCORE;
				HIGHSCORE << pellet[0].iCurrentHighScore << std::endl;
				UG::DrawString(HIGHSCORE.str().c_str(), (int)(iScreenWidth * 0.5f), iScreenHeight *0.5f, 1.f);


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
					menuState = 1;
				}
				if (menuState <= 0)
				{
					menuState = 2;
				}
				switch (menuState)
				{
				case HIGHSCORES:
				{
					UG::MoveSprite(selectSprite.SpriteID, iCenterX, (mapHeight*tileWidth)*0.35f);
					if (UG::IsKeyDown(UG::KEY_ENTER))
					{
						pellet[0].ClearHighScore();
					}
					break;
				}
				case QUIT:
				{
					if (UG::IsKeyDown(UG::KEY_ENTER))
					{
						menuState = 0;
						PlaySound(TEXT("./sounds/chomp1.wav"), NULL, SND_FILENAME | SND_SYNC);
						highScoresSprite.HideSprite();
						menuSprite.ShowSprite();
						currentState = MENU;
					}
					UG::MoveSprite(selectSprite.SpriteID, iCenterX, ((mapHeight*tileWidth)*0.19f));
					break;
				}
				}
			}
			break;


			}
			
		} while (UG::Process());
		delete[] pellet;
		UG::RemoveFont("./fonts/invaders.fnt");
		UG::StopDrawingSprite(pacSprite.SpriteID);
		UG::DestroySprite(pacSprite.SpriteID);
		UG::Dispose();
	}
	return 0;
}
void Reset(PacmanProperties& pacSprite)
{
	
}