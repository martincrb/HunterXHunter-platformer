#include "Hisoka.h"
#include <iostream>


Hisoka::Hisoka() {
	this->p = p;
	attacking = false;
	invulnerable = false;
	hurtDelay = 0;
	lives = 5;
	shoot_time = 0;
	inv_time = 0;
	
	Animation idle;
	idle.addFrame(200, 2, 2, 61, 24, 60, 202, 0, 0);
	animations.push_back(idle);

	Animation attack;
	attack.addFrame(200, 28, 2, 65, 30, 60, 202, 0, 0);
	attack.addFrame(200, 2, 69, 63, 49, 60, 202, -15, 0);
	animations.push_back(attack);

	Animation defend;
	defend.addFrame(200, 2, 134, 66, 45, 60, 202, 0, 0);
	animations.push_back(defend);

	currentAnimation = &animations[0];
	currentFrame = currentAnimation->frames[0];
}

bool Hisoka::Collides(cRect *rc) {
	for (int i = 0; i < cards.size(); ++i) {
		if (cards[i].Collides(rc)) {
			return true;
		}
	}
	if (cBicho::Collides(rc)) return true;;
	return false;
}

void Hisoka::Logic() {

	if (!invulnerable && (x - obj_x) <= MIN_DIST) {
		if (!attacking) {
			attacking = true;
			currentAnimation = &animations[1];
			currentFrame = currentAnimation->frames[0];

		}
		if (shoot_time <= 0) {
			shoot_time = T;
			currentFrame = currentAnimation->frames[1];
			Card card = Card(x, y, obj_x + 16, obj_y + 10);
			card.SetWidthHeight(16, 16);
			cards.push_back(card);
		}
		if (shoot_time == T - 20) {
			currentFrame = currentAnimation->frames[0];
		}
	}
	else {
		attacking = false;
		if (invulnerable) {
			currentAnimation = &animations[2];
			currentFrame = currentAnimation->frames[0];
		}
		else {
			currentAnimation = &animations[0];
			currentFrame = currentAnimation->frames[0];
		}
		frameDelay = 8;
	}
	if (shoot_time > 0) shoot_time--;
	if (invulnerable) {
		inv_time--;
		invulnerable = inv_time > 0;
		if (!invulnerable) {
			currentAnimation = &animations[0];
			currentFrame = currentAnimation->frames[0];
		}
	}
	if (inv_time == INV_TIME - 30) {
		currentAnimation = &animations[2];
		currentFrame = currentAnimation->frames[0];
	}
	if (!cards.empty() && !cards[0].alive)
		cards.erase(cards.begin());

	for (unsigned int i = 0; i < cards.size(); i++) {
		cards[i].Logic();
	}
}

void Hisoka::Draw(int tex_id) {
	float xo, yo, xf, yf;
	xo = currentFrame.tile_px + float(currentFrame.tile_width) / float(60);	yo = currentFrame.tile_py + float(currentFrame.tile_heigth) / float(202);
	xf = currentFrame.tile_px;
	yf = yo - float(currentFrame.tile_heigth) / float(202);
	//NextFrame(currentAnimation->frames.size());
	cBicho::SetWidthHeight(currentFrame.tile_width, currentFrame.tile_heigth);
	DrawRect(tex_id, xo, yo, xf, yf);

	for (unsigned int i = 0; i < cards.size(); ++i)
		cards[i].Draw();
}

void Hisoka::Hurt() {
	if (!invulnerable) {
		lives--;
		alive = lives > 0;
		invulnerable = true;
		attacking = false;
		inv_time = INV_TIME;
		std::cout << "asdfadsfasdfasdfasd" << std::endl;
	}
}

Hisoka::Card::Card(int x, int y, int obj_x, int obj_y) {
	this->x = x;
	this->y = y + 16;
	initial_x = x;
	initial_y = y + 16;
	dist = 0;

	move_x = obj_x - x;
	move_y = obj_y - y;

	//normalize
	float module = sqrt(pow(move_x, 2) + pow(move_y, 2));

	move_x = SPEED * move_x / module;
	move_y = SPEED * move_y / module;
}

void Hisoka::Card::Logic() {
	alive = dist <= MAX_DIST;
	dist++;

	x = initial_x + move_x * SPEED * dist;
	y = initial_y + move_y * SPEED * dist;
}

void Hisoka::Card::Draw() {
	float xo, yo, xf, yf;

	xo = currentFrame.tile_px + float(currentFrame.tile_width) / float(16);	yo = currentFrame.tile_py + float(currentFrame.tile_heigth) / float(16);
	xf = currentFrame.tile_px;
	currentFrame.px_disp = 0;
	currentFrame.py_disp = 0;
	yf = yo - float(currentFrame.tile_heigth) / float(16);
	//cBicho::SetWidthHeight(16, 16);
	DrawRect(19, 0, 1, 1, 0);
}
