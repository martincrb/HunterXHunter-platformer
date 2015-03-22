#include "PlayerController.h"


PlayerController::PlayerController()
{
	command_queue.push(0);
}
PlayerController::PlayerController(cPlayer* playerOne, cPlayer* playerTwo)
{
	Gon = playerOne;
	Killua = playerTwo;
	currentPlayer = Gon;
	command_queue.push(0);
}

PlayerController::~PlayerController()
{
}
cPlayer* PlayerController::getCurrentPlayer() {
	return currentPlayer;
}
cPlayer* PlayerController::getNotCurrentPlayer() {
	if (currentPlayer == Gon) return Killua;
	else return Gon;
}
void PlayerController::setPlayers(cPlayer* playerOne, cPlayer* playerTwo)
{
	Gon = playerOne;
	Killua = playerTwo;
	currentPlayer = Gon;
}
void PlayerController::Punch(cScene* scene) {
	command_queue.push(0);
	if (command_queue.size() > 20) {
		command_queue.pop();
	}
	currentPlayer->Punch(scene->GetMap());
}
void PlayerController::Jump(cScene* scene){
	command_queue.push(1);
	if (command_queue.size() > 20) {
		command_queue.pop();
	}
	currentPlayer->Jump(scene->GetMap());
}
void PlayerController::MoveLeft(cScene* scene){
	command_queue.push(2);
	if (command_queue.size() > 20) {
		command_queue.pop();
	}
	currentPlayer->MoveLeft(scene->GetMap());
}
void PlayerController::MoveRight(cScene* scene){
	command_queue.push(3);
	if (command_queue.size() > 20) {
		command_queue.pop();
	}
	currentPlayer->MoveRight(scene->GetMap());
}

void PlayerController::moveCompanion(cScene* scene) {
	int command = 0;
	if (!command_queue.empty()) {
		command = command_queue.front();
		command_queue.pop();
	}
	else {
		if (currentPlayer == Gon) {
			Killua->Stop();
		}
		else Gon->Stop();

	}
	switch (command) {
	case 0:
		break;
	case 1:
		if (currentPlayer == Gon) {
			Killua->Jump(scene->GetMap());
		}
		else Gon->Jump(scene->GetMap());
		break;
	case 2:
		if (currentPlayer == Gon) {
			Killua->MoveLeft(scene->GetMap());
		}
		else Gon->MoveLeft(scene->GetMap());
		break;
	case 3:
		if (currentPlayer == Gon) {
			Killua->MoveRight(scene->GetMap());
		}
		else Gon->MoveRight(scene->GetMap());
		break;
	}
}
void PlayerController::changeCurrentPlayer(){
	if (currentPlayer == Gon) {
		Gon->Stop();
		currentPlayer = Killua;
	}
	else {
		Killua->Stop();
		currentPlayer = Gon;
	}
}