#include "Animation.h"


Animation::Animation()
{
}


Animation::~Animation()
{
}

void Animation::addFrame(int duration, float tile_px, float tile_py, int tile_heigth, int tile_width, int tileset_w, int tileset_h, int px_d, int py_d) {
	AnimationFrame frame(duration, float(tile_px) / float(tileset_w), float(tile_py) / float(tileset_h), tile_heigth, tile_width, px_d, py_d);
	frames.push_back(frame);
}

void Animation::addFrame(int duration, float tile_px, float tile_py, int tile_heigth, int tile_width, int tileset_w, int tileset_h, int px_d, int py_d, cRect hitBox) {
	AnimationFrame frame(duration, float(tile_px) / float(tileset_w), float(tile_py) / float(tileset_h), tile_heigth, tile_width, px_d, py_d);
	frame.addHitBox(hitBox.left, hitBox.bottom, hitBox.right - hitBox.left, hitBox.top - hitBox.bottom);
	frames.push_back(frame);
}