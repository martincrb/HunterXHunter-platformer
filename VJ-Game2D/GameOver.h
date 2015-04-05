#pragma once
#include "cScreen.h"
class GameOver :
	public cScreen
{
public:
	GameOver();
	~GameOver();
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
};

