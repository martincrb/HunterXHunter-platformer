#pragma once

#include "cTexture.h"
#include "Globals.h"
#include "Animation.h"
#include "cRect.h"



#define FRAME_DELAY		8
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

	virtual bool Collides(cRect *rc);
	bool inWater(cRect *rc);
	virtual bool CollidesMapWall(int *map,bool right);
	virtual bool CollidesMapFloor(int *map);
	bool CollidesGhostTile(int *map);
	//virtual bool CollidesMapTop(int *map);
	virtual bool HurtsDestructible(int *map, cRect hitBox);

	void GetArea(cRect *rc);
	void DrawRect(int tex_id,float xo,float yo,float xf,float yf);
	virtual void Draw(int tex_id);

	virtual void MoveRight(int *map);
	virtual void MoveLeft(int *map);

	bool hasHitBox();
	cRect getHitBox();

	void setObjectivePos(int x, int y);
	void Jump(int *map);
	void Duck(int *map);
	void Stop();
	virtual void Logic(int *map);
	int  GetState();
	void SetState(int s);
	bool inAir();
	void NextFrame(int max);
	int  GetFrame();
	bool in_water;
	
protected:
	Animation *currentAnimation;
	std::vector<Animation> animations;
	AnimationFrame currentFrame;
	int x, y;
	int obj_x, obj_y;
	int w, h;
	int state;
	bool in_air;
	bool jumping;
	int jump_alfa;
	int jump_y;

	int seq, delay;
private:
	
};
