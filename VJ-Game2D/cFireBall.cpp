#include "cFireBall.h"


cFireBall::cFireBall()
{
}


cFireBall::~cFireBall()
{
}

bool cFireBall::Collides(cRect *rc) {
	return cBicho::Collides(rc);
}

void cFireBall::Draw(int tex_id) {
	float xo, yo, xf, yf;

	xo = currentFrame.tile_px + float(currentFrame.tile_width) / float(16);	yo = currentFrame.tile_py + float(currentFrame.tile_heigth) / float(16);
	xf = currentFrame.tile_px;
	yf = yo - float(currentFrame.tile_heigth) / float(16);
	currentFrame.px_disp = 0;
	currentFrame.py_disp = 0;
	cBicho::SetWidthHeight(16, 16);
	DrawRect(7, 0, 1, 1, 0);
}