#pragma once

#include "cScreen.h"
#include "StartScreen.h"
#include "LevelScreen.h"
#include "MapScreen.h"

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

	void startMapScreen(int lvl);
	void startLevel(int lvl);
	int getLevel();

private:
	StartScreen startScreen;
	LevelScreen levelScreen;
	MapScreen mapScreen;
	cScreen* currentScreen;
	int actualLevel;
	int score;
};
