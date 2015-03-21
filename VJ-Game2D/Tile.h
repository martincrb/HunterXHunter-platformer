#pragma once
#include <string>
#include <iostream>
class Tile
{
public:
	Tile();
	Tile(bool s, bool destructable, std::string t);
	~Tile();
	bool isSolid();
	bool isDestructable();
	bool isAlive();
	void destroy();
	std::string getType();
	void printinfo();
private:
	bool solid;
	bool destructable;
	bool alive;
	std::string type;
};

