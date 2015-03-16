#include "Boundary.h"


Boundary::Boundary()
{
}


Boundary::~Boundary()
{
}

bool Boundary::collides()
{
	//TODO
	return true;
}

void Boundary::addBoundary(cRect rectangle) {
	areas.push_back(rectangle);
}

