#pragma once
#include "cScreen.h"

#define INITIAL_ANIM_DELAY 48
#define PUSH_START_BLINK_FREQ 10

class StartScreen :
	public cScreen
{
public:
	StartScreen();
	~StartScreen();
	bool Init(cGame* cG);
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
	int frameCounter;
	int initialAnimCounter;
	bool endInitialAnim;
	bool drawPressButton;

};

