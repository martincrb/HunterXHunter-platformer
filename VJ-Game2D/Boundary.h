#pragma once
#include "cRect.h"
#include <vector>
class Boundary
{
public:
	Boundary();
	~Boundary();
	bool collides(); //TODO
	void addBoundary(cRect rectangle);

private:
	std::vector<cRect> areas;

};

