#pragma once

#include "cTexture.h"
#include "Tile.h"
#include <vector>

#define FILENAME		"level"
#define FILENAME_EXT	".txt"



class cScene
{
public:

	cScene(void);
	virtual ~cScene(void);

	std::string LoadLevel(int level);
	void Draw(int tex_id);
	int *GetMap();
	bool isSolid(int tileID);
	std::string getTileType(int tileID);
	static int TILE_SIZE;
	static int BLOCK_SIZE;
	static int SCENE_Xo;
	static int SCENE_Yo;
	static int SCENE_WIDTH;
	static int SCENE_HEIGHT;
	std::vector<int> map;	//scene
	static std::vector<Tile> tiles; //Tiles and properties

private:
	int id_DL;								//actual level display list
};