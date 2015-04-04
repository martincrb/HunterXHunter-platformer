#include "cFireBall.h"


cFireBall::cFireBall(int dist, float angle) : dist(dist), angle(angle) {
	direc = -1;
}


cFireBall::~cFireBall()
{
}

bool cFireBall::Collides(cRect *rc) {
	return cBicho::Collides(rc);
}

void cFireBall::Draw(cData* data) {
	float xo, yo, xf, yf;
	int tex_id = data->GetID(IMG_OCTO_BALL);
	xo = currentFrame.tile_px + float(currentFrame.tile_width) / float(16);	yo = currentFrame.tile_py + float(currentFrame.tile_heigth) / float(16);
	xf = currentFrame.tile_px;
	yf = yo - float(currentFrame.tile_heigth) / float(16);
	currentFrame.px_disp = 0;
	currentFrame.py_disp = 0;
	cBicho::SetWidthHeight(16, 16);
	DrawRect(tex_id, 0, 1, 1, 0);
}