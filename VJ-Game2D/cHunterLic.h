#pragma once
#include "cBicho.h"
class cHunterLic :
	public cBicho
{
public:
	cHunterLic();
	~cHunterLic();
	void Logic();
	void Draw(int tex_id);
};

