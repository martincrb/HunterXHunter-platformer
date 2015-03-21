#include "Gon.h"


Gon::Gon()
{
	cBicho::SetState(0);
	Animation idle;
	idle.addFrame(200, 2, 2, 44, 30, 128, 256, 0, 0);
	idle.addFrame(200, 34, 2, 45, 31, 128, 256,0,0);
	idle.addFrame(200, 2, 2, 44, 30, 128, 256,0,0);
	idle.addFrame(200, 67, 2, 45, 30, 128, 256, 0, 0);
	animations.push_back(idle);

	Animation walk;
	walk.addFrame(200, 2, 49, 40, 31, 128, 256,0,0);
	walk.addFrame(200, 35, 49, 41, 36, 128, 256, 0, 0);
	walk.addFrame(200, 73, 49, 40, 23, 128, 256, 0, 0);
	walk.addFrame(200, 2, 92, 40, 31, 128, 256, 0, 0);
	walk.addFrame(200, 35, 92, 41, 36, 128, 256, 0, 0);
	walk.addFrame(200, 73, 92, 39, 23, 128, 256, 0, 0);
	animations.push_back(walk);

	Animation jump;
	jump.addFrame(200, 2, 135, 45, 38, 128, 256, 0, 0);
	animations.push_back(jump);

	Animation punch;
	punch.addFrame(200, 42, 135, 42, 52, 128, 256, 0, 0);
	animations.push_back(punch);

	currentAnimation = &animations[0];
	currentFrame = currentAnimation->frames[0];

	punchDelay = 0;
	punching = false;
}


Gon::~Gon()
{
}


void Gon::Punch(int *map){
	punching = true;
}

void Gon::Draw(int tex_id){
	//Esto no deberia ir aqui, deberia ir en la logica del player (la hereda de cbicho?)
	if (punching) punchDelay++;
	if (punchDelay == PUNCH_DURATION)
	{
		punchDelay = 0;
		punching = false;
	}

	float xo, yo, xf, yf;
	switch (GetState())
	{
		//1
	case STATE_LOOKLEFT:
		if (inAir()) {
			currentAnimation = &animations[2];
			currentFrame = currentAnimation->frames[0];
		}
		else if (punching) {
			currentAnimation = &animations[3];
			currentFrame = currentAnimation->frames[0];
		}
		else {
			currentAnimation = &animations[0];
		}
		xo = currentFrame.tile_px + float(currentFrame.tile_width) / float(128);	yo = currentFrame.tile_py + float(currentFrame.tile_heigth) / float(256);
		xf = currentFrame.tile_px;
		yf = yo - float(currentFrame.tile_heigth) / float(256);
		NextFrame(currentAnimation->frames.size());
		break;
		//4
	case STATE_LOOKRIGHT:
		if (inAir()) {
			currentAnimation = &animations[2];
			currentFrame = currentAnimation->frames[0];
		}
		else if (punching) {
			currentAnimation = &animations[3];
			currentFrame = currentAnimation->frames[0];
		}
		else {
			currentAnimation = &animations[0];
		}
		xo = currentFrame.tile_px;	yo = currentFrame.tile_py + float(currentFrame.tile_heigth) / float(256);
		xf = xo + float(currentFrame.tile_width) / float(128);
		yf = yo - float(currentFrame.tile_heigth) / float(256);
		NextFrame(currentAnimation->frames.size());
		break;
		//1..3
	case STATE_WALKLEFT:
		if (inAir()) {
			currentAnimation = &animations[2];
			currentFrame = currentAnimation->frames[0];
		}
		else if (punching) {
			currentAnimation = &animations[3];
			currentFrame = currentAnimation->frames[0];
		}
		else {
			currentAnimation = &animations[1];
		}
		xo = currentFrame.tile_px + float(currentFrame.tile_width) / float(128);	yo = currentFrame.tile_py + float(currentFrame.tile_heigth) / float(256);
		xf = currentFrame.tile_px;
		yf = yo - float(currentFrame.tile_heigth) / float(256);
		NextFrame(currentAnimation->frames.size());
		break;
		//4..6
	case STATE_WALKRIGHT:
		if (inAir()) {
			currentAnimation = &animations[2];
			currentFrame = currentAnimation->frames[0];
		}
		else if (punching) {
			currentAnimation = &animations[3];
			currentFrame = currentAnimation->frames[0];
		}
		else {
			currentAnimation = &animations[1];
		}
		xo = currentFrame.tile_px;	yo = currentFrame.tile_py + float(currentFrame.tile_heigth) / float(256);
		xf = xo + float(currentFrame.tile_width) / float(128);
		yf = yo - float(currentFrame.tile_heigth) / float(256);
		NextFrame(currentAnimation->frames.size());
		break;
	}
	//std::cout << "FRAME: " << std::endl;
	//std::cout << "Xo: " << xo << " Yo: " << yo << std::endl;
	//std::cout << "Xf: " << xf << " Yf: " << yf << std::endl;
	cBicho::SetWidthHeight(currentFrame.tile_width, currentFrame.tile_heigth);
	int xd, yd = 0;
	cBicho::GetPosition(&xd, &yd);
	cBicho::SetPosition(xd+currentFrame.px_disp, yd-currentFrame.py_disp);
	DrawRect(tex_id, xo, yo, xf, yf);
}