#pragma once
#include "cBicho.h"
class Entity
{
public:
	Entity();
	~Entity();
	const char* type;
	cBicho* bicho;
	bool alive;
	int spawn_x;
	int spawn_y;
};

