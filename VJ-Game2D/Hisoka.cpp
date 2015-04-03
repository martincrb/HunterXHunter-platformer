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
	idle.addFrame(200, 2, 2, 61, 24, 60, 134, 0, 0);
	animations.push_back(idle);

	Animation attack;
	attack.addFrame(200, 28, 2, 65, 30, 60, 134, 0, 0);
	attack.addFrame(200, 2, 69, 63, 49, 60, 134, -15, 0);
	animations.push_back(attack);

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

	if ((x - obj_x) <= MIN_DIST) {
		if (!attacking) {
			attacking = true;
			currentAnimation = &animations[1];
			currentFrame = currentAnimation->frames[0];

		}
		if (shoot_time <= 0) {
			shoot_time = T;
			currentFrame = currentAnimation->frames[1];
			Card card = Card(x, y);
			card.SetWidthHeight(16, 16);
			cards.push_back(card);
		}
		if (shoot_time == T - 20) {
			currentFrame = currentAnimation->frames[0];
		}
	}
	else {
		attacking = false;
		currentAnimation = &animations[0];
		currentFrame = currentAnimation->frames[0];
		frameDelay = 8;
	}
	if (shoot_time > 0) shoot_time--;
	if (invulnerable) {
		inv_time--;
		invulnerable = inv_time > 0;
	}

	if (!cards.empty() && !cards[0].alive)
		cards.erase(cards.begin());

	for (unsigned int i = 0; i < cards.size(); i++) {
		cards[i].Logic();
	}
}

void Hisoka::Draw(int tex_id) {
	float xo, yo, xf, yf;
	xo = currentFrame.tile_px + float(currentFrame.tile_width) / float(60);	yo = currentFrame.tile_py + float(currentFrame.tile_heigth) / float(134);
	xf = currentFrame.tile_px;
	yf = yo - float(currentFrame.tile_heigth) / float(134);
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
		inv_time = INV_TIME;
		std::cout << "asdfadsfasdfasdfasd" << std::endl;
	}
}

Hisoka::Card::Card(int x, int y) {
	this->x = x;
	this->y = y + 16;
	initial_x = x;
}

void Hisoka::Card::Logic() {
	alive = (initial_x - x) <= MAX_DIST;
	x -= STEP;
}

void Hisoka::Card::Draw() {
	float xo, yo, xf, yf;

	xo = currentFrame.tile_px + float(currentFrame.tile_width) / float(16);	yo = currentFrame.tile_py + float(currentFrame.tile_heigth) / float(16);
	xf = currentFrame.tile_px;
	currentFrame.px_disp = 0;
	currentFrame.py_disp = 0;
	yf = yo - float(currentFrame.tile_heigth) / float(16);
	//cBicho::SetWidthHeight(16, 16);
	DrawRect(7, 0, 1, 1, 0);
}
