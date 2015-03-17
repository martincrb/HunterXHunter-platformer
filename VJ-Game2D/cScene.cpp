#include "cScene.h"
#include "Globals.h"
#include "TMXParser.h"
#include "cBicho.h"
#include "cPlayer.h"
#include "cJumpingFrog.h"
#include <iostream>
#include <functional>
//TMXParser git: https://github.com/solar-storm-studios/TMXParser

int cScene::TILE_SIZE;
int cScene::BLOCK_SIZE;
int cScene::SCENE_Xo;
int cScene::SCENE_Yo;
int cScene::SCENE_WIDTH;
int cScene::SCENE_HEIGHT;
std::vector<Tile> cScene::tiles;

cScene::cScene(void)
{
}

cScene::~cScene(void)
{
}

void split(const std::string& s, char c,
	std::vector<std::string>& v) {
	std::string::size_type i = 0;
	std::string::size_type j = s.find(c);
	while (j != std::string::npos) {
		v.push_back(s.substr(i, j - i));
		i = ++j;
		j = s.find(c, j);
		if (j == std::string::npos)
			v.push_back(s.substr(i, s.length()));
	}
}

std::string cScene::LoadLevel(const char* level)
{
	bool res;
	FILE *fd;
	char file[16];
	int i,j,px,py;
	char tile;
	float coordx_tile, coordy_tile;
	int tilesetheight;
	int tilesetwidth;

	res=true;

	TMX::Parser tmx;
	
	tmx.load(level);
	std::cout << "Map Version: " << tmx.mapInfo.version << std::endl;
	std::cout << "Map Orientation: " << tmx.mapInfo.orientation << std::endl;
	std::cout << "Map Width: " << tmx.mapInfo.width << std::endl;
	std::cout << "Map Height: " << tmx.mapInfo.height << std::endl;
	std::cout << "Tile Width: " << tmx.mapInfo.tileWidth << std::endl;
	std::cout << "Tile Height: " << tmx.mapInfo.tileHeight << std::endl;
	std::cout << "Background Color: " << tmx.mapInfo.backgroundColor << std::endl;
	SCENE_HEIGHT = tmx.mapInfo.height;
	SCENE_WIDTH = tmx.mapInfo.width;
	std::string source = tmx.tilesetList[0].source;
	tilesetwidth = tmx.tilesetList[0].imgwidth;
	tilesetheight = tmx.tilesetList[0].imgheight;

	//Save Tile properties in a data structure
	std::vector<std::map<std::string, std::string> > tileVector = tmx.tilesetList[0].property;
	for (int tileID = 0; tileID < tileVector.size(); ++tileID) {
		Tile tile(tmx.tilesetList[0].property[tileID]["solid"] == "true", tmx.tilesetList[0].property[tileID]["type"]);
		std::cout << "TILEID: " << tileID << std::endl;
		tile.printinfo();
		tiles.push_back(tile);
	}

	map = std::vector<int>(SCENE_HEIGHT*SCENE_WIDTH);
	TILE_SIZE = tmx.mapInfo.tileWidth;
	BLOCK_SIZE = tmx.mapInfo.tileWidth;
	SCENE_Xo = 0;
	SCENE_Yo = 0;

	//fd=fopen(file,"r");
	//if(fd==NULL) return false;

	id_DL=glGenLists(1);
	glNewList(id_DL,GL_COMPILE);
		glBegin(GL_QUADS);
		
		//Print every layer from the TMX
		for (std::map<std::string, TMX::Parser::TileLayer>::iterator it = tmx.tileLayer.begin(); it != tmx.tileLayer.end(); ++it) {
			std::cout << std::endl;
			std::cout << "Tile Layer Name: " << it->first << std::endl;
			std::cout << "Tile Layer Visibility: " << tmx.tileLayer[it->first].visible << std::endl;
			std::cout << "Tile Layer Opacity: " << tmx.tileLayer[it->first].opacity << std::endl;
			std::cout << "Tile Layer Properties:" << std::endl;
			if (tmx.tileLayer[it->first].property.size() > 0) {
				for (std::map<std::string, std::string>::iterator it2 = tmx.tileLayer[it->first].property.begin(); it2 != tmx.tileLayer[it->first].property.end(); ++it2) {
					std::cout << "-> " << it2->first << " : " << it2->second << std::endl;
				}
			}
			std::cout << "Tile Layer Data Encoding: " << tmx.tileLayer[it->first].data.encoding << std::endl;
			if (tmx.tileLayer[it->first].data.compression != "none") {
				std::cout << "Tile Layer Data Compression: " << tmx.tileLayer[it->first].data.compression << std::endl;
			}
		//	std::cout << "Tile Layer Data Contents: " << tmx.tileLayer[it->first].data.contents << std::endl;
			std::vector<std::string> layer;
			split(tmx.tileLayer[it->first].data.contents, ',', layer);
			for (j = SCENE_HEIGHT-1; j >= 0; j--)
			{
				px = SCENE_Xo;
				py = SCENE_Yo -(j*TILE_SIZE);
				//std::cout << px << " " << py << std::endl;
				for (i = 0; i < SCENE_WIDTH; i++)
				{
					
					if (atoi(layer[(j*SCENE_WIDTH) + i].c_str()) == 0)
					{
						//Tiles must be != 0 !!!
						map[(j*SCENE_WIDTH) + i] = 0;
					}
					else
					{
						//Tiles = 1,2,3,...
						int tileID = atoi(layer[(j*SCENE_WIDTH) + i].c_str());
						map[(j*SCENE_WIDTH) + i] = atoi(layer[(j*SCENE_WIDTH) + i].c_str());
						//std::cout << "TileSetHeigth: " << tilesetheight << std::endl;
						int tileColumn = (map[(j*SCENE_WIDTH) + i] - 1) % (tilesetheight / TILE_SIZE);
						int tileRow = (map[(j*SCENE_WIDTH) + i] - 1) / (tilesetwidth / TILE_SIZE);
						coordx_tile = float(tileColumn*TILE_SIZE) / float(tilesetwidth);
						coordy_tile = float(tileRow*TILE_SIZE) / float(tilesetheight);
						float offsetW = float(BLOCK_SIZE) / float(tilesetwidth);
						float offsetH = float(BLOCK_SIZE) / float(tilesetheight);
						//if (tiles[tileID].isSolid()) { //DEBUG:: DRAW ONLY SOLID TILES
							glTexCoord2f(coordx_tile, coordy_tile + offsetH);	glVertex2i(px, py);
							glTexCoord2f(coordx_tile + offsetW, coordy_tile + offsetH);	glVertex2i(px + BLOCK_SIZE, py);
							glTexCoord2f(coordx_tile + offsetW, coordy_tile);	glVertex2i(px + BLOCK_SIZE, py + BLOCK_SIZE);
							glTexCoord2f(coordx_tile, coordy_tile);	glVertex2i(px, py + BLOCK_SIZE);
						//}
					}
					px += TILE_SIZE;
				}
			}
		}

		glEnd();
	glEndList();

	//Fill OBJECTS DATA from TMX:


	//Fill ENTITIES DATA from TMX:
	for (std::map<std::string, TMX::Parser::ObjectGroup>::iterator it = tmx.objectGroup.begin(); it != tmx.objectGroup.end(); ++it) {
		std::cout << std::endl;
		std::cout << "Object Group Name: " << it->first << std::endl;
		//std::cout << "Object Group Color: " << tmx.objectGroup[it->first].color << std::endl;
		//std::cout << "Object Group Visibility: " << tmx.objectGroup[it->first].visible << std::endl;
		//std::cout << "Object Group Opacity: " << tmx.objectGroup[it->first].opacity << std::endl;
		//std::cout << "Object Group Properties:" << std::endl;
		//if (tmx.objectGroup[it->first].property.size() > 0) {
		//	for (std::map<std::string, std::string>::iterator it2 = tmx.objectGroup[it->first].property.begin(); it2 != tmx.objectGroup[it->first].property.end(); ++it2) {
		//		std::cout << "-> " << it2->first << " : " << it2->second << std::endl;
		//	}
		//}
		std::string name = it->first;

		if (strcmp(name.c_str(), "Camera_limits") == 0) {
			//Read Camera Boundaries
			std::cout << "LOADING BOUNDARY " << std::endl;
			for (std::vector<TMX::Parser::Object>::iterator it2 = tmx.objectGroup[it->first].object.begin(); it2 != tmx.objectGroup[it->first].object.end(); ++it2) {
				std::cout << std::endl;
				std::cout << "AAAAAA " << std::endl;
				//if (it2->second.name != "") { std::cout << "Object Name: " << it2->first << std::endl; }
				//if (it2->second.type != "") { std::cout << "Object Type: " << tmx.objectGroup[it->first].object[it2->first].type << std::endl; }
				std::cout << "Object Position X: " << it2->x << std::endl;
				std::cout << "Object Position Y: " << it2->y << std::endl;
				std::cout << "Object Width: " << it2->width << std::endl;
				std::cout << "Object Height: " << it2->height << std::endl;
				//if (it2->second.gid != 0) { std::cout << "Object Tile GID: " << tmx.objectGroup[it->first].object[it2->first].gid << std::endl; }
				//std::cout << "Object Visible: " << tmx.objectGroup[it->first].object[it2->first].visible << std::endl;
				cRect boundary;
				boundary.left = it2->x;
				boundary.right = boundary.left + it2->width;
				boundary.top = it2->y;
				boundary.bottom = boundary.top + it2->height;
				camera_limits.addBoundary(boundary);
			}
		}

		if (strcmp(name.c_str(), "Entities") == 0) {
			//Read Entity data
			std::cout << "LOADING ENTITY " << std::endl;
			for (std::vector<TMX::Parser::Object>::iterator it2 = tmx.objectGroup[it->first].object.begin(); it2 != tmx.objectGroup[it->first].object.end(); ++it2) {
				std::cout << std::endl;
				//if (it2->second.name != "") { std::cout << "Object Name: " << it2->first << std::endl; }
				if (it2->type != "") { std::cout << "Object Type: " << it2->type << std::endl; }
				std::cout << "Object Position X: " << it2->x << std::endl;
				std::cout << "Object Position Y: " << it2->y << std::endl;
				//std::cout << "Object Width: " << it2->width << std::endl;
				//std::cout << "Object Height: " << it2->height << std::endl;
				//SAVE ENTITIES INFORMATION TO THE VECTOR OF ENTITIES
				
				Entity entity;
				entity.alive = true;
				entity.spawn_x = it2->x;
				entity.spawn_y = it2->y;
				entity.type = it2->type;
				if (entity.type == "jfrog") {
					std::cout << "Loading a hell of a frog" << std::endl;
					entity.bicho = new cJumpingFrog();
				}
				//FILL WITH OTHER ENTITY TYPES

				Entities.push_back(entity);
			}
		}

	}
	return source;
}

Boundary* cScene::getBoundaries() {
	return &camera_limits;

}

std::vector<Entity>* cScene::getEntities() {
	return &Entities;
}


void cScene::Draw(int tex_id)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,tex_id);
	glCallList(id_DL);
	glDisable(GL_TEXTURE_2D);
}
int* cScene::GetMap()
{
	return &map[0];
}

bool cScene::isSolid(int tileID)
{
	return tiles[tileID].isSolid();
}

std::string cScene::getTileType(int tileID)
{
	return tiles[tileID].getType();
}