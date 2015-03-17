#pragma once
#include "cBicho.h"

#define JUMP_DELAY 20

class cJumpingFrog :
	public cBicho
{
public:
	cJumpingFrog();
	~cJumpingFrog();
	void Draw(int text_id);
	void Logic(int *map);
};

