#pragma once
#include "cScene.h"
#include "cPlayer.h"
#include <queue>
#define PLAYERS_DELAY 10
class PlayerController
{
public:
	enum actions { MOVE_RIGHT, MOVE_LEFT, JUMP, JUMP_RIGHT, JUMP_LEFT, STOP, HABILITY, HAB_JUMP, HAB_JUMP_LEFT, HAB_JUMP_RIGHT};

	PlayerController();
	PlayerController(cPlayer* playerOne, cPlayer* playerTwo, cScene* scene);
	void setPlayers(cPlayer* playerOne, cPlayer* playerTwo);
	cPlayer* getCurrentPlayer();
	cPlayer* getNotCurrentPlayer();
	void action(actions a);
	void changeCurrentPlayer();
	void moveCompanion();
private:
	cPlayer* currentPlayer;
	cPlayer* Gon;
	cPlayer* Killua;
	cScene* scene;
	std::queue<actions> command_queue;
	void action(actions a, cPlayer* p);
};

