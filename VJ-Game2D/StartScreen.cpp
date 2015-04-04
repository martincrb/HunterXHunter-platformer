#include "StartScreen.h"
#include "Resources.h"
#include "cGame.h"
#include "cText.h"

StartScreen::StartScreen()
{
	frameCounter = 0;
	initialAnimCounter = 0;
	drawPressButton = false;
	endInitialAnim = false;
}


StartScreen::~StartScreen()
{
}

bool StartScreen::Init(cGame* cG) {
	gameController = cG;
	bool res = true;
	Sound.init();



	res = Data.LoadImage(IMG_START_SCREEN0, Resources::START_SCREEN0, GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_START_SCREEN1, Resources::START_SCREEN1, GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_START_SCREEN2, Resources::START_SCREEN2, GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_START_SCREEN3, Resources::START_SCREEN3, GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_START_SCREEN4, Resources::START_SCREEN4, GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_START_SCREEN5, Resources::START_SCREEN, GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_FONT, Resources::FONT, GL_RGBA);
	if (!res) return false;

	Sound.LoadSound(TITLE_MUSIC, "res/audio/title_music.wav", BG_MUSIC);

	Sound.Play(TITLE_MUSIC, MUSIC_CHANNEL);

	return res;


}
bool StartScreen::Loop() {

	bool res = true;

	res = Process();
	if (res) Render();

	return res;

}
void StartScreen::Finalize() {
	Sound.Stop(TITLE_MUSIC);
	//Sound.FreeAll();
}

//Input
void StartScreen::ReadKeyboard(unsigned char key, int x, int y, bool press) {
	keys[key] = press;
}
void StartScreen::ReadMouse(int button, int state, int x, int y) {

}
//Process
bool StartScreen::Process() {
	Sound.UpdateSound();
	if (keys[99] && endInitialAnim)		gameController->startMapScreen(1);
	return true;
}
//Output
void StartScreen::Render() {
	cText text;
	text.setText("PUSH START BUTTON");
	text.setPosition(370, 200);
	
	if (endInitialAnim) {
		++frameCounter;
	}
	else {
		++initialAnimCounter;
	}

	int bgID = Data.GetID(IMG_START_SCREEN5);
	if (!endInitialAnim) {
		if (initialAnimCounter < INITIAL_ANIM_DELAY) {
			bgID = Data.GetID(IMG_START_SCREEN0);
		}
		else if (initialAnimCounter < 2 * INITIAL_ANIM_DELAY) {
			bgID = Data.GetID(IMG_START_SCREEN1);
		}
		else if (initialAnimCounter < 3 * INITIAL_ANIM_DELAY) {
			bgID = Data.GetID(IMG_START_SCREEN2);
		}
		else if (initialAnimCounter < 4 * INITIAL_ANIM_DELAY) {
			bgID = Data.GetID(IMG_START_SCREEN3);
		}
		else if (initialAnimCounter < 5 * INITIAL_ANIM_DELAY) {
			bgID = Data.GetID(IMG_START_SCREEN4);
		}
		else if (initialAnimCounter < 6 * INITIAL_ANIM_DELAY) {
			bgID = Data.GetID(IMG_START_SCREEN5);
		}
		else {
			endInitialAnim = true;
		}
	}

	if (frameCounter == PUSH_START_BLINK_FREQ) {
		frameCounter = 0;
		drawPressButton = !drawPressButton;
	}
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();
	int screen_x, screen_y;
	screen_x = 0;
	screen_y = 0;

	glEnable(GL_TEXTURE_2D);
	//std::cout << "QUAD SIZE: " << std::endl;
	//std::cout << w << " " << h << std::endl;
	glBindTexture(GL_TEXTURE_2D, bgID);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1);	glVertex2i(screen_x, screen_y);
	glTexCoord2f(1, 1);	glVertex2i(screen_x + GAME_WIDTH, screen_y);
	glTexCoord2f(1, 0);	glVertex2i(screen_x + GAME_WIDTH, screen_y + GAME_HEIGHT);
	glTexCoord2f(0, 0);	glVertex2i(screen_x, screen_y + GAME_HEIGHT);
	glEnd();

	if (drawPressButton) {
		text.Draw(Data.GetID(IMG_FONT));
	}
	
	glDisable(GL_TEXTURE_2D);
	glutSwapBuffers();
}