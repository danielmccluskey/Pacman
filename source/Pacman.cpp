//==============================================================================================================================
// Project: Pacman
// File: Pacman.cpp
// Author: Daniel McCluskey
// Date Created: 17/10/16
// Brief: This is the header file that contains the code that controls the mechanics and behaviour of Pacman during Gameplay.
// Last Edited by: (See BitBucket Commits: https://bitbucket.org/Danielmclovin/ct4019-pacman)
//==============================================================================================================================
#include "Pacman.h"
#include "UGFW.h"
#include "stdlib.h"
#include "CustomEnum.h"
#include "windows.h"
#include <iostream>

//The collision map for pacman
int iPacmanMap[1008] =
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
void PacmanProperties::SetSpriteFrame()
{
	fTimer += 0.2f;
	int iFirstFrame = 0;
	int iSecondFrame = 1;
	float iSpriteFrames[8][4] = 
	{
		{ 0.f,0.f,.5f,.25f}, //Up Open/
		{ 0.f,.5f,.5f,.75f },//Up Closed
		{ .5f,0.f,1.f,.25f },//East Open
		{ .5f,.5f,1.f,.75f },//East Closed
		{ 0.f,.25f,.5f,.5f },//South Open
		{ 0.f,.75f,.5f,1.f },//South Closed
		{ .5f,.25f,1.f,.5f },//West Open
		{ .5f,.75f,1.f,1.f }//West Closed
	};


	

	//If and If else block to set the appropriate first and second frame for the animated frames of pacman
	if (bPlayerDirection[north] == true)
	{
		iFirstFrame = 0;
		iSecondFrame = 1;		
	}
	else if (bPlayerDirection[south] == true)
	{
		iFirstFrame = 4;
		iSecondFrame = 5;
	}
	else if (bPlayerDirection[west] == true)
	{
		iFirstFrame = 6;
		iSecondFrame = 7;
	}
	else if (bPlayerDirection[east] == true)
	{
		iFirstFrame = 2;
		iSecondFrame = 3;
	}
	if (fTimer < 1)
	{
		UG::SetSpriteUVCoordinates(iSpriteID, iSpriteFrames[iFirstFrame]);//Updates the UV to the first frame if the fTimer is between 1 and 2
	}
	else
	{
		UG::SetSpriteUVCoordinates(iSpriteID, iSpriteFrames[iSecondFrame]);//Updates the UV to the first frame if the fTimer is between 0 and 1
	}
	if (fTimer > 2)
	{
		fTimer = 0;//Reset fTimer
	}
}

void PacmanProperties::SetEatGhostsTimer(int a_iA, int a_iB, int a_iC, int a_iD)
{
	if (fEatGhostsTimer > -1)
	{
		fEatGhostsTimer -= 0.1f;
	}
	
	if (fEatGhostsTimer < 0 && bCanEatGhosts == true)
	{
		
		bCanEatGhosts = false;//Stops eat ghosts mode
		//Stops drawing the relative edible ghosts
		UG::StopDrawingSprite(a_iA);
		UG::StopDrawingSprite(a_iB);
		UG::StopDrawingSprite(a_iC);
		UG::StopDrawingSprite(a_iD);
	}
}


void PacmanProperties::SetLives(PacmanProperties& a_pacSprite)
{
	--iLives;//Take away a life
	initialise();//Reset directional and movement values

	//Set the positional values to the starting posotion
	fX = 32;
	fY = 64;

	PlaySound(TEXT("./sounds/death.wav"), NULL, SND_FILENAME | SND_ASYNC);//Plays Death sound
	bPlayerDirection[east] = true;//Reset directional and movement values
}

//Creating Sprite
void PacmanProperties::CreatePacman()
{
	iSpriteID = UG::CreateSprite("./images/pacman/pacmanSheet.png", iSpriteWidth, iSpriteWidth, true);//Create the sprite
	UG::DrawSprite(iSpriteID);	//Draws it
	initialise(); //Reset directional and movement values
	UG::MoveSprite(iSpriteID, 32, 64); //Moves Pacman to starting Position
	UG::SetSpriteUVCoordinates(iSpriteID, .5f, .5f, 1.f, .75f);//Set Starting UV coordinates (Faceing right)
	bPlayerDirection[east] = true;//Reset directional and movement values
}



int PacmanProperties::GetTile(int a_iX, int a_iY)
{
	return iPacmanMap[(a_iY * 28) + a_iX];//Finds and returns what tile is at X,Y
}
void PacmanProperties::GetTiles()
{
	iMapXPos = (fX) / iTileWidths;
	iMapYPos = (fY) / iTileWidths;

	//Finds what tile is at the appropriate value e.g. iTileTop will get the tile above pacman
	//GetTile(x,y) will get the tile top right of pacman so adjustments are made within with integers.
	iTileTop = GetTile(iMapXPos - 1, (iMapYPos));
	iTileLeft = GetTile((iMapXPos - 2), iMapYPos - 1);
	iTileRight = GetTile((iMapXPos), iMapYPos - 1);
	iTileBottom = GetTile(iMapXPos - 1, (iMapYPos - 2));
	iTileCurrent = GetTile((iMapXPos - 1), iMapYPos - 1);
}

