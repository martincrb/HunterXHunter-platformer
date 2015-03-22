#pragma once
#include "cScene.h"
#include "cPlayer.h"
#include <queue>
#define PLAYERS_DELAY 10
class PlayerController
{
public:
	PlayerController();
	PlayerController(cPlayer* playerOne, cPlayer* playerTwo);
	~PlayerController();
	void setPlayers(cPlayer* playerOne, cPlayer* playerTwo);
	cPlayer* getCurrentPlayer();
	cPlayer* getNotCurrentPlayer();
	void Punch(cScene* scene);
	void Stop();
	void Jump(cScene* scene);
	void MoveLeft(cScene* scene);
	void MoveRight(cScene* scene);
	void changeCurrentPlayer();
	void moveCompanion(cScene* scene);
private:
	cPlayer* currentPlayer;
	cPlayer* Gon;
	cPlayer* Killua;
	std::queue<int> command_queue;
};

