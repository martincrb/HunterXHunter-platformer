#include "cJumpingFrog.h"


cJumpingFrog::cJumpingFrog()
{
	jumpDelay = 0;
	jump_freq = rand()%240+60; //default random

	Animation idle;
	idle.addFrame(200, 2, 28, 16, 16, 20, 47,0,0);
	animations.push_back(idle);

	Animation jump;
	jump.addFrame(200, 2, 2, 24, 16, 20, 47,0,0);
	animations.push_back(jump);

	Animation die;
	die.addFrame(200, 2, 28, 16, 16, 20, 47, 0, 0);
	die.addFrame(200, 2, 2, 24, 16, 20, 47, 0, 0);
	animations.push_back(die);
	currentAnimation = &animations[0];
	currentFrame = currentAnimation->frames[0];
}

void cJumpingFrog::Hurt() {
	dying = true;
}
cJumpingFrog::~cJumpingFrog()
{
}

void cJumpingFrog::setJumpFreq(int x) {
	jump_freq = x;
}
void cJumpingFrog::Logic() {
	if (!dying) {
		jumpDelay++;
		if (jumpDelay == jump_freq)
		{
			jumpDelay = 0;
			if (!inAir()) {
				Jump();
			}
		}
	}
	else {
		if (GetFrame() == currentAnimation->frames.size() - 1) {
			alive = false;
		}
	}
	cBicho::Logic();
}
void cJumpingFrog::Draw(cData* data) {
	int tex_id = data->GetID(IMG_JUMPING_FROG);
	if (inAir()) {
		currentAnimation = &animations[1];
	}
	else {
		currentAnimation = &animations[0];
	}

	float xo, yo, xf, yf;

	if (dying) {
		currentAnimation = &animations[2];
	}
	switch (GetState())
	{
		//1
	case STATE_LOOKRIGHT:
		xo = currentFrame.tile_px + float(currentFrame.tile_width) / float(20);	yo = currentFrame.tile_py + float(currentFrame.tile_heigth) / float(47);
		xf = currentFrame.tile_px;
		yf = yo - float(currentFrame.tile_heigth) / float(47);
		NextFrame(currentAnimation->frames.size());
		break;
		//4
	case STATE_LOOKLEFT:
		xo = currentFrame.tile_px;	yo = currentFrame.tile_py + float(currentFrame.tile_heigth) / float(47);
		xf = xo + float(currentFrame.tile_width) / float(20);
		yf = yo - float(currentFrame.tile_heigth) / float(47);
		NextFrame(currentAnimation->frames.size());
		break;
		//1..3
	case STATE_WALKRIGHT:
		xo = currentFrame.tile_px + float(currentFrame.tile_width) / float(20);	yo = currentFrame.tile_py + float(currentFrame.tile_heigth) / float(47);
		xf = currentFrame.tile_px;
		yf = yo - float(currentFrame.tile_heigth) / float(47);
		NextFrame(currentAnimation->frames.size());
		break;
		//4..6
	case STATE_WALKLEFT:
		xo = currentFrame.tile_px;	yo = currentFrame.tile_py + float(currentFrame.tile_heigth) / float(47);
		xf = xo + float(currentFrame.tile_width) / float(20);
		yf = yo - float(currentFrame.tile_heigth) / float(47);
		NextFrame(currentAnimation->frames.size());
		break;
	}
	cBicho::SetWidthHeight(currentFrame.tile_width, currentFrame.tile_heigth);
	DrawRect(tex_id, xo, yo, xf, yf);
}