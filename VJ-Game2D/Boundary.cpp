#include "Boundary.h"


Boundary::Boundary()
{
}

Boundary::Boundary(const Boundary& boundary) : areas(boundary.areas) {}


bool Boundary::collides()
{
	//TODO
	return true;
}

void Boundary::addBoundary(cRect rectangle) {
	areas.push_back(rectangle);
}

bool Boundary::point_inside(int x, int y) {
	for (int i = 0; i < areas.size(); i++) {
		if (x >= areas[i].left && x <= areas[i].right && y >= areas[i].top && y <= areas[i].bottom)
			return true;
	}
	return false;
}

bool Boundary::adjust(int& orig_x, int& orig_y, int width, int height) {
	// comprobar si los 4 vertices estan dentro
	// si uno no esta dentro desplazar hasta que lo este y volver a empezar
	// si despues de haber movido hacia los 4 lados sigue sin estar dentro devolver false
	return false;
}

