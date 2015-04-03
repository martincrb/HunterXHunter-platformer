#pragma once
#include "cSound.h"
#include "cData.h"

class cGame;

class cScreen
{
public:
	cScreen();
	~cScreen();

	virtual bool Init(cGame* cg) = 0;
	virtual bool Loop() = 0;
	virtual void Finalize() = 0;

	//Input
	virtual void ReadKeyboard(unsigned char key, int x, int y, bool press) = 0;
	virtual void ReadMouse(int button, int state, int x, int y) = 0;
	//Process
	virtual bool Process() = 0;
	//Output
	virtual void Render() = 0;

protected:
	unsigned char keys[256];
	cGame* gameController;
	cSound Sound;
	cData Data;
};

