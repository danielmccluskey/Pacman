#include "Pellets.h"
#include "UGFW.h"
#include <iostream>
#include "stdlib.h"
#include <fstream>
#include "Pacman.h"
#include "windows.h"
#include <string>
#include <sstream>

int pelletMap[1008] =
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
	0,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,0,
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
	0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0,
	0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0,
	0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};
void PelletProperties::CreatePellet(char* imagePath, int iTileX, int iTileY)
{
	int tileX = (iTileX * 16) + 15;
	int tileY = (iTileY * 16) + 15;
	SpriteID = UG::CreateSprite(imagePath, 4, 4, true);
	UG::MoveSprite(SpriteID, tileX, tileY);
	UG::DrawSprite(SpriteID);
}

void PelletProperties::DrawPellets(PelletProperties *pellet)
{
	for (int y = 0; y < iMapHeight; ++y)  //Counts through the Y axis of the array each time the X axis completes a row
	{
		for (int x = 0; x < iMapWidth; ++x) //Counts through the X axis
		{
			PelletProperties &currentPellet = GetPellet(pellet, x, y);
			int currentTile = GetTile(x,y);
			if (currentTile == 1)
			{
					currentPellet.SpriteID = UG::CreateSprite("./images/pacman/pellet.png", 4, 4, true);
					//Otherwise duplicate the sprite that the enemy at 0,0 has.
					int tileX = (x * 16) + 15;
					int tileY = (y * 16) + 15;
					UG::MoveSprite(currentPellet.SpriteID, tileX, tileY);
					UG::DrawSprite(currentPellet.SpriteID);

			}
			
		}
	}
}
void PelletProperties::DestroyPellets(PelletProperties *pellet, int x, int y)
{
	
	int currentTile = GetTile(x, y);
	if (currentTile == 1)
	{
		PelletProperties &currentPellet = GetPellet(pellet, x, y);
		pelletMap[(y * 28) + x] = 2;
		pelletsCollected += 10;
		UG::StopDrawingSprite(currentPellet.SpriteID);
		UG::DestroySprite(currentPellet.SpriteID);
		PlaySound(TEXT("./sounds/chomp4.wav"), NULL, SND_FILENAME | SND_ASYNC);
		
	}
}

PelletProperties& PelletProperties::GetPellet(PelletProperties *pellet, int x, int y)
{
	return pellet[(y * 28) + x];
}
int PelletProperties::GetTile(int x, int y)
{
	return pelletMap[(y * 28) + x];
}
void PelletProperties::GetHighScore()
{
	char* scoresPath = "./highscores/scores.txt"; //Path to the Highscore folder
	std::ifstream previousScore; //Creates a input fstream member
	previousScore.open(scoresPath); //Opens the scores file under the previousScore member
	if (!previousScore) //Checks if the previous line failed, this will only run if the file didnt open correctly / if the file doesn't exist.
	{
		previousScore.open(scoresPath, std::fstream::in | std::fstream::out | std::fstream::trunc); //Opens/Creates the File
		previousScore.close(); //Closes the file
		//iCurrentHighScore = 0;
	}
	previousScore >> iCurrentHighScore; //Stores the contents of the file into the varible
	previousScore.close(); //Closes the file
}

void PelletProperties::SetHighScore()
{

	char* scoresPath = "./highscores/scores.txt"; //Path to the Highscore folder
	GetHighScore();


	std::ofstream highScores;//Creates a output fstream member
	highScores.open(scoresPath, std::fstream::in | std::fstream::out); //Opens the file
	if (pelletsCollected > iCurrentHighScore) //Checks if the current score is higher than the old highscore
	{
		highScores << pelletsCollected; //Sets the contents of the file to the current score.
		iCurrentHighScore = pelletsCollected;
	}
	else
	{
		std::cout << "LOWER SCORE"; //For debugging. Only runs if the current score is lower than the old highscore.
	}
	
	highScores.close();//Closes the file
}

void PelletProperties::DrawHighScore()
{
	int iScreenWidth, iScreenHeight;
	UG::GetScreenSize(iScreenWidth, iScreenHeight);
	UG::ClearScreen();
	UG::SetFont("./fonts/font.fnt");

	UG::DrawString("1UP", (int)(iScreenWidth * 0.16f), iScreenHeight *0.98f, 0.8f);

	std::ostringstream SCORE;
	SCORE << pelletsCollected << std::endl;
	UG::DrawString(SCORE.str().c_str(), (int)(iScreenWidth * 0.19f), iScreenHeight *0.95f, 0.8f);

	UG::DrawString("HIGH SCORE", (int)(iScreenWidth * 0.5f), iScreenHeight *0.98f, 0.8f);

	std::ostringstream HIGHSCORE;
	HIGHSCORE << iCurrentHighScore << std::endl;
	UG::DrawString(HIGHSCORE.str().c_str(), (int)(iScreenWidth * 0.5f), iScreenHeight *0.95f, 0.8f);
	
	
}
