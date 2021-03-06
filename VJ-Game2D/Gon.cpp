#include "Gon.h"
#include "cScene.h"

Gon::Gon()
{
	cBicho::SetState(0);
	Animation idle;
	idle.addFrame(200, 2, 2, 44, 30, 256, 256, 0, -1);
	idle.addFrame(200, 34, 2, 45, 31, 256, 256, 0, -1);
	idle.addFrame(200, 2, 2, 44, 30, 256, 256, 0, -1);
	idle.addFrame(200, 67, 2, 43, 30, 256, 256, 0, -1);
	animations.push_back(idle);

	Animation walk;
	walk.addFrame(200, 99, 2, 40, 31, 256, 256, 0, 0);
	walk.addFrame(200, 132, 2, 41, 36, 256, 256, 0, 0);
	walk.addFrame(200,170, 2, 40, 23, 256, 256, 0, 0);
	walk.addFrame(200, 195, 2, 40, 31, 256, 256, 0, 0);
	walk.addFrame(200, 2, 49, 41, 36, 256, 256, 0, 0);
	walk.addFrame(200, 40, 49, 39, 23, 256, 256, 0, 0);
	animations.push_back(walk);

	Animation jump;
	jump.addFrame(200, 56, 92, 45, 38, 256, 256, 0, 0);
	animations.push_back(jump);

	Animation punch;
	cRect hitBox;
	hitBox.bottom = -10;
	hitBox.left = 50;
	hitBox.top = -20 - 15;
	hitBox.right = 50 + 30;
	punch.addFrame(200, 96, 92, 42, 52, 256, 256, -20, 0, hitBox);
	animations.push_back(punch);

	Animation swim;
	swim.addFrame(200, 102, 49, 34, 37, 256, 256, 0, 0);
	swim.addFrame(200, 141, 49, 28, 46, 256, 256, 0, 0);
	swim.addFrame(200, 189, 49, 34, 37, 256, 256, 0, 0);
	animations.push_back(swim);

	Animation swimPunch;
	hitBox.bottom = -10;
	hitBox.left = 50;
	hitBox.top = -40;
	hitBox.right = 50 + 30;
	swimPunch.addFrame(200, 2, 92, 34, 52,256,256,-17,0, hitBox);
	animations.push_back(swimPunch);

	Animation duck;
	duck.addFrame(200, 65, 49, 39, 35, 256, 256, 0, 0);
	animations.push_back(duck);
	currentAnimation = &animations[0];
	currentFrame = currentAnimation->frames[0];

	punchDelay = 0;
	cooldown = 0;
	hability = false;
}


Gon::~Gon()
{
}


int Gon::HurtsDestructible(cRect hitBox) {
	int tile_x, tile_y;
	int j;
	int width_tiles, height_tiles;


	//Compute WORLD position of hitbox
	int xb, yb, wb, hb;
	//Set tile from these coords

	tile_x = hitBox.left / cScene::TILE_SIZE;
	tile_y = cScene::SCENE_HEIGHT - (hitBox.top / cScene::TILE_SIZE);

	int tileID = map[tile_x + tile_y*cScene::SCENE_WIDTH];
	if (tileID != 0) {
		if (cScene::tiles[tileID - 1].isDestructable())	{
			std::cout << "DESTROY" << std::endl;
			map[tile_x + tile_y*cScene::SCENE_WIDTH] = 0;
			return tileID;
		}
	}
	return -1;

}

void Gon::DrawRect(int tex_id, float xo, float yo, float xf, float yf) {
	int screen_x, screen_y;
	screen_x = x + cScene::SCENE_Xo;
	screen_y = y + cScene::SCENE_Yo;

	int dx = currentFrame.px_disp;
	int dy = currentFrame.py_disp;

	if (state == STATE_LOOKLEFT || state == STATE_WALKLEFT) {
		screen_x += dx;
	}
	screen_y += dy;
	glEnable(GL_TEXTURE_2D);
	//std::cout << "QUAD SIZE: " << std::endl;
	//std::cout << w << " " << h << std::endl;
	glBindTexture(GL_TEXTURE_2D, tex_id);
	glBegin(GL_QUADS);
	glTexCoord2f(xo, yo);	glVertex2i(screen_x, screen_y);
	glTexCoord2f(xf, yo);	glVertex2i(screen_x + w, screen_y);
	glTexCoord2f(xf, yf);	glVertex2i(screen_x + w, screen_y + h);
	glTexCoord2f(xo, yf);	glVertex2i(screen_x, screen_y + h);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}
