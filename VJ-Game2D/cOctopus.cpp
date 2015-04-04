#include "cOctopus.h"
#include "cFireBall.h"
#include <cmath>


cOctopus::cOctopus()
{
	ball_y = std::vector<float>(BALLS);
	balls = std::vector<cFireBall*>(BALLS);
	for (int i = 0; i < balls.size(); ++i) {
		int dist = (i + 1) * 15;
		float angle = MIN_ANGLE + 4 * i;
		balls[i] = new cFireBall(dist, angle);
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

	int ball_x, ball_y;

	for (int i = 0; i < balls.size(); ++i) {
		float angle = balls[i]->angle;
		ball_x = cos(angle * PI / 180.0) * balls[i]->dist;
		ball_y = sin(angle * PI / 180.0) * balls[i]->dist;
		balls[i]->SetWidthHeight(16, 16);
		//balls[i]->SetPosition(octoposx-20, octoposy);
		balls[i]->SetPosition(x + 10 + ball_x, y + 30 + ball_y);

		angle += balls[i]->direc * STEP;
		if (angle > MAX_ANGLE) {
			angle = MAX_ANGLE - (angle - MAX_ANGLE);
			balls[i]->direc = -balls[i]->direc;
		}
		else if (angle < MIN_ANGLE) {
			angle = MIN_ANGLE - (MIN_ANGLE - angle);
			balls[i]->direc = -balls[i]->direc;
		}
		balls[i]->angle = angle;
	}
}
void cOctopus::Draw(cData* data) {
	int tex_id = data->GetID(IMG_OCTO);
	for (int i = 0; i < balls.size(); ++i) {
		balls[i]->Draw(data);
	}

	float xo, yo, xf, yf;
	xo = currentFrame.tile_px;	yo = currentFrame.tile_py + float(currentFrame.tile_heigth) / float(76);
	xf = xo + float(currentFrame.tile_width) / float(64);
	yf = yo - float(currentFrame.tile_heigth) / float(76);
	cBicho::SetWidthHeight(currentFrame.tile_width, currentFrame.tile_heigth);
	DrawRect(tex_id, xo, yo, xf, yf);

	
	
	
}