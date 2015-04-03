#pragma once
#include "cBicho.h"
class cFireBall :
	public cBicho
{
public:
	cFireBall(int dist, float angle);
	~cFireBall();
	bool Collides(cRect *rc);
	void Draw(int tex_id);

	int dist;
	int direc;
	float angle;
};

