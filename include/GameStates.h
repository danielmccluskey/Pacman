#ifndef _GAMESTATES_H_
#define _GAMESTATES_H_


class GameStateProperties
{
public:
	void CreateSprite(char* imagePath, int x, int y, int sizeX, int sizeY);
	void ShowSprite();
	void HideSprite();
	int SpriteID = 0;
private:
	

};

#endif