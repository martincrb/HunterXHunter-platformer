#include "Gon.h"


Gon::Gon()
{
	cBicho::SetState(0);
	Animation idle;
	AnimationFrame frame(200, float(2) / float(128), float(2) / float(256), 44, 30);
	idle.frames.push_back(frame);
	AnimationFrame frame2(200, float(34) / float(128), float(2) / float(256), 45, 31);
	idle.frames.push_back(frame2);
	AnimationFrame frame3(200, float(2) / float(128), float(2) / float(256), 44, 30);
	idle.frames.push_back(frame3);
	AnimationFrame frame4(200, float(67) / float(128), float(2) / float(256), 45, 30);
	idle.frames.push_back(frame4);
	animations.push_back(idle);

	Animation walk;
	AnimationFrame frame5(200, float(2) / float(128), float(49) / float(256), 40, 31);
	walk.frames.push_back(frame5);
	AnimationFrame frame6(200, float(35) / float(128), float(49) / float(256), 41, 36);
	walk.frames.push_back(frame6);
	AnimationFrame frame7(200, float(73) / float(128), float(49) / float(256), 40, 23);
	walk.frames.push_back(frame7);
	AnimationFrame frame8(200, float(2) / float(128), float(92) / float(256), 40, 31);
	walk.frames.push_back(frame8);
	AnimationFrame frame9(200, float(35) / float(128), float(92) / float(256), 41, 36);
	walk.frames.push_back(frame9);
	AnimationFrame frame10(200, float(73) / float(128), float(92) / float(256), 39, 23);
	walk.frames.push_back(frame10);
	animations.push_back(walk);

	Animation jump;
	AnimationFrame frame11(200, float(2) / float(128), float(135) / float(256), 45, 38);
	jump.frames.push_back(frame11);
	animations.push_back(jump);

	Animation punch;
	AnimationFrame frame12(200, float(42) / float(128), float(135) / float(256), 42, 52);
	punch.frames.push_back(frame12);
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
	DrawRect(tex_id, xo, yo, xf, yf);
}