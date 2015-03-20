#include "PlayerController.h"


PlayerController::PlayerController()
{
}
PlayerController::PlayerController(cPlayer* playerOne, cPlayer* playerTwo)
{
	Gon = playerOne;
	Killua = playerTwo;
	currentPlayer = Gon;
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
	currentPlayer->Punch(scene->GetMap());
}
void PlayerController::Jump(cScene* scene){
	currentPlayer->Jump(scene->GetMap());
}
void PlayerController::MoveLeft(cScene* scene){
	currentPlayer->MoveLeft(scene->GetMap());
}
void PlayerController::MoveRight(cScene* scene){
	currentPlayer->MoveRight(scene->GetMap());
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