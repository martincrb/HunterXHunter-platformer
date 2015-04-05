#include "Help.h"
#include "cGame.h"
#include "Resources.h"

Help::Help()
{
	frameCounter = 0;
	drawPressButton = false;
}


Help::~Help()
{
}

bool Help::Init(cGame* cG) {
	gameController = cG;
	bool res = true;

	res = Data.LoadImage(IMG_HELP_KEYS, Resources::HELP_KEYS, GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_FONT, Resources::FONT, GL_RGBA);
	if (!res) return false;

	return res;


}
bool Help::Loop() {

	bool res = true;

	res = Process();
	if (res) Render();

	return res;

}
void Help::Finalize() {
	//Sound.FreeAll();
}

//Input
void Help::ReadKeyboard(unsigned char key, int x, int y, bool press) {
	std::cout << int(key) << std::endl;
	keys[key] = press;
}
void Help::ReadMouse(int button, int state, int x, int y) {

}
//Process
bool Help::Process() {
	return true;
}
//Output
void Help::Render() {
	++frameCounter;
	if (frameCounter == 10) {
		frameCounter = 0;
		drawPressButton = !drawPressButton;
	}

	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	int screen_x, screen_y;
	screen_x = 0;
	screen_y = 0;

	glBegin(GL_QUADS);
	glColor3f(0, 0, 0);
	glVertex2i(screen_x, screen_y);
	glVertex2i(screen_x + GAME_WIDTH, screen_y);
	glVertex2i(screen_x + GAME_WIDTH, screen_y + GAME_HEIGHT);
	glVertex2i(screen_x, screen_y + GAME_HEIGHT);
	glColor3f(1, 1, 1);
	glEnd();

	screen_y = -50;
	screen_x = 50;
	cText text;

	
	text.setText("JUMP OR MOVE UP");
	text.setPosition(90, 550);
	text.Draw(Data.GetID(IMG_FONT));

	text.setText("MOVE LEFT");
	text.setPosition(10, 480);
	text.Draw(Data.GetID(IMG_FONT));

	text.setText("MOVE RIGHT");
	text.setPosition(285, 480);
	text.Draw(Data.GetID(IMG_FONT));

	text.setText("SQUAT");
	text.setPosition(170, 320);
	text.Draw(Data.GetID(IMG_FONT));

	text.setText("CHANGE PLAYER");
	text.setPosition(170, 200);
	text.Draw(Data.GetID(IMG_FONT));

	text.setText("USE HABILITY");
	text.setPosition(170, 70);
	text.Draw(Data.GetID(IMG_FONT));

	text.setText("PRESS SCAPE TO CONTINUE");
	text.setPosition(220, 20);
	
	if (drawPressButton)
		text.Draw(Data.GetID(IMG_FONT));

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Data.GetID(IMG_HELP_KEYS));
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1);	glVertex2i(screen_x, screen_y);
	glTexCoord2f(1, 1);	glVertex2i(screen_x + 327, screen_y);
	glTexCoord2f(1, 0);	glVertex2i(screen_x + 327, screen_y + 600);
	glTexCoord2f(0, 0);	glVertex2i(screen_x, screen_y + 600);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glutSwapBuffers();
}