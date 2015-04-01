#pragma once
#include "cBicho.h"
class cFireBall :
	public cBicho
{
public:
	cFireBall();
	~cFireBall();
	bool Collides(cRect *rc);
	void Draw(int tex_id);
};

