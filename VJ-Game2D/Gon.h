#pragma once
#include "cPlayer.h"
class Gon :
	public cPlayer
{
public:
	Gon();
	~Gon();
	void Draw(cData* data);
	void DrawRect(int tex_id, float xo, float yo, float xf, float yf);
	int HurtsDestructible(cRect hitBox);
	virtual void Hability();
protected:
	int punchDelay;
	int cooldown;
};

