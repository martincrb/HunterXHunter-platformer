
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

bool cPlayer::HurtsDestructible(cRect hitBox) {
	return false;
}