#include "Gon.h"
#include "cScene.h"

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
	cRect hitBox;
	hitBox.bottom = -20;
	hitBox.left = 40;
	hitBox.top = -20 - 8;
	hitBox.right = 40 + 15;
	punch.addFrame(200, 42, 135, 42, 52, 128, 256, 0, 0, hitBox);
	animations.push_back(punch);

	currentAnimation = &animations[0];
	currentFrame = currentAnimation->frames[0];

	punchDelay = 0;
	hability = false;
}


Gon::~Gon()
{
}


bool Gon::HurtsDestructible(cRect hitBox) {
	int tile_x, tile_y;
	int j;
	int width_tiles, height_tiles;


	//Compute WORLD position of hitbox
	int xb, yb, wb, hb;
	/*
	GetPosition(&xb, &yb);
	xb += hitBox.left;
	yb += hitBox.bottom;
	wb = hitBox.right - hitBox.left;
	hb = hitBox.top - hitBox.bottom;

	hitBox.left = xb;
	hitBox.bottom = yb + hb;
	hitBox.top = yb;
	hitBox.right = xb + wb;
	*/
	//Set tile from these coords

	tile_x = hitBox.left / cScene::TILE_SIZE;
	tile_y = hitBox.top / cScene::TILE_SIZE;
	//width_tiles = floor((float(wb) / float(cScene::TILE_SIZE)) + 0.5);
	//height_tiles = hb / cScene::TILE_SIZE;

	int tileID = map[abs(tile_x + ((-tile_y+1)*cScene::SCENE_WIDTH))];
	if (tileID != 0) {
		if (cScene::tiles[tileID - 1].isDestructable())	{
			std::cout << "DESTROY" << std::endl;
			map[abs(tile_x + ((-tile_y + 1)*cScene::SCENE_WIDTH))] = 0;
			return true;
		}
	}
	return false;
	/*
	for (j = 0; j<height_tiles; j++)
	{
		int altura;
		if (cScene::BLOCK_SIZE == 32) altura = -tile_y;
		else if (cScene::BLOCK_SIZE == 16) altura = -tile_y - 1;
		cScene::debugmap[abs(tile_x + ((altura + j)*cScene::SCENE_WIDTH))] = 1;
		int tileID = map[abs(tile_x + ((altura + j)*cScene::SCENE_WIDTH))];
		if (tileID != 0) {
			if (cScene::tiles[tileID - 1].isSolid())	{
				//std::cout << "COLLIDING" << std::endl;

				return true;
			}
		}
	}
	//std::cout << "NOT COLLIDING" << std::endl;
	return false;
	*/

}

void Gon::Draw(int tex_id){
	//Esto no deberia ir aqui, deberia ir en la logica del player (la hereda de cbicho?)
	if (hability) punchDelay++;
	if (punchDelay == PUNCH_DURATION)
	{
		punchDelay = 0;
		hability = false;
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
		else if (hability) {
			currentAnimation = &animations[3];
			currentFrame = currentAnimation->frames[0];
			currentFrame.invertHitBoxX();
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
		else if (hability) {
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
		else if (hability) {
			currentAnimation = &animations[3];
			currentFrame = currentAnimation->frames[0];
			currentFrame.invertHitBoxX();
			
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
		else if (hability) {
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
	//int xd, yd = 0;
	//cBicho::GetPosition(&xd, &yd);
	//cBicho::SetPosition(xd+currentFrame.px_disp, yd-currentFrame.py_disp);
	DrawRect(tex_id, xo, yo, xf, yf);
	
}