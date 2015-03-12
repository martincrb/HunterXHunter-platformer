#include "Tile.h"


Tile::Tile()
{
}

Tile::Tile(bool s, std::string t)
{
	solid = s;
	type = t;
}

Tile::~Tile()
{
}

bool Tile::isSolid(){
	return solid;
}
std::string Tile::getType(){
	return type;
}

void Tile::printinfo() {
	std::cout << "SOLID: ";
	if (solid) std::cout << "YES" << std::endl;
	else std::cout << "NO" << std::endl;

}
