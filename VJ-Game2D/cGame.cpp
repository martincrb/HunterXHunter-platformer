#include "cGame.h"
#include "Globals.h"
#include "Resources.h"


cGame::cGame(void)
{
	currentScreen = &startScreen;
	//currentScreen = &helpScreen;
	showHelp = false;
	lives = 3;
}

cGame::~cGame(void)
{

}

void cGame::setTemporalScore(int s) {
	temporalScore = s;
}
int cGame::getTemporalScore() {
	return temporalScore;
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

void cGame::Reset() {
	Finalize();
	currentScreen = &startScreen;
	Init();
}
void cGame::startMapScreen(int lvl) {
	Finalize();
	actualLevel = lvl;
	if (lvl == -1) {
		currentScreen = &gameOverScreen;
	}
	else if (lvl == -2) {
		currentScreen = &startScreen;
		lives = 3;
	}
	else if (lvl == 4) {
		currentScreen = &credits;
	}
	else {
		currentScreen = &mapScreen;
	}
	Init();
}

void cGame::startGameOverScreen() {
	Finalize();
	actualLevel = 1;
	currentScreen = &startScreen;
	Init();
}
int cGame::getLevel(){
	return actualLevel;
}
void cGame::setScore(int s) {
	score = s;
}
int cGame::getLives() {
	return lives;
}
void cGame::setLives(int l) {
	lives = l;
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