void PacmanProperties::SetPlayerDirection(PacmanProperties& a_pacSprite, float a_fMovementSpeed, short a_upKey, short a_downKey, short a_leftKey, short a_rightKey)
{
	GetTiles();//Get All the tiles around pacman

	//Code for the side tunnels that teleport pacman
	if (iTileRight == 8)
	{
		//Teleport pacman to the other tunnel
		fX = 432;
		fY = 304;

		initialise();//Reset directional and movement values
		bPlayerDirection[west] = true;//Make the player go in the opposite direction from the starting direction
	}
	if (iTileLeft == 6)
	{
		//Teleport pacman to the other tunnel
		fX = 32;
		fY = 304;
		initialise();//Reset directional and movement values
		bPlayerDirection[east] = true;//Make the player go in the opposite direction from the starting direction
	}
	if (bMoving == false)
	{

		//If Block to change the direction based on keypress and the tiles around pacman
		//Direction cannot be changed if the tile in that direction is 0
		if (UG::IsKeyDown(a_upKey) && iTileTop != 0)
		{
			initialise();//Reset directional and movement values
			bPlayerDirection[north] = true;//Set player direction
			
		}
		if (UG::IsKeyDown(a_downKey) && iTileBottom != 0)
		{
			initialise();//Reset directional and movement values
			bPlayerDirection[south] = true;//Set player direction
			
		}
		if (UG::IsKeyDown(a_leftKey) && iTileLeft != 0)
		{
			initialise();//Reset directional and movement values
			bPlayerDirection[west] = true;//Set player direction
			
		}
		if (UG::IsKeyDown(a_rightKey) && iTileRight != 0)
		{
			initialise();//Reset directional and movement values
			bPlayerDirection[east] = true;//Set player direction
			
		}

		//If block to constantly set the next tile


		if (bPlayerDirection[north] == true && iTileTop != 0)
		{
			iNextTile = fY + iTileWidths;//Sets the next tile pacman should go to
			bMoving = true;//Allows pacman to move
		}
		else if (bPlayerDirection[south] == true && iTileBottom != 0)
		{
			iNextTile = fY - iTileWidths;//Sets the next tile pacman should go to
			bMoving = true;//Allows pacman to move
		}
		else if (bPlayerDirection[west] == true && iTileLeft != 0)
		{
			iNextTile = fX - iTileWidths;//Sets the next tile pacman should go to
			bMoving = true;//Allows pacman to move
		}
		else if (bPlayerDirection[east] == true && iTileRight != 0)
		{
			iNextTile = fX + iTileWidths;//Sets the next tile pacman should go to
			bMoving = true;//Allows pacman to move

		}
		
	}
}
void PacmanProperties::MovePlayer(PacmanProperties& a_pacSprite, float a_fMovementSpeed)
{
	if (bMoving == true)//If the player is allowed to move
	{
		char* cSoundPath;//Declars the sound path variable
		if (bCanEatGhosts == true)
		{
			cSoundPath = "./sounds/eatGhosts.wav";//If the player is in Eat Ghost mode, use this sound file
		}
		else
		{
			cSoundPath = "./sounds/siren.wav";//If the player is not in Eat Ghost mode, use this sound file
		}

		SetSpriteFrame();//Set the animation frame.

		//If block to move the player in the chosen direction
		if (bPlayerDirection[north] == true)
		{
			fY += a_fMovementSpeed; //Adds the movement speed to the position to move the pacman
			if (fY >= iNextTile)//If the position is past the next tile
			{
				fY = iNextTile;//Sets the position to the next tile to keep grid alignment
				bMoving = false;//Sets movement to false to allow direction change again
				PlaySound(TEXT(cSoundPath), NULL,SND_FILENAME | SND_ASYNC);//Plays the sound chosen at the start of the function
				
			}
		}
		else if (bPlayerDirection[south] == true)
		{
			fY -= a_fMovementSpeed;//Adds the movement speed to the position to move the pacman
			if (fY <= iNextTile)//If the position is past the next tile
			{
				fY = iNextTile;//Sets the position to the next tile to keep grid alignment
				bMoving = false;//Sets movement to false to allow direction change again
				PlaySound(TEXT(cSoundPath), NULL, SND_FILENAME | SND_ASYNC);//Plays the sound chosen at the start of the function

			}
		}
		else if (bPlayerDirection[east] == true)
		{
			fX += a_fMovementSpeed;//Adds the movement speed to the position to move the pacman
			if (fX >= iNextTile)//If the position is past the next tile
			{
				fX = iNextTile;//Sets the position to the next tile to keep grid alignment
				bMoving = false;//Sets movement to false to allow direction change again
				PlaySound(TEXT(cSoundPath), NULL, SND_FILENAME | SND_ASYNC);//Plays the sound chosen at the start of the function
			}
		}
		else if (bPlayerDirection[west] == true)
		{
			fX -= a_fMovementSpeed;//Adds the movement speed to the position to move the pacman
			if (fX <= iNextTile)//If the position is past the next tile
			{
				fX = iNextTile;//Sets the position to the next tile to keep grid alignment
				bMoving = false;//Sets movement to false to allow direction change again
				PlaySound(TEXT(cSoundPath), NULL, SND_FILENAME | SND_ASYNC);//Plays the sound chosen at the start of the function

			}
		}
		
	}
	UG::MoveSprite(iSpriteID, fX, fY);//Moves the sprite
}










