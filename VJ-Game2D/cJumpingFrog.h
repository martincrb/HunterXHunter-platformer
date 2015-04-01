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
	void Logic();
	void Hurt();
private:
	int jump_freq;
	int jumpDelay;
};

