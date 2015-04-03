#pragma once

#include "cTexture.h"
#include "Globals.h"
#include "Animation.h"
#include "cRect.h"



#define STEP_LENGTH		2
#define JUMP_HEIGHT		96
#define JUMP_STEP		4

#define STATE_LOOKLEFT		0
#define STATE_LOOKRIGHT		1
#define STATE_WALKLEFT		2
#define STATE_WALKRIGHT		3
#define STATE_DUCKLEFT		4
#define STATE_DUCKRIGHT		5



class cBicho
{
public:
	cBicho(void);
	cBicho(int x,int y,int w,int h);
	~cBicho(void);

	void SetPosition(int x,int y);
	void GetPosition(int *x,int *y);
	void SetTile(int tx,int ty);
	void GetTile(int *tx,int *ty);
	void SetWidthHeight(int w,int h);
	void GetWidthHeight(int *w,int *h);
	void SetMap(int* map);

	bool inWater(cRect *rc);
	bool CollidesGhostTile(int *map);
	int CollidesItem(int *itemMap);
	virtual bool Collides(cRect *rc);
	virtual bool CollidesMapWall();
	virtual bool CollidesMapWall(bool right);
	virtual bool CollidesMapFloor();
	virtual int HurtsDestructible(cRect hitBox);

	virtual void GetArea(cRect *rc);
	virtual void DrawRect(int tex_id,float xo,float yo,float xf,float yf);
	virtual void Draw(int tex_id);

	virtual void MoveRight();
	virtual void MoveLeft();
	virtual void Hurt();

	bool hasHitBox();
	cRect getHitBox();

	void setObjectivePos(int x, int y);
	void Jump();
	void Duck();
	void Stop();
	virtual void Logic();
	int  GetState();
	void SetState(int s);
	bool inAir();
	void NextFrame(int max);
	int  GetFrame();
	bool in_water;
	bool alive;
	
protected:
	Animation *currentAnimation;
	std::vector<Animation> animations;
	AnimationFrame currentFrame;
	int frameDelay;
	int hurtDelay;
	bool hurtable;
	double speed;
	int x, y;
	int obj_x, obj_y;
	int w, h;
	int state;
	bool in_air;
	bool jumping;
	int jump_alfa;
	int jump_y;
	int last_x, last_y;
	virtual void adjust();

	int seq, delay;
	int *map;
private:
	
};
