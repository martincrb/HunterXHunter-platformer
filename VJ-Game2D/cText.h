#pragma once
#include <string>
#include "Globals.h"
class cText
{
public:
	cText();
	~cText();
	void setText(std::string text);
	void Draw(int text_id);
	void setPosition(int x, int y);
private:

	int x;
	int y;
	std::string order;
	std::string text;
};

