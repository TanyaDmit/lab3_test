#pragma once
#include <iostream>
#include<ctime>
#include <GL/freeglut.h>

class figure {
public:
	enum kind_of_figure_t { triangle, circle, line, point, square, star };
	
	virtual void figure_draw(void);
	virtual void figure_move(int x, int y);
	void activ_selected(bool);

protected:
	figure(void);
	int figure_color[3];
	int figure_color_select[3] = { 0,255,0 };
	bool figure_clarity = false;//видимость
	int RGB_max = 255;
	bool need_of_calculation = true;
	bool need_to_select = false;
	kind_of_figure_t kind_of_figure;//?
	virtual void coordinates_calculate(void);
	virtual void initialization_array(void);
};
