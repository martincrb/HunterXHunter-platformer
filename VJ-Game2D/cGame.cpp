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
	for (unsigned int i = 0; i < Entities->size(); i++) {
		if ((*Entities)[i].alive) {
			(*Entities)[i].bicho->SetPosition((*Entities)[i].spawn_x, (*Entities)[i].spawn_y);
			(*Entities)[i].bicho->SetWidthHeight(32, 32);
			(*Entities)[i].bicho->SetMap(Scene.GetMap());
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
	Player->SetTile(5, 20);
	Player->SetWidthHeight(32, 32);
	Player->SetState(STATE_LOOKRIGHT);
	Player->SetMap(Scene.GetMap());

	Player2->SetWidthHeight(32, 32);
	Player2->SetTile(5, 20);
	Player2->SetWidthHeight(32, 32);
	Player2->SetState(STATE_LOOKRIGHT);
	Player2->SetMap(Scene.GetMap());

	pController.setPlayers(Player, Player2);
	int x, y;
	pController.getCurrentPlayer()->GetPosition(&x, &y);
	camera = Camera(0, 0, GAME_WIDTH, GAME_HEIGHT, Scene.getBoundaries(), x, y);
	
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
	for (unsigned int k = 0; k < cScene::debugmap.size(); ++k) {
		cScene::debugmap[k] = 0;
	}
	//Process Input
	bool something_done = false;
	if(keys[27])	res=false;	

	if (keys[99])		pController.changeCurrentPlayer();
	if (keys[98])	cScene::DEBUG_ON = !cScene::DEBUG_ON; //B for debug (draw cllisions)

	if (keys[GLUT_KEY_DOWN] && keys[GLUT_KEY_UP] && keys[GLUT_KEY_LEFT] && !keys[GLUT_KEY_RIGHT])
		pController.action(PlayerController::actions::HAB_JUMP_LEFT);

	else if (keys[GLUT_KEY_DOWN] && keys[GLUT_KEY_UP] && !keys[GLUT_KEY_LEFT] && keys[GLUT_KEY_RIGHT])
		pController.action(PlayerController::actions::HAB_JUMP_RIGHT);

	else if (keys[GLUT_KEY_DOWN] && keys[GLUT_KEY_UP])
		pController.action(PlayerController::actions::HAB_JUMP);

	else if (keys[GLUT_KEY_DOWN])
		pController.action(PlayerController::actions::HABILITY);

	else if (keys[GLUT_KEY_UP] && keys[GLUT_KEY_LEFT] && !keys[GLUT_KEY_RIGHT])
		pController.action(PlayerController::actions::JUMP_LEFT);

	else if (keys[GLUT_KEY_UP] && !keys[GLUT_KEY_LEFT] && keys[GLUT_KEY_RIGHT])
		pController.action(PlayerController::actions::JUMP_RIGHT);

	else if (keys[GLUT_KEY_UP])
		pController.action(PlayerController::actions::JUMP);

	else if (keys[GLUT_KEY_LEFT] && !keys[GLUT_KEY_RIGHT])
		pController.action(PlayerController::actions::MOVE_LEFT);

	else if (!keys[GLUT_KEY_LEFT] && keys[GLUT_KEY_RIGHT])
		pController.action(PlayerController::actions::MOVE_RIGHT);

	else 
		pController.action(PlayerController::actions::STOP);
	
	pController.moveCompanion();

	//Camera follows player
	int x, y;
	pController.getCurrentPlayer()->GetPosition(&x, &y);
	camera.move_player(x, y);
	
	//Game Logic
	//...
	Player->Logic();
	Player2->Logic();

	//Process all entities in the map
	for (unsigned int i = 0; i < Entities->size(); i++) {
		if ((*Entities)[i].alive) {
			(*Entities)[i].bicho->Logic();
			int xe, ye, we, he;
			(*Entities)[i].bicho->GetPosition(&xe, &ye);
			(*Entities)[i].bicho->GetWidthHeight(&we, &he);
			cRect EntityBox;
			EntityBox.left = xe;
			EntityBox.top = ye;
			EntityBox.bottom = ye + he;
			EntityBox.right = xe + we;
			if (Player->hasHitBox()) {
				cRect hitBox = Player->getHitBox();
				//Set coordinates referencing world not player

				int xb, yb, wb, hb;
				Player->GetPosition(&xb, &yb);
				xb += hitBox.left;
				yb += hitBox.bottom;
				wb = hitBox.right - hitBox.left;
				hb = hitBox.top - hitBox.bottom;

				hitBox.left = xb;
				hitBox.bottom = yb;
				hitBox.top = yb + hb;
				hitBox.right = xb + wb;
				//std::cout << "HitBox ON" << std::endl;
				if ((*Entities)[i].bicho->Collides(&hitBox)) { //if entity collides with hitbox from player
					if (cScene::DEBUG_ON) {
						std::cout << "Im killing a " << (*Entities)[i].type << std::endl;
					}
					(*Entities)[i].Kill();
				}
				Player->HurtsDestructible(hitBox);

			}
			
			if (!Player->isUsingHability() && Player->Collides(&EntityBox)) { //Player colliding with enemy
				if (cScene::DEBUG_ON) {
					std::cout << "Im touching a " << (*Entities)[i].type << std::endl;
				}
					//(*Entities)[i].Kill();
			}
			

		}
	}
	return res;
}

//Output
void cGame::Render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	
	int x, y;
	camera.get_camera_pos(x, y);
	glTranslated(-x, - y, 0);
	//glTranslated(10, 10, 0);
	//glScaled(2, 2, 2);
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
	if (cScene::DEBUG_ON) {
		//Render hitBoxes
		if (Player->hasHitBox()) {
			cRect hitBox = Player->getHitBox();
			int xb, yb, wb, hb;
			Player->GetPosition(&xb, &yb);

			xb += hitBox.left;
			yb += hitBox.bottom;
			wb = hitBox.right - hitBox.left;
			hb = hitBox.top - hitBox.bottom;


			glBegin(GL_QUADS);
			glColor3f(1, 0, 0);
			glVertex2i(xb, yb);;
			glVertex2i(xb + wb, yb);
			glVertex2i(xb + wb, yb + hb);
			glVertex2i(xb, yb + hb);
			glColor3f(1, 1, 1);
			glEnd();
		}

	}

	//Render all entities in the map
	for (unsigned int i = 0; i < Entities->size(); i++) {
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
