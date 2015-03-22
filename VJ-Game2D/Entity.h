#pragma once
#include "cBicho.h"
#include <string>
class Entity
{
public:
	Entity();
	~Entity();
	void Kill();
	std::string type;
	cBicho* bicho;
	bool alive;
	int spawn_x;
	int spawn_y;
};

