#pragma once
#include "cScreen.h"

#define MAP_SCREEN_DURATION 240
class MapScreen :
	public cScreen
{
public:
	MapScreen();
	~MapScreen();
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
	int uncover_displace;
};

