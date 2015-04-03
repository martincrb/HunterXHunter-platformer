#pragma once
#include "cBicho.h"
#include "PlayerController.h"

class Hisoka :
	public cBicho
{
public:
	Hisoka(PlayerController* p);
	bool Collides(cRect *rc);
	void Logic();
	void Draw(int tex_id);
	void Hurt();

private:
	class Card : public cBicho {
	public:
		Card(int x, int y);
		void Logic();
		void Draw();
	private:
		int initial_x;
		//static int tex_id;
		static const int STEP = 2;
		static const int MAX_DIST = 500;
	};

	std::vector<Card> cards;
	static int tex_id;
	PlayerController* p;
	bool attacking;
	bool invulnerable;
	int shoot_time;
	int inv_time;
	int lives;

	static const int MIN_DIST = 350;
	static const int T = 90;
	static const int INV_TIME = 120;
};

