#pragma once
#include "cBicho.h"

#define LICK_DELAY 60
#define INITIAL_DELAY 100

class cGhost :
	public cBicho
{
public:
	cGhost();
	~cGhost();
	void Logic();
	void Draw(cData* data);

	
private:
	int lick_counter;
	int initial_counter;
	bool lick;
};

