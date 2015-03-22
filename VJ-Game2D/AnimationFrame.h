#pragma once
#include "cRect.h"
class AnimationFrame
{
public:
	AnimationFrame();
	AnimationFrame(int duration, float tile_px, float tile_py, int tile_heigth, int tile_width, int px_disp, int py_disp);
	void addHitBox(int x, int y, int w, int h);
	cRect getHitBox();
	~AnimationFrame();
	int duration;
	int px_disp;
	int py_disp;
	float tile_px;
	float tile_py;
	int tile_heigth;
	int tile_width;
	bool hasHitBox;
	cRect hitBox;
};

