#include "Tile.h"


Tile::Tile()
{
}

Tile::Tile(bool s, bool d, std::string t)
{
	destructable = d;
	solid = s;
	type = t;
	alive = true;
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

bool Tile::isDestructable() {
	return destructable;
}
bool Tile::isAlive() {
	return alive;
}
void Tile::destroy() {
	if (isDestructable()) {
		alive = false;
	}
}