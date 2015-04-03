#include "StartScreen.h"
#include "Resources.h"
#include "cGame.h"

StartScreen::StartScreen()
{
}


StartScreen::~StartScreen()
{
}

bool StartScreen::Init(cGame* cG) {
	gameController = cG;
	bool res = true;
	Sound.init();

	//Graphics initialization
	glClearColor(0.0f, 0.2f, 1.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, GAME_WIDTH, 0, GAME_HEIGHT, 0, 1);
	glMatrixMode(GL_MODELVIEW);

	glAlphaFunc(GL_GREATER, 0.05f);
	glEnable(GL_ALPHA_TEST);


	res = Data.LoadImage(IMG_START_SCREEN, Resources::START_SCREEN, GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_PLAYER, Resources::SPRITESHEET_GON, GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_PLAYER2, Resources::SPRITESHEET_KILLUA, GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_JUMPING_FROG, Resources::SPRITESHEET_JUMPING_FROG, GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_EVIL_BIRD, Resources::SPRITESHEET_EVIL_PTERO, GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_OCTO, Resources::SPRITESHEET_OCTO, GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_OCTO_BALL, Resources::SPRITESHEET_OCTO_BALL, GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_GHOST, Resources::SPRITESHEET_GHOST, GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_EVIL_FISH, Resources::SPRITESHEET_EVIL_FISH, GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_HISOKA, Resources::SPRITESHEET_HISOKA, GL_RGBA);
	if (!res) return false;

	Sound.LoadSound(TITLE_MUSIC, "res/audio/title_music.wav", BG_MUSIC);
	Sound.LoadSound(LEVEL_BG, "res/audio/level_1.wav", BG_MUSIC);
	Sound.LoadSound(BOO_HI, "res/audio/ghost_laugh.wav", EFFECT);
	Sound.LoadSound(GON_JUMP, "res/audio/gon_jump.wav", EFFECT);
	Sound.LoadSound(KILLUA_JUMP, "res/audio/killua_jump.wav", EFFECT);
	Sound.LoadSound(GET_COIN, "res/audio/coin.wav", EFFECT);

	//Sound.Play(TITLE_MUSIC, MUSIC_CHANNEL);

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
	Sound.FreeAll();
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
	return true;
}
//Output
void StartScreen::Render() {
	int screen_x, screen_y;
	screen_x = 0;
	screen_y = 0;

	glEnable(GL_TEXTURE_2D);
	//std::cout << "QUAD SIZE: " << std::endl;
	//std::cout << w << " " << h << std::endl;
	glBindTexture(GL_TEXTURE_2D, Data.GetID(IMG_START_SCREEN));
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1);	glVertex2i(screen_x, screen_y);
	glTexCoord2f(1, 1);	glVertex2i(screen_x + GAME_WIDTH, screen_y);
	glTexCoord2f(1, 0);	glVertex2i(screen_x + GAME_WIDTH, screen_y + GAME_HEIGHT);
	glTexCoord2f(0, 0);	glVertex2i(screen_x, screen_y + GAME_HEIGHT);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glutSwapBuffers();
}