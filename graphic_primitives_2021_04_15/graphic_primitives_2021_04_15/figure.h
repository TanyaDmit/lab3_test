#pragma once
#include <iostream>
#include <GL/freeglut.h>
#include "class_for_color.h"

class figure {
public:
	static const int general_quantity_of_figure = 10;
	enum kind_of_figure_t { triangle, circle, line, point, square, star, check_mark };
	kind_of_figure_t kind_of_figure;
	virtual void figure_draw(void);
	virtual void figure_move(int x, int y);
	void activ_selected(bool);
	virtual void figure_position(int&, int&);
	figure(void);
	virtual void active_figure_paint(int);
	virtual void active_figure_fill(int);
protected:
	
	bool figure_clarity;
	bool need_of_calculation;
	bool need_to_select;
	bool figure_fill;
	int figure_color[3];
	int figure_color_select[3] = { 0,0,0 };
	virtual void coordinates_calculate(void);
	virtual void initialization_array(void);
};
