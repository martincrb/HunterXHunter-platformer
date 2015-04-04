#pragma once
#include "cBicho.h"


class cJumpingFrog :
	public cBicho
{
public:
	cJumpingFrog();
	~cJumpingFrog();
	void setJumpFreq(int x);
	void Draw(cData* data);
	void Logic();
	void Hurt();
private:
	int jump_freq;
	int jumpDelay;
};

