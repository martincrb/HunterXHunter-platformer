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