void Gon::Draw(cData* data){
	int tex_id = data->GetID(IMG_PLAYER);
	//Esto no deberia ir aqui, deberia ir en la logica del player (la hereda de cbicho?)
	if (hability) {
	hability = false;
	Stop();
}

	float xo, yo, xf, yf;
	switch (GetState())
	{
		//1
	case STATE_DUCKLEFT:

		if (!inAir() && !in_water) {
			currentAnimation = &animations[6];
			
			NextFrame(currentAnimation->frames.size());
		}
		xo = currentFrame.tile_px + float(currentFrame.tile_width) / float(256);	yo = currentFrame.tile_py + float(currentFrame.tile_heigth) / float(256);
		xf = currentFrame.tile_px;
		yf = yo - float(currentFrame.tile_heigth) / float(256);
		break;
	case STATE_DUCKRIGHT:
		if (!inAir() && !in_water) {
			currentAnimation = &animations[6];
			
			NextFrame(currentAnimation->frames.size());
		}
		xo = currentFrame.tile_px;	yo = currentFrame.tile_py + float(currentFrame.tile_heigth) / float(256);
		xf = currentFrame.tile_px + float(currentFrame.tile_width) / float(256);
		yf = yo - float(currentFrame.tile_heigth) / float(256);
		break;
	case STATE_LOOKLEFT:
		if (inAir()) {
			if (in_water) in_air = false;
			currentAnimation = &animations[2];
			currentFrame = currentAnimation->frames[0];
			if (punchDelay > 0) {
				currentAnimation = &animations[3];
				currentFrame = currentAnimation->frames[0];
			}
		}
		else if (in_water) {
			currentAnimation = &animations[4];
			if (punchDelay > 0) {
				currentAnimation = &animations[5];
				currentFrame = currentAnimation->frames[0];
			}
		}
		else if (punchDelay > 0) {
			currentAnimation = &animations[3];
			currentFrame = currentAnimation->frames[0];
		}
		else {
			currentAnimation = &animations[0];
		}
		xo = currentFrame.tile_px + float(currentFrame.tile_width) / float(256);	yo = currentFrame.tile_py + float(currentFrame.tile_heigth) / float(256);
		xf = currentFrame.tile_px;
		yf = yo - float(currentFrame.tile_heigth) / float(256);
		NextFrame(currentAnimation->frames.size());
		break;
		//4
	case STATE_LOOKRIGHT:
		if (inAir()) {
			if (in_water) in_air = false;
			currentAnimation = &animations[2];
			currentFrame = currentAnimation->frames[0];
			if (punchDelay > 0) {
				currentAnimation = &animations[3];
				currentFrame = currentAnimation->frames[0];
			}
		}
		else if (in_water) {
			currentAnimation = &animations[4];
			if (punchDelay > 0) {
				currentAnimation = &animations[5];
				currentFrame = currentAnimation->frames[0];
			}
		}
		else if (punchDelay > 0) {
			currentAnimation = &animations[3];
			currentFrame = currentAnimation->frames[0];
		}
		else {
			currentAnimation = &animations[0];
		}
		xo = currentFrame.tile_px;	yo = currentFrame.tile_py + float(currentFrame.tile_heigth) / float(256);
		xf = xo + float(currentFrame.tile_width) / float(256);
		yf = yo - float(currentFrame.tile_heigth) / float(256);
		//std::cout << currentAnimation->frames.size() << std::endl;
		NextFrame(currentAnimation->frames.size());
		break;
		//1..3
	case STATE_WALKLEFT:
		if (inAir()) {
			if (in_water) in_air = false;
			currentAnimation = &animations[2];
			currentFrame = currentAnimation->frames[0];
		}
		else if (in_water) {
			currentAnimation = &animations[4];
			if (punchDelay > 0) {
				currentAnimation = &animations[5];
				currentFrame = currentAnimation->frames[0];
			}
		}
		else if (punchDelay > 0) {
			currentAnimation = &animations[3];
			currentFrame = currentAnimation->frames[0];
			
		}
		else {
			currentAnimation = &animations[1];
		}
		xo = currentFrame.tile_px + float(currentFrame.tile_width) / float(256);	yo = currentFrame.tile_py + float(currentFrame.tile_heigth) / float(256);
		xf = currentFrame.tile_px;
		yf = yo - float(currentFrame.tile_heigth) / float(256);
		NextFrame(currentAnimation->frames.size());
		break;
		//4..6
	case STATE_WALKRIGHT:
		if (inAir()) {
			if (in_water) in_air = false;
			currentAnimation = &animations[2];
			currentFrame = currentAnimation->frames[0];
		}
		else if (in_water) {
			currentAnimation = &animations[4];
			if (punchDelay > 0) {
				currentAnimation = &animations[5];
				currentFrame = currentAnimation->frames[0];
			}
		}
		else if (punchDelay > 0) {
			currentAnimation = &animations[3];
			currentFrame = currentAnimation->frames[0];
		}
		else {
			currentAnimation = &animations[1];
		}
		xo = currentFrame.tile_px;	yo = currentFrame.tile_py + float(currentFrame.tile_heigth) / float(256);
		xf = xo + float(currentFrame.tile_width) / float(256);
		yf = yo - float(currentFrame.tile_heigth) / float(256);
		NextFrame(currentAnimation->frames.size());
		break;
	}

	if (punchDelay > 0)
		punchDelay--;
	if (cooldown > 0)
		cooldown--;
	//std::cout << "FRAME: " << std::endl;
	//std::cout << "Xo: " << xo << " Yo: " << yo << std::endl;
	//std::cout << "Xf: " << xf << " Yf: " << yf << std::endl;
	cBicho::SetWidthHeight(currentFrame.tile_width, currentFrame.tile_heigth);
	//int xd, yd = 0;
	//cBicho::GetPosition(&xd, &yd);
	//cBicho::SetPosition(xd+currentFrame.px_disp, yd-currentFrame.py_disp);
	DrawRect(tex_id, xo, yo, xf, yf);
	
}

void Gon::Hability(){
	if (cooldown == 0) {
		hability = true;
		punchDelay = PUNCH_DURATION;
		cooldown = PUNCH_COOLDOWN;
	}
}