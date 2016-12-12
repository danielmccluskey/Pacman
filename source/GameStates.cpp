#include "UGFW.h"
#include "Enumerations.h"
#include "CustomEnum.h"
#include "GameStates.h"

void GameStateProperties::CreateSprite(char* imagePath,int x,int y, int sizeX, int sizeY)
{
	SpriteID = UG::CreateSprite(imagePath, sizeX, sizeY, true);
	UG::MoveSprite(SpriteID, x, y);

}

void GameStateProperties::ShowSprite()
{
	UG::ClearScreen();
	UG::DrawSprite(SpriteID);
}

void GameStateProperties::HideSprite()
{
	UG::StopDrawingSprite(SpriteID);
	UG::ClearScreen();
}
