#include "Camera.h"
#include <cassert>
#include <iostream>


Camera::Camera() {}

Camera::Camera(int orig_x, int orig_y, int width, int height, Boundary* boundary, int player_x, int player_y)
: orig_x(orig_x), orig_y(orig_y), width(width), height(height), player_x(player_x), player_y(player_y), player_last_x(player_x), player_last_y(player_y) {
	this->boundary = *boundary;
	last_valid_camera = pos_to_rect();
	assert(this->boundary.is_inside(last_valid_camera)); // La camara tiene que estar dentro de los boundaries
}

void Camera::set_boundary(Boundary boundary) {
	this->boundary = boundary;
}

void Camera::set_player_pos(int x, int y) {
	player_x = x;
	player_y = y;
}

void Camera::set_camera(int orig_x, int orig_y, int width, int height) {
	
	this->orig_x = orig_x;
	this->orig_y = orig_y;
	this->width = width;
	this->height = height;
	last_valid_camera = pos_to_rect();
	assert(boundary.is_inside(last_valid_camera)); // La camara tiene que estar dentro de los boundaries
	
}

void Camera::move_player(int pos_x, int pos_y) {
	//std::cout << "pos: " << pos_x << "|" << pos_y << std::endl;
	assert(boundary.point_inside(pos_x, pos_y)); // El jugador tiene que estar dentro
	
	int dx = player_last_x - pos_x;
	int dy = player_last_y - pos_y;
	player_last_x = pos_x;
	player_last_y = pos_y;

	// calcular camara
	orig_x = pos_x - width / 2;
	orig_y = pos_y - height / 2;
	cRect new_camera = pos_to_rect();
	boundary.adjust(new_camera, last_valid_camera); // La camara tiene que estar dentro
	last_valid_camera = new_camera;
	orig_x = new_camera.left;
	orig_y = new_camera.top;
}

void Camera::get_camera_pos(int& x, int& y) {
	x = orig_x;
	y = orig_y;
}

cRect Camera::pos_to_rect() {
	cRect rect;
	rect.left = orig_x;
	rect.right = orig_x + width;
	rect.top = orig_y;
	rect.bottom = orig_y + height;
	return rect;
}
