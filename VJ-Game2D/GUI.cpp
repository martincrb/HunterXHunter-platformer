#include "GUI.h"
#include "cGame.h"

GUI::GUI()
{
}


GUI::~GUI()
{
}

void GUI::Draw(cGame* data){
	cText text;
	
	int score = data->getScore();
	//char* buff;
	//itoa(score, buff, 10);
	std::string sc = std::to_string(score);
	text.setText("SCORE: "+sc);
	text.setPosition(350, 550);

	glPushMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, GAME_WIDTH, 0, GAME_HEIGHT, 0, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	text.Draw(data->getCurrentScreen()->getTexID(IMG_FONT));
	glPopMatrix();
}