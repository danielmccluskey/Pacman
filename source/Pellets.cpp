//==============================================================================================================================
// Project: Pacman
// File: Pellets.cpp
// Author: Daniel McCluskey
// Date Created: 17/10/16
// Brief: This is the header file that contains the code that controls the mechanics of the pellets during Gameplay.
// Last Edited by: (See BitBucket Commits: https://bitbucket.org/Danielmclovin/ct4019-pacman)
//==============================================================================================================================
#include "Pellets.h"
#include "UGFW.h"
#include <iostream>
#include "stdlib.h"
#include <fstream>
#include "Pacman.h"
#include "windows.h"
#include <string>
#include <sstream>

//Map of where the pellets are placed and what types
// 1 == Small pellet
// 3 == Big pellet
int iPelletMap[1008] =
{
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
	0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,
	0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,
	0,1,1,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,1,1,0,
	0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0,
	0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0,
	0,3,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,3,0,
	0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0,
	0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0,
	0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,
	0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,
	0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,
	0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,
	0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,
	0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,
	0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,
	0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,
	0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,
	0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,
	0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,
	0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,
	0,1,1,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,1,1,0,
	0,1,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,1,0,
	0,1,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,1,0,
	0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
	0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0,
	0,3,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,3,0,
	0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0,
	0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};
void PelletProperties::CreatePellet(char* a_cImagePath, int a_iTileX, int a_iTileY)
{
	//Converts the Map position to the coordinates of the users window
	int iRealTileX = (a_iTileX * 16) + 15;
	int iRealTileY = (a_iTileY * 16) + 15;

	//Creates, moves and draws the sprite
	iSpriteID = UG::CreateSprite(a_cImagePath, 4, 4, true);
	UG::MoveSprite(iSpriteID, iRealTileX, iRealTileY);
	UG::DrawSprite(iSpriteID);
}

void PelletProperties::DrawPellets(PelletProperties *a_pellet)
{
	for (int y = 0; y < iMapHeight; ++y)  //Counts through the Y axis of the array each time the X axis completes a row
	{
		for (int x = 0; x < iMapWidth; ++x) //Counts through the X axis
		{
			PelletProperties &currentPellet = GetPellet(a_pellet, x, y);//Gets the current pellet at the point in the for loop
			int iCurrentTile = GetTile(x,y); //Gets the current tile at the point in the for loop
			if (iCurrentTile == 1)//If the current tile is a small pellet
			{
				//Converts the Map position to the coordinates of the users window
				int iRealTileX = (x * 16) + 15;
				int iRealTileY = (y * 16) + 15;

				//Creates, moves and draws the sprite
				currentPellet.iSpriteID = UG::CreateSprite("./images/pacman/pellet.png", 4, 4, true);
				UG::MoveSprite(currentPellet.iSpriteID, iRealTileX, iRealTileY);
				UG::DrawSprite(currentPellet.iSpriteID);

			}
			if (iCurrentTile == 3)//If the current tile is a Large pellet
			{
				//Converts the Map position to the coordinates of the users window
				int iRealTileX = (x * 16) + 15;
				int iRealTileY = (y * 16) + 15;

				//Creates, moves and draws the sprite
				currentPellet.iSpriteID = UG::CreateSprite("./images/pacman/pellet.png", 12, 12, true);
				UG::MoveSprite(currentPellet.iSpriteID, iRealTileX, iRealTileY);
				UG::DrawSprite(currentPellet.iSpriteID);

			}
			
		}
	}
}
void PelletProperties::FillPellets(PelletProperties *a_pellet)
{
	for (int y = 0; y < iMapHeight; ++y)  //Counts through the Y axis of the array each time the X axis completes a row
	{
		for (int x = 0; x < iMapWidth; ++x) //Counts through the X axis
		{
			PelletProperties &currentPellet = GetPellet(a_pellet, x, y);//Gets the current pellet at the point in the for loop
			int iCurrentTile = GetTile(x, y);//Gets the current tile at the point in the for loop
			if (iCurrentTile == 2)//If the current tile is a small pellet that has been eaten
			{
				//Converts the Map position to the coordinates of the users window
				int iRealTileX = (x * 16) + 15;
				int iRealTileY = (y * 16) + 15;

				//Creates, moves and draws the sprite
				currentPellet.iSpriteID = UG::CreateSprite("./images/pacman/pellet.png", 4, 4, true);
				UG::MoveSprite(currentPellet.iSpriteID, iRealTileX, iRealTileY);
				UG::DrawSprite(currentPellet.iSpriteID);

				//Resets the current tile back to uneaten
				iPelletMap[(y * 28) + x] = 1;

			}
			if (iCurrentTile == 4)
			{
				//Converts the Map position to the coordinates of the users window
				int iRealTileX = (x * 16) + 15;
				int iRealTileY = (y * 16) + 15;

				//Creates, moves and draws the sprite
				currentPellet.iSpriteID = UG::CreateSprite("./images/pacman/pellet.png", 12, 12, true);
				UG::MoveSprite(currentPellet.iSpriteID, iRealTileX, iRealTileY);
				UG::DrawSprite(currentPellet.iSpriteID);

				//Resets the current tile back to uneaten
				iPelletMap[(y * 28) + x] = 3;

			}
		}
	}
}
bool PelletProperties::DestroyPellets(PelletProperties *a_pellet, int a_iX, int a_iY)
{
	
	int iCurrentTile = GetTile(a_iX, a_iY);//Get the current tile at the current X,Y pos
	if (iCurrentTile == 1)//If the tile is a small pellet
	{
		PelletProperties &currentPellet = GetPellet(a_pellet, a_iX, a_iY);//Gets the current pellet at the point in the for loop
		iPelletMap[(a_iY * 28) + a_iX] = 2;//Set the point in the array to eaten
		iTotalScore += 10; //Add points
		iTotalPellets += 1; //Add total pellets eaten
		UG::StopDrawingSprite(currentPellet.iSpriteID);
		UG::DestroySprite(currentPellet.iSpriteID);
		PlaySound(TEXT("./sounds/chomp4.wav"), NULL, SND_FILENAME | SND_ASYNC);
		return false;
	}
	else if (iCurrentTile == 3)
	{
		PelletProperties &currentPellet = GetPellet(a_pellet, a_iX, a_iY);//Gets the current pellet at the point in the for loop
		iPelletMap[(a_iY * 28) + a_iX] = 4;//Set the point in the array to eaten
		iTotalScore += 40;//Add points
		iTotalPellets += 1;//Add total pellets eaten
		UG::StopDrawingSprite(currentPellet.iSpriteID);
		UG::DestroySprite(currentPellet.iSpriteID);
		PlaySound(TEXT("./sounds/bigPellet.wav"), NULL, SND_FILENAME | SND_ASYNC);
		return true;
	}
}

