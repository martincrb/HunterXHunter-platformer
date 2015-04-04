#include "cHunterLic.h"


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