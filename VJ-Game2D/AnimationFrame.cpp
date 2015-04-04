#include "AnimationFrame.h"

AnimationFrame::AnimationFrame(int duration, float tile_px, float tile_py, int tile_heigth, int tile_width, int px_displace, int py_displace) {
	this->px_disp = px_displace;
	this->py_disp = py_displace;
	this->duration = duration;
	this->tile_px = tile_px;
	this->tile_py = tile_py;
	this->tile_heigth = tile_heigth;
	this->tile_width = tile_width;
	hasHitBox = false;
}
AnimationFrame::AnimationFrame()
{
}


AnimationFrame::~AnimationFrame()
{
}

void AnimationFrame::invertHitBoxX() { //Inverts hitbox for mirrored animations 
	int width = hitBox.right - hitBox.left;
	hitBox.left -= (1.5*tile_width - (hitBox.right - hitBox.left) - px_disp);
	hitBox.right = hitBox.left + width;
}

void AnimationFrame::addHitBox(int x, int y, int w, int h) {
	hitBox.left = x;
	hitBox.right = x + w;
	hitBox.top = -y - h;
	hitBox.bottom = -y;

	invhitBox.left = x - (tile_width + w) + px_disp + 5;
	invhitBox.right = invhitBox.left + w;
	invhitBox.top = hitBox.top;
	invhitBox.bottom = hitBox.bottom;

	hasHitBox = true;
}
cRect AnimationFrame::getHitBox(bool inverted) {
	if (!inverted) {
		return hitBox;
	}
	else {
		return invhitBox;
	}
}