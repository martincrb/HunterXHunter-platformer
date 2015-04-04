#include "Killua.h"


Killua::Killua()
{
	cBicho::SetState(0);
	Animation idle;
	idle.addFrame(200, 2, 2, 49, 20, 128, 256, 0, -1);
	idle.addFrame(200, 24, 2, 49, 20, 128, 256, 0, -1);
	idle.addFrame(200, 46, 2, 48, 20, 128, 256, 0, -1);
	idle.addFrame(200, 68, 2, 47, 20, 128, 156, 0, -2);
	animations.push_back(idle);

	Animation walk;
	//walk.addFrame(200, 2, 53, 48, 24, 128, 256, 0, 0);
	walk.addFrame(200, 28, 53, 46, 28, 128, 256, 0, 0);
	walk.addFrame(200, 58, 53, 46, 25, 128, 256, 0, 0);
	walk.addFrame(200, 85, 53, 46, 21, 128, 256, 0, 0);
	//walk.addFrame(200, 2, 103, 48, 23, 128, 256, 0, 0);
	walk.addFrame(200, 27, 103, 47, 30, 128, 256, 0, 0);
	walk.addFrame(200, 59, 103, 45, 27, 128, 256, 0, 0);
	walk.addFrame(200, 88, 103, 45, 22, 128, 256, 0, 0);
	animations.push_back(walk);

	Animation special;
	special.addFrame(200, 89, 190, 49, 33, 128, 256, 0, 0);
	animations.push_back(special);

	Animation jump;
	jump.addFrame(200, 90, 2, 40, 28, 128, 256, 0, 0);
	animations.push_back(jump);

	Animation swim;
	swim.addFrame(200, 39, 153, 35, 43, 128, 256, 0, 0);
	swim.addFrame(200, 2, 190, 28, 43, 128, 256, 0, 0);
	swim.addFrame(200, 47, 190, 35, 40, 128, 256, 0, 0);
	animations.push_back(swim);

	Animation duck;
	duck.addFrame(200, 2, 153, 34, 35, 128, 256, 0, 0);
	animations.push_back(duck);

	currentAnimation = &animations[0];
	currentFrame = currentAnimation->frames[0];

	hability = false;

}


Killua::~Killua()
{
}

void Killua::Draw(cData* data){
	int tex_id = data->GetID(IMG_PLAYER2);
	//Esto no deberia ir aqui, deberia ir en la logica del player (la hereda de cbicho?)
	if (in_water) in_air = false;
	float xo, yo, xf, yf;
	switch (GetState())	{
	case STATE_DUCKLEFT:
		if (!inAir() && !in_water) {
			currentAnimation = &animations[5];
			NextFrame(currentAnimation->frames.size());
		}
		xo = currentFrame.tile_px + float(currentFrame.tile_width) / float(128);	yo = currentFrame.tile_py + float(currentFrame.tile_heigth) / float(256);
		xf = currentFrame.tile_px;
		yf = yo - float(currentFrame.tile_heigth) / float(256);
		break;
	case STATE_DUCKRIGHT:
		if (!inAir() && !in_water) {
			currentAnimation = &animations[5];

			NextFrame(currentAnimation->frames.size());
		}
		xo = currentFrame.tile_px;	yo = currentFrame.tile_py + float(currentFrame.tile_heigth) / float(256);
		xf = currentFrame.tile_px + float(currentFrame.tile_width) / float(128);
		yf = yo - float(currentFrame.tile_heigth) / float(256);
		break;
	case STATE_LOOKLEFT:
		if (inAir()) {
			currentAnimation = &animations[3];
			currentFrame = currentAnimation->frames[0];
			if (isSuperJumping()) {
				currentAnimation = &animations[2];
				currentFrame = currentAnimation->frames[0];
			}
		}
		else if (in_water) {
			currentAnimation = &animations[4];
		}
		else {
			currentAnimation = &animations[0];
		}
		xo = currentFrame.tile_px + float(currentFrame.tile_width) / float(128);	yo = currentFrame.tile_py + float(currentFrame.tile_heigth) / float(256);
		xf = currentFrame.tile_px;
		yf = yo - float(currentFrame.tile_heigth) / float(256);
		NextFrame(currentAnimation->frames.size());
		break;
		//4
	case STATE_LOOKRIGHT:
		if (inAir()) {
			currentAnimation = &animations[3];
			currentFrame = currentAnimation->frames[0];
			if (isSuperJumping()) {
				currentAnimation = &animations[2];
				currentFrame = currentAnimation->frames[0];
				currentFrame.invertHitBoxX();
			}
			
		}
		else if (in_water) {
			currentAnimation = &animations[4];
		}
		else {
			currentAnimation = &animations[0];
		}
		xo = currentFrame.tile_px;	yo = currentFrame.tile_py + float(currentFrame.tile_heigth) / float(256);
		xf = xo + float(currentFrame.tile_width) / float(128);
		yf = yo - float(currentFrame.tile_heigth) / float(256);
		//std::cout << currentAnimation->frames.size() << std::endl;
		NextFrame(currentAnimation->frames.size());
		break;
		//1..3
	case STATE_WALKLEFT:
		if (inAir()) {
			currentAnimation = &animations[3];
			currentFrame = currentAnimation->frames[0];
			if (isSuperJumping()) {
				currentAnimation = &animations[2];
				currentFrame = currentAnimation->frames[0];
				currentFrame.invertHitBoxX();
			}
		}
		else if (in_water) {
			currentAnimation = &animations[4];
		}
		else {
			currentAnimation = &animations[1];
		}
		xo = currentFrame.tile_px + float(currentFrame.tile_width) / float(128);	yo = currentFrame.tile_py + float(currentFrame.tile_heigth) / float(256);
		xf = currentFrame.tile_px;
		yf = yo - float(currentFrame.tile_heigth) / float(256);
		NextFrame(currentAnimation->frames.size());
		break;
		//4..6
	case STATE_WALKRIGHT:
		if (inAir()) {
			currentAnimation = &animations[3];
			currentFrame = currentAnimation->frames[0];
			if (isSuperJumping()) {
				currentAnimation = &animations[2];
				currentFrame = currentAnimation->frames[0];
				currentFrame.invertHitBoxX();
			}
		}
		else if (in_water) {
			currentAnimation = &animations[4];
		}
		else {
			currentAnimation = &animations[1];
		}
		xo = currentFrame.tile_px;	yo = currentFrame.tile_py + float(currentFrame.tile_heigth) / float(256);
		xf = xo + float(currentFrame.tile_width) / float(128);
		yf = yo - float(currentFrame.tile_heigth) / float(256);
		NextFrame(currentAnimation->frames.size());
		break;
	}
	//std::cout << "FRAME: " << std::endl;
	//std::cout << "Xo: " << xo << " Yo: " << yo << std::endl;
	//std::cout << "Xf: " << xf << " Yf: " << yf << std::endl;
	cBicho::SetWidthHeight(currentFrame.tile_width, currentFrame.tile_heigth);
	//int xd, yd = 0;
	//cBicho::GetPosition(&xd, &yd);
	//cBicho::SetPosition(xd+currentFrame.px_disp, yd-currentFrame.py_disp);
	DrawRect(tex_id, xo, yo, xf, yf);
}
