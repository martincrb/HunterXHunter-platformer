#pragma once

#include "cBicho.h"

#define PLAYER_START_CX		3
#define PLAYER_START_CY		2
#define PUNCH_DURATION		2

class cPlayer: public cBicho
{
public:
	cPlayer();
	~cPlayer();
	cPlayer(int state);
	void Punch(int *map);
	void Draw(int tex_id);
private:
	int punchDelay;
	bool punching;

};
