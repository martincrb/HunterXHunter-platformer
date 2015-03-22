#pragma once
#include <vector>
#include "AnimationFrame.h"

class Animation
{
public:
	Animation();
	~Animation();
	void addFrame(int duration, float tile_px, float tile_py, int tile_heigth, int tile_width, int tileset_w, int tileset_h, int px_d, int py_d);
	void addFrame(int duration, float tile_px, float tile_py, int tile_heigth, int tile_width, int tileset_w, int tileset_h, int px_d, int py_d, cRect hitBox);
	std::vector < AnimationFrame > frames;
};

