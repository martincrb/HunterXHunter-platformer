#pragma once
#include "cScreen.h"
class Help :
	public cScreen
{
public:
	Help();
	~Help();
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
	bool drawPressButton;
};

