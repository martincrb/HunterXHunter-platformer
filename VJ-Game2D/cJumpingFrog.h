#pragma once
#include "cBicho.h"


class cJumpingFrog :
	public cBicho
{
public:
	cJumpingFrog();
	~cJumpingFrog();
	void setJumpFreq(int x);
	void Draw(int text_id);
	void Logic(int *map);
private:
	int jump_freq;
	int jumpDelay;
};

