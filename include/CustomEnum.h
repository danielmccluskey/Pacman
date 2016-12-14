//==============================================================================================================================
// Project: Pacman
// File: CustomEnum.h
// Author: Daniel McCluskey
// Date Created: 17/10/16
// Brief: This is the header file that contains all of the Enumerations I have used throughout my code. This header is included in every CPP file in the project.
// Last Edited by: (See BitBucket Commits: https://bitbucket.org/Danielmclovin/ct4019-pacman)
//==============================================================================================================================

#ifndef _CUSTOMENUM_H_
#define _CUSTOMENUM_H_
typedef enum GameStates //Enumeration for the different gamestates
{
	SPLASH,
	MENU,
	GAMEPLAY,
	GAMEOVER,
	DIFFICULTY,
	PAUSE,
	SCORES,
	DEATH
}GameState;
enum DIFFICULTY//Enumeration for the different difficulties
{
	EASY, MEDIUM, HARD
};
enum Direction//Enumeration for the different directions
{
	north, east, south, west
};
enum Ghosts//Enumerations for the different ghosts
{
	blinky, pinky, inky, clyde, edible
};
enum TileTypes //Enumerations for the Creation of the map to help me understand the values.
{
	bottom, left, right, top, corner1, corner2, corner3, corner4, blank, island1, island2, island3, island4
};
enum menuStates//Enumeration for the different main menu options
{
	PLAY, HIGHSCORES, QUIT
};
#endif //_CUSTOMENUM_H_