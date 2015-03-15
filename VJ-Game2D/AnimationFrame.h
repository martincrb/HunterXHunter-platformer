#pragma once
class AnimationFrame
{
public:
	AnimationFrame();
	AnimationFrame(int duration, float tile_px, float tile_py, int tile_heigth, int tile_width);
	~AnimationFrame();
	int duration;
	float tile_px;
	float tile_py;
	int tile_heigth;
	int tile_width;
};

