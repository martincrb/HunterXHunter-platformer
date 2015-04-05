#pragma once

#include "cScreen.h"
#include "StartScreen.h"
#include "LevelScreen.h"
#include "MapScreen.h"
#include "Credits.h"
#include "Help.h"

#define GAME_WIDTH	800
#define GAME_HEIGHT 600

class cGame
{
public:
	cGame(void);
	virtual ~cGame(void);

	bool Init();
	bool Loop();
	void Finalize();

	//Input
	void ReadKeyboard(unsigned char key, int x, int y, bool press);
	void ReadMouse(int button, int state, int x, int y);
	//Process
	bool Process();
	//Output
	void Render();

	void Reset();
	void startMapScreen(int lvl);
	void startLevel(int lvl);
	int getLevel();
	int getScore();
	void setScore(int s);
	cScreen* getCurrentScreen();
	bool currentIsGon();
	bool currentIsKillua();
private:
	StartScreen startScreen;
	LevelScreen levelScreen;
	MapScreen mapScreen;
	Credits credits;
	cScreen* currentScreen;
	bool showHelp;
	int actualLevel;
	int score;
};
