#pragma once
#include "cBicho.h"

#define BALLS 6

class cOctopus :
	public cBicho
{
public:
	cOctopus();
	~cOctopus();
	bool Collides(cRect *rc);
	void Logic();
	void Draw(int tex_id);
	void Hurt();
private:
	std::vector<float> ball_y;
	std::vector<cBicho*> balls;
	float sinangle;
};

