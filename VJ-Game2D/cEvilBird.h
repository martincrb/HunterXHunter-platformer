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
	void Draw(int tex_id);
	bool CollidesMapFloor();
	bool CollidesMapWall(bool right);
	void MoveRight();
	void MoveLeft();
private:
	int actualDirection;
};

