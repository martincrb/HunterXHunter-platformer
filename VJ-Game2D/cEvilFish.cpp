#include "cEvilFish.h"
#include "cScene.h"

cEvilFish::cEvilFish()
{
	cBicho::SetState(0);
	actualDirection = RIGHT; //random initial dir
	Animation walk;
	walk.addFrame(200, 2, 2, 28, 30, 128, 128, 0, 0);
	walk.addFrame(200, 34, 2, 28, 31, 128, 128, 0, 0);
	walk.addFrame(200, 67, 2, 28, 29, 128, 128, 0, 0);
	walk.addFrame(200, 2, 32, 28, 29, 128, 128, 0, 0);
	walk.addFrame(200, 33, 32, 28, 28, 128, 128, 0, 0);
	walk.addFrame(200, 63, 32, 28, 30, 128, 128, 0, 0);
	walk.addFrame(200, 95, 32, 28, 30, 128, 128, 0, 0);
	walk.addFrame(200, 2, 62, 28, 31, 128, 128, 0, 0);
	walk.addFrame(200, 35, 62, 28, 30, 128, 128, 0, 0);
	walk.addFrame(200, 67, 62, 28, 29, 128, 128, 0, 0);
	walk.addFrame(200, 98, 62, 28, 28, 128, 128, 0, 0);
	animations.push_back(walk);


	currentAnimation = &animations[0];
	currentFrame = currentAnimation->frames[0];
}
void cEvilFish::Hurt() {
	alive = false;
}
bool cEvilFish::CollidesMapWall()
{
	int tile_x1 = x / cScene::TILE_SIZE;
	int tile_x2 = (x + w + 1) / cScene::TILE_SIZE;
	int tile_y = cScene::SCENE_HEIGHT - (y + h) / cScene::TILE_SIZE;
	int tile_ini = tile_y;
	int tile_fin = cScene::SCENE_HEIGHT - y / cScene::TILE_SIZE;
	for (int i = tile_ini; i <= tile_fin; i++) {
		cScene::debugmap[tile_x1 + i * cScene::SCENE_WIDTH] = 1;
		int tileID = map[tile_x1 + i * cScene::SCENE_WIDTH];
		if (tileID != 0 && cScene::tiles[tileID - 1].isSolid())
			return true;

		cScene::debugmap[tile_x2 + i * cScene::SCENE_WIDTH] = 1;
		tileID = map[tile_x2 + i * cScene::SCENE_WIDTH];
		if (tileID != 0 && cScene::tiles[tileID - 1].isSolid())
			//cScene::debugmap[tile_x2 + i * cScene::SCENE_WIDTH] = 1;
			return true;
	}
	return false;
}
cEvilFish::~cEvilFish()
{
}


void cEvilFish::MoveRight() {
	int xaux;

	//Whats next tile?
	if ((x % cScene::TILE_SIZE) == 0)
	{
		xaux = x;
		x += STEP_LENGTH;

		if (CollidesMapWall())
		{
			x = xaux;
			state = STATE_LOOKLEFT;
			actualDirection = LEFT;
		}
	}
	//Advance, no problem
	else
	{
		x += STEP_LENGTH;

		if (state != STATE_WALKRIGHT)
		{
			state = STATE_WALKRIGHT;
			seq = 0;
			delay = 0;
		}
	}
}
void cEvilFish::MoveLeft() {
	int xaux;

	//Whats next tile?
	if ((x % cScene::TILE_SIZE) == 0)
	{
		xaux = x;
		x -= STEP_LENGTH;

		if (CollidesMapWall())
		{
			x = xaux;
			state = STATE_LOOKRIGHT;
			actualDirection = RIGHT;
		}
	}
	//Advance, no problem
	else
	{
		x -= STEP_LENGTH;
		if (state != STATE_WALKLEFT)
		{
			state = STATE_WALKLEFT;
			seq = 0;
			delay = 0;
		}
	}
}

void cEvilFish::Logic() {
	//if (actualDirection == LEFT) std::cout << "LEFT" << std::endl;
	//if (actualDirection == RIGHT) std::cout << "RIGHT" << std::endl;
	switch (actualDirection) {
	case LEFT:

		MoveLeft();
		break;

	case RIGHT:
		MoveRight();
		break;
	}

	//cBicho::Logic(map);
}

bool cEvilFish::CollidesMapFloor() {
	return true;
}

void cEvilFish::Draw(cData* data) {

	float xo, yo, xf, yf;
	int tex_id = data->GetID(IMG_EVIL_FISH);
	switch (GetState())
	{
		//1
	case STATE_LOOKRIGHT:
		xo = currentFrame.tile_px + float(currentFrame.tile_width) / float(128);	yo = currentFrame.tile_py + float(currentFrame.tile_heigth) / float(128);
		xf = currentFrame.tile_px;
		yf = yo - float(currentFrame.tile_heigth) / float(128);
		NextFrame(currentAnimation->frames.size());
		break;
		//4
	case STATE_LOOKLEFT:
		xo = currentFrame.tile_px;	yo = currentFrame.tile_py + float(currentFrame.tile_heigth) / float(128);
		xf = xo + float(currentFrame.tile_width) / float(128);
		yf = yo - float(currentFrame.tile_heigth) / float(128);
		NextFrame(currentAnimation->frames.size());
		break;
		//1..3
	case STATE_WALKRIGHT:
		xo = currentFrame.tile_px + float(currentFrame.tile_width) / float(128);	yo = currentFrame.tile_py + float(currentFrame.tile_heigth) / float(128);
		xf = currentFrame.tile_px;
		yf = yo - float(currentFrame.tile_heigth) / float(128);
		NextFrame(currentAnimation->frames.size());
		break;
		//4..6
	case STATE_WALKLEFT:
		xo = currentFrame.tile_px;	yo = currentFrame.tile_py + float(currentFrame.tile_heigth) / float(128);
		xf = xo + float(currentFrame.tile_width) / float(128);
		yf = yo - float(currentFrame.tile_heigth) / float(128);
		NextFrame(currentAnimation->frames.size());
		break;
	}
	cBicho::SetWidthHeight(currentFrame.tile_width, currentFrame.tile_heigth);
	DrawRect(tex_id, xo, yo, xf, yf);
}