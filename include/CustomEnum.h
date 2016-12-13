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
typedef enum GameStates
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
enum DIFFICULTY
{
	EASY, MEDIUM, HARD
};
enum Direction
{
	north, east, south, west
};
enum Ghosts
{
	blinky, pinky, inky, clyde, edible
};
enum TileTypes //Enumerations for the Creation of the map to help me understand the values.
{
	bottom, left, right, top, corner1, corner2, corner3, corner4, blank, island1, island2, island3, island4
};
enum menuStates
{
	PLAY, HIGHSCORES, QUIT
};
#endif //_CUSTOMENUM_H_