#pragma once

#include "cScene.h"
#include "cData.h"
#include "cPlayer.h"
#include "Gon.h"
#include "Killua.h"
#include "PlayerController.h"
#include "Camera.h"
#include "cSound.h"

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

private:
	unsigned char keys[256];
	int actualLevel;
	bool reaper;
	int score;
	cScene Scene;
	cData Data;
	cSound Sound;
	std::vector<Entity>* Entities;
	cPlayer* Player;
	cPlayer* Player2;
	PlayerController pController;
	Camera camera;
};
