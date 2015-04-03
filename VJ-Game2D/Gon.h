#pragma once
#include "cPlayer.h"
class Gon :
	public cPlayer
{
public:
	Gon();
	~Gon();
	void Draw(int tex_id);
	void DrawRect(int tex_id, float xo, float yo, float xf, float yf);
	int HurtsDestructible(cRect hitBox);
};

