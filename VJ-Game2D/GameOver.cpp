#include "GameOver.h"
#include "Resources.h"
#include "cGame.h"
#include "cText.h"

GameOver::GameOver()
{
}


GameOver::~GameOver()
{
}

bool GameOver::Init(cGame* cG) {
	gameController = cG;
	bool res = true;
	for (int key = 0; key < 256; key++)
		keys[key] = false;
	res = Data.LoadImage(IMG_FONT, Resources::FONT, GL_RGBA);
	if (!res) return false;

	Sound.init();

	Sound.LoadSound(GAME_OVER, "res/audio/game_over.wav", BG_MUSIC);
	Sound.setVolume(EFFECTS_CHANNEL, 0.5);
	Sound.Play(GAME_OVER, EFFECTS_CHANNEL);

	return res;


}
bool GameOver::Loop() {

	bool res = true;

	res = Process();
	if (res) Render();

	return res;

}
void GameOver::Finalize() {
	Sound.Stop(GAME_OVER);
	Sound.FreeAll();
}

//Input
void GameOver::ReadKeyboard(unsigned char key, int x, int y, bool press) {
	//std::cout << int(key) << std::endl;
	keys[key] = press;
}
void GameOver::ReadMouse(int button, int state, int x, int y) {

}
//Process
bool GameOver::Process() {
	Sound.UpdateSound();
	if (keys[13])		{
		Finalize();
		gameController->startMapScreen(-2);
	}
	return true;
}
//Output
void GameOver::Render() {
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
	text1.setText("GAME OVER");
	text1.setPosition(290, 350);
	text1.Draw(Data.GetID(IMG_FONT));

	int score = gameController->getTemporalScore();
	//char* buff;
	//itoa(score, buff, 10);
	std::string sc = std::to_string(score);

	cText text2;
	text2.setText("SCORE:"+sc);
	text2.setPosition(300, 300);
	text2.Draw(Data.GetID(IMG_FONT));

	glDisable(GL_TEXTURE_2D);
	glutSwapBuffers();
}
