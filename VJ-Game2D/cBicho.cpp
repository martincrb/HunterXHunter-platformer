#include "cBicho.h"
#include "Globals.h"
#include "cScene.h"

cBicho::cBicho(void)
{
	seq=0;
	delay=0;
	jumping = false;
	in_water = false;
}
cBicho::~cBicho(void){}

cBicho::cBicho(int posx,int posy,int width,int height)
{
	x = posx;
	y = posy;
	w = width;
	h = height;
	in_water = false;
}
void cBicho::SetPosition(int posx,int posy)
{
	x = posx;
	y = posy;
}
void cBicho::GetPosition(int *posx,int *posy)
{
	*posx = x;
	*posy = y;
}
void cBicho::SetTile(int tx,int ty)
{
	x = tx * cScene::TILE_SIZE;
	y = ty * cScene::TILE_SIZE;
}
void cBicho::GetTile(int *tx,int *ty)
{
	*tx = x / cScene::TILE_SIZE;
	*ty = y / cScene::TILE_SIZE;
}
void cBicho::SetWidthHeight(int width,int height)
{
	w = width;
	h = height;
}
void cBicho::GetWidthHeight(int *width,int *height)
{
	*width = w;
	*height = h;
}
bool cBicho::Collides(cRect *rc)
{
	//std::cout << "INSIDE COLLIDES" << std::endl;
	//std::cout << rc->left << " "   << rc->right << " " << -rc->bottom << " " << -rc->top << " " << std::endl;
	//std::cout << x        << " "   << x + w     << " " << -y          << " " << -(y + h) << " " << std::endl;
	if (x + w < rc->left) {
		//std::cout << " a is left of b" << std::endl;
		return false; // a is left of b
	}
	if (x > rc->right) {
		//std::cout << " a is right of b" << std::endl;
		return false; // a is right of b
	}
	if (-y < -rc->bottom){
		//std::cout << " a is above b" << std::endl;
		return false; // a is above b
	}
	if (-(y + h) > -rc->top) {
		//std::cout << "a is below b " << std::endl;
		return false; // a is below b
	}
	//std::cout << "yes" << std::endl;
	return true;
	
}
bool cBicho::inWater(cRect *rc) {
	return Collides(rc);
}

bool cBicho::CollidesMapWall(int *map,bool right)
{
	int tile_x,tile_y;
	int j;
	int width_tiles,height_tiles;

	tile_x = x / cScene::TILE_SIZE;
	tile_y = y / cScene::TILE_SIZE;
	width_tiles  = floor ((float(w) / float(cScene::TILE_SIZE))+0.5);
	height_tiles = h / cScene::TILE_SIZE;
	if (right)	tile_x += width_tiles;
	
	for(j=0;j<height_tiles;j++)
	{
		int altura;
		if (cScene::BLOCK_SIZE == 32) altura = -tile_y;
		else if (cScene::BLOCK_SIZE == 16) altura = -tile_y - 1;
		cScene::debugmap[abs(tile_x + ((altura + j)*cScene::SCENE_WIDTH))] = 1;
		int tileID = map[abs(tile_x + ((altura + j)*cScene::SCENE_WIDTH))];
		if (tileID != 0) {
			if (cScene::tiles[tileID-1].isSolid())	{
				//std::cout << "COLLIDING" << std::endl;
				
				return true;
			}
		}
	}
	//std::cout << "NOT COLLIDING" << std::endl;
	return false;
}

