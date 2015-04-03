#include "cGame.h"
#include "Globals.h"
#include "Resources.h"


cGame::cGame(void)
{

}

cGame::~cGame(void)
{
}

bool cGame::Init()
{
	return currentScreen.Init();
}

bool cGame::Loop()
{
	bool res=true;

	res = Process();
	if(res) Render();

	return res;
}

void cGame::Finalize()
{
	currentScreen.Finalize();
}

//Input
void cGame::ReadKeyboard(unsigned char key, int x, int y, bool press)
{
	currentScreen.ReadKeyboard(key, x, y, press);
}

void cGame::ReadMouse(int button, int state, int x, int y)
{
	currentScreen.ReadMouse(button, state, x, y);
}

//Process
bool cGame::Process()
{
	return currentScreen.Process();
}

//Output
void cGame::Render()
{
	currentScreen.Render();
}
