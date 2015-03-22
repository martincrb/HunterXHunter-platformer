#include "cEvilBird.h"
#include "cScene.h"

cEvilBird::cEvilBird()
{
	cBicho::SetState(0);
	actualDirection = LEFT; //random initial dir
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

bool cEvilBird::CollidesMapWall(int *map, bool right)
{
	bool collides = false;
	//if (right) std::cout << "Going RIGHT" << std::endl;
	//else std::cout << "Going LEFT" << std::endl;
	int tile_x, tile_y;
	int j;
	int width_tiles, height_tiles;
	tile_x = x / cScene::TILE_SIZE;
	tile_y = y / cScene::TILE_SIZE;
	width_tiles = floor((float(w) / float(cScene::TILE_SIZE)) + 0.5);
	height_tiles = h / cScene::TILE_SIZE;
	if (right)	{
		tile_x = tile_x + width_tiles;
	}
		for (j = 0; j<height_tiles; j++)
		{

			int altura;
			if (cScene::BLOCK_SIZE == 32) altura = -tile_y;
			else if (cScene::BLOCK_SIZE == 16) altura = -tile_y - 1;
			cScene::debugmap[abs(tile_x + ((altura + j)*cScene::SCENE_WIDTH))] = 1;
			int tileID = map[abs(tile_x + ((altura + j)*cScene::SCENE_WIDTH))];
			if (tileID != 0) {
				if (cScene::tiles[tileID - 1].isSolid())	{
					collides = true;
				}
			}
		}
	
	//std::cout << "NOT COLLIDING" << std::endl;
	return collides;
}

void cEvilBird::MoveRight(int *map) {
	int xaux;

	//Whats next tile?
	if ((x % cScene::TILE_SIZE) == 0)
	{
		xaux = x;
		x += STEP_LENGTH;

		if (CollidesMapWall(map, true))
		{
			x = xaux;
			state = STATE_LOOKRIGHT;
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
void cEvilBird::MoveLeft(int *map) {
	int xaux;

	//Whats next tile?
	if ((x % cScene::TILE_SIZE) == 0)
	{
		xaux = x;
		x -= STEP_LENGTH;

		if (CollidesMapWall(map, false))
		{
			x = xaux;
			state = STATE_LOOKLEFT;
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

void cEvilBird::Logic(int *map) {
	//if (actualDirection == LEFT) std::cout << "LEFT" << std::endl;
	//if (actualDirection == RIGHT) std::cout << "RIGHT" << std::endl;
	switch (actualDirection) {
	case LEFT:

		MoveLeft(map);
		break;

	case RIGHT:
		MoveRight(map);
		break;
	}
	
	//cBicho::Logic(map);
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