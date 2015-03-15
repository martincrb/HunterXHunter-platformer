#pragma once
#include <vector>
#include "AnimationFrame.h"

class Animation
{
public:
	Animation();
	~Animation();
	std::vector < AnimationFrame > frames;
};

