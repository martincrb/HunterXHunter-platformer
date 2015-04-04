#include "Credits.h"
#include "Resources.h"
#include "cGame.h"
#include "cText.h"


Credits::Credits()
{
	final_pos = 500;
	text_pos = 0;
	endInitialAnim = false;
}


Credits::~Credits()
{
}

bool Credits::Init(cGame* cG) {
	gameController = cG;
	bool res = true;

	res = Data.LoadImage(IMG_FONT, Resources::FONT, GL_RGBA);
	if (!res) return false;

	Sound.init();

	Sound.LoadSound(TITLE_MUSIC, "res/audio/title_music.wav", BG_MUSIC);
	Sound.setVolume(MUSIC_CHANNEL, 0.5);
	Sound.Play(TITLE_MUSIC, MUSIC_CHANNEL);

	return res;


}
bool Credits::Loop() {

	bool res = true;

	res = Process();
	if (res) Render();

	return res;

}
void Credits::Finalize() {
	Sound.Stop(TITLE_MUSIC);
	//Sound.FreeAll();
}

//Input
void Credits::ReadKeyboard(unsigned char key, int x, int y, bool press) {
	keys[key] = press;
}
void Credits::ReadMouse(int button, int state, int x, int y) {

}
//Process
bool Credits::Process() {
	Sound.UpdateSound();
	if (keys[99] && endInitialAnim)		gameController->Reset();
	return true;
}
//Output
void Credits::Render() {
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
	
	glEnable(GL_TEXTURE_2D);
	cText text1;
	text1.setText("CREDITS");
	text1.setPosition(340, text_pos - 200);
	text1.Draw(Data.GetID(IMG_FONT));

	cText text2;
	text2.setText("MARTIN CRISTOBAL BALASCH");
	text2.setPosition(200, text_pos - 300);
	text2.Draw(Data.GetID(IMG_FONT));

	cText text3;
	text3.setText("DAVID BOSCH SERRA");
	text3.setPosition(250, text_pos - 350);
	text3.Draw(Data.GetID(IMG_FONT));
	
	if (text_pos < GAME_HEIGHT) {
		++text_pos;
	}
	else {
		endInitialAnim = true;
	}
	glDisable(GL_TEXTURE_2D);
	glutSwapBuffers();
}
