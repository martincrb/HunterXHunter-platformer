
#include "cPlayer.h"

cPlayer::cPlayer() {
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


	currentAnimation = &animations[0];
	currentFrame = currentAnimation->frames[0];
}

cPlayer::~cPlayer(){}

cPlayer::cPlayer(int state) {
	
}

void cPlayer::Draw(int tex_id)
{	
	float xo,yo,xf,yf;

	switch(GetState())
	{
		//1
		case STATE_LOOKLEFT:	currentAnimation = &animations[0];
								xo = currentFrame.tile_px + float(currentFrame.tile_width) / float(128);	yo = currentFrame.tile_py + float(currentFrame.tile_heigth) / float(256);
								xf = currentFrame.tile_px;
								yf = yo - float(currentFrame.tile_heigth) / float(256);
								NextFrame(currentAnimation->frames.size());
								break;
		//4
		case STATE_LOOKRIGHT:	currentAnimation = &animations[0];
								xo = currentFrame.tile_px;	yo = currentFrame.tile_py + float(currentFrame.tile_heigth) / float(256);
								xf = xo + float(currentFrame.tile_width) / float(128);
								yf = yo - float(currentFrame.tile_heigth) / float(256);
								NextFrame(currentAnimation->frames.size());
								break;
		//1..3
		case STATE_WALKLEFT:	currentAnimation = &animations[1];
								xo = currentFrame.tile_px + float(currentFrame.tile_width) / float(128);	yo = currentFrame.tile_py + float(currentFrame.tile_heigth) / float(256);
								xf = currentFrame.tile_px;
								yf = yo - float(currentFrame.tile_heigth) / float(256);
								NextFrame(currentAnimation->frames.size());
								break;
		//4..6
		case STATE_WALKRIGHT:	currentAnimation = &animations[1];
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
	DrawRect(tex_id,xo,yo,xf,yf);
}
