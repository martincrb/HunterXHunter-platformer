#include "cHunterLic.h"
#include "cScene.h"


cHunterLic::cHunterLic()
{
	Animation rotate;
	rotate.addFrame(200, 2, 2, 30, 19, 64, 64, 0, 0);
	rotate.addFrame(200, 23, 2, 30, 15, 64, 64, 2, 0);
	rotate.addFrame(200, 40, 2, 30, 10, 64, 64, 4, 0);
	rotate.addFrame(200, 52, 2, 30, 6, 64, 64, 6, 0);
	rotate.addFrame(200, 60, 2, 30, 2, 64, 64, 8, 0);
	rotate.addFrame(200, 52, 2, 30, 6, 64, 64, 6, 0);
	rotate.addFrame(200, 40, 2, 30, 10, 64, 64, 4, 0);
	rotate.addFrame(200, 23, 2, 30, 15, 64, 64, 2, 0);
	animations.push_back(rotate);
	currentAnimation = &animations[0];
	currentFrame = currentAnimation->frames[0];
}


cHunterLic::~cHunterLic()
{
}

void cHunterLic::Logic() {
	if (!CollidesMapFloor() && !in_water) {
		y -= (2 * STEP_LENGTH);
	}
	adjust();
}
void cHunterLic::Draw(int tex_id) {
	float xo, yo, xf, yf;
	xo = currentFrame.tile_px + float(currentFrame.tile_width) / float(64);	yo = currentFrame.tile_py + float(currentFrame.tile_heigth) / float(64);
	xf = currentFrame.tile_px;
	yf = yo - float(currentFrame.tile_heigth) / float(64);
	NextFrame(currentAnimation->frames.size());
	cBicho::SetWidthHeight(currentFrame.tile_width, currentFrame.tile_heigth);
	DrawRect(tex_id, xo, yo, xf, yf);
}

bool cHunterLic::CollidesMapFloor()
{
	int tile_x = x / cScene::TILE_SIZE;
	int tile_y = cScene::SCENE_HEIGHT - y / cScene::TILE_SIZE;
	if (y % cScene::TILE_SIZE == 0) tile_y++;

	int tile_ini = tile_x;
	int tile_fin = (x + w) / cScene::TILE_SIZE;
	for (int i = tile_ini; i <= tile_fin; i++) {
		//cScene::debugmap[i + tile_y * cScene::SCENE_WIDTH] = 1;
		int tileID = map[i + tile_y * cScene::SCENE_WIDTH];
		if (tileID != 0 && cScene::tiles[tileID - 1].isSolid()) {
			in_air = false;
			return true;
		}
	}
	in_air = true;
	return false;

}