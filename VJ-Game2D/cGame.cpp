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
	res = Data.LoadImage(IMG_PLAYER2, Resources::SPRITESHEET_KILLUA, GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_JUMPING_FROG, Resources::SPRITESHEET_JUMPING_FROG, GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_EVIL_BIRD, Resources::SPRITESHEET_EVIL_PTERO, GL_RGBA);
	if (!res) return false;

	Player = new Gon();
	Player2 = new Killua();

	Player->SetWidthHeight(32,32);
	Player->SetTile(5, -5);
	Player->SetWidthHeight(32, 32);
	Player->SetState(STATE_LOOKRIGHT);

	Player2->SetWidthHeight(32, 32);
	Player2->SetTile(3, -5);
	Player2->SetWidthHeight(32, 32);
	Player2->SetState(STATE_LOOKRIGHT);

	pController.setPlayers(Player, Player2);

	pController.getCurrentPlayer()->GetPosition(&posx, &posy);
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

	if (keys[99])		pController.changeCurrentPlayer();
	if (keys[GLUT_KEY_DOWN])		pController.Punch(&Scene);
	if (keys[GLUT_KEY_UP])			pController.Jump(&Scene);
	if (keys[GLUT_KEY_LEFT])			pController.MoveLeft(&Scene);
	else if (keys[GLUT_KEY_RIGHT])	pController.MoveRight(&Scene);
	else pController.getCurrentPlayer()->Stop();
	
	//Camera follows player
	pController.getCurrentPlayer()->GetPosition(&posx, &posy);
	posx = -posx;
	posy = -posy;
	//Game Logic
	//...
	Player->Logic(Scene.GetMap());
	Player2->Logic(Scene.GetMap());

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
	glTranslated(posx+50, posy+90, 0);
	//glScaled(2.0, 2.0, 2.0);
	Scene.Draw(Data.GetID(IMG_BLOCKS));

	//Current player must be rendered on top of IA player
	if (pController.getCurrentPlayer() == Player) {
		Player2->Draw(Data.GetID(IMG_PLAYER2));
		Player->Draw(Data.GetID(IMG_PLAYER));
	}
	else {
		Player->Draw(Data.GetID(IMG_PLAYER));
		Player2->Draw(Data.GetID(IMG_PLAYER2));
	}
	

	//Render all entities in the map
	for (int i = 0; i < Entities->size(); i++) {
		if ((*Entities)[i].alive) {
			if ((*Entities)[i].type == "jfrog") {
				(*Entities)[i].bicho->Draw(Data.GetID(IMG_JUMPING_FROG));
			}
			else if ((*Entities)[i].type == "evilBird") {
				(*Entities)[i].bicho->Draw(Data.GetID(IMG_EVIL_BIRD));
			}
			 //Select texture using entity type
			
		}
	}
	glutSwapBuffers();
}
