#ifndef _PELLETS_H_
#define _PELLETS_H_

class PelletProperties
{
public:

	


	float fX;
	float fY;
	int SpriteID = -1;
	int SpriteWidth = 16;

	int iMapWidth = 28;
	int iMapHeight = 36;
	
	int nextTile;
	int tileWidths;



	void CreatePellet(char* imagePath, int iTileX, int iTileY);
	void DrawPellets(PelletProperties *pellet);
	PelletProperties& GetPellet(PelletProperties *pellet, int x, int y);
	int GetTile(int x, int y);
	void DestroyPellets(PelletProperties *pellet, int x, int y);


private:

};

#endif