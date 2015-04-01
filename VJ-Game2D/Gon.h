#pragma once
#include "cPlayer.h"
class Gon :
	public cPlayer
{
public:
	Gon();
	~Gon();
	void Draw(int tex_id);
	int HurtsDestructible(cRect hitBox);
};

