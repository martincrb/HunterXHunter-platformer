#pragma once
#include "cBicho.h"
#include <string>
class Entity
{
public:
	Entity();
	~Entity();
	void Kill();
	void Hurt();
	bool killsPlayer;
	std::string type;
	cBicho* bicho;
	int spawn_x;
	int spawn_y;
};

