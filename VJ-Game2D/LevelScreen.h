#pragma once
#include "cScreen.h"
#include "cScene.h"
#include "cPlayer.h"
#include "Gon.h"
#include "Killua.h"
#include "PlayerController.h"
#include "Camera.h"
#include "GUI.h"

class LevelScreen :
	public cScreen
{
public:
	LevelScreen();
	~LevelScreen();
	bool Init(cGame* cg);
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
	GUI gui;
	std::vector<Entity>* Entities;
	cPlayer* Player;
	cPlayer* Player2;
	PlayerController pController;
	Camera camera;
	bool reaper;
	cScene Scene;
};

