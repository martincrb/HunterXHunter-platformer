#pragma once
#include "cBicho.h"
class cHunterLic :
	public cBicho
{
public:
	cHunterLic();
	~cHunterLic();
	void Logic();
	void Draw(cData* data);
	virtual bool CollidesMapFloor();
};

