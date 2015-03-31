#include "cGame.h"
#include "Globals.h"
#include "Resources.h"


cGame::cGame(void)
{
	actualLevel = 0;
}

cGame::~cGame(void)
{
}

bool cGame::Init()
{
	bool res=true;
	reaper = false;
	Sound.init();
	score = 0;
	//Graphics initialization
	glClearColor(0.0f,0.2f,1.0f,0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,GAME_WIDTH,0,GAME_HEIGHT,0,1);
	glMatrixMode(GL_MODELVIEW);
	
	glAlphaFunc(GL_GREATER, 0.05f);
	glEnable(GL_ALPHA_TEST);


	res = Data.LoadImage(IMG_START_SCREEN, Resources::START_SCREEN, GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_PLAYER, Resources::SPRITESHEET_GON, GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_PLAYER2, Resources::SPRITESHEET_KILLUA, GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_JUMPING_FROG, Resources::SPRITESHEET_JUMPING_FROG, GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_EVIL_BIRD, Resources::SPRITESHEET_EVIL_PTERO, GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_OCTO, Resources::SPRITESHEET_OCTO, GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_OCTO_BALL, Resources::SPRITESHEET_OCTO_BALL, GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_GHOST, Resources::SPRITESHEET_GHOST, GL_RGBA);
	if (!res) return false;

	Sound.LoadSound(TITLE_MUSIC,"res/audio/title_music.wav", BG_MUSIC);
	Sound.LoadSound(LEVEL_BG, "res/audio/level_1.wav", BG_MUSIC);
	Sound.LoadSound(BOO_HI, "res/audio/ghost_laugh.wav", EFFECT);
	Sound.LoadSound(GON_JUMP, "res/audio/gon_jump.wav", EFFECT);
	Sound.LoadSound(KILLUA_JUMP, "res/audio/killua_jump.wav", EFFECT);
	//Scene initialization
	if (actualLevel == 0) {
		Sound.Play(TITLE_MUSIC, MUSIC_CHANNEL);
		
	}
	else {
		if (actualLevel == 1) {
			Sound.Play(LEVEL_BG, MUSIC_CHANNEL);
		}
		std::string tileset_source = Scene.LoadLevel(Resources::LEVEL01);
		if (strcmp(tileset_source.c_str(), "") == 0) {
			return false;
		}

		//Point to the entity vector
		Entities = Scene.getEntities();

		//Entities init
		for (int i = 0; i < Entities->size(); i++) {
			if ((*Entities)[i].alive && (*Entities)[i].type != "player_spawn") {
				(*Entities)[i].bicho->SetPosition((*Entities)[i].spawn_x, -(*Entities)[i].spawn_y);
				(*Entities)[i].bicho->SetWidthHeight(32, 32);
			}
		}

		res = Data.LoadImage(IMG_BLOCKS, tileset_source.c_str(), GL_RGBA);
		if (!res) return false;

		//Player initialization
		

		Player = new Gon();
		Player2 = new Killua();

		Player->SetWidthHeight(32, 32);
		Player->SetPosition(Scene.player_spawn_x, -Scene.player_spawn_y);
		Player->SetWidthHeight(32, 32);
		Player->SetState(STATE_LOOKRIGHT);
		Player->inWater(Scene.getWaterZone());
		Player2->SetWidthHeight(32, 32);
		Player2->SetPosition(Scene.player_spawn_x - 10, -Scene.player_spawn_y);
		Player2->SetWidthHeight(32, 32);
		Player2->SetState(STATE_LOOKRIGHT);
		Player2->inWater(Scene.getWaterZone());
		pController.setPlayers(Player, Player2);
		int x, y;
		pController.getCurrentPlayer()->GetPosition(&x, &y);
		camera = Camera(0, 0, GAME_WIDTH, GAME_HEIGHT, Scene.getBoundaries(), x, -y);
	}
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
	Sound.FreeAll();
	Scene.FreeAll();
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
	bool res = true;
	Sound.UpdateSound();
	if (actualLevel == 0) {
		if (keys[98])	{
			actualLevel = 1;
			Sound.Stop(TITLE_MUSIC);
			this->Init();
		}
	}
	else {
		
		for (int k = 0; k < cScene::debugmap.size(); ++k) {
			cScene::debugmap[k] = 0;
		}
		//Process Input

		if (keys[27])	res = false;

		if (keys[99])		pController.changeCurrentPlayer();
		if (keys[98])	cScene::DEBUG_ON = !cScene::DEBUG_ON; //B for debug (draw cllisions)

		if (keys[GLUT_KEY_UP])			{
			if (!pController.getCurrentPlayer()->inAir()) {
				Sound.Play(GON_JUMP, EFFECTS_CHANNEL);
			}
			pController.Jump(&Scene);
			
		}
		if (keys[GLUT_KEY_LEFT])			{
			pController.MoveLeft(&Scene);

		}
		else if (keys[GLUT_KEY_RIGHT])	{
			pController.MoveRight(&Scene);

		}
		else if (keys[GLUT_KEY_DOWN])		{
			pController.Duck(&Scene);

		}
		else if (keys[97]) {
			pController.Punch(&Scene);
		}
		else pController.Stop();

		pController.moveCompanion(&Scene);
		//Camera follows player
		int x, y;
		pController.getCurrentPlayer()->GetPosition(&x, &y);
		camera.move_player(x, -y);

		//Game Logic
		//...
		int playerx, playery;

		Player->Logic(Scene.GetMap());
		Player2->Logic(Scene.GetMap());

		Player->GetPosition(&playerx, &playery);
		int xe, ye, we, he;
		Player2->GetPosition(&xe, &ye);
		Player2->GetWidthHeight(&we, &he);

		if (Player->inWater(Scene.getWaterZone())) {
			Player->in_water = true;
		}
		else Player->in_water = false;

		if (Player2->inWater(Scene.getWaterZone())) {
			Player2->in_water = true;
		}
		else Player2->in_water = false;

		if (Player->CollidesGhostTile(Scene.GetMap()) && !reaper) {
			reaper = true;
			Sound.Play(BOO_HI, EFFECTS_CHANNEL);
			Scene.addEntity("ghost", playerx, playery - 50);
		}

		//Process all entities in the map
		cRect playerBox;
		Player->GetArea(&playerBox);
		for (int i = 0; i < Entities->size(); i++) {
			if ((*Entities)[i].alive && (*Entities)[i].type != "player_spawn") {
				(*Entities)[i].bicho->Logic(Scene.GetMap());

				//Player hits enemy
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
					hitBox.bottom = yb + hb;
					hitBox.top = yb;
					hitBox.right = xb + wb;
					//std::cout << "HitBox ON" << std::endl;
					if ((*Entities)[i].bicho->Collides(&hitBox)) { //if entity collides with hitbox from player
						if (cScene::DEBUG_ON) {
							std::cout << "Im killing a " << (*Entities)[i].type << std::endl;
						}
						if ((*Entities)[i].type != "ghost") {
							(*Entities)[i].Kill();
						}
					}
					Player->HurtsDestructible(Scene.GetMap(), hitBox);

				}

				//Enemy touches player
				int xe, ye, we, he;
				(*Entities)[i].bicho->GetPosition(&xe, &ye);
				(*Entities)[i].bicho->GetWidthHeight(&we, &he);
				if ((*Entities)[i].type == "ghost") {
					(*Entities)[i].bicho->setObjectivePos(playerx, playery);
				}

				if ((*Entities)[i].bicho->Collides(&playerBox)) { //if octopus collides with player
					//Kill player
					std::cout << "dead" << std::endl;
					Finalize();
					Init();
				}



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
	if (actualLevel == 0) {
		int screen_x, screen_y;
		screen_x = 0;
		screen_y = 0;

		glEnable(GL_TEXTURE_2D);
		//std::cout << "QUAD SIZE: " << std::endl;
		//std::cout << w << " " << h << std::endl;
		glBindTexture(GL_TEXTURE_2D, Data.GetID(IMG_START_SCREEN));
		glBegin(GL_QUADS);
		glTexCoord2f(0, 1);	glVertex2i(screen_x, screen_y);
		glTexCoord2f(1, 1);	glVertex2i(screen_x + GAME_WIDTH, screen_y);
		glTexCoord2f(1, 0);	glVertex2i(screen_x + GAME_WIDTH, screen_y + GAME_HEIGHT);
		glTexCoord2f(0, 0);	glVertex2i(screen_x, screen_y + GAME_HEIGHT);
		glEnd();

		glDisable(GL_TEXTURE_2D);
	}
	else {
		int x, y;
		camera.get_camera_pos(x, y);
		glTranslated(-x, y + GAME_HEIGHT, 0);
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
		for (int i = 0; i < Entities->size(); i++) {
			if ((*Entities)[i].alive) {
				if ((*Entities)[i].type == "jfrog") {
					(*Entities)[i].bicho->Draw(Data.GetID(IMG_JUMPING_FROG));
				}
				else if ((*Entities)[i].type == "evilBird") {
					(*Entities)[i].bicho->Draw(Data.GetID(IMG_EVIL_BIRD));
				}
				else if ((*Entities)[i].type == "octopus") {
					(*Entities)[i].bicho->Draw(Data.GetID(IMG_OCTO));
				}
				else if ((*Entities)[i].type == "ghost") {
					(*Entities)[i].bicho->Draw(Data.GetID(IMG_GHOST));
				}
				//Select texture using entity type

			}
		}
	}
	glutSwapBuffers();
}
