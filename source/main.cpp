//==============================================================================================================================
// Project: Pacman
// File: main.cpp
// Author: Daniel McCluskey
// Date Created: 17/10/16
// Brief: This is the file that contains the code to control how the game runs. The project as a whole is a small recreation of the game Pacman using the UG framework.
// Last Edited by: (See BitBucket Commits: https://bitbucket.org/Danielmclovin/ct4019-pacman)
//==============================================================================================================================

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



//Sets the Variable for the death animation
float fDeathFrames[16][4] =
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

//Positions (Will convert to Vector 2 class later)
float fXPos, fYPos = 0;

//Width of the tiles
float iTileWidth = 16;

//Timer for the Splash screen
float fTime = 0;

//Decides the position for the selection box for the main menu
int iMenuState = 0;

float fEdibleGhostTime;

//Co-ords of the Center of the screen
int iCenterX = (iMapWidth*iTileWidth)*0.5f;
int iCenterY = (iMapHeight*iTileWidth)*0.5f;

//Screen width and height variables
int iScreenWidth, iScreenHeight;

//Holds the amount of pellets on the map to make initialising the Array easier.
int iPelletCount = iMapWidth*iMapHeight;

//Movement Speed for the player, Divided by iTileWidth to keep it Grid aligned
float fMovementSpeed = 19/ iTileWidth;

//Variable to keep track of when the game is being started for the first time
bool bGameStart = true;

void SetMenuPosition(int a_iUpperBound, int a_iLowerBound);

