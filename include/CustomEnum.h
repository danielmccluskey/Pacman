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
	blinky, pinky, inky, clyde
};
enum TileTypes //Enumerations for the Creation of the map to help me understand the values.
{
	bottom, left, right, top, corner1, corner2, corner3, corner4, blank, island1, island2, island3, island4
};
enum menuStates
{
	PLAY, HIGHSCORES, QUIT
};
#endif