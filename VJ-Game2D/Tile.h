#pragma once
#include <string>
#include <iostream>
class Tile
{
public:
	Tile();
	Tile(bool s, std::string t);
	~Tile();
	bool isSolid();
	std::string getType();
	void printinfo();
private:
	bool solid;
	std::string type;
};

