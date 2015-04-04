#pragma once
#include "cScreen.h"
class Credits :
	public cScreen
{
public:
	Credits();
	~Credits();
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
	int final_pos;
	bool endInitialAnim;
	int text_pos;
};