bool cBicho::HurtsDestructible(int *map, cRect hitBox) {

	return false;
}
bool cBicho::CollidesMapFloor(int *map)
{
	/*
	int tile_x, tile_y;
	int j;
	int width_tiles, height_tiles;

	tile_x = x / cScene::TILE_SIZE;
	tile_y = y / cScene::TILE_SIZE;
	width_tiles = w / cScene::TILE_SIZE;
	height_tiles = h / cScene::TILE_SIZE;

	//std::cout << "tile_x " << tile_x << "tile_y " << tile_y << std::endl;
	for (j = 0; j < width_tiles; j++)
	{
		int tileID = map[abs(tile_x+j + ((-tile_y + 1)*cScene::SCENE_WIDTH))];

		if (tileID != 0) { //no tile, empty
			if (cScene::tiles[tileID - 1].isSolid())	{
				//std::cout << "YES SOLID FLOOR TILE " << tileID << std::endl;
				in_air = false;
				return true;
			}
		}
	}
	in_air = true;
	return false;
	*/
	int tile_x, tile_y;
	int width_tiles;
	bool on_base;
	int i;

	tile_x = x / cScene::TILE_SIZE;
	tile_y = y / cScene::TILE_SIZE;

	width_tiles = floor((float(w) / float(cScene::TILE_SIZE)) + 0.5);
	if ((x % cScene::TILE_SIZE) != 0) width_tiles++;

	on_base = false;
	i = 0;
	while ((i<width_tiles) && !on_base)
	{

		cScene::debugmap[abs(tile_x + i + ((-tile_y + 1)*cScene::SCENE_WIDTH))] = 1;
		int actualTile = map[abs(tile_x + i + ((-tile_y)*cScene::SCENE_WIDTH))];
		if (actualTile != 0) { //Si me he quedado encajado dentro de un tile solido, subo
			if (cScene::tiles[actualTile].isSolid())
			{
				y = (tile_y + 1) * cScene::TILE_SIZE;
				in_air = false;
				on_base = true;
			}
		}
		if ((y % cScene::TILE_SIZE) == 0)
		{

			int tileID = map[abs(tile_x + i + ((-tile_y + 1)*cScene::SCENE_WIDTH))];
			if (tileID != 0) {
				if (cScene::tiles[tileID - 1].isSolid())
					in_air = false;
					on_base = true;
			}
		}
		else
		{
			int tileID = map[abs(tile_x + i + ((-tile_y)*cScene::SCENE_WIDTH))];
			if (tileID != 0) {
				if (cScene::tiles[tileID - 1].isSolid())
				{
					y = (tile_y + 1) * cScene::TILE_SIZE;
					in_air = false;
					on_base = true;
				}
			}
		}
		i++;
	}
	return on_base;
}

bool cBicho::CollidesGhostTile(int *map)
{
	int tile_x, tile_y;
	int width_tiles;
	bool on_base;
	int i;

	tile_x = x / cScene::TILE_SIZE;
	tile_y = y / cScene::TILE_SIZE;

	width_tiles = floor((float(w) / float(cScene::TILE_SIZE)) + 0.5);
	if ((x % cScene::TILE_SIZE) != 0) width_tiles++;

	on_base = false;
	i = 0;
	while ((i<width_tiles) && !on_base)
	{

		int tileID = map[abs(tile_x + i + ((-tile_y + 1)*cScene::SCENE_WIDTH))];
		if (tileID == 47) {
			on_base = true;
		}
		i++;
	}
	return on_base;
}
/*
bool cBicho::CollidesMapTop(int *map) {
	int tile_x, tile_y;
	int width_tiles, heigth_tiles;
	bool hits_top;
	int i;

	tile_x = x / cScene::TILE_SIZE;
	tile_y = y / cScene::TILE_SIZE;

	width_tiles = floor((float(w) / float(cScene::TILE_SIZE)) + 0.5);
	if ((x % cScene::TILE_SIZE) != 0) width_tiles++;

	heigth_tiles = h / cScene::TILE_SIZE;
	hits_top = false;
	i = 0;
	while ((i<width_tiles) && !hits_top)
	{

		cScene::debugmap[abs(tile_x + i + ((-tile_y - heigth_tiles)*cScene::SCENE_WIDTH))] = 1;
		int tileID = map[abs(tile_x + i + ((-tile_y - heigth_tiles)*cScene::SCENE_WIDTH))];
		if (tileID != 0) {
			if (cScene::tiles[tileID - 1].isSolid()) {
				hits_top = true;
			}
		}

	/*	if ((y % cScene::TILE_SIZE) == 0)
		{

			int tileID = map[abs(tile_x + i + ((-tile_y - heigth_tiles)*cScene::SCENE_WIDTH))];
			if (tileID != 0) {
				if (cScene::tiles[tileID - 1].isSolid())
					in_air = false;
				hits_top = true;
			}
		}
		else
		{
			int tileID = map[abs(tile_x + i + ((-tile_y)*cScene::SCENE_WIDTH))];
			if (tileID != 0) {
				if (cScene::tiles[tileID - 1].isSolid())
				{
					y = (tile_y + heigth_tiles) * cScene::TILE_SIZE;
					hits_top = true;
				}
			}
		}*/
		//i++;
	//return true;
	//}
	//return hits_top;
//}

void cBicho::setObjectivePos(int x, int y) {
	obj_x = x;
	obj_y = y;
}

bool cBicho::hasHitBox() {
	return currentFrame.hasHitBox;
}
cRect  cBicho::getHitBox() {
	return currentFrame.getHitBox();
}

