#pragma once
#include "cPlayer.h"
class Killua :
	public cPlayer
{
public:
	Killua();
	~Killua();
	void Punch(int *map);
	void Draw(int tex_id);
};

