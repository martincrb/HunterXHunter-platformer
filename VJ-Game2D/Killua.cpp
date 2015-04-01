#include "Killua.h"


Killua::Killua()
{
	cBicho::SetState(0);
	Animation idle;
	idle.addFrame(200, 2, 2, 49, 20, 128, 256, 0, 0);
	idle.addFrame(200, 24, 2, 49, 20, 128, 256, 0, 0);
	idle.addFrame(200, 46, 2, 48, 20, 128, 256, 0, 0);
	idle.addFrame(200, 68, 2, 47, 20, 128, 156, 0, 0);
	animations.push_back(idle);

	Animation walk;
	//walk.addFrame(200, 2, 53, 48, 24, 128, 256, 0, 0);
	walk.addFrame(200, 28, 53, 46, 28, 128, 256, 0, 0);
	walk.addFrame(200, 58, 53, 46, 25, 128, 256, 0, 0);
	walk.addFrame(200, 85, 53, 46, 21, 128, 256, 0, 0);
	//walk.addFrame(200, 2, 103, 48, 23, 128, 256, 0, 0);
	walk.addFrame(200, 27, 103, 47, 30, 128, 256, 0, 0);
	walk.addFrame(200, 59, 103, 45, 27, 128, 256, 0, 0);
	walk.addFrame(200, 88, 103, 45, 22, 128, 256, 0, 0);
	animations.push_back(walk);

	Animation jump;
	jump.addFrame(200, 90, 2, 40, 28, 128, 256, 0, 0);
	animations.push_back(jump);

	currentAnimation = &animations[0];
	currentFrame = currentAnimation->frames[0];

	punchDelay = 0;
	hability = false;
}


Killua::~Killua()
{
}

void Killua::Draw(int tex_id){
	//Esto no deberia ir aqui, deberia ir en la logica del player (la hereda de cbicho?)

	float xo, yo, xf, yf;
	switch (GetState())
	{
		//1
	case STATE_LOOKLEFT:
		if (inAir()) {
			currentAnimation = &animations[2];
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
	DrawRect(tex_id, xo, yo, xf, yf);
}