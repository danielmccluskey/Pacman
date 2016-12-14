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



//Sets the Variable for frames of the death animation
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

//Variables for Positions
float fXPos, fYPos = 0;

//Variable to define the Width of the tiles
float fTileWidth = 16;

//Timer for the Splash screen
float fTime = 0;

//Decides the position for the selection box for the main menu
int iMenuState = 0;

//Sets the time that the player can eat the ghosts for after collecting a big pellet.
float fEdibleGhostTime;

//Co-ords of the Center of the screen
float fCenterX = (fMapWidth*fTileWidth)*0.5f;
float fCenterY = (fMapHeight*fTileWidth)*0.5f;

//Screen width and height variables
int iScreenWidth, iScreenHeight;

//Holds the amount of pellets on the map to make initialising the Array easier.
int iPelletCount = fMapWidth*fMapHeight;

//Movement Speed for the player, Divided by iTileWidth to keep it Grid aligned
float fMovementSpeed = 19/ fTileWidth;

//Variable to keep track of when the game is being started for the first time
bool bGameStart = true;

void SetMenuPosition(int a_iUpperBound, int a_iLowerBound);

int main(int argv, char* argc[])
{	
	
	//Creation of the PacMan Window, Width and height is the size of the Map array multiplied by the tile images resolution.
	if (UG::Create((fMapWidth*fTileWidth), (fMapHeight*fTileWidth), false, "Pacman", 100, 100))
	{		
		//Adds the font for the text displayed on Screen.
		UG::AddFont("./fonts/font.fnt");

		//Sets the Background colour
		UG::SetBackgroundColor(0x0f0f0f);
		
		//Gets screen size
		UG::GetScreenSize(iScreenWidth, iScreenHeight);
		
		
		//Draws the background map with individual tiled images
		TileProperties newTile;//Creates new class member
		newTile.DrawMap();//Draws the map on to the screen	

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

		//Creating Edible Ghosts
		GhostProperties *EdibleGhosts = new GhostProperties[4]; //Creates a class member using an array for the Ghosts pacman can eat.
		for (int i = 0; i < 4; i++)
		{
			EdibleGhosts[i].CreateGhost(4);//Creates the Sprite and moves the Edible Ghost to their relative Ghost
		}

		GameStateProperties highScoresSprite; //Creates new class member for the High Score menu sprite.
		highScoresSprite.CreateSprite("./images/backgrounds/highscores.png", fCenterX, fCenterY, (fMapWidth*fTileWidth), (fMapHeight*fTileWidth)); //Creates the sprite, Sizes it and moves it to the correct position

		GameStateProperties pauseSprite; //Creates new class member for the Pause menu sprite.
		pauseSprite.CreateSprite("./images/backgrounds/pause.png", fCenterX, fCenterY, 700, 230);//Creates the sprite, Sizes it and moves it to the correct position

		GameStateProperties difficultySprite; //Creates new class member for the Difficulty menu sprite.
		difficultySprite.CreateSprite("./images/backgrounds/difficulty.png", fCenterX, fCenterY, (fMapWidth*fTileWidth), (fMapHeight*fTileWidth));//Creates the sprite, Sizes it and moves it to the correct position

		GameStateProperties menuSprite; //Creates new class member for the Main menu sprite.
		menuSprite.CreateSprite("./images/backgrounds/menu.png", fCenterX, fCenterY, (fMapWidth*fTileWidth), (fMapHeight*fTileWidth));//Creates the sprite, Sizes it and moves it to the correct position

		GameStateProperties selectSprite; //Creates new class member for the Selection box sprite.
		selectSprite.CreateSprite("./images/backgrounds/selection.png", fCenterX, fCenterY, 234, 49);//Creates the sprite, Sizes it and moves it to the correct position

		GameStateProperties splashSprite; //Creates new class member for the Splash screen sprite.
		splashSprite.CreateSprite("./images/backgrounds/splash.png", fCenterX, fCenterY, (fMapWidth*fTileWidth), (fMapHeight*fTileWidth));//Creates the sprite, Sizes it and moves it to the correct position

		GameStateProperties slidingSprite; //Creates new class member for the Sliding sprite on the Splash screen.
		slidingSprite.CreateSprite("./images/backgrounds/slide.png", ((fMapWidth*fTileWidth) + (156 / 2)), ((fMapHeight*fTileWidth)*0.55f), 156, 26);//Creates the sprite, Sizes it and moves it to the correct position
		
		GameStateProperties deathSprite;//Creates new class member for the Death animation that plays when the player dies.
		deathSprite.CreateSprite("./images/pacman/deathSheets.png", (fTileWidth), (fTileWidth), fTileWidth, fTileWidth);//Creates the sprite, Sizes it and moves it to the correct position

		int iCurrentState = SPLASH; //Sets the Game State to the Splash screen.
		splashSprite.ShowSprite(); //Draws the Splash screen image
		slidingSprite.ShowSprite();//Draws the sliding sprite image
		do
		{
			
			switch (iCurrentState)//Main Switch statement to control the Gamestates of the game e.g. Pause, Menu, Diffiuclty, Gameplay etc
			{
			case SPLASH:
			{
				UG::ClearScreen(); //Clears the Screen				
				if (fTime == 0) //Will only execute on the first frame of the program.
				{
					PlaySound(TEXT("./sounds/intro.wav"), NULL, SND_ASYNC); //Plays the Pacman intro sound.
				}//Plays Sounds
				if (fTime >= 50) //Exits the Splash screen and goes to menu
				{
					fTime = 0;//Resets the timer
					UG::MoveSprite(slidingSprite.iSpriteID, ((fMapWidth*fTileWidth) + (156 / 2)), ((fMapHeight*fTileWidth)*0.55f));//Moves the sliding sprite back to the starting position
					splashSprite.HideSprite(); //Hides the Splash screen from view (Stops Drawing)
					slidingSprite.HideSprite();	//Hides the Sliding Sprite from view (Stops Drawing)
					menuSprite.ShowSprite();//Draws the Main menu screen image
					selectSprite.ShowSprite();//Draws the Selection box image

					iCurrentState = MENU; //Sets the Current GameState to the Main menu
					break;
				}
				UG::GetSpritePosition(slidingSprite.iSpriteID, fXPos, fYPos); //Gets the current position of the sliding sprite
				UG::MoveSprite(slidingSprite.iSpriteID, fXPos - 2.5f, fYPos); //Moves the Sliding sprite along the screen every frame
				fTime += 0.2f;//Increases the timers value.
				break;
			}
			case MENU:
			{
				SetMenuPosition(3,-1);//Controls the value of iMenuState for the switch statement
				switch (iMenuState)
				{
				case PLAY:
				{
					UG::MoveSprite(selectSprite.iSpriteID, fCenterX, fCenterY); //Moves the Selection box to the center of the screen
					if (UG::IsKeyDown(UG::KEY_ENTER))
					{
						iMenuState = 1; //Resets the menu state
						PlaySound(TEXT("./sounds/chomp1.wav"), NULL, SND_FILENAME | SND_SYNC); //Plays a sound and hangs the program until finished, this makes the program wait for a second to avoid the keypress being carried over into the next gamestate
						menuSprite.HideSprite();//Hides the menu sprite from view
						difficultySprite.ShowSprite();//Draws the difficulty menu.
						iCurrentState = DIFFICULTY;//Changes the GameState to Difficulty menu
					}
					break;
				}
				case HIGHSCORES:
				{
					if (UG::IsKeyDown(UG::KEY_ENTER))
					{
						iMenuState = 1;//Resets the menu state
						PlaySound(TEXT("./sounds/chomp1.wav"), NULL, SND_FILENAME | SND_SYNC);//Plays a sound and hangs the program until finished, this makes the program wait for a second to avoid the keypress being carried over into the next gamestate
						menuSprite.HideSprite();//Hides the menu sprite from view
						highScoresSprite.ShowSprite();//Draws the HighScores menu.
						iCurrentState = SCORES;//Changes the GameState to HighScores menu
					}
					UG::MoveSprite(selectSprite.iSpriteID, fCenterX, ((fMapHeight*fTileWidth)*0.35f));//Moves the Selection box to the next menu item on the screen
					
				}
				break;
				case QUIT:
				{
					UG::MoveSprite(selectSprite.iSpriteID, fCenterX, ((fMapHeight*fTileWidth)*0.19f));//Moves the Selection box to the next menu item on the screen
					if (UG::IsKeyDown(UG::KEY_ENTER))
					{
						PlaySound(TEXT("./sounds/death.wav"), NULL, SND_FILENAME | SND_SYNC);//Plays a sound and hangs the program until finished, this makes the program wait for a second to avoid the keypress being carried over into the next gamestate
						UG::Close();//Closes the program
					}
				}
				break;
				}
				break;
			}

			case DIFFICULTY:
			{
				SetMenuPosition(3,-1);//Controls the value of iMenuState for the switch statement

				if (UG::IsKeyDown(UG::KEY_ESCAPE))//Returns to the main menu
				{
					PlaySound(TEXT("./sounds/chomp1.wav"), NULL, SND_FILENAME | SND_SYNC);//Plays a sound and hangs the program until finished, this makes the program wait for a second to avoid the keypress being carried over into the next gamestate
					menuSprite.ShowSprite();//Draws the menu sprite
					difficultySprite.HideSprite();//Hides the Difficulty sprite
					
					iCurrentState = MENU; //Changes the Current GameState to Main menu
				}
				switch (iMenuState)
				{
				case EASY:
				{
					UG::MoveSprite(selectSprite.iSpriteID, fCenterX, fCenterY);//Moves the Selection box to the center of the screen
					if (UG::IsKeyDown(UG::KEY_ENTER))
					{
						iMenuState = 0;//Resets the Menu states
						PlaySound(TEXT("./sounds/chomp1.wav"), NULL, SND_FILENAME | SND_SYNC);//Plays a sound and hangs the program until finished, this makes the program wait for a second to avoid the keypress being carried over into the next gamestate
						fMovementSpeed = 10 / fTileWidth; //Sets the movement speed relative to the difficulty
						pacSprite.iLives = 3;//Sets the lives relative to the chosen diffiuclty
						fEdibleGhostTime = 100;//Sets the amount of time the ghosts can be eaten for after eatinga big pellet relative to the chosen difficulty
						difficultySprite.HideSprite();//Hides the Diffiuclty sprite
						selectSprite.HideSprite();//Hides the Selection box sprite
						iCurrentState = GAMEPLAY;//Sets the Current GameState to GAMEPLAY
					}
				}
				break;
				case MEDIUM:
				{
					UG::MoveSprite(selectSprite.iSpriteID, fCenterX, ((fMapHeight*fTileWidth)*0.35f));//Moves the Selection box to the next menu item on the screen
					if (UG::IsKeyDown(UG::KEY_ENTER))
					{
						iMenuState = 0;//Resets the Menu states
						fMovementSpeed = 15 / fTileWidth;//Sets the movement speed relative to the difficulty
						pacSprite.iLives = 2;//Sets the lives relative to the chosen diffiuclty
						fEdibleGhostTime = 50;//Sets the amount of time the ghosts can be eaten for after eatinga big pellet relative to the chosen difficulty
						difficultySprite.HideSprite();//Hides the Diffiuclty sprite
						selectSprite.HideSprite();//Hides the Selection box sprite
						iCurrentState = GAMEPLAY;//Sets the Current GameState to GAMEPLAY
					}
				}
					break;
				case HARD:
				{
					UG::MoveSprite(selectSprite.iSpriteID, fCenterX, ((fMapHeight*fTileWidth)*0.19f));//Moves the Selection box to the next menu item on the screen
					if (UG::IsKeyDown(UG::KEY_ENTER))
					{
						iMenuState = 0;//Resets the Menu states
						fMovementSpeed = 20 / fTileWidth;//Sets the movement speed relative to the difficulty						
						pacSprite.iLives = 1;//Sets the lives relative to the chosen diffiuclty
						fEdibleGhostTime = 20;//Sets the amount of time the ghosts can be eaten for after eatinga big pellet relative to the chosen difficulty
						difficultySprite.HideSprite();//Hides the Diffiuclty sprite
						selectSprite.HideSprite();//Hides the Selection box sprite
						iCurrentState = GAMEPLAY;//Sets the Current GameState to GAMEPLAY
					}
				}
				break;
				}
				break;
			}
			break;
			case GAMEPLAY:
			{
				pellet[0].DrawHighScore(); //Draws the score at the top of the screen
				if (bGameStart == true)//Will only execute when the game starts for the first time
				{
					PlaySound(TEXT("./sounds/intro.wav"), NULL, SND_FILENAME);//Hangs the program and plays the intro song
					
					bGameStart = false;//REsets the starting variable
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
				EdibleGhosts[0].SetEdibleGhostsPos(blinky);//Moves the Edible ghost to its relative ghost
				EdibleGhosts[1].SetEdibleGhostsPos(pinky);//Moves the Edible ghost to its relative ghost
				EdibleGhosts[2].SetEdibleGhostsPos(inky);//Moves the Edible ghost to its relative ghost
				EdibleGhosts[3].SetEdibleGhostsPos(clyde);//Moves the Edible ghost to its relative ghost


				//Pellets
				bool bEatBigPellet = pellet[0].DestroyPellets(pellet, pacSprite.iMapXPos - 1, pacSprite.iMapYPos - 1); //Quick check to see what type of pellet the player has just gone over.

				if (bEatBigPellet == true)//If the player went over a big pellet
				{
					if (pacSprite.bCanEatGhosts == false)//If the user is not already in Eat ghosts mode.
					{
						for (int i = 0; i < 4; i++)
						{
							UG::DrawSprite(EdibleGhosts[i].iSpriteID);//Draws all of the Edible ghosts to view.
						}
					}
					pacSprite.bCanEatGhosts = true;//Enables Pacman to eat ghosts
					pacSprite.fEatGhostsTimer = fEdibleGhostTime;//Sets the Eating timer to the relative difficulty timer
					
				}
				pacSprite.SetEatGhostsTimer(EdibleGhosts[0].iSpriteID, EdibleGhosts[1].iSpriteID, EdibleGhosts[2].iSpriteID, EdibleGhosts[3].iSpriteID);//Controls the timer and stops drawing the Edible sprites when the timer runs out


				if (pellet[0].iTotalPellets > 245) //If the player has collected all of the pellets
				{
					pellet[0].iTotalPellets = 0;//Reset the pellet count
					pellet[0].FillPellets(pellet);//Refill the map with Pellets
					pacSprite.iLives += 1;//Add a life so I can use the Death sequence to reset the game for efficiency
					pacSprite.SetLives(pacSprite);//Death sequence (Resets Position and direction etc.)
					
					//Sets the Cage time for the relative ghost
					blinky.iCageTime = 200;
					pinky.iCageTime = 400;
					inky.iCageTime = 600;
					clyde.iCageTime = 700;
					PlaySound(TEXT("./sounds/intro.wav"), NULL, SND_FILENAME);//Plays the intro sound file and hangs the program until finished
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
					if (collide[i] == true && pacSprite.bCanEatGhosts == false) //If they have collided and the player is not in Eat ghosts  mode
					{
						fTime = 15;//Set the Death animation timer
						UG::MoveSprite(deathSprite.iSpriteID, pacSprite.fX, pacSprite.fY);//Move the death sprite to the position of the pacman
						pacSprite.SetLives(pacSprite);//Death sequence (Resets Position and direction etc.)

						//Sets the Cage time for the relative ghost
						blinky.iCageTime = 200;
						pinky.iCageTime = 400;
						inky.iCageTime = 600;
						clyde.iCageTime = 700;

						UG::StopDrawingSprite(pacSprite.iSpriteID);//Stop drawing pacman so the Death sprite can be shown
						deathSprite.ShowSprite();//Draw the death sprite

						if (pacSprite.iLives < 0)//If the player runs out of lives
						{
							pellet[0].FillPellets(pellet);//Refilles the map with pellets
							iCurrentState = GAMEOVER;//Sets GameState to the Gameover
						}
						else
						{
							iCurrentState = DEATH;//Sets the current GameState to DEATH
						}
						
						
					}
					else if (collide[i] == true && pacSprite.bCanEatGhosts == true)//If the player collides and is in Eat ghosts mode
					{
						switch (i)
						{
						case 0:
						{
							blinky.iCageTime = 200;//Sets the cage time for the relative ghost
						}
						break;
						case 1:
						{
							pinky.iCageTime = 400;//Sets the cage time for the relative ghost
						}
						break;
						case 2:
						{
							inky.iCageTime = 600;//Sets the cage time for the relative ghost
						}
						break;
						case 3:
						{
							clyde.iCageTime = 700;//Sets the cage time for the relative ghost
						}
						break;
						}
						pellet[0].iTotalScore += 100; //Adds 100 score
						PlaySound(TEXT("./sounds/bigPellet.wav"), NULL, SND_FILENAME);//Plays the eat ghost sound
					}
					
				}
				if (UG::IsKeyDown(UG::KEY_ESCAPE))
				{
					PlaySound(TEXT("./sounds/chomp1.wav"), NULL, SND_FILENAME);//Play the chomp sound and hang the program
					pauseSprite.ShowSprite();//Show the pause menu
					selectSprite.ShowSprite();//Show the selection box
					iCurrentState = PAUSE;//Set the current GameState to PAUSE
				}


				//Controls the tiemr for the amount of time the ghosts are in the cage in the middle.
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
				fTime -= 0.2f;//Takes away from the timer value
				if (fTime < 0)//If the timer goes below 0
				{
					pellet[0].SetHighScore();//Sets the highscore if currentscore is higher
					pellet[0].iTotalScore = 0;//Sets teh score to 0
					menuSprite.ShowSprite();//Shows the Menu sprite
					selectSprite.ShowSprite();//Shows the Selection box	
					bGameStart = true;//Resets the gamestart variable
					deathSprite.HideSprite();//hides the Death animation sprite
					UG::DrawSprite(pacSprite.iSpriteID);//Draws pacman
					iCurrentState = MENU;//Sets the current GameState to the main menu
				}
				else
				{
					UG::SetSpriteUVCoordinates(deathSprite.iSpriteID, fDeathFrames[(int(fTime))]);//Controls the death animation going through the frames from the 2D array declared on line 29
				}		
			}
			break;
			case PAUSE:
			{
				SetMenuPosition(2,-1);//Controls the position of the selection box
				switch (iMenuState)
				{
				case EASY:
				{
					UG::MoveSprite(selectSprite.iSpriteID, fCenterX, ((fMapHeight*fTileWidth)*0.62f));//Moves the selection box to the relative position
					if (UG::IsKeyDown(UG::KEY_ENTER))
					{
						iMenuState = 0;//Resets the menu state
						PlaySound(TEXT("./sounds/chomp1.wav"), NULL, SND_FILENAME);//Plays the chomp sound and hangs the program
						selectSprite.HideSprite();//Hides the selection sprite
						pauseSprite.HideSprite();//Hides the pause menu sprite
						iCurrentState = GAMEPLAY;//Sets the current GameState back to Gameplay
					}
					break;
				}
				case MEDIUM:
				{
					UG::MoveSprite(selectSprite.iSpriteID, fCenterX, ((fMapHeight*fTileWidth)*0.385f));//Moves the selection box to the relative position
					if (UG::IsKeyDown(UG::KEY_ENTER))
					{
						iMenuState = 0;//Resets the menu state
						PlaySound(TEXT("./sounds/chomp1.wav"), NULL, SND_FILENAME);//Plays the chomp sound and hangs the program
						pacSprite.iLives = -1;//Removes lives
						pacSprite.fX = blinky.fX;//Moves Pacman to position of Ghost to initiate reset sequence
						pacSprite.fY = blinky.fY;//Moves Pacman to position of Ghost to initiate reset sequence
						selectSprite.HideSprite();//Hides the selection sprite
						pauseSprite.HideSprite();//Hides the pause menu sprite
						iCurrentState = GAMEPLAY;//Sets the current GameState to the Main menu
					}
				}
				break;
				}
			}
			break;
			case SCORES:
			{

				std::ostringstream HIGHSCORE;//Opens a string stream to display the highscores
				HIGHSCORE << pellet[0].iCurrentHighScore << std::endl;//Inserts the highscore value into the String stream
				UG::DrawString(HIGHSCORE.str().c_str(), (int)(iScreenWidth * 0.5f), iScreenHeight *0.5f, 1.f);//Draws the string stream

				SetMenuPosition(3,0);//Controls the position of the selection box
				switch (iMenuState)
				{
				case HIGHSCORES:
				{
					UG::MoveSprite(selectSprite.iSpriteID, fCenterX, (fMapHeight*fTileWidth)*0.35f);//Moves the Selection box to its relative positoon
					if (UG::IsKeyDown(UG::KEY_ENTER))
					{
						pellet[0].ClearHighScore();//Resets the highscore
					}
					break;
				}
				case QUIT:
				{
					if (UG::IsKeyDown(UG::KEY_ENTER))
					{
						iMenuState = 0;//REsets the menu state
						PlaySound(TEXT("./sounds/chomp1.wav"), NULL, SND_FILENAME);//Plays a sound and hangs the program so that the keypresses are not carried over into the next menu
						highScoresSprite.HideSprite();//Hides the highscores menu from view
						menuSprite.ShowSprite();//Shows the main menu
						iCurrentState = MENU;//Sets the current gamestate to the main menu
					}
					UG::MoveSprite(selectSprite.iSpriteID, fCenterX, ((fMapHeight*fTileWidth)*0.19f));//Moves the Selection box to its relative positoon
					break;
				}
				}
			}
			break;

			case DEATH:
			{

				fTime -= 0.2f;//Subtracts from the timer every frame
				if (fTime < 0)//If the timer runs out
				{
					UG::DrawSprite(pacSprite.iSpriteID);//Draw pacman
					deathSprite.HideSprite();//Hide the death sprite
					PlaySound(TEXT("./sounds/intro.wav"), NULL, SND_FILENAME | SND_SYNC);//Plays a sound and hangs the program
					iCurrentState = GAMEPLAY;//Sets the Current gamestate back to GAMEPALY
				}
				else
				{
					UG::SetSpriteUVCoordinates(deathSprite.iSpriteID, fDeathFrames[(int(fTime))]);//Controls the death animation going through the frames from the 2D array declared on line 29
				}
			}
			break;
			}
			
		} while (UG::Process());

		//Disposal of sprites and arrays
		delete[] pellet;
		delete[] EdibleGhosts;
		UG::RemoveFont("./fonts/invaders.fnt");
		
		UG::DestroySprite(pacSprite.iSpriteID);
		UG::DestroySprite(blinky.iSpriteID);
		UG::DestroySprite(pinky.iSpriteID);
		UG::DestroySprite(inky.iSpriteID);
		UG::DestroySprite(clyde.iSpriteID);
		UG::DestroySprite(highScoresSprite.iSpriteID);
		UG::DestroySprite(pauseSprite.iSpriteID);
		UG::DestroySprite(difficultySprite.iSpriteID);
		UG::DestroySprite(menuSprite.iSpriteID);
		UG::DestroySprite(selectSprite.iSpriteID);
		UG::DestroySprite(splashSprite.iSpriteID);
		UG::DestroySprite(slidingSprite.iSpriteID);
		UG::DestroySprite(deathSprite.iSpriteID);
		UG::Dispose();
	}
	return 0;
}
void SetMenuPosition(int a_iUpperBound, int a_iLowerBound)//Controls the position of the selection box
{
	if (UG::IsKeyDown(UG::KEY_S))
	{
		++iMenuState;
		PlaySound(TEXT("./sounds/chomp1.wav"), NULL, SND_FILENAME | SND_SYNC);//Plays a sound and hangs the program so that the keypresses are not carried over into the next frame instantly
	}
	if (UG::IsKeyDown(UG::KEY_W))
	{
		--iMenuState;
		PlaySound(TEXT("./sounds/chomp1.wav"), NULL, SND_FILENAME | SND_SYNC);//Plays a sound and hangs the program so that the keypresses are not carried over into the next frame instantly
	}
	if (iMenuState >= a_iUpperBound)//If the menu exceeds the upper bound of the menu
	{
		iMenuState = a_iLowerBound + 1;//Set it to one above the lower bound
	}
	if (iMenuState <= a_iLowerBound)//If the menu goes below the lower bound of the menu
	{
		iMenuState = a_iUpperBound - 1;//Set it to one below the upper bound
	}
}