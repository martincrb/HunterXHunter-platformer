
#include "cPlayer.h"
#include "cScene.h"

cPlayer::cPlayer() {
	superjump = false;
	charging = false;
	charge = 0;
}

cPlayer::~cPlayer(){}

cPlayer::cPlayer(int state) {
	
}

void cPlayer::Hability(){
		hability = true;
}
void cPlayer::Draw(int tex_id)
{	
}

bool cPlayer::isUsingHability() {
	return hability;
}

int cPlayer::HurtsDestructible(cRect hitBox) {
	return false;
}

bool cPlayer::Collides(cRect *rc) {
	if (x + coll_box.right < rc->left) {
		return false; // a is left of b
	}
	if (x + coll_box.left > rc->right) {
		return false; // a is right of b
	}
	if (y + coll_box.top < rc->bottom){
		return false; // a is above b
	}
	if (y + coll_box.bottom > rc->top) {
		return false; // a is below b
	}
	return true;
}

void cPlayer::setCollisionBox(cRect r) {
	coll_box = r;
}

bool cPlayer::CollidesMapWall()
{
	int tile_x1 = (x + coll_box.left) / cScene::TILE_SIZE;
	int tile_x2 = (x + coll_box.right) / cScene::TILE_SIZE;
	int tile_y = cScene::SCENE_HEIGHT - 1 - (y + coll_box.top) / cScene::TILE_SIZE;
	int tile_ini = tile_y;
	int tile_fin = cScene::SCENE_HEIGHT - 1 - (y + coll_box.bottom) / cScene::TILE_SIZE;
	for (int i = tile_ini; i <= tile_fin; i++) {
		//cScene::debugmap[tile_x1 + i * cScene::SCENE_WIDTH] = 1;
		int tileID = map[tile_x1 + i * cScene::SCENE_WIDTH];
		if (tileID != 0 && cScene::tiles[tileID - 1].isSolid())
			return true;

		//cScene::debugmap[tile_x2 + i * cScene::SCENE_WIDTH] = 1;
		tileID = map[tile_x2 + i * cScene::SCENE_WIDTH];
		if (tileID != 0 && cScene::tiles[tileID - 1].isSolid())
			//cScene::debugmap[tile_x2 + i * cScene::SCENE_WIDTH] = 1;
			return true;
	}
	return false;
}

bool cPlayer::CollidesMapFloor()
{
	int tile_x = (x + coll_box.left) / cScene::TILE_SIZE;
	int tile_y = cScene::SCENE_HEIGHT - 1 - (y + coll_box.bottom) / cScene::TILE_SIZE;
	if ((y + coll_box.bottom) % cScene::TILE_SIZE == 0) tile_y++;

	int tile_ini = tile_x;
	int tile_fin = (x + coll_box.right) / cScene::TILE_SIZE;
	if ((x + coll_box.right) % cScene::TILE_SIZE == 0) tile_fin--;
	for (int i = tile_ini; i <= tile_fin; i++) {
		//cScene::debugmap[i + tile_y * cScene::SCENE_WIDTH] = 1;
		int tileID = map[i + tile_y * cScene::SCENE_WIDTH];
		if (tileID != 0 && cScene::tiles[tileID - 1].isSolid()) {
			in_air = false;
			return true;
		}
	}
	return false;
}

