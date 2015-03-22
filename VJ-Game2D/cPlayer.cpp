
#include "cPlayer.h"

cPlayer::cPlayer() {
}

cPlayer::~cPlayer(){}

cPlayer::cPlayer(int state) {
	
}

void cPlayer::Punch(int *map){
	punching = true;
}
void cPlayer::Draw(int tex_id)
{	
}

bool cPlayer::isPunching() {
	return punching;
}

bool cPlayer::HurtsDestructible(int *map, cRect hitBox) {
	return false;
}