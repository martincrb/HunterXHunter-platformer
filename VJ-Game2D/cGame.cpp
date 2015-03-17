#include "cGame.h"
#include "Globals.h"
#include "Resources.h"

int posx ;
int posy;

cGame::cGame(void)
{
}

cGame::~cGame(void)
{
}

bool cGame::Init()
{
	bool res=true;

	//Graphics initialization
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,GAME_WIDTH,0,GAME_HEIGHT,0,1);
	glMatrixMode(GL_MODELVIEW);
	
	glAlphaFunc(GL_GREATER, 0.05f);
	glEnable(GL_ALPHA_TEST);

	//Scene initialization

	std::string tileset_source = Scene.LoadLevel(Resources::LEVEL01);
	if(strcmp(tileset_source.c_str(), "") == 0) {
		return false;
	}
	res = Data.LoadImage(IMG_BLOCKS,tileset_source.c_str(),GL_RGBA);
	if(!res) return false;

	//Player initialization
	res = Data.LoadImage(IMG_PLAYER,Resources::SPRITESHEET_GON,GL_RGBA);
	if(!res) return false;

	Player.SetWidthHeight(32,32);
	Player.SetTile(5,-5);
	Player.SetWidthHeight(32,32);
	Player.SetState(STATE_LOOKRIGHT);

	Player.GetPosition(&posx, &posy);
	posx = -posx;
	posy = -posy;
	//Camera centered at PLAYER

	return res;
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
}

//Input
void cGame::ReadKeyboard(unsigned char key, int x, int y, bool press)
{
	keys[key] = press;
}

void cGame::ReadMouse(int button, int state, int x, int y)
{
}

//Process
bool cGame::Process()
{
	bool res=true;
	
	//Process Input
	if(keys[27])	res=false;	

	if(keys[GLUT_KEY_UP])			Player.Jump(Scene.GetMap());
	if(keys[GLUT_KEY_LEFT])			Player.MoveLeft(Scene.GetMap());
	else if(keys[GLUT_KEY_RIGHT])	Player.MoveRight(Scene.GetMap());
	else Player.Stop();
	
	//Camera follows player
	Player.GetPosition(&posx, &posy);
	posx = -posx;
	posy = -posy;
	//Game Logic
	//...
	Player.Logic(Scene.GetMap());

	return res;
}

//Output
void cGame::Render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	glLoadIdentity();
	glTranslated(posx, posy, 0);
	Scene.Draw(Data.GetID(IMG_BLOCKS));
	Player.Draw(Data.GetID(IMG_PLAYER));

	glutSwapBuffers();
}
