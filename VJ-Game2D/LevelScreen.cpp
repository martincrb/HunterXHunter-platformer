#include "LevelScreen.h"
#include "Resources.h"
#include "cGame.h"

LevelScreen::LevelScreen()
{
	changePlayerDelay = 0;
}


LevelScreen::~LevelScreen()
{
}

bool LevelScreen::currentIsGon() {
	return pController.getCurrentPlayer() == Player;

}
bool LevelScreen::currentIsKillua() {
	return pController.getCurrentPlayer() == Player2;

}

bool LevelScreen::Init(cGame* cG) {
	gameController = cG;
	bool res = true;
	reaper = false;
	int level = cG->getLevel();
	Sound.init();
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
	res = Data.LoadImage(IMG_EVIL_FISH, Resources::SPRITESHEET_EVIL_FISH, GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_HISOKA, Resources::SPRITESHEET_HISOKA, GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_HISO_CARD, Resources::SPRITESHEET_HISO_CARD, GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_FONT, Resources::FONT, GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_GUI_GON, Resources::GUI_USING_GON, GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_GUI_KILLUA, Resources::GUI_USING_KILLUA, GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_PARTICLE_ROCK, Resources::PARTICLE_ROCK, GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_PARTICLE_EXPLOSION, Resources::PARTICLE_EXPLOSION, GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_HUNTER_LIC, Resources::HUNTER_LICENSE, GL_RGBA);
	if (!res) return false;
	Sound.LoadSound(LEVEL_BG, "res/audio/level_1.wav", BG_MUSIC);
	Sound.LoadSound(BOO_HI, "res/audio/ghost_laugh.wav", EFFECT);
	Sound.LoadSound(GON_JUMP, "res/audio/gon_jump.wav", EFFECT);
	Sound.LoadSound(KILLUA_JUMP, "res/audio/killua_jump.wav", EFFECT);
	Sound.LoadSound(GET_COIN, "res/audio/coin.wav", EFFECT);

	//Scene initialization
	//Sound.Play(LEVEL_BG, MUSIC_CHANNEL);

	std::string tileset_source = Scene.LoadLevel(Resources::getResourceLevel(level));
	if (strcmp(tileset_source.c_str(), "") == 0) {
		return false;
	}
	res = Data.LoadImage(IMG_BLOCKS, tileset_source.c_str(), GL_RGBA);
	if (!res) return false;

	//Point to the entity vector
	Entities = Scene.getEntities();

	//Entities init
	for (unsigned int i = 0; i < Entities->size(); i++) {
		if ((*Entities)[i].type != "player_spawn" && (*Entities)[i].bicho->alive) {
			(*Entities)[i].bicho->SetPosition((*Entities)[i].spawn_x, (*Entities)[i].spawn_y);
			(*Entities)[i].bicho->SetWidthHeight(32, 32);
			(*Entities)[i].bicho->SetMap(Scene.GetMap());
			if ((*Entities)[i].type == "end_level") {
				(*Entities)[i].killsPlayer = false;
			}
		}
	}

	//Particle System init
	//particleSystem.setRandomSpeed(-0.5, 0.5);
	//particleSystem.Init(50, Data.GetID(IMG_OCTO_BALL), Scene.player_spawn_x, Scene.player_spawn_y, 0, -0.07, 0, 0);

	//Player initialization


	Player = new Gon();
	Player2 = new Killua();

	Player->SetWidthHeight(32, 32);
	Player->SetPosition(Scene.player_spawn_x, Scene.player_spawn_y);
	Player->SetWidthHeight(32, 32);
	Player->SetState(STATE_LOOKRIGHT);
	Player->SetMap(Scene.GetMap());
	cRect r; r.bottom = 0; r.left = 0; r.right = 31; r.top = 31;
	Player->setCollisionBox(r);

	Player->inWater(Scene.getWaterZone());
	Player2->SetWidthHeight(32, 32);
	Player2->SetPosition(Scene.player_spawn_x, Scene.player_spawn_y);
	Player2->SetWidthHeight(32, 32);
	Player2->SetState(STATE_LOOKRIGHT);
	Player2->SetMap(Scene.GetMap());
	Player2->setCollisionBox(r);

	Player2->inWater(Scene.getWaterZone());
	pController.setPlayers(Player, Player2);
	int x, y;
	pController.getCurrentPlayer()->GetPosition(&x, &y);
	camera = Camera(0, 0, GAME_WIDTH, GAME_HEIGHT, Scene.getBoundaries(), x, y);
	return res;

}

