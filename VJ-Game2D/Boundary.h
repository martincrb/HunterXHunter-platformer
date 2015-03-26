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
	void adjust(cRect& rect, const cRect& last_valid);
	bool is_inside(cRect rect);
private:
	class Point {
	public:
		Point() {}
		Point(int x, int y) : x(x), y(y) {}
		bool operator ==(const Point &p) const {
			return x == p.x && y == p.y;
		}
		int x, y;
	};

	std::vector<cRect> areas;
	std::vector<Point> vertices;

	void add_vertex(Point p);
};

