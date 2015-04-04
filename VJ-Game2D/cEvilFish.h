#pragma once
#include "cBicho.h"
#define LEFT 0
#define RIGHT 1

class cEvilFish :
	public cBicho
{
public:
	cEvilFish();
	~cEvilFish();
	void Logic();
	void Draw(cData* data);
	bool CollidesMapFloor();
	bool CollidesMapWall();
	void MoveRight();
	void MoveLeft();
	void Hurt();
private:
	int actualDirection;
};

