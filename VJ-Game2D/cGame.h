#pragma once

#include "cScreen.h"
#include "StartScreen.h"
#include "LevelScreen.h"
#include "MapScreen.h"
#include "Credits.h"
#include "GameOver.h"
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
	void startGameOverScreen();
	void startLevel(int lvl);
	int getLevel();
	int getScore();
	int getLives();
	void setLives(int l);
	void setScore(int s);
	void setTemporalScore(int s);
	int getTemporalScore();
	cScreen* getCurrentScreen();
	bool currentIsGon();
	bool currentIsKillua();
private:
	StartScreen startScreen;
	LevelScreen levelScreen;
	MapScreen mapScreen;
	Credits credits;
	GameOver gameOverScreen;
	cScreen* currentScreen;
	int lives;
	bool showHelp;
	int actualLevel;
	int temporalScore;
	int score;
};
