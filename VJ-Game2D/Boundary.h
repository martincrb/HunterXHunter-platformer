#pragma once
#include "cRect.h"
#include <vector>
class Boundary
{
public:
	Boundary();
	Boundary(const Boundary& boundary);
	bool collides(); //TODO
	void addBoundary(cRect rectangle);
	bool point_inside(int x, int y);
	bool adjust(int& orig_x, int& orig_y, int width, int height);

private:
	std::vector<cRect> areas;

};