PelletProperties& PelletProperties::GetPellet(PelletProperties *a_pellet, int a_iX, int a_iY)
{
	return a_pellet[(a_iY * 28) + a_iX];//Finds and returns what pellet is at X,Y
}
int PelletProperties::GetTile(int a_iX, int a_iY)
{
	return iPelletMap[(a_iY * 28) + a_iX];//Finds and returns what tile is at X,Y
}
void PelletProperties::ClearHighScore()
{
	char* cScoresPath = "./highscores/scores.txt"; //Path to the Highscore folder
	std::ofstream HIGHSCORE;//Creates an output fstream member
	HIGHSCORE.open(cScoresPath, std::ofstream::out | std::ofstream::trunc);//Opens and Removes all of the text inside the file.
	HIGHSCORE << 0; //Adds 0 to the file
	HIGHSCORE.close(); //Closes the file.
	GetHighScore();
}
void PelletProperties::GetHighScore()
{
	char* cScoresPath = "./highscores/scores.txt"; //Path to the Highscore folder
	std::ifstream previousScore; //Creates a input fstream member
	previousScore.open(cScoresPath); //Opens the scores file under the previousScore member
	if (!previousScore) //Checks if the previous line failed, this will only run if the file didnt open correctly / if the file doesn't exist.
	{
		previousScore.open(cScoresPath, std::fstream::in | std::fstream::out | std::fstream::trunc); //Opens/Creates the File
		previousScore.close(); //Closes the file
		ClearHighScore();
	}
	previousScore >> iCurrentHighScore; //Stores the contents of the file into the varible
	previousScore.close(); //Closes the file
}

void PelletProperties::SetHighScore()
{

	char* cScoresPath = "./highscores/scores.txt"; //Path to the Highscore folder
	GetHighScore();


	std::ofstream highScores;//Creates an output fstream member
	highScores.open(cScoresPath, std::fstream::in | std::fstream::out); //Opens the file
	if (iTotalScore > iCurrentHighScore) //Checks if the current score is higher than the old highscore
	{
		highScores << iTotalScore; //Sets the contents of the file to the current score.
		iCurrentHighScore = iTotalScore;
	}
	else
	{
		std::cout << "LOWER SCORE"; //For debugging. Only runs if the current score is lower than the old highscore.
	}
	
	highScores.close();//Closes the file
}

void PelletProperties::DrawHighScore()
{
	int iScreenWidth, iScreenHeight;//Declare variables for the Screen height and Width
	UG::GetScreenSize(iScreenWidth, iScreenHeight);//Get the screensize
	UG::ClearScreen();
	UG::SetFont("./fonts/font.fnt");

	UG::DrawString("1UP", (int)(iScreenWidth * 0.16f), iScreenHeight *0.98f, 0.8f);//Draws the 1UP during Gameplay

    //Stringstream to draw the current score below the 1UP text during GAMEPLAY
	std::ostringstream SCORE;
	SCORE << iTotalScore << std::endl;
	UG::DrawString(SCORE.str().c_str(), (int)(iScreenWidth * 0.19f), iScreenHeight *0.95f, 0.8f);


	UG::DrawString("HIGH SCORE", (int)(iScreenWidth * 0.5f), iScreenHeight *0.98f, 0.8f);//Draws the HIGHSCORES text during Gameplay

	//Stringstream to draw the current highscore below HIGHSCORES during GAMEPLAY
	std::ostringstream HIGHSCORE;
	HIGHSCORE << iCurrentHighScore << std::endl;
	UG::DrawString(HIGHSCORE.str().c_str(), (int)(iScreenWidth * 0.5f), iScreenHeight *0.95f, 0.8f);
	
	
}
