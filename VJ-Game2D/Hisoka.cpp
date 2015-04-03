#include "Hisoka.h"
#include <iostream>


Hisoka::Hisoka(PlayerController* p) {
	this->p = p;
	attacking = false;
	invulnerable = false;
	hurtDelay = 0;
	lives = 5;
	shoot_time = 0;
	inv_time = 0;

	Animation idle;
	idle.addFrame(200, 2, 2, 23, 25, 32, 64, 0, 0);
	animations.push_back(idle);
	currentAnimation = &animations[0];
	currentFrame = currentAnimation->frames[0];
}

bool Hisoka::Collides(cRect *rc) {
	cRect playerBox;
	p->getCurrentPlayer()->GetArea(&playerBox);
	if (rc->bottom == playerBox.bottom && rc->left == playerBox.left && rc->right == playerBox.right && rc->top == playerBox.top) { // si rc es el player box
		if (cBicho::Collides(rc))
			return true;
		for (unsigned int i = 0; i < cards.size(); i++)
			if (cards[i].Collides(rc))
				return true;
		return false;
	}
	else { // si rc es el hitbox
		return cBicho::Collides(rc);
	}
}

void Hisoka::Logic() {
	int player_x, player_y;
	p->getCurrentPlayer()->GetPosition(&player_x, &player_y);
	if ((x - player_x) <= MIN_DIST) {
		if (!attacking) {
			attacking = true;
		}
		if (shoot_time <= 0) {
			shoot_time = T;
			Card card = Card(x, y);
			card.SetWidthHeight(16, 16);
			cards.push_back(card);
		}
	}
	else {
		attacking = false;
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
	xo = currentFrame.tile_px + float(currentFrame.tile_width) / float(32);	yo = currentFrame.tile_py + float(currentFrame.tile_heigth) / float(64);
	xf = currentFrame.tile_px;
	yf = yo - float(currentFrame.tile_heigth) / float(64);
	cBicho::SetWidthHeight(currentFrame.tile_width, currentFrame.tile_heigth);
	DrawRect(7, xo, yo, xf, yf);

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
	yf = yo - float(currentFrame.tile_heigth) / float(16);
	//cBicho::SetWidthHeight(16, 16);
	DrawRect(7, 0, 1, 1, 0);
}
