#pragma once
#include "cBicho.h"
#include "cFireBall.h"

#define BALLS 8
#define PI 3.14159265358979323846

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
	std::vector<cFireBall*> balls;
	float sinangle;

	static const int MIN_ANGLE = 95;
	static const int MAX_ANGLE = 200;
	static const int STEP = 1;
};