int main(int argv, char* argc[])
{	
	
	//Creation of the PacMan Window, Width and height is the size of the Map array multiplied by the tile images resolution.
	if (UG::Create((iMapWidth*iTileWidth), (iMapHeight*iTileWidth), false, "Pacman", 100, 100))
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
		PelletProperties *pellet = new PelletProperties[iPelletCount]; //Creates new class member using array
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


		GhostProperties *EdibleGhosts = new GhostProperties[4];
		for (int i = 0; i < 4; i++)
		{
			EdibleGhosts[i].CreateGhost(4);
		}

		GameStateProperties highScoresSprite;
		highScoresSprite.CreateSprite("./images/backgrounds/highscores.png", iCenterX, iCenterY, (iMapWidth*iTileWidth), (iMapHeight*iTileWidth));
		GameStateProperties pauseSprite;
		pauseSprite.CreateSprite("./images/backgrounds/pause.png", iCenterX, iCenterY, 700, 230);
		GameStateProperties difficultySprite;
		difficultySprite.CreateSprite("./images/backgrounds/difficulty.png", iCenterX, iCenterY, (iMapWidth*iTileWidth), (iMapHeight*iTileWidth));
		GameStateProperties menuSprite;
		menuSprite.CreateSprite("./images/backgrounds/menu.png", iCenterX, iCenterY, (iMapWidth*iTileWidth), (iMapHeight*iTileWidth));
		GameStateProperties selectSprite;
		selectSprite.CreateSprite("./images/backgrounds/selection.png", iCenterX, iCenterY, 234, 49);
		GameStateProperties splashSprite;
		splashSprite.CreateSprite("./images/backgrounds/splash.png", iCenterX, iCenterY, (iMapWidth*iTileWidth), (iMapHeight*iTileWidth));
		GameStateProperties slidingSprite; 
		slidingSprite.CreateSprite("./images/backgrounds/slide.png", ((iMapWidth*iTileWidth) + (156 / 2)), ((iMapHeight*iTileWidth)*0.55f), 156, 26);
		
		GameStateProperties deathSprite;
		deathSprite.CreateSprite("./images/pacman/deathSheets.png", (16), (16), 16, 16);
		int iCurrentState = SPLASH;

		splashSprite.ShowSprite();
		slidingSprite.ShowSprite();
		do
		{
			switch (iCurrentState)
			{
			case SPLASH:
			{
				UG::ClearScreen();				
				if (fTime == 0)
				{
					PlaySound(TEXT("./sounds/intro.wav"), NULL, SND_ASYNC);
				}//Plays Sounds
				if (fTime >= 50) //Exits the Splash screen and goes to menu
				{
					fTime = 0;
					UG::MoveSprite(slidingSprite.iSpriteID, ((iMapWidth*iTileWidth) + (156 / 2)), ((iMapHeight*iTileWidth)*0.55f));
					splashSprite.HideSprite();
					slidingSprite.HideSprite();	
					menuSprite.ShowSprite();
					selectSprite.ShowSprite();

					iCurrentState = MENU;
					break;
				}
				UG::GetSpritePosition(slidingSprite.iSpriteID, fXPos, fYPos);
				UG::MoveSprite(slidingSprite.iSpriteID, fXPos - 2.5f, fYPos);
				fTime += 0.2f;
				break;
			}
			case MENU:
			{
				SetMenuPosition(3,-1);
				switch (iMenuState)
				{
				case PLAY:
				{
					UG::MoveSprite(selectSprite.iSpriteID, iCenterX, iCenterY);
					if (UG::IsKeyDown(UG::KEY_ENTER))
					{
						iMenuState = 1;
						PlaySound(TEXT("./sounds/chomp1.wav"), NULL, SND_FILENAME | SND_SYNC);
						menuSprite.HideSprite();
						difficultySprite.ShowSprite();
						iCurrentState = DIFFICULTY;
					}
					break;
				}
				case HIGHSCORES:
				{
					if (UG::IsKeyDown(UG::KEY_ENTER))
					{
						iMenuState = 1;
						PlaySound(TEXT("./sounds/chomp1.wav"), NULL, SND_FILENAME | SND_SYNC);
						menuSprite.HideSprite();
						highScoresSprite.ShowSprite();
						iCurrentState = SCORES;
					}
					UG::MoveSprite(selectSprite.iSpriteID, iCenterX, ((iMapHeight*iTileWidth)*0.35f));
					
				}
				break;
				case QUIT:
				{
					UG::MoveSprite(selectSprite.iSpriteID, iCenterX, ((iMapHeight*iTileWidth)*0.19f));
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
				SetMenuPosition(3,-1);
				if (UG::IsKeyDown(UG::KEY_ESCAPE))
				{
					PlaySound(TEXT("./sounds/chomp1.wav"), NULL, SND_FILENAME | SND_SYNC);
					menuSprite.ShowSprite();
					difficultySprite.HideSprite();
					
					iCurrentState = MENU;
				}
				switch (iMenuState)
				{
				case EASY:
				{
					UG::MoveSprite(selectSprite.iSpriteID, iCenterX, iCenterY);
					if (UG::IsKeyDown(UG::KEY_ENTER))
					{
						iMenuState = 0;
						PlaySound(TEXT("./sounds/chomp1.wav"), NULL, SND_FILENAME | SND_SYNC);
						fMovementSpeed = 10 / iTileWidth;
						pacSprite.iLives = 3;
						fEdibleGhostTime = 100;
						difficultySprite.HideSprite();
						selectSprite.HideSprite();
						iCurrentState = GAMEPLAY;
					}
				}
				break;
				case MEDIUM:
				{
					UG::MoveSprite(selectSprite.iSpriteID, iCenterX, ((iMapHeight*iTileWidth)*0.35f));
					if (UG::IsKeyDown(UG::KEY_ENTER))
					{
						iMenuState = 0;
						fMovementSpeed = 15 / iTileWidth;
						pacSprite.iLives = 2;
						fEdibleGhostTime = 50;
						difficultySprite.HideSprite();
						selectSprite.HideSprite();
						iCurrentState = GAMEPLAY;
					}
				}
					break;
				case HARD:
				{
					UG::MoveSprite(selectSprite.iSpriteID, iCenterX, ((iMapHeight*iTileWidth)*0.19f));
					if (UG::IsKeyDown(UG::KEY_ENTER))
					{
						fMovementSpeed = 20 / iTileWidth;
						iMenuState = 0;
						pacSprite.iLives = 1;
						fEdibleGhostTime = 20;
						difficultySprite.HideSprite();
						selectSprite.HideSprite();
						iCurrentState = GAMEPLAY;
					}
				}
				break;
				}
				break;
			}
			break;
			case GAMEPLAY:
			{
				
				std::cout << pacSprite.bCanEatGhosts << std::endl;

				
				
				pellet[0].DrawHighScore();
				if (bGameStart == true)
				{

					PlaySound(TEXT("./sounds/intro.wav"), NULL, SND_FILENAME);
					
					bGameStart = false;
				}
				//Handling Pacmans movement
				pacSprite.SetPlayerDirection(pacSprite, fMovementSpeed, UG::KEY_W, UG::KEY_S, UG::KEY_A, UG::KEY_D); //Sets direction on keypress
				pacSprite.MovePlayer(pacSprite, fMovementSpeed);//Decides whether to move Pacman depending on direction and collision

				//Movement for Blinky (Red)
				blinky.SetGhostDirection(blinky, fMovementSpeed);//Sets direction Randomly
				blinky.MoveGhost(blinky, fMovementSpeed);//Decides whether to move ghost depending on direction and collision

				//Movement for Pinky (Pink)
				pinky.SetGhostDirection(pinky, fMovementSpeed);//Sets direction Randomly
				pinky.MoveGhost(pinky, fMovementSpeed);//Decides whether to move ghost depending on direction and collision

				//Movement for Inky (Blue)
				inky.SetGhostDirection(inky, fMovementSpeed);//Sets direction Randomly
				inky.MoveGhost(inky, fMovementSpeed);//Decides whether to move ghost depending on direction and collision

				//Movement for Clyde (Orange)
				clyde.SetGhostDirection(clyde, fMovementSpeed);//Sets direction Randomly
				clyde.MoveGhost(clyde, fMovementSpeed);//Decides whether to move ghost depending on direction and collision

				//Movement for Edible Ghosts
				EdibleGhosts[0].SetEdibleGhostsPos(blinky);
				EdibleGhosts[1].SetEdibleGhostsPos(pinky);
				EdibleGhosts[2].SetEdibleGhostsPos(inky);
				EdibleGhosts[3].SetEdibleGhostsPos(clyde);


				//Pellets
				bool bEatBigPellet = pellet[0].DestroyPellets(pellet, pacSprite.iMapXPos - 1, pacSprite.iMapYPos - 1);

				if (bEatBigPellet == true)//Function to destroy pellets on the same tile as Pacman
				{
					if (pacSprite.bCanEatGhosts == false)
					{
						for (int i = 0; i < 4; i++)
						{
							UG::DrawSprite(EdibleGhosts[i].iSpriteID);
						}
					}
					pacSprite.bCanEatGhosts = true;
					pacSprite.fEatGhostsTimer = fEdibleGhostTime;
					
				}
				pacSprite.SetEatGhostsTimer(EdibleGhosts[0].iSpriteID, EdibleGhosts[1].iSpriteID, EdibleGhosts[2].iSpriteID, EdibleGhosts[3].iSpriteID);


				if (pellet[0].iTotalPellets > 245)
				{
					pellet[0].iTotalPellets = 0;
					pellet[0].FillPellets(pellet);
					pacSprite.iLives += 1;
					pacSprite.SetLives(pacSprite);
					blinky.iCageTime = 200;
					pinky.iCageTime = 400;
					inky.iCageTime = 600;
					clyde.iCageTime = 700;
					PlaySound(TEXT("./sounds/intro.wav"), NULL, SND_SYNC);
				}
				//Test Collison with Ghosts
				bool collide[4] = { false, false, false, false }; //Array to see if any of the Ghosts are colliding with Pacman
				collide[0] = blinky.Pacmancollide(blinky, pacSprite.fX, pacSprite.fY);//Checks if Pacman is colliding with Blinky
				collide[1] = pinky.Pacmancollide(pinky, pacSprite.fX, pacSprite.fY);//Checks if Pacman is colliding with Pinky
				collide[2] = inky.Pacmancollide(inky, pacSprite.fX, pacSprite.fY);//Checks if Pacman is colliding with Inky
				collide[3] = clyde.Pacmancollide(clyde, pacSprite.fX, pacSprite.fY);//Checks if Pacmanis coll iding with Clyde

				//For Loop to loop through the array to see if any of the ghosts collided with Pacman



				for (int i = 0; i < 4; i++)
				{
					if (collide[i] == true && pacSprite.bCanEatGhosts == false)
					{
						fTime = 15;
						UG::MoveSprite(deathSprite.iSpriteID, pacSprite.fX, pacSprite.fY);
						pacSprite.SetLives(pacSprite);
						blinky.iCageTime = 200;
						pinky.iCageTime = 400;
						inky.iCageTime = 600;
						clyde.iCageTime = 700;
						UG::StopDrawingSprite(pacSprite.iSpriteID);
						deathSprite.ShowSprite();

						if (pacSprite.iLives < 0)
						{
							pellet[0].FillPellets(pellet);
							iCurrentState = GAMEOVER;//Sets GameState to the Menu
						}
						else
						{
							iCurrentState = DEATH;
						}
						
						
					}
					else if (collide[i] == true && pacSprite.bCanEatGhosts == true)
					{
						switch (i)
						{
						case 0:
						{
							blinky.iCageTime = 200;
						}
						break;
						case 1:
						{
							pinky.iCageTime = 400;
						}
						break;
						case 2:
						{
							inky.iCageTime = 600;
						}
						break;
						case 3:
						{
							clyde.iCageTime = 700;
						}
						break;
						}
						pellet[0].iTotalScore += 100; 
						PlaySound(TEXT("./sounds/bigPellet.wav"), NULL, SND_FILENAME);
					}
					
				}
				if (UG::IsKeyDown(UG::KEY_ESCAPE))
				{
					PlaySound(TEXT("./sounds/chomp1.wav"), NULL, SND_FILENAME | SND_SYNC);
					pauseSprite.ShowSprite();
					selectSprite.ShowSprite();
					iCurrentState = PAUSE;
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
				fTime -= 0.2f;
				if (fTime < 0)
				{
					pellet[0].SetHighScore();
					pellet[0].iTotalScore = 0;
					menuSprite.ShowSprite();//Shows the Menu sprite
					selectSprite.ShowSprite();//Shows the Selection box	
					bGameStart = true;
					deathSprite.HideSprite();
					UG::DrawSprite(pacSprite.iSpriteID);
					iCurrentState = MENU;
				}
				else
				{
					UG::SetSpriteUVCoordinates(deathSprite.iSpriteID, fDeathFrames[(int(fTime))]);
				}		
			}
			break;
			case PAUSE:
			{
				SetMenuPosition(2,-1);
				switch (iMenuState)
				{
				case EASY:
				{
					UG::MoveSprite(selectSprite.iSpriteID, iCenterX, ((iMapHeight*iTileWidth)*0.62f));
					if (UG::IsKeyDown(UG::KEY_ENTER))
					{
						iMenuState = 0;
						PlaySound(TEXT("./sounds/chomp1.wav"), NULL, SND_FILENAME | SND_SYNC);
						selectSprite.HideSprite();
						pauseSprite.HideSprite();
						iCurrentState = GAMEPLAY;
					}
					break;
				}
				case MEDIUM:
				{
					UG::MoveSprite(selectSprite.iSpriteID, iCenterX, ((iMapHeight*iTileWidth)*0.385f));
					if (UG::IsKeyDown(UG::KEY_ENTER))
					{
						iMenuState = 0;
						PlaySound(TEXT("./sounds/chomp1.wav"), NULL, SND_FILENAME | SND_SYNC);
						menuSprite.ShowSprite();
						pauseSprite.HideSprite();
						iCurrentState = MENU;
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
				std::cout << pellet[0].iCurrentHighScore << std::endl;

				SetMenuPosition(3,0);
				switch (iMenuState)
				{
				case HIGHSCORES:
				{
					UG::MoveSprite(selectSprite.iSpriteID, iCenterX, (iMapHeight*iTileWidth)*0.35f);
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
						iMenuState = 0;
						PlaySound(TEXT("./sounds/chomp1.wav"), NULL, SND_FILENAME | SND_SYNC);
						highScoresSprite.HideSprite();
						menuSprite.ShowSprite();
						iCurrentState = MENU;
					}
					UG::MoveSprite(selectSprite.iSpriteID, iCenterX, ((iMapHeight*iTileWidth)*0.19f));
					break;
				}
				}
			}
			break;

			case DEATH:
			{

				fTime -= 0.2f;
				if (fTime < 0)
				{
					UG::DrawSprite(pacSprite.iSpriteID);
					deathSprite.HideSprite();
					PlaySound(TEXT("./sounds/intro.wav"), NULL, SND_SYNC);
					iCurrentState = GAMEPLAY;
				}
				else
				{
					UG::SetSpriteUVCoordinates(deathSprite.iSpriteID, fDeathFrames[(int(fTime))]);
				}
			}
			break;
			}
			
		} while (UG::Process());
		delete[] pellet;
		UG::RemoveFont("./fonts/invaders.fnt");
		UG::StopDrawingSprite(pacSprite.iSpriteID);
		UG::DestroySprite(pacSprite.iSpriteID);
		UG::Dispose();
	}
	return 0;
}
void SetMenuPosition(int a_iUpperBound, int a_iLowerBound)
{
	if (UG::IsKeyDown(UG::KEY_S))
	{
		++iMenuState;
		PlaySound(TEXT("./sounds/chomp1.wav"), NULL, SND_FILENAME | SND_SYNC);
	}
	if (UG::IsKeyDown(UG::KEY_W))
	{
		--iMenuState;
		PlaySound(TEXT("./sounds/chomp1.wav"), NULL, SND_FILENAME | SND_SYNC);
	}
	if (iMenuState >= a_iUpperBound)
	{
		iMenuState = a_iLowerBound + 1;
	}
	if (iMenuState <= a_iLowerBound)
	{
		iMenuState = a_iUpperBound - 1;
	}
}