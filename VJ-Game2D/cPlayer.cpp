
#include "cPlayer.h"

cPlayer::cPlayer() {
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