#include "ParticleSystem.h"


ParticleSystem::ParticleSystem()
{
	randomSpeed = false;
	randomAcc = false;
	finished = false;
	particles_lifetime = 200;
}


ParticleSystem::~ParticleSystem()
{
}
void ParticleSystem::setLifespan(int lfspan) {
	particles_lifetime = lfspan;
	if (!particles.empty()) {
		for (std::list<Particle>::iterator it = particles.begin(); it != particles.end(); it++)
			it->setLifespan(particles_lifetime);
	}
}
void ParticleSystem::Init(int max, float emit_x, float emit_y, float a_x, float a_y, float v_x, float v_y) {
	
	max_particles_to_spawn = max;
	emitter_x = emit_x;
	emitter_y = emit_y;
	acc_x = a_x;
	acc_y = a_y;
	vel_x = v_x;
	vel_y = v_y;
	for (int i = 0; i < max; ++i) {
		Particle p(emitter_x, emitter_y);
		p.setAcceleration(acc_x, acc_y);
		p.setSpeed(vel_x, vel_y);
		p.setWidthHeight(particle_w, particle_h);
		if (randomSpeed) {
			float random_x = ((float)rand()) / (float)RAND_MAX;
			float random_y = ((float)rand()) / (float)RAND_MAX;
			float range = max_vel - min_vel;
			random_x = (random_x*range) + min_vel;
			random_y = (random_y*range) + min_vel;
			p.setSpeed(random_x, random_y);
		}
		if (randomAcc) {
			float random_x = ((float)rand()) / (float)RAND_MAX;
			float random_y = ((float)rand()) / (float)RAND_MAX;
			float range = max_acc - min_acc;
			random_x = (random_x*range) + min_acc;
			random_y = (random_y*range) + min_acc;
			p.setAcceleration(random_x, random_y);
		}
		p.setLifespan(particles_lifetime);
		particles.push_back(p);
	}
}

void ParticleSystem::setRandomSpeed(float min, float max) {
	randomSpeed = true;
	min_vel = min;
	max_vel = max;

}
void ParticleSystem::setRandomAcc(float min, float max) {
	randomAcc = true;
	min_acc = min;
	max_acc = max;


}


void ParticleSystem::Process() {
	if (!particles.empty()) {
		std::list<Particle>::iterator it = particles.begin();
		while (it != particles.end()) {
			it->Process();
			if (it->isDead()) {
				it = particles.erase(it);
				
			}
			else {
				it++;
			}
		}
	}
	else {
		finished = true;
	}
}
bool ParticleSystem::isFinished() {
	return finished;
}

void ParticleSystem::setWidthHeight(int w, int h) {
	particle_h = h;
	particle_w = w;
}

void ParticleSystem::Draw(int tex_id) {
	if (!particles.empty()) {
		for (std::list<Particle>::iterator it = particles.begin(); it != particles.end(); it++)
			it->Draw(tex_id);
	}
}