#pragma once
#include "cScene.h"
#include "cPlayer.h"
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
	void Jump(cScene* scene);
	void MoveLeft(cScene* scene);
	void MoveRight(cScene* scene);
	void changeCurrentPlayer();
private:
	cPlayer* currentPlayer;
	cPlayer* Gon;
	cPlayer* Killua;
};

