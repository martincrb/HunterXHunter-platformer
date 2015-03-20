#pragma once
#include "cPlayer.h"
class Gon :
	public cPlayer
{
public:
	Gon();
	~Gon();
	void Punch(int *map);
	void Draw(int tex_id);
};

