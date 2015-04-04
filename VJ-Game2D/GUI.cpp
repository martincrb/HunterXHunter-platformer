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
	text.setText("SCORE:"+sc);
	text.setPosition(350, 550);

	glPushMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, GAME_WIDTH, 0, GAME_HEIGHT, 0, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	text.Draw(data->getCurrentScreen()->getTexID(IMG_FONT));

	//Draw currentPlayer GUI
	int pos_gui_x, pos_gui_y;
	int gui_w, gui_h;
	gui_w = 150;
	gui_h = 150;
	pos_gui_x = 0;
	pos_gui_y = GAME_HEIGHT-gui_h;
	
	//std::cout << "QUAD SIZE: " << std::endl;
	//std::cout << w << " " << h << std::endl;
	text.setPosition(100, GAME_HEIGHT - 50);

	int tex_id = data->getCurrentScreen()->getTexID(IMG_GUI_GON);
	if (data->currentIsGon()) {
		text.setText("GON");
		tex_id = data->getCurrentScreen()->getTexID(IMG_GUI_GON);
	}
	else if (data->currentIsKillua()) {
		text.setText("KILLUA");
		tex_id = data->getCurrentScreen()->getTexID(IMG_GUI_KILLUA);
	}
	text.Draw(data->getCurrentScreen()->getTexID(IMG_FONT));
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex_id);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1);	glVertex2i(pos_gui_x, pos_gui_y);
	glTexCoord2f(1, 1);	glVertex2i(pos_gui_x + gui_w, pos_gui_y);
	glTexCoord2f(1, 0);	glVertex2i(pos_gui_x + gui_w, pos_gui_y + gui_h);
	glTexCoord2f(0, 0);	glVertex2i(pos_gui_x, pos_gui_y + gui_h);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}