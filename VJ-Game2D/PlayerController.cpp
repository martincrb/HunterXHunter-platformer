#include "PlayerController.h"


PlayerController::PlayerController()
{
	for (int i = 0; i < PLAYERS_DELAY; ++i)
		command_queue.push(actions::STOP);
}
PlayerController::PlayerController(cPlayer* playerOne, cPlayer* playerTwo, cScene* scene)
{
	Gon = playerOne;
	Killua = playerTwo;
	this->scene = scene;
	currentPlayer = Gon;
	for (int i = 0; i < PLAYERS_DELAY; ++i)
		command_queue.push(actions::STOP);
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

void PlayerController::action(PlayerController::actions a) {
	action(a, currentPlayer);
	}

void PlayerController::action(PlayerController::actions a, cPlayer* p) {
	if (currentPlayer == p) {
		if (p == Gon) {
			if (a == actions::HABILITY) // Las habilidades solo las realiza el currentPlayer
				command_queue.push(actions::STOP);
			else if (a == actions::HAB_JUMP)
				command_queue.push(actions::JUMP);
			else if (a == actions::HAB_JUMP_LEFT)
				command_queue.push(actions::JUMP_LEFT);
			else if (a == actions::HAB_JUMP_RIGHT)
				command_queue.push(actions::JUMP_RIGHT);
			else
				command_queue.push(a);
		}
		else {
			if (a == actions::HABILITY || a == actions::HAB_JUMP)
				a = actions::SJ;
			else if (a == actions::HAB_JUMP_LEFT)
				a = actions::SJ_LEFT;
			else if (a == actions::HAB_JUMP_RIGHT)
				a = actions::SJ_RIGHT;
			command_queue.push(a);
		}
	}
	switch (a) {
	case actions::JUMP:
		p->Jump();
		break;
	case actions::JUMP_LEFT:
		p->Jump();
		p->MoveLeft();
		break;
	case actions::JUMP_RIGHT:
		p->Jump();
		p->MoveRight();
		break;
	case actions::MOVE_LEFT:
		p->MoveLeft();
		break;
	case actions::MOVE_RIGHT:
		p->MoveRight();
		break;
	case actions::STOP:
		p->Stop();
		break;
	case actions::HABILITY:
		p->Hability();
		break;
	case actions::HAB_JUMP:
		p->Hability(); 
		p->Jump();
		break;
	case actions::HAB_JUMP_LEFT:
		p->Hability(); 
		p->Jump();
		p->MoveLeft();
		break;
	case actions::HAB_JUMP_RIGHT:
		p->Hability(); 
		p->Jump();
		p->MoveRight();
		break;
	case actions::DUCK:
		p->Duck();
		break;
	case actions::SJ:
		p->SuperJump();
		break;
	case actions::SJ_LEFT:
		p->SuperJump();
		p->MoveLeft();
		break;
	case actions::SJ_RIGHT:
		p->SuperJump();
		p->MoveRight();
		break;
	}
}

void PlayerController::moveCompanion() {
	actions command = command_queue.front();
	command_queue.pop();
	action(command, (currentPlayer == Gon ? Killua : Gon));
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



void PlayerController::Draw(cData* Data) {
	if (currentPlayer == Killua) {
		if (Killua->isSuperJumping())
			Killua->Draw(Data->GetID(IMG_PLAYER2));
		else {
			Gon->Draw(Data->GetID(IMG_PLAYER));
			Killua->Draw(Data->GetID(IMG_PLAYER2));
		}
	}
	else {
		Killua->Draw(Data->GetID(IMG_PLAYER2));
		Gon->Draw(Data->GetID(IMG_PLAYER));
	}
}