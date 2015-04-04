#include "Particle.h"


Particle::Particle()
{
}

Particle::Particle(float spawn_x, float spawn_y) {
	location_x = spawn_x;
	location_y = spawn_y;
	dead = false;
}
Particle::~Particle()
{
}

bool Particle::isDead() {
	return dead;
}
void Particle::setSpeed(float x, float y) {
	vel_x = x;
	vel_y = y;
}
void Particle::setAcceleration(float x, float y) {
	acc_x = x;
	acc_y = y;
}
void Particle::setLifespan(int lifespan) {
	frame_lifetime = lifespan;
}
void Particle::Process() {
	if (!dead) {
		vel_x += acc_x;
		vel_y += acc_y;
		location_x += vel_x;
		location_y += vel_y;
		--frame_lifetime;
		if (frame_lifetime == 0)
			dead = true;
	}
}
void Particle::Draw(int tex_id) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex_id);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1);  glVertex2i(location_x, location_y);
	glTexCoord2f(1, 1); glVertex2i(location_x + 16, location_y);
	glTexCoord2f(1, 0); glVertex2i(location_x + 16, location_y + 16);
	glTexCoord2f(0, 0); glVertex2i(location_x, location_y + 16);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}
