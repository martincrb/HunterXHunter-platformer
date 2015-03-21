#include "cEvilBird.h"


cEvilBird::cEvilBird()
{
	cBicho::SetState(0);
	actualDirection = RIGHT; //random initial dir
	Animation walk;
	walk.addFrame(200, 2, 2, 42, 32, 64, 128,0,0);
	walk.addFrame(200, 2, 46, 43, 29, 64, 128, 0, 0);
	walk.addFrame(200, 33, 46, 39, 29, 64, 128, 0, 0);
	walk.addFrame(200, 2, 91, 35, 29, 64, 128, 0, 0);
	animations.push_back(walk);


	currentAnimation = &animations[0];
	currentFrame = currentAnimation->frames[0];
}


cEvilBird::~cEvilBird()
{
}


void cEvilBird::Logic(int *map) {
	//if (actualDirection == LEFT) std::cout << "LEFT" << std::endl;
	//if (actualDirection == RIGHT) std::cout << "RIGHT" << std::endl;
	switch (actualDirection) {
	case LEFT:
		MoveLeft(map);
		if (CollidesMapWall(map, false)) actualDirection = RIGHT;
		break;

	case RIGHT:
		MoveRight(map);
		if (CollidesMapWall(map, true)) actualDirection = LEFT;
		break;
	}
	
	cBicho::Logic(map);
}

bool cEvilBird::CollidesMapFloor(int *map) {
	return true;
	//Evil Bird is always flying, so it is always " in the floor "
}

void cEvilBird::Draw(int tex_id) {

	float xo, yo, xf, yf;

	switch (GetState())
	{
		//1
	case STATE_LOOKRIGHT:
		xo = currentFrame.tile_px + float(currentFrame.tile_width) / float(64);	yo = currentFrame.tile_py + float(currentFrame.tile_heigth) / float(128);
		xf = currentFrame.tile_px;
		yf = yo - float(currentFrame.tile_heigth) / float(128);
		NextFrame(currentAnimation->frames.size());
		break;
		//4
	case STATE_LOOKLEFT:
		xo = currentFrame.tile_px;	yo = currentFrame.tile_py + float(currentFrame.tile_heigth) / float(128);
		xf = xo + float(currentFrame.tile_width) / float(64);
		yf = yo - float(currentFrame.tile_heigth) / float(128);
		NextFrame(currentAnimation->frames.size());
		break;
		//1..3
	case STATE_WALKRIGHT:
		xo = currentFrame.tile_px + float(currentFrame.tile_width) / float(64);	yo = currentFrame.tile_py + float(currentFrame.tile_heigth) / float(128);
		xf = currentFrame.tile_px;
		yf = yo - float(currentFrame.tile_heigth) / float(128);
		NextFrame(currentAnimation->frames.size());
		break;
		//4..6
	case STATE_WALKLEFT:
		xo = currentFrame.tile_px;	yo = currentFrame.tile_py + float(currentFrame.tile_heigth) / float(128);
		xf = xo + float(currentFrame.tile_width) / float(64);
		yf = yo - float(currentFrame.tile_heigth) / float(128);
		NextFrame(currentAnimation->frames.size());
		break;
	}
	cBicho::SetWidthHeight(currentFrame.tile_width, currentFrame.tile_heigth);
	DrawRect(tex_id, xo, yo, xf, yf);
}