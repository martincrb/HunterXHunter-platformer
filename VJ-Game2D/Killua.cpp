#include "Killua.h"


Killua::Killua()
{
	cBicho::SetState(0);
	Animation idle;
	AnimationFrame frame(200, float(2) / float(128), float(2) / float(256), 49, 20);
	idle.frames.push_back(frame);
	AnimationFrame frame2(200, float(24) / float(128), float(2) / float(256), 49, 20);
	idle.frames.push_back(frame2);
	AnimationFrame frame3(200, float(46) / float(128), float(2) / float(256), 48, 20);
	idle.frames.push_back(frame3);
	AnimationFrame frame4(200, float(68) / float(128), float(2) / float(256), 47, 20);
	idle.frames.push_back(frame4);
	animations.push_back(idle);

	Animation walk;
	AnimationFrame frame5(200, float(2) / float(128), float(53) / float(256), 48, 24);
	walk.frames.push_back(frame5);
	AnimationFrame frame6(200, float(28) / float(128), float(53) / float(256), 46, 28);
	walk.frames.push_back(frame6);
	AnimationFrame frame7(200, float(58) / float(128), float(53) / float(256), 46, 25);
	walk.frames.push_back(frame7);
	AnimationFrame frame8(200, float(85) / float(128), float(53) / float(256), 46, 21);
	walk.frames.push_back(frame8);
	AnimationFrame frame9(200, float(2) / float(128), float(103) / float(256), 48, 23);
	walk.frames.push_back(frame9);
	AnimationFrame frame10(200, float(27) / float(128), float(103) / float(256), 47, 30);
	walk.frames.push_back(frame10);
	AnimationFrame frame11(200, float(59) / float(128), float(103) / float(256), 45, 27);
	walk.frames.push_back(frame11);
	AnimationFrame frame12(200, float(88) / float(128), float(103) / float(256), 45, 22);
	walk.frames.push_back(frame12);
	animations.push_back(walk);

	Animation jump;
	AnimationFrame frame13(200, float(90) / float(128), float(2) / float(256), 40, 28);
	jump.frames.push_back(frame13);
	animations.push_back(jump);

	currentAnimation = &animations[0];
	currentFrame = currentAnimation->frames[0];

	punchDelay = 0;
	punching = false;
}


Killua::~Killua()
{
}

void Killua::Punch(int *map){
	punching = true;
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