bool LevelScreen::Loop() {
	bool res = true;

	res = Process();
	if (res) Render();

	return res;

}
void LevelScreen::Finalize() {
	Sound.FreeAll();
	Scene.FreeAll();
}

//Input
void LevelScreen::ReadKeyboard(unsigned char key, int x, int y, bool press) {
	keys[key] = press;
}
void LevelScreen::ReadMouse(int button, int state, int x, int y) {

}
//Process
bool LevelScreen::Process() {
	bool res = true;
	Sound.UpdateSound();

	if (changePlayerDelay > 0) {
		--changePlayerDelay;
	}

	for (int k = 0; k < cScene::debugmap.size(); ++k) {
		cScene::debugmap[k] = 0;
	}
	if (keys[GLUT_KEY_UP])			{
		if (!pController.getCurrentPlayer()->inAir() && !pController.getCurrentPlayer()->in_water) {
			Sound.Play(GON_JUMP, EFFECTS_CHANNEL);
		}
	}
	//Process Input

	if (keys[27])	res = false;

	if (changePlayerDelay == 0 && keys[99])		{
		pController.changeCurrentPlayer();
		changePlayerDelay = 20;
	}
	if (keys[98])	cScene::DEBUG_ON = !cScene::DEBUG_ON; //B for debug (draw cllisions)

	if (keys[97] && keys[GLUT_KEY_UP] && keys[GLUT_KEY_LEFT] && !keys[GLUT_KEY_RIGHT])
		pController.action(PlayerController::actions::HAB_JUMP_LEFT);

	else if (keys[97] && keys[GLUT_KEY_UP] && !keys[GLUT_KEY_LEFT] && keys[GLUT_KEY_RIGHT])
		pController.action(PlayerController::actions::HAB_JUMP_RIGHT);

	else if (keys[97] && keys[GLUT_KEY_UP])
		pController.action(PlayerController::actions::HAB_JUMP);

	else if (keys[97])
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

	else if (keys[GLUT_KEY_DOWN])
		pController.action(PlayerController::actions::DUCK);

	else
		pController.action(PlayerController::actions::STOP);

	pController.moveCompanion();

	//Camera follows player
	int x, y;
	pController.getCurrentPlayer()->GetPosition(&x, &y);
	camera.move_player(x, y);

	//Game Logic
	//...

	//Process Particles

	for (int p = particleSystem.size()-1; p >= 0; --p) {
		particleSystem[p].Process();
		if (particleSystem[p].isFinished()) {
			particleSystem.erase(particleSystem.begin() + p);
		}
	}
	int playerx, playery;

	Player->Logic();
	Player2->Logic();

	pController.getCurrentPlayer()->GetPosition(&playerx, &playery);
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

	if (pController.getCurrentPlayer()->CollidesGhostTile(Scene.GetMap()) && !reaper) {
		reaper = true;
		Sound.Play(BOO_HI, EFFECTS_CHANNEL);
		Scene.addEntity("ghost", playerx, playery - 50);
	}

	int actualScore = gameController->getScore();
	int itemID = pController.getCurrentPlayer()->CollidesItem(Scene.GetItemMap());
	if (itemID != -1) {
		if (itemID == 44) {
			actualScore += 40;
			Sound.Play(GET_COIN, EFFECTS_CHANNEL);
			std::cout << "score: " << actualScore << std::endl;
		}
	}
	itemID = Player2->CollidesItem(Scene.GetItemMap());
	if (itemID != -1) {
		if (itemID == 44) {
			actualScore += 40;
			Sound.Play(GET_COIN, EFFECTS_CHANNEL);
			std::cout << "score: " << actualScore << std::endl;
		}
	}
	gameController->setScore(actualScore);

	//Process all entities in the map
	cRect playerBox;
	pController.getCurrentPlayer()->GetArea(&playerBox);

	for (unsigned int i = 0; i < Entities->size(); i++) {
		if (((*Entities)[i].type != "player_spawn") && (*Entities)[i].bicho->alive)  {
			(*Entities)[i].bicho->Logic();

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
				hitBox.bottom = yb;
				hitBox.top = yb + hb;
				hitBox.right = xb + wb;
				//std::cout << "HitBox ON" << std::endl;
				if ((*Entities)[i].bicho->Collides(&hitBox)) { //if entity collides with hitbox from player
					if (cScene::DEBUG_ON) {
						std::cout << "Im killing a " << (*Entities)[i].type << std::endl;
					}
					if ((*Entities)[i].type != "ghost") {
						ParticleSystem pS;
						pS.setLifespan(40);
						pS.setRandomSpeed(-0.7, 0.7);
						pS.setWidthHeight(20, 20);
						pS.Init(3, hitBox.left, hitBox.bottom, 0, 0, 0, 0);
						pS.type = "explosion";
						particleSystem.push_back(pS);
						(*Entities)[i].Hurt();
					}
				}
				int destructedTile = Player->HurtsDestructible(hitBox);
				if (destructedTile != -1) {
					//play particleSystem
					ParticleSystem pS;
					pS.setLifespan(100);
					pS.setRandomSpeed(-0.5, 0.5);
					pS.setWidthHeight(16, 16);
					pS.Init(10, hitBox.left, hitBox.bottom, 0, -0.08, 0, 0);
					pS.type = "rocks";
					particleSystem.push_back(pS);

					if (destructedTile == 35) {
						if (rand() % 100 < 30) {
							Sound.Play(BOO_HI, EFFECTS_CHANNEL);
							Scene.addEntity("ghost", playerx, playery - 50);
						}
					}
				}
			}

			//Enemy touches player
			int xe, ye, we, he;
			(*Entities)[i].bicho->GetPosition(&xe, &ye);
			(*Entities)[i].bicho->GetWidthHeight(&we, &he);
			if ((*Entities)[i].type == "ghost" || (*Entities)[i].type == "hisoka") {
				(*Entities)[i].bicho->setObjectivePos(playerx, playery);
			}


			if ((*Entities)[i].killsPlayer && (*Entities)[i].bicho->Collides(&playerBox)) { //if entity collides with player
				//Kill player
				std::cout << "dead" << std::endl;
				//Finalize();
				//Init();
			}
			if ((*Entities)[i].type == "end_level" && (*Entities)[i].bicho->Collides(&playerBox)) {
				gameController->startMapScreen(gameController->getLevel()+1);
			}
		}
	}
	return res;
}
//Output
void LevelScreen::Render() {

	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	int x, y;
	camera.get_camera_pos(x, y);
	glTranslated(-x, -y, 0);
	//glTranslated(10, 10, 0);
	//glScaled(2, 2, 2);
	Scene.Draw(Data.GetID(IMG_BLOCKS));

	//Draw particles
	/*
	if (!particleSystem.empty()) {
		std::list<ParticleSystem>::iterator it = particleSystem.begin();
		while (it != particleSystem.end()) {
			it->Draw(Data.GetID(IMG_OCTO_BALL));
		}
	}
	*/
	for (int p = 0; p < particleSystem.size(); ++p) {
		if (particleSystem[p].type == "rocks") {
			particleSystem[p].Draw(Data.GetID(IMG_PARTICLE_ROCK));
		}
		else if (particleSystem[p].type == "explosion") {
			particleSystem[p].Draw(Data.GetID(IMG_PARTICLE_EXPLOSION));
		}
	}
	//Current player must be rendered on top of IA player
	pController.Draw(&Data);

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
			glVertex2i(xb, yb);
			glVertex2i(xb + wb, yb);
			glVertex2i(xb + wb, yb + hb);
			glVertex2i(xb, yb + hb);
			glColor3f(1, 1, 1);
			glEnd();
		}

	}

	//Render all entities in the map
	for (unsigned int i = 0; i < Entities->size(); i++) {
		if (((*Entities)[i].type != "player_spawn") && (*Entities)[i].bicho->alive) {
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
			else if ((*Entities)[i].type == "evilFish") {
				(*Entities)[i].bicho->Draw(Data.GetID(IMG_EVIL_FISH));
			}
			else if ((*Entities)[i].type == "hisoka") {
				(*Entities)[i].bicho->Draw(Data.GetID(IMG_HISOKA));
			}
			else if ((*Entities)[i].type == "end_level") {
				(*Entities)[i].bicho->Draw(Data.GetID(IMG_HUNTER_LIC));
			}
			//Select texture using entity type
		}
	}
	
	gui.Draw(gameController);

glutSwapBuffers();
}