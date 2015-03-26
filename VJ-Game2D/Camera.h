#include "Boundary.h"

#include "cRect.h"

#pragma once
class Camera
{
public:
	Camera();
	Camera(int orig_x, int orig_y, int width, int height, Boundary* boundary, int player_x, int player_y);
	void set_camera(int orig_x, int orig_y, int width, int height);
	void move_player(int pos_x, int pos_y);
	void get_camera_pos(int& x, int& y);
private:
	int orig_x;
	int orig_y;
	int width;
	int height;
	Boundary boundary;
	int player_x;
	int player_y;
	int player_last_x;
	int player_last_y;
	cRect last_valid_camera;
	void set_boundary(Boundary boundary);
	void set_player_pos(int x, int y);
	cRect pos_to_rect();
};

