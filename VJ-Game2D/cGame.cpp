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

	//Point to the entity vector
	Entities = Scene.getEntities();

	//Entities init
	for (int i = 0; i < Entities->size(); i++) {
		if ((*Entities)[i].alive) {
			(*Entities)[i].bicho->SetPosition((*Entities)[i].spawn_x, -(*Entities)[i].spawn_y);
			(*Entities)[i].bicho->SetWidthHeight(32, 32);
		}
	}

	res = Data.LoadImage(IMG_BLOCKS,tileset_source.c_str(),GL_RGBA);
	if(!res) return false;

	//Player initialization
	res = Data.LoadImage(IMG_PLAYER,Resources::SPRITESHEET_GON,GL_RGBA);
	if(!res) return false;

	res = Data.LoadImage(IMG_JUMPING_FROG, Resources::SPRITESHEET_JUMPING_FROG, GL_RGBA);
	if (!res) return false;

	Player.SetWidthHeight(32,32);
	Player.SetTile(0,0);
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


	//Process all entities in the map
	for (int i = 0; i < Entities->size(); i++) {
		if ((*Entities)[i].alive) {
			(*Entities)[i].bicho->Logic(Scene.GetMap());
		}
	}
	return res;
}

//Output
void cGame::Render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	glLoadIdentity();
	glTranslated(posx+10, posy+90, 0);
	Scene.Draw(Data.GetID(IMG_BLOCKS));
	Player.Draw(Data.GetID(IMG_PLAYER));
	//Render all entities in the map
	for (int i = 0; i < Entities->size(); i++) {
		if ((*Entities)[i].alive) {
			if ((*Entities)[i].type == "jfrog") {
				(*Entities)[i].bicho->Draw(Data.GetID(IMG_JUMPING_FROG));
			}
			 //Select texture using entity type
			
		}
	}
	glutSwapBuffers();
}
