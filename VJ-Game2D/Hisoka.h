#pragma once
#include "cBicho.h"

class Hisoka :
	public cBicho
{
public:
	Hisoka();
	bool Collides(cRect *rc);
	void Logic();
	void Draw(cData* data);
	void Hurt();

private:
	class Card : public cBicho {
	public:
		Card(int x, int y, int obj_x, int obj_y);
		void Logic();
		void Draw(cData* data);
	private:
		float move_x;
		float move_y;
		int initial_x;
		int initial_y;
		int dist;
		//static int tex_id;
		static const int SPEED = 2;
		static const int MAX_DIST = 400;
	};

	std::vector<Card> cards;
	static int tex_id;
	bool attacking;
	bool invulnerable;
	int shoot_time;
	int inv_time;
	int lives;

	static const int MIN_DIST = 400;
	static const int T = 120;
	static const int INV_TIME = 120;
};

