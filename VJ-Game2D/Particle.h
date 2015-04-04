#pragma once
#include "cData.h"
class Particle
{
public:
	Particle();
	Particle(float spawn_x, float spawn_y);
	~Particle();
	void setSpeed(float x, float y);
	void setLifespan(int lifespan);
	void setAcceleration(float x, float y);
	bool isDead();
	void Process();
	void Draw(int tex_id);
private:
	int frame_lifetime;
	float location_x;
	float location_y;
	float vel_x;
	float vel_y;
	float acc_x;
	float acc_y;
	bool dead;
};

