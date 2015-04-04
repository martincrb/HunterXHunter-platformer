#include "cText.h"


cText::cText()
{
	 
	order = "ABCDEFGHIJKLMNOPQRSTUVWXYZ!:?0123456789 ";
}


cText::~cText()
{
}

void cText::setText(std::string t) {
	text = t;
}
void cText::Draw(int text_id) {
	const int x_pix[40] = { 5, 18, 31, 44, 57,
							70, 83, 96, 109, 120,
							133, 146, 159, 173, 186,
							199, 212, 225, 238, 251,
							264, 277, 290, 304, 317,
							330, 343, 352, 361, 374,
							387, 398, 411, 424, 437,
							449, 461, 473, 485, 0 };
	const int y_pix[40] = { 5, 5, 5, 5, 5,
							5, 5, 5, 5, 5,
							5, 5, 5, 5, 5,
							5, 5, 5, 5, 5,
							5, 5, 5, 5, 5,
							5, 5, 6, 5, 5,
							5, 5, 5, 5, 5,
							5, 5, 5, 5, 0 };
	const int w_pix[40] = { 8, 8, 8, 8, 8,
							8, 8, 8, 6, 8,
							8, 8, 9, 8, 8,
							8, 8, 8, 8, 8,
							8, 8, 9, 8, 8,
							8, 4, 4, 8, 8,
							6, 8, 8, 8, 7,
							7, 7, 7, 8, 0 };
	const int h_pix[40] = { 9, 9, 9, 9, 9,
							9, 9, 9, 9, 9,
							9, 9, 9, 9, 9,
							9, 10, 9, 9, 9,
							9, 9, 9, 9, 9,
							9, 9, 7, 9, 9,
							9, 9, 9, 9, 9,
							9, 9, 9, 9, 0 };
	for (int i = 0; i < text.size(); ++i) {

		int posx = x + i * 16;
		int ypos = y;
		float xo, xf, yo, yf;
		int id = 0;

		for (int j = 0; j < order.size(); ++j) {
			if (order[j] == text[i]){
				id = j;
			}
		}
		xo = float(x_pix[id]) / float(498);
		xf = xo + (float(w_pix[id]) / float(498));
		yo = float(y_pix[id]) / float(15) + (float(h_pix[id]) / float(15));
		yf = float(y_pix[id]) / float(15);

		glEnable(GL_TEXTURE_2D);
		//std::cout << "QUAD SIZE: " << std::endl;
		//std::cout << w << " " << h << std::endl;
		glBindTexture(GL_TEXTURE_2D, text_id);
		glBegin(GL_QUADS);
		glTexCoord2f(xo, yo);	glVertex2i(posx, y);
		glTexCoord2f(xf, yo);	glVertex2i(posx + w_pix[id]*2, y);
		glTexCoord2f(xf, yf);	glVertex2i(posx + w_pix[id]*2, y + h_pix[id]*2);
		glTexCoord2f(xo, yf);	glVertex2i(posx, y + h_pix[id]*2);
		glEnd();

		glDisable(GL_TEXTURE_2D);
	}
}
void cText::setPosition(int x, int y) {
	this->x = x;
	this->y = y;
}