void cPlayer::adjust() {
	int dif_x = x - last_x;
	int dif_y = y - last_y;
	int tile_x = x / cScene::TILE_SIZE;
	int tile_y = cScene::SCENE_HEIGHT - 1 - y / cScene::TILE_SIZE;

	if (dif_x < 0) { // moved left
		int tile_ini = cScene::SCENE_HEIGHT - 1 - (y + coll_box.top) / cScene::TILE_SIZE;
		int tile_fin = tile_y;
		for (int i = tile_ini; i <= tile_fin; i++) {
			int tileID = map[tile_x + i * cScene::SCENE_WIDTH];
			if (tileID != 0 && cScene::tiles[tileID - 1].isSolid()) {
				x = (tile_x + 1) * cScene::TILE_SIZE;
				break;
			}
		}
	}
	else if (dif_x > 0) { // moved right
		tile_x = (x + coll_box.right) / cScene::TILE_SIZE;
		int tile_ini = cScene::SCENE_HEIGHT - 1 - (y + coll_box.top) / cScene::TILE_SIZE;
		int tile_fin = tile_y;
		for (int i = tile_ini; i <= tile_fin; i++) {
			int tileID = map[tile_x + i * cScene::SCENE_WIDTH];
			if (tileID != 0 && cScene::tiles[tileID - 1].isSolid()) {
				x = tile_x * cScene::TILE_SIZE - coll_box.right;
				break;
			}
		}
	}
	if (dif_y < 0) { // moved down
		int tile_ini = tile_x;
		int tile_fin = (x + coll_box.right) / cScene::TILE_SIZE;
		if ((x + coll_box.right) % cScene::TILE_SIZE == 0) tile_fin--;
		for (int i = tile_ini; i <= tile_fin; i++) {
			int tileID = map[i + tile_y * cScene::SCENE_WIDTH];
			if (tileID != 0 && cScene::tiles[tileID - 1].isSolid()) {
				y = (cScene::SCENE_HEIGHT - tile_y) * cScene::TILE_SIZE;
				break;
			}
		}
	}
	else if (dif_y > 0) { // moved up
		tile_y = cScene::SCENE_HEIGHT - 1 - (y + coll_box.top) / cScene::TILE_SIZE;
		int tile_ini = tile_x;
		int tile_fin = (x + coll_box.right) / cScene::TILE_SIZE;
		if ((x + coll_box.right) % cScene::TILE_SIZE == 0) tile_fin--;
		for (int i = tile_ini; i <= tile_fin; i++) {
			//cScene::debugmap[i + tile_y * cScene::SCENE_WIDTH] = 1;
			int tileID = map[i + tile_y * cScene::SCENE_WIDTH];
			if (tileID != 0 && cScene::tiles[tileID - 1].isSolid()) {
				y = (cScene::SCENE_HEIGHT - tile_y - 1) * cScene::TILE_SIZE - coll_box.top;
				jumping = false;
				charge = 0;
				break;
			}
		}
	}
}

void cPlayer::GetArea(cRect *rc)
{
	rc->bottom = y + coll_box.bottom;
	rc->right = x + coll_box.right;
	rc->left = x + coll_box.left;
	rc->top = y + coll_box.top;
}

void cPlayer::Logic()
{
	float alfa;
	last_x = x;
	last_y = y;
	if (charging && !superjump) {
		charging = false;
		in_air = true;
		jumping = true;
		jump_alfa = 0;
		jump_y = y;
	}
	if (jumping) {
		jump_alfa += JUMP_STEP;

		if (jump_alfa == 180) {
			jumping = false;
			charging = false;
			charge = 0;
			y = jump_y;
		}
		else {
			alfa = ((float)jump_alfa) * 0.017453f;
			if (charge != 0)
				y = jump_y + (int)(JUMP_HEIGHT * charge * sin(alfa));
			else
				y = jump_y + (int)(JUMP_HEIGHT * sin(alfa));

			if (jump_alfa > 90)	{
				//Over floor?
				in_air = !CollidesMapFloor();
				jumping = false;
				charge = 0;
			}
		}
	}
	else {
		//Over floor?
		if (!CollidesMapFloor()) {
			if (!in_water) {
				y -= (2 * STEP_LENGTH);
				in_air = true;
			}
			else {
				y -= (STEP_LENGTH / 2);
			}
		}
	}
	if (superjump)
		superjump = false;
	adjust();
}

void cPlayer::SuperJump() {
	if (!inAir() && !in_water) {
		if (state == STATE_WALKLEFT || state == STATE_LOOKLEFT) {
			state = STATE_DUCKLEFT;
		}
		else if (state == STATE_WALKRIGHT || state == STATE_LOOKRIGHT) {
			state = STATE_DUCKRIGHT;
		}
		if (charging) {
			charge += CHARGE_SPEED;
			if (charge > MAX_CHARGE)
				charge = MAX_CHARGE;
		}
		else {
			charging = true;
			charge = 0.4;
		}
		superjump = true;
	}
	//else
	//hability = false;
}

bool cPlayer::isSuperJumping() {
	return jumping && charge != 0;
}