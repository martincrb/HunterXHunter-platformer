#pragma once

#include "cTexture.h"
#include "Tile.h"
#include <vector>
#include "Boundary.h"
#include "Entity.h"
#define FILENAME		"level"
#define FILENAME_EXT	".txt"



class cScene
{
public:

	cScene(void);
	virtual ~cScene(void);

	std::string LoadLevel(const char* level);
	void Draw(int tex_id);
	int *GetMap();
	bool isSolid(int tileID);
	std::string getTileType(int tileID);
	void FreeAll();
	static int TILE_SIZE;
	static int BLOCK_SIZE;
	static int SCENE_Xo;
	static int SCENE_Yo;
	static int SCENE_WIDTH;
	static int SCENE_HEIGHT;
	static int DEBUG_ON;
	std::vector< std::vector<int> > map;	//scene
	static std::vector<int> debugmap;	//scene
	static std::vector<Tile> tiles; //Tiles and properties
	Boundary* getBoundaries();
	cRect* getWaterZone();
	std::vector<Entity>* getEntities();
	void addEntity(std::string type, int sx, int sy);
	int player1_actualx;
	int player1_actualy;
	int player2_actualx;
	int player2_actualy;
	int player_spawn_x;
	int player_spawn_y;
private:
	
	
	int tilesetheight;
	int tilesetwidth;
	//int id_DL;								//actual level display list
	std::vector<Entity> Entities;
	cRect water_zone;
	Boundary camera_limits;
};
