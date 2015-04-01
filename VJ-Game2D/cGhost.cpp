#include "cGhost.h"

cGhost::cGhost()
{
	lick_counter = 0;
	initial_counter = 0;
	lick = false;
	speed = 2;
	state = STATE_LOOKLEFT;
	Animation idle1;
	Animation idle2;
	idle1.addFrame(200, 2, 2, 23, 25, 32, 64, 0, 0);
	idle2.addFrame(200, 2, 27, 27, 25, 32, 64, 0, 0);
	animations.push_back(idle1);
	animations.push_back(idle2);
	currentAnimation = &animations[0];
	currentFrame = currentAnimation->frames[0];


}


cGhost::~cGhost()
{
}

void cGhost::Logic() {
	if (initial_counter < INITIAL_DELAY) ++initial_counter;
	else {
		//Pursue player
		float move_x = obj_x - x;
		float move_y = obj_y - y;

		//normalize
		float module = sqrt(pow(move_x, 2) + pow(move_y, 2));

		move_x = speed*move_x/module;
		move_y = speed*move_y/module;
		if (move_x < 0) state = STATE_LOOKLEFT;
		else if (move_x >= 0) state = STATE_LOOKRIGHT;
		x += floor(move_x+0.5);
		y += floor(move_y+0.5);
	}

	if (!lick) {
		if (rand() % 100 < 1) {
			lick = true;
			currentAnimation = &animations[1];
			currentFrame = currentAnimation->frames[0];
		}
	}
	else {
		++lick_counter;
		if (lick_counter >= LICK_DELAY) {
			if (rand() % 10 < 7) {
				lick_counter = 0;
				lick = false;
				currentAnimation = &animations[0];
				currentFrame = currentAnimation->frames[0];
			}
		}
	}
}

void cGhost::Draw(int tex_id) {
	float xo, yo, xf, yf;
	if (state == STATE_LOOKLEFT) {
		xo = currentFrame.tile_px + float(currentFrame.tile_width) / float(32);	yo = currentFrame.tile_py + float(currentFrame.tile_heigth) / float(64);
		xf = currentFrame.tile_px;
		yf = yo - float(currentFrame.tile_heigth) / float(64);
	}
	else if (state == STATE_LOOKRIGHT) {
		xo = currentFrame.tile_px;	yo = currentFrame.tile_py + float(currentFrame.tile_heigth) / float(64);
		xf = xo + float(currentFrame.tile_width) / float(32);
		yf = yo - float(currentFrame.tile_heigth) / float(64);
	}
	
	
	cBicho::SetWidthHeight(currentFrame.tile_width, currentFrame.tile_heigth);
	DrawRect(tex_id, xo, yo, xf, yf);
}