#pragma once

#include "cBicho.h"

#define PLAYER_START_CX		3
#define PLAYER_START_CY		2
#define PUNCH_DURATION		10
#define PUNCH_COOLDOWN		60
#define CHARGE_SPEED		0.025

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
	virtual bool isUsingHability();
	void setCollisionBox(cRect r);
	virtual bool CollidesMapWall();
	virtual bool CollidesMapFloor();
	virtual void GetArea(cRect *rc);
	virtual void Logic();
	void SuperJump();
	bool isSuperJumping();
protected:
	bool hability;
	cRect coll_box;
	virtual void adjust();
	
	bool superjump;
	bool charging;
	float charge;

	static const int MAX_CHARGE = 4;

};
