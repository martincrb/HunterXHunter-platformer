#pragma once
#include "cData.h"
#include "Particle.h"
#include <list>
class ParticleSystem
{
public:
	ParticleSystem();
	
	~ParticleSystem();
	void Init(int max_part, 
			float emitter_x, float emitter_y,
				float acc_x, float acc_y,
				float vel_x, float vel_y);
	void setRandomSpeed(float min, float max);
	void setWidthHeight(int w, int h);
	void setRandomAcc(float min, float max);
	void setLifespan(int lfspan);
	void Process();
	void Draw(int tex_id);
	bool isFinished();
	std::string type;
protected:
	std::list<Particle> particles;
	bool randomSpeed;
	bool randomAcc;

	float min_acc;
	float max_acc;

	float min_vel;
	float max_vel;

	int particle_w;
	int particle_h;

	float emitter_x;
	float emitter_y;
	float acc_x;
	float acc_y;
	float vel_x;
	float vel_y;
	int max_particles_to_spawn;
	int particles_lifetime;
	int tex_id;
	int frameCounter;
	int particles_spawned;
	bool finished;
};

