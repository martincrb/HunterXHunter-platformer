#include "Boundary.h"
#include <cassert>


Boundary::Boundary()
{
}

Boundary::Boundary(const Boundary& boundary) : areas(boundary.areas), vertices(boundary.vertices) {}


bool Boundary::collides()
{
	//TODO
	return true;
}

void Boundary::addBoundary(cRect rect) {
	areas.push_back(rect);
	add_vertex(Point(rect.left, rect.top));
	add_vertex(Point(rect.right, rect.bottom));
}

bool Boundary::point_inside(int x, int y) {
	for (unsigned int i = 0; i < areas.size(); i++) {
		if (x >= areas[i].left && x <= areas[i].right && y <= areas[i].top && y >= areas[i].bottom)
			return true;
	}
	return false;
}

bool Boundary::is_inside(cRect rect) {
	return point_inside(rect.left, rect.top) && point_inside(rect.left, rect.bottom) && point_inside(rect.right, rect.bottom) && point_inside(rect.right, rect.top);
}

void Boundary::adjust(cRect& rect, const cRect& last_valid) {
	assert(vertices.size() > 0); // Asumimos que siempre habrán vertices	
	// comprobar si los 4 vertices estan dentro
	bool left_top = point_inside(rect.left, rect.top);
	bool left_bottom = point_inside(rect.left, rect.bottom);
	bool right_bottom = point_inside(rect.right, rect.bottom);
	bool right_top = point_inside(rect.right, rect.top);
	//std::cout << rect.top << "|" << rect.left << "|" << rect.bottom << "|" << rect.right << std::endl;

	if (left_top && left_bottom && right_bottom && right_top)
		return;

	// pushers - to do

	// sides
	if (!left_top && !right_top) { //top
		int i = 0; // Indice
		Point vertex = vertices[0];
		while (vertex.y > rect.top || vertex.y < last_valid.top) {
			i++;
			assert(i < vertices.size()); // Se tendria que cumplir siempre
			vertex = vertices[i];
		}
		rect.bottom += rect.top - vertex.y;
		rect.top = vertex.y;
		left_top = point_inside(rect.left, rect.top);
		left_bottom = point_inside(rect.left, rect.bottom);
		right_bottom = point_inside(rect.right, rect.bottom);
		right_top = point_inside(rect.right, rect.top);
		assert(left_bottom || right_bottom); // Si la parte inferior esta fuera es que el boundary es demasiado pequeño
	}

	if (!left_top && !left_bottom) { //left
		int i = 0; // Indice
		Point vertex = vertices[0];
		while (vertex.x < rect.left || vertex.x > last_valid.left) {
			i++;
			assert(i < vertices.size()); // Se tendria que cumplir siempre
			vertex = vertices[i];
		}
		rect.right += vertex.x - rect.left;
		rect.left = vertex.x;
		left_top = point_inside(rect.left, rect.top);
		left_bottom = point_inside(rect.left, rect.bottom);
		right_bottom = point_inside(rect.right, rect.bottom);
		right_top = point_inside(rect.right, rect.top);
		assert(right_bottom || right_top); // Si la parte derecha esta fuera es que el boundary es demasiado pequeño
	}

	if (!left_bottom && !right_bottom) { //bottom
		int i = 0; // Indice
		Point vertex = vertices[0];
		while (vertex.y < rect.bottom || vertex.y > last_valid.bottom) {
			i++;
			assert(i < vertices.size()); // Se tendria que cumplir siempre
			vertex = vertices[i];
		}
		rect.top -= vertex.y - rect.bottom;
		rect.bottom = vertex.y;
		
		left_top = point_inside(rect.left, rect.top);
		left_bottom = point_inside(rect.left, rect.bottom);
		right_bottom = point_inside(rect.right, rect.bottom);
		right_top = point_inside(rect.right, rect.top);
		assert(left_top || right_top); // Si la parte superior esta fuera es que el boundary es demasiado pequeño
	}

	if (!right_top && !right_bottom) { //right
		int i = 0; // Indice
		Point vertex = vertices[0];
		while (vertex.x > rect.right || vertex.x < last_valid.right) {
			i++;
			assert(i < vertices.size()); // Se tendria que cumplir siempre
			vertex = vertices[i];
		}
		rect.left -= rect.right - vertex.x;
		rect.right = vertex.x;

		left_top = point_inside(rect.left, rect.top);
		left_bottom = point_inside(rect.left, rect.bottom);
		right_bottom = point_inside(rect.right, rect.bottom);
		right_top = point_inside(rect.right, rect.top);
		assert(left_bottom || left_top); // Si la parte izquierda esta fuera es que el boundary es demasiado pequeño
	}
}

void Boundary::add_vertex(Point p) {
	// Agrega solo los que son diferentes
	// Es lineal, pero como habrá pocos no pasa nada. Además, solo se hace al cargar un nivel
	for (unsigned int i = 0; i < vertices.size(); i++) {
		if (vertices[i] == p)
			return;
	}
	vertices.push_back(p);
}
