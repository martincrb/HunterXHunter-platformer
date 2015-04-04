#include "cGame.h"
#include "Globals.h"
#include "Resources.h"


cGame::cGame(void)
{
	//currentScreen = &startScreen;
	currentScreen = &levelScreen;
	actualLevel = 2;
}

cGame::~cGame(void)
{

}

bool cGame::currentIsGon() {
	return currentScreen->currentIsGon();
}
bool cGame::currentIsKillua() {
	return currentScreen->currentIsKillua();
}

bool cGame::Init()
{
	//Graphics initialization
	glClearColor(0.0f, 0.2f, 1.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, GAME_WIDTH, 0, GAME_HEIGHT, 0, 1);
	glMatrixMode(GL_MODELVIEW);

	glAlphaFunc(GL_GREATER, 0.05f);
	glEnable(GL_ALPHA_TEST);

	return currentScreen->Init(this);
}
cScreen* cGame::getCurrentScreen() {
	return currentScreen;
}
void cGame::startLevel(int lvl) {
	Finalize();
	actualLevel = lvl;
	currentScreen = &levelScreen;
	Init();
}

void cGame::startMapScreen(int lvl) {
	Finalize();
	actualLevel = lvl;
	currentScreen = &mapScreen;
	Init();
}
int cGame::getLevel(){
	return actualLevel;
}
void cGame::setScore(int s) {
	score = s;
}
bool cGame::Loop()
{
	bool res=true;

	res = Process();
	if(res) Render();

	return res;
}

void cGame::Finalize()
{
	currentScreen->Finalize();
}

//Input
void cGame::ReadKeyboard(unsigned char key, int x, int y, bool press)
{
	currentScreen->ReadKeyboard(key, x, y, press);
}

void cGame::ReadMouse(int button, int state, int x, int y)
{
	currentScreen->ReadMouse(button, state, x, y);
}

//Process
bool cGame::Process()
{
	
	return currentScreen->Process();
}

//Output
void cGame::Render()
{
	currentScreen->Render();
}

int cGame::getScore() {
	return score;
}