bool cBicho::inAir() {
	return in_air;
}
void cBicho::GetArea(cRect *rc)
{
	rc->left   = x;
	rc->right  = x+w;
	rc->bottom = y+h;
	rc->top    = y;
}
void cBicho::DrawRect(int tex_id,float xo,float yo,float xf,float yf)
{
	int screen_x,screen_y;
	screen_x = x + cScene::SCENE_Xo;
	screen_y = y + cScene::SCENE_Yo;


	glEnable(GL_TEXTURE_2D);
	//std::cout << "QUAD SIZE: " << std::endl;
	//std::cout << w << " " << h << std::endl;
	glBindTexture(GL_TEXTURE_2D,tex_id);
	glBegin(GL_QUADS);	
		glTexCoord2f(xo,yo);	glVertex2i(screen_x  ,screen_y);
		glTexCoord2f(xf,yo);	glVertex2i(screen_x+w,screen_y);
		glTexCoord2f(xf, yf);	glVertex2i(screen_x + w, screen_y + h);
		glTexCoord2f(xo, yf);	glVertex2i(screen_x, screen_y + h);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}


void cBicho::MoveLeft(int *map)
{
	int xaux;
	
	//Whats next tile?
	if( (x % cScene::TILE_SIZE) == 0)
	{
		xaux = x;
		x -= STEP_LENGTH;

		if(CollidesMapWall(map,false))
		{
			x = xaux;
			state = STATE_LOOKLEFT;
		}
	}
	//Advance, no problem
	else
	{
		x -= STEP_LENGTH;
		if(state != STATE_WALKLEFT)
		{
			state = STATE_WALKLEFT;
			seq = 0;
			delay = 0;
		}
	}
}
void cBicho::MoveRight(int *map)
{
	int xaux;

	//Whats next tile?
	if( (x % cScene::TILE_SIZE) == 0)
	{
		xaux = x;
		x += STEP_LENGTH;

		if(CollidesMapWall(map,true))
		{
			x = xaux;
			state = STATE_LOOKRIGHT;
		}
	}
	//Advance, no problem
	else
	{
		x += STEP_LENGTH;

		if(state != STATE_WALKRIGHT)
		{
			state = STATE_WALKRIGHT;
			seq = 0;
			delay = 0;
		}
	}
}
void cBicho::Stop()
{
	switch(state)
	{
		case STATE_WALKLEFT:	state = STATE_LOOKLEFT;		break;
		case STATE_WALKRIGHT:	state = STATE_LOOKRIGHT;	break;
		case STATE_DUCKLEFT:	state = STATE_LOOKLEFT;		break;
		case STATE_DUCKRIGHT:	state = STATE_LOOKRIGHT;	break;
	}
}
void cBicho::Jump(int *map)
{
	if (!in_water) {
		if (!jumping)
		{
			if (CollidesMapFloor(map))
			{
				in_air = true;
				jumping = true;
				jump_alfa = 0;
				jump_y = y;
			}

		}
	}
	else {
		//WATER LOGIC
		y += (STEP_LENGTH);
	}
}

void cBicho::Duck(int *map) {
	if (!inAir() && !in_water) {
		if (state == STATE_WALKLEFT || state == STATE_LOOKLEFT) {
			state = STATE_DUCKLEFT;
		}
		else if (state == STATE_WALKRIGHT || state == STATE_LOOKRIGHT) {
			state = STATE_DUCKRIGHT;
		}
	}
	else if (in_water) {
		y -= (STEP_LENGTH/2);
	}

}
void cBicho::Logic(int *map)
{
	float alfa;
	if(jumping)
	{
		
			jump_alfa += JUMP_STEP;

			if (jump_alfa == 180)
			{
				jumping = false;
				y = jump_y;
			}
			else
			{
				alfa = ((float)jump_alfa) * 0.017453f;
				y = jump_y + (int)(((float)JUMP_HEIGHT) * sin(alfa));

				if (jump_alfa > 90)
				{
					//Over floor?
					jumping = !CollidesMapFloor(map);
				}
			}
	}
	else
	{
		//Over floor?
		if (!CollidesMapFloor(map)) {
			if (!in_water) {
				y -= (2 * STEP_LENGTH);
			}
			else {
				y -= (STEP_LENGTH/2);
			}
		}
	}
	
}
void cBicho::NextFrame(int max)
{
	delay++;
	if(delay == FRAME_DELAY)
	{
		seq++;
		seq%=max;
		delay = 0;
		//std::cout << "SEQ " << seq << " " << currentAnimation->frames.size() << std::endl;
		currentFrame = currentAnimation->frames[seq];
		//std::cout << currentFrame.tile_px << std::endl;
	}
}
int cBicho::GetFrame()
{
	return seq;
}
int cBicho::GetState()
{
	return state;
}
void cBicho::SetState(int s)
{
	state = s;
}

void cBicho::Draw(int tex_id){

}