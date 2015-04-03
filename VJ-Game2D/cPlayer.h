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
	virtual void Hability();
	virtual void Draw(int tex_id);
	virtual bool Collides(cRect *rc);
	int HurtsDestructible(cRect hitBox);
	bool isUsingHability();
	void setCollisionBox(cRect r);
protected:
	int punchDelay;
	bool hability;
	cRect coll_box;

};
