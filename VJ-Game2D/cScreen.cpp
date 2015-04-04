#include "cScreen.h"


cScreen::cScreen()
{
}


cScreen::~cScreen()
{
}

int cScreen::getTexID(int tex_id) {
	return Data.GetID(tex_id);
}

bool cScreen::currentIsGon() {
	return false;
}
bool cScreen::currentIsKillua() {
	return false;
}