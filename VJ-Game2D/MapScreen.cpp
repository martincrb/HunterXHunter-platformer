#include "MapScreen.h"
#include "Resources.h"
#include "cGame.h"

MapScreen::MapScreen()
{
	frameCounter = 0;
}


MapScreen::~MapScreen()
{
}

bool MapScreen::Init(cGame* cG) {
	gameController = cG;
	frameCounter = 0;
	uncover_displace = 0;
	bool res = true;
	for (int key = 0; key < 256; key++)
		keys[key] = false;
	Sound.init();



	res = Data.LoadImage(IMG_MAP_SCREEN, Resources::MAP_SCREEN , GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_MAP_UNCOVER, Resources::MAP_COVER, GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_FONT, Resources::FONT, GL_RGBA);
	if (!res) return false;

	Sound.LoadSound(MAP_MUSIC, "res/audio/map.wav", EFFECT);
	Sound.setVolume(EFFECTS_CHANNEL, 0.3);
	Sound.Play(MAP_MUSIC, EFFECTS_CHANNEL);

	return res;


}
bool MapScreen::Loop() {

	bool res = true;

	res = Process();
	if (res) Render();

	return res;

}
void MapScreen::Finalize() {
	Sound.Stop(MAP_MUSIC);
	Sound.FreeAll();
}

//Input
void MapScreen::ReadKeyboard(unsigned char key, int x, int y, bool press) {
	keys[key] = press;
}
void MapScreen::ReadMouse(int button, int state, int x, int y) {

}
//Process
bool MapScreen::Process() {
	
	Sound.UpdateSound();
	++frameCounter;
	if (frameCounter >= MAP_SCREEN_DURATION) {
		gameController->startLevel(gameController->getLevel());
	}
	//if (keys[99])		gameController->startLevel(1);
	return true;
}
//Output
void MapScreen::Render() {
	if (uncover_displace <= 478)
		uncover_displace += 5;
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();
	int screen_x, screen_y;
	screen_x = 0;
	screen_y = 0;

	glEnable(GL_TEXTURE_2D);
	//std::cout << "QUAD SIZE: " << std::endl;
	//std::cout << w << " " << h << std::endl;
	glBindTexture(GL_TEXTURE_2D, Data.GetID(IMG_MAP_SCREEN));
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1);	glVertex2i(screen_x, screen_y);
	glTexCoord2f(1, 1);	glVertex2i(screen_x + GAME_WIDTH, screen_y);
	glTexCoord2f(1, 0);	glVertex2i(screen_x + GAME_WIDTH, screen_y + GAME_HEIGHT);
	glTexCoord2f(0, 0);	glVertex2i(screen_x, screen_y + GAME_HEIGHT);
	glEnd();

	
	screen_x += 165 + uncover_displace;
	glBindTexture(GL_TEXTURE_2D, Data.GetID(IMG_MAP_UNCOVER));
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1);	glVertex2i(screen_x, screen_y);
	glTexCoord2f(1, 1);	glVertex2i(screen_x + GAME_WIDTH, screen_y);
	glTexCoord2f(1, 0);	glVertex2i(screen_x + GAME_WIDTH, screen_y + GAME_HEIGHT);
	glTexCoord2f(0, 0);	glVertex2i(screen_x, screen_y + GAME_HEIGHT);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	cText text;
	if (gameController->getLevel() == 1) {
		text.setText("MT ETERNAL");
	}
	else if (gameController->getLevel() == 2) {
		text.setText("GREED ISLAND");
	}
	else if (gameController->getLevel() == 3) {
		text.setText("HISOKA CHAMBER");
	}
	text.setPosition(300, 100);
	text.Draw(Data.GetID(IMG_FONT));
	glutSwapBuffers();
}