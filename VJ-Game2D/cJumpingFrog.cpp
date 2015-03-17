#include "cJumpingFrog.h"


cJumpingFrog::cJumpingFrog()
{
	cBicho::SetState(0);
	jumpDelay = 0;
	jump_freq = rand()%240+60; //default random
	Animation idle;
	AnimationFrame frame(200, float(2) / float(20), float(28) / float(47), 16, 16);
	idle.frames.push_back(frame);
	animations.push_back(idle);

	Animation jump;
	AnimationFrame frame5(200, float(2) / float(20), float(2) / float(47), 24, 16);
	jump.frames.push_back(frame5);
	animations.push_back(jump);


	currentAnimation = &animations[0];
	currentFrame = currentAnimation->frames[0];
}


cJumpingFrog::~cJumpingFrog()
{
}

void cJumpingFrog::setJumpFreq(int x) {
	jump_freq = x;
}
void cJumpingFrog::Logic(int *map) {
	jumpDelay++;
	if (jumpDelay == jump_freq)
	{
		jumpDelay = 0;
		if (!inAir()) {
			Jump(map);
		}
	}
	
	cBicho::Logic(map);
}
void cJumpingFrog::Draw(int tex_id) {
	if (inAir()) {
		currentAnimation = &animations[1];
	}
	else {
		currentAnimation = &animations[0];
	}

	float xo, yo, xf, yf;

	switch (GetState())
	{
		//1
	case STATE_LOOKLEFT:
		xo = currentFrame.tile_px + float(currentFrame.tile_width) / float(20);	yo = currentFrame.tile_py + float(currentFrame.tile_heigth) / float(47);
		xf = currentFrame.tile_px;
		yf = yo - float(currentFrame.tile_heigth) / float(47);
		NextFrame(currentAnimation->frames.size());
		break;
		//4
	case STATE_LOOKRIGHT:
		xo = currentFrame.tile_px;	yo = currentFrame.tile_py + float(currentFrame.tile_heigth) / float(47);
		xf = xo + float(currentFrame.tile_width) / float(20);
		yf = yo - float(currentFrame.tile_heigth) / float(47);
		NextFrame(currentAnimation->frames.size());
		break;
		//1..3
	case STATE_WALKLEFT:
		xo = currentFrame.tile_px + float(currentFrame.tile_width) / float(20);	yo = currentFrame.tile_py + float(currentFrame.tile_heigth) / float(47);
		xf = currentFrame.tile_px;
		yf = yo - float(currentFrame.tile_heigth) / float(47);
		NextFrame(currentAnimation->frames.size());
		break;
		//4..6
	case STATE_WALKRIGHT:
		xo = currentFrame.tile_px;	yo = currentFrame.tile_py + float(currentFrame.tile_heigth) / float(47);
		xf = xo + float(currentFrame.tile_width) / float(20);
		yf = yo - float(currentFrame.tile_heigth) / float(47);
		NextFrame(currentAnimation->frames.size());
		break;
	}
	cBicho::SetWidthHeight(currentFrame.tile_width, currentFrame.tile_heigth);
	DrawRect(tex_id, xo, yo, xf, yf);
}