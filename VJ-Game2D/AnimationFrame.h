#pragma once
class AnimationFrame
{
public:
	AnimationFrame();
	AnimationFrame(int duration, float tile_px, float tile_py, int tile_heigth, int tile_width, int px_disp, int py_disp);
	~AnimationFrame();
	int duration;
	int px_disp;
	int py_disp;
	float tile_px;
	float tile_py;
	int tile_heigth;
	int tile_width;
};

