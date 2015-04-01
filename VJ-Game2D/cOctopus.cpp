#include "cOctopus.h"
#include "cFireBall.h"


cOctopus::cOctopus()
{
	ball_y = std::vector<float>(BALLS);
	balls = std::vector<cBicho*>(BALLS);
	for (int i = 0; i < balls.size(); ++i) {
		balls[i] = new cFireBall();
	}
	sinangle = 0;
	hurtDelay = 0;
	Animation idle;
	idle.addFrame(200, 0, 0, 76, 64, 64, 76, 0, 0);
	animations.push_back(idle);
	currentAnimation = &animations[0];
	currentFrame = currentAnimation->frames[0];
}


cOctopus::~cOctopus()
{
}

void cOctopus::Hurt() {
		
		if (hurtDelay == 0) {
			hurtDelay = 20;
			if (balls.size() == 0)
				alive = false;
			else {
				balls.pop_back();
				ball_y.pop_back();
			}
		}
}

bool cOctopus::Collides(cRect *rc) {
	for (int i = 0; i < balls.size(); ++i) {
		if (balls[i]->Collides(rc)) {
			return true;
			std::cout << "Collides with ball" << std::endl;
		}
	}
	if (cBicho::Collides(rc)) return true;;
	return false; 

}

void cOctopus::Logic() {
	if (hurtDelay > 0) {
		--hurtDelay;
	}
	sinangle += 0.06;
	if (sinangle >= 360) sinangle = 0;

	int octoposx, octoposy;
	GetPosition(&octoposx, &octoposy);
	int bally;
	for (int i = 0; i < balls.size(); ++i) {
		bally = 10 * sin((i + sinangle));
		balls[i]->SetWidthHeight(16, 16);
		//balls[i]->SetPosition(octoposx-20, octoposy);
		balls[i]->SetPosition(octoposx + 10 - (i + 1) * 16, octoposy + 30 + bally);
	}
}
void cOctopus::Draw(int tex_id) {

	for (int i = 0; i < balls.size(); ++i) {
		balls[i]->Draw(7);
	}

	float xo, yo, xf, yf;
	xo = currentFrame.tile_px;	yo = currentFrame.tile_py + float(currentFrame.tile_heigth) / float(76);
	xf = xo + float(currentFrame.tile_width) / float(64);
	yf = yo - float(currentFrame.tile_heigth) / float(76);
	cBicho::SetWidthHeight(currentFrame.tile_width, currentFrame.tile_heigth);
	DrawRect(tex_id, xo, yo, xf, yf);

	
	
	
}