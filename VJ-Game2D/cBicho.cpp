#include "cBicho.h"
#include "Globals.h"
#include "cScene.h"

cBicho::cBicho(void)
{
	seq=0;
	frameDelay = 8;
	delay=0;
	jumping = false;
	in_water = false;
}
cBicho::~cBicho(void){}

cBicho::cBicho(int posx,int posy,int width,int height)
{
	x = posx;
	y = posy;
	last_x = x;
	last_y = y;
	w = width;
	h = height;
	in_water = false;
}
void cBicho::SetPosition(int posx,int posy)
{
	x = posx;
	y = posy;
	last_x = x;
	last_y = y;
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
	last_x = x;
	last_y = y;
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

void cBicho::SetMap(int* map) {
	this->map = map;
}
bool cBicho::Collides(cRect *rc)
{
	//std::cout << "INSIDE COLLIDES" << std::endl;
	//std::cout << rc->left << " "   << rc->right << " " << rc->bottom << " " << rc->top << " " << std::endl;
	//std::cout << x        << " "   << x + w     << " " << y          << " " << (y + h) << " " << std::endl;
	if (x + w < rc->left) {
		//std::cout << " a is left of b" << std::endl;
		return false; // a is left of b
	}
	if (x > rc->right) {
		//std::cout << " a is right of b" << std::endl;
		return false; // a is right of b
	}
	if (y + h < rc->bottom){
		//std::cout << " a is above b" << std::endl;
		return false; // a is above b
	}
	if (y > rc->top) {
		//std::cout << "a is below b " << std::endl;
		return false; // a is below b
	}
	//std::cout << "yes" << std::endl;
	return true;
	
}
bool cBicho::inWater(cRect *rc) {
	return Collides(rc);
}
bool cBicho::CollidesMapWall(bool right) {
	return CollidesMapWall();
}
bool cBicho::CollidesMapWall()
{
	int tile_x1 = x / cScene::TILE_SIZE;
	int tile_x2 = (x + w) / cScene::TILE_SIZE;
	int tile_y = cScene::SCENE_HEIGHT - 1 - (y + h) / cScene::TILE_SIZE;
	int tile_ini = tile_y;
	int tile_fin = cScene::SCENE_HEIGHT - 1 - y / cScene::TILE_SIZE;
	for (int i = tile_ini; i <= tile_fin; i++) {
		//cScene::debugmap[tile_x1 + i * cScene::SCENE_WIDTH] = 1;
		int tileID = map[tile_x1 + i * cScene::SCENE_WIDTH];
		if (tileID != 0 && cScene::tiles[tileID - 1].isSolid())
			return true;

		//cScene::debugmap[tile_x2 + i * cScene::SCENE_WIDTH] = 1;
		tileID = map[tile_x2 + i * cScene::SCENE_WIDTH];
		if (tileID != 0 && cScene::tiles[tileID - 1].isSolid())
			//cScene::debugmap[tile_x2 + i * cScene::SCENE_WIDTH] = 1;
				return true;
			}
	return false;
}

int cBicho::HurtsDestructible(cRect hitBox) {

	return 0;
}

void cBicho::Hurt() {

}
bool cBicho::CollidesMapFloor()
{
	int tile_x = x / cScene::TILE_SIZE;
	int tile_y = cScene::SCENE_HEIGHT - 1 - y / cScene::TILE_SIZE;
	if (y % cScene::TILE_SIZE == 0) tile_y++;

	int tile_ini = tile_x;
	int tile_fin = (x + w) / cScene::TILE_SIZE;
	for (int i = tile_ini; i <= tile_fin; i++) {
		cScene::debugmap[i + tile_y * cScene::SCENE_WIDTH] = 1;
		int tileID = map[i + tile_y * cScene::SCENE_WIDTH];
		if (tileID != 0 && cScene::tiles[tileID - 1].isSolid()) {
			in_air = false;
			return true;
		}
	}
	return false;

}
int cBicho::CollidesItem(int *itemMap) {
	int tile_x = x / cScene::TILE_SIZE;
	int tile_y = cScene::SCENE_HEIGHT - 1 - y / cScene::TILE_SIZE;
	//if (y % cScene::TILE_SIZE == 0) tile_y++;

	int tile_ini = tile_x;
	int tile_fin = (x + w) / cScene::TILE_SIZE;
	for (int i = tile_ini; i <= tile_fin; i++) {
		//cScene::debugmap[i + tile_y * cScene::SCENE_WIDTH] = 1;
		int tileID = itemMap[i + tile_y * cScene::SCENE_WIDTH];
		int coverTileID = map[i + tile_y * cScene::SCENE_WIDTH];
		if (tileID != 0 && coverTileID == 0) {
			itemMap[i + tile_y * cScene::SCENE_WIDTH] = 0;
			return tileID;
			
		}
	}
	return -1;
}
bool cBicho::CollidesGhostTile(int *map)
{
	int tile_x = x / cScene::TILE_SIZE;
	int tile_y = cScene::SCENE_HEIGHT - 1 - y / cScene::TILE_SIZE;
	if (y % cScene::TILE_SIZE == 0) tile_y++;

	int tile_ini = tile_x;
	int tile_fin = (x + w) / cScene::TILE_SIZE;
	for (int i = tile_ini; i <= tile_fin; i++) {
		//cScene::debugmap[i + tile_y * cScene::SCENE_WIDTH] = 1;
		int tileID = map[i + tile_y * cScene::SCENE_WIDTH];
		if (tileID == 47) {
			return true;
		}
	}
	return false;
}


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
	rc->bottom = y;
	rc->top    = y+h;
}
void cBicho::DrawRect(int tex_id,float xo,float yo,float xf,float yf)
{
	int screen_x,screen_y;
	screen_x = x + cScene::SCENE_Xo;
	screen_y = y + cScene::SCENE_Yo;

	int dx = currentFrame.px_disp;
	int dy = currentFrame.py_disp;

	screen_x += dx;
	screen_y += dy;
	glEnable(GL_TEXTURE_2D);
	//std::cout << "QUAD SIZE: " << std::endl;
	//std::cout << w << " " << h << std::endl;
	glBindTexture(GL_TEXTURE_2D,tex_id);
	glBegin(GL_QUADS);	
		glTexCoord2f(xo,yo);	glVertex2i(screen_x ,screen_y);
		glTexCoord2f(xf,yo);	glVertex2i(screen_x + w,screen_y);
		glTexCoord2f(xf, yf);	glVertex2i(screen_x + w, screen_y + h);
		glTexCoord2f(xo, yf);	glVertex2i(screen_x, screen_y + h);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void cBicho::adjust() {
	int dif_x = x - last_x;
	int dif_y = y - last_y;
	int tile_x = x / cScene::TILE_SIZE;
	int tile_y = cScene::SCENE_HEIGHT - 1 - y / cScene::TILE_SIZE;

	if (dif_x < 0) { // moved left
		int tile_ini = cScene::SCENE_HEIGHT - 1 - (y + h) / cScene::TILE_SIZE;
		int tile_fin = tile_y;
		for (int i = tile_ini; i <= tile_fin; i++) {
			int tileID = map[tile_x + i * cScene::SCENE_WIDTH];
			if (tileID != 0 && cScene::tiles[tileID - 1].isSolid()) {
				x = (tile_x + 1) * cScene::TILE_SIZE;
				break;
			}
		}
	}
	else if (dif_x > 0) { // moved right
		tile_x = (x + w) / cScene::TILE_SIZE;
		int tile_ini = cScene::SCENE_HEIGHT - 1 - (y + h) / cScene::TILE_SIZE;
		int tile_fin = tile_y;
		for (int i = tile_ini; i <= tile_fin; i++) {
			int tileID = map[tile_x + i * cScene::SCENE_WIDTH];
			if (tileID != 0 && cScene::tiles[tileID - 1].isSolid()) {
				x = tile_x * cScene::TILE_SIZE - w;
				break;
			}
		}
	}
	if (dif_y < 0) { // moved down
		int tile_ini = tile_x;
		int tile_fin = (x + w) / cScene::TILE_SIZE;
		for (int i = tile_ini; i <= tile_fin; i++) {
			int tileID = map[i + tile_y * cScene::SCENE_WIDTH];
			if (tileID != 0 && cScene::tiles[tileID - 1].isSolid()) {
				y = (cScene::SCENE_HEIGHT - tile_y) * cScene::TILE_SIZE;
				break;
			}
		}
	}
	else if (dif_y > 0) { // moved up
		tile_y = cScene::SCENE_HEIGHT - 1 - (y + h) / cScene::TILE_SIZE;
		int tile_ini = tile_x;
		int tile_fin = (x + w) / cScene::TILE_SIZE;
		for (int i = tile_ini; i <= tile_fin; i++) {
			//cScene::debugmap[i + tile_y * cScene::SCENE_WIDTH] = 1;
			int tileID = map[i + tile_y * cScene::SCENE_WIDTH];
			if (tileID != 0 && cScene::tiles[tileID - 1].isSolid()) {
				y = (cScene::SCENE_HEIGHT - tile_y - 1) * cScene::TILE_SIZE - h;
				jumping = false;
				break;
			}
		}
	}
}


void cBicho::MoveLeft()
{
	last_x = x;
	last_y = y;
	
	x -= STEP_LENGTH;
	adjust();
	if (CollidesMapWall()) {
		state = STATE_LOOKLEFT;
	}
	else {
		if (state != STATE_WALKLEFT) {
			state = STATE_WALKLEFT;
			seq = 0;
			delay = 0;
		}
	}
}
		
void cBicho::MoveRight()
{
	last_x = x;
	last_y = y;

	x += STEP_LENGTH;
	adjust();
	if (CollidesMapWall()) {
		state = STATE_LOOKRIGHT;
	}
	else {
		if (state != STATE_WALKRIGHT) {
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
void cBicho::Jump()
{
	if (!in_water) {
		if (!jumping) {
			if (CollidesMapFloor())	{
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
	adjust();
}

void cBicho::Duck() {
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
		adjust();
	}

}
void cBicho::Logic()
{
	float alfa;
	last_x = x;
	last_y = y;
	if(jumping)	{
		jump_alfa += JUMP_STEP;
		
		if (jump_alfa == 180) {
			jumping = false;
			y = jump_y;
		}
		else {
			alfa = ((float)jump_alfa) * 0.017453f;
			y = jump_y + (int)(((float)JUMP_HEIGHT) * sin(alfa));
		
			if (jump_alfa > 90)	{
				//Over floor?
				//jumping = !CollidesMapFloor();
				jumping = false;
			}
		}
	}
	else {
		//Over floor?
		if (!CollidesMapFloor()) {
			if (!in_water) {
				y -= (2 * STEP_LENGTH);
			}
			else {
				y -= (STEP_LENGTH/2);
			}
		}
	}
	adjust();
}
void cBicho::NextFrame(int max)
{
	delay++;
	if(delay == frameDelay)
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