#pragma once
#include "cBicho.h"
#define LEFT 0
#define RIGHT 1

class cEvilBird :
	public cBicho
{
public:
	cEvilBird();
	~cEvilBird();
	void Logic(int *map);
	void Draw(int tex_id);
	bool CollidesMapFloor(int *map);
private:
	int actualDirection;
};

