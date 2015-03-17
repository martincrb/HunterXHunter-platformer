#include "Camera.h"
#include <cassert>


Camera::Camera() : boundary(), orig_x(0), orig_y(0), width(0), height(0), player_x(0), player_y(0) {}

Camera::Camera(int orig_x, int orig_y, int width, int height, Boundary boundary, int player_x, int player_y)
: boundary(boundary), orig_x(orig_x), orig_y(orig_y), width(width), height(height), player_x(player_x), player_y(player_y), player_last_x(player_x), player_last_y(player_y) {}

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
}

void Camera::move_player(int pos_x, int pos_y) {
	assert(boundary.point_inside(pos_x, pos_y)); // El jugador tiene que estar dentro
	
	int dx = player_last_x - pos_x;
	int dy = player_last_y - pos_y;
	player_last_x = pos_x;
	player_last_y = pos_y;

	// calcular camara
	orig_x = pos_x + width / 2;
	orig_y = pos_y + height / 2;

	assert(boundary.adjust(orig_x, orig_y, width, height)); // La camara tiene que estar dentro
}

void Camera::get_camera_pos(int& x, int& y) {
	x = orig_x;
	y = orig_y;
}
