#include "AnimationFrame.h"

AnimationFrame::AnimationFrame(int duration, float tile_px, float tile_py, int tile_heigth, int tile_width, int px_displace, int py_displace) {
	this->px_disp = px_displace;
	this->py_disp = py_displace;
	this->duration = duration;
	this->tile_px = tile_px;
	this->tile_py = tile_py;
	this->tile_heigth = tile_heigth;
	this->tile_width = tile_width;

}
AnimationFrame::AnimationFrame()
{
}


AnimationFrame::~AnimationFrame()